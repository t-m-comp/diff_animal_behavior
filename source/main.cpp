/*
 * main.cpp
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */


#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <chrono>
#include <ratio>
#include <bitset>

#include "sax.h"
#include "spectral_clustering.h"
#include "k_means++.h"
#include "read_txt.h"
#include "struct.h"
#include "useful.h"
#include "sort.h"
#include "bat_den_progross.h"
#include "mem_usage.h"

#include <f2c.h>
extern"C"
{
#include <clapack.h>
}


using namespace std;
using namespace chrono;


int main()
{	//input data folder address 
	char filepath_gps[256] = "./bird_2019/motion/"; // movement
	char filepath_depth[256] = "./bird_2019/en/";//environment

	int matrix = 0;
	int ma_num = 0;

	int size_seg;
	int pre_num;
	double vm, rss;

	int size;
	vector<re_sy> re_symbol;
	vector<string> filelist_gps;
	vector<string> filelist_en;

	ListFiles(filepath_gps, filelist_gps);
	ListFiles(filepath_depth, filelist_en);

	vector<vector <double>> input_gps(filelist_gps.size());
	vector<vector <double>> input_en(filelist_en.size());
	vector<vector <double>> input(filelist_gps.size() + filelist_en.size());

	vector<double> bird_num;
	vector<double> bird_seg;

	Read_folder(filelist_gps, input_gps);
	Read_folder(filelist_en, input_en);

	for (unsigned int i = 0; i < input.size(); ++i)
	{
		if (i < filelist_en.size())
		{
			input[i].swap(input_en[i]);
		}
		else
		{
			input[i].swap(input_gps[i-filelist_en.size()]);
		}
	}

	vector<vector <double>>().swap(input_en);
	vector<vector <double>>().swap(input_gps);

	vector<vector <en_result>> en_re_seg(filelist_en.size());	//store result of environment
	vector<vector <result>> re_seg(filelist_gps.size());		//store result of trajectory features
	vector<int> output1;
	re_sy re_sy_temp;
	result re_temp;
	en_result en_re_temp;

	vector<double> data_median;
	vector<int> datagroup;
	vector<vector<double>> La_eigen;
	vector<vector <int>> data_seg_ele;
	vector<int> input_seg;

	int se_len;

	//time start
	chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

	//get modes from environment data
	for (unsigned int se_data = 0; se_data < filelist_en.size()-1; ++se_data) 
	{
		cout<<se_data<<endl;

		for (int size_seg = 20; size_seg >= 4; --size_seg)
		{

			int sax_j = 0;

			pre_num = find_pre(re_symbol, size_seg);
			re_sy_temp.mean.resize(size_seg);
			re_sy_temp.num.resize(size_seg);
			input_seg.resize(input[se_data].size());
			
			if(sax_j == 0)
			{
				Csax(input[se_data]);
				++sax_j;
			}

			if(pre_num == -1)
			{
				size = Sax_seg(input[se_data], output1, data_seg_ele, re_sy_temp, data_median, size_seg);
			}
			else
			{
				size = Sax_seg_adv(re_symbol[pre_num], data_seg_ele, data_median, re_sy_temp);
			}

			if(size_seg % 2 == 0)
			{
				re_sy_temp.sy_num = size_seg;
				re_symbol.push_back(re_sy_temp);
			}

			datagroup.resize(size, 0);
			La_eigen.resize(size);
			laplacian(data_seg_ele, data_median, La_eigen);

			for (unsigned num_cluster = 3; num_cluster <= 10 && num_cluster <= (unsigned int)size; ++num_cluster)
			{
				kmeans_pp(La_eigen, num_cluster, datagroup);
				en_re_data(datagroup, data_seg_ele, num_cluster, input_seg, en_re_temp);

				en_re_temp.para_sax = size_seg;
				en_re_temp.para_kmeans = num_cluster;

				unsigned int pan = 1;
				for (unsigned int ha = 0; ha < datagroup.size()-1; ++ha)
				{
					if (datagroup[ha] != datagroup[ha+1])
					{
						++pan;
					}
				}

				if( pan == num_cluster)
					en_re_seg[se_data].push_back(en_re_temp);
			}
			vector<int>().swap(output1);
			vector<double>().swap(re_sy_temp.mean);
			vector<int>().swap(re_sy_temp.num);
			vector<vector <int>>().swap(re_sy_temp.data_seg);
			vector<vector <int>>().swap(data_seg_ele);
			vector<double>().swap(data_median);
			vector<int>().swap(datagroup);
			vector<vector <double>>().swap(La_eigen);
			vector<int>().swap(input_seg);
			pre_num = -1;
		}
		vector<re_sy>().swap(re_symbol);
	}


	//get mode from GPS data
	for (unsigned int se_data = 0; se_data < filelist_gps.size(); ++se_data) 
	{
		cout<<se_data<<endl;
		int sax_j = 0;

		for (int size_seg = 20; size_seg >= 4; --size_seg)
		{
			pre_num = find_pre(re_symbol, size_seg);
			re_sy_temp.mean.resize(size_seg);
			re_sy_temp.num.resize(size_seg);
			input_seg.resize(input[se_data + filelist_en.size()].size());

			if(sax_j == 0)
			{
				Csax(input[se_data + filelist_en.size()]);
				++sax_j;
			}
			
			if(pre_num == -1)
			{
				size = Sax_seg(input[se_data + filelist_en.size()], output1, data_seg_ele, re_sy_temp, data_median, size_seg);
			}
			else
			{
				size = Sax_seg_adv(re_symbol[pre_num], data_seg_ele, data_median, re_sy_temp);
			}

			if(size_seg % 2 == 0)
			{
				re_sy_temp.sy_num = size_seg;
				re_symbol.push_back(re_sy_temp);
			}

			datagroup.resize(size, 0);
			La_eigen.resize(size);

			laplacian(data_seg_ele, data_median, La_eigen);

			for (unsigned num_cluster = 3; num_cluster <= 10 && num_cluster <= (unsigned int)size; ++num_cluster)
			{
				kmeans_pp(La_eigen, num_cluster, datagroup);
				re_data(datagroup, data_seg_ele, num_cluster, input_seg, re_temp);

				re_temp.para_sax = size_seg;
				re_temp.para_kmeans = num_cluster;

				unsigned int pan = 1;
				for (unsigned int ha = 0; ha < datagroup.size()-1; ++ha)
				{
					if (datagroup[ha] != datagroup[ha+1])
					{
						++pan;
					}
				}

				if( pan == num_cluster)
					re_seg[se_data].push_back(re_temp);
				}
			}
			//free memory
			vector<int>().swap(output1);
			vector<double>().swap(re_sy_temp.mean);
			vector<int>().swap(re_sy_temp.num);
			vector<vector <int>>().swap(re_sy_temp.data_seg);
			vector<vector <int>>().swap(data_seg_ele);
			vector<double>().swap(data_median);
			vector<int>().swap(datagroup);
			vector<vector <double>>().swap(La_eigen);
			vector<int>().swap(input_seg);
			pre_num = -1;
		}
		vector<re_sy>().swap(re_symbol);
	}

	vector<score> Score;
	score score;
	double score_temp, diff_temp, ratio_f, ratio_m;
	int eq;

	//time end
	chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();

	//calculate difference score 
	for (unsigned int en_no = 0; en_no < en_re_seg.size(); ++en_no)
	{
		cout<<en_no<<endl;
		for (unsigned  int tra_no = 0; tra_no < re_seg.size(); ++tra_no)
		{
			for (unsigned int i = 0; i < en_re_seg[en_no].size(); ++i)
				{
					for (unsigned  int j = 0; j < re_seg[tra_no].size(); ++j)
					{
						for (unsigned int m = 0; m < en_re_seg[en_no][i].data_seg.size() ; ++m)
						{
							for (unsigned int n = 0; n < re_seg[tra_no][j].data_seg.size() ; ++n)
							{
								//score_temp = useful(en_re_seg[en_no][i].data_seg[m], re_seg[tra_no][j].data_seg[n], bird_seg, bird_num);
								score_temp = useful_difference_fm(en_re_seg[en_no][i].data_seg[m], re_seg[tra_no][j].data_seg[n], diff_temp, ratio_f, ratio_m);

								if(score_temp > 0.0)
								{
									score.max_score = score_temp;
									score.clu_nu_0 = m;
									score.clu_nu_1 = n;
									score.para_sax_0 = en_re_seg[en_no][i].para_sax;
									score.para_kmeans_0 = en_re_seg[en_no][i].para_kmeans;
									score.para_sax_1 = re_seg[tra_no][j].para_sax;
									score.para_kmeans_1 = re_seg[tra_no][j].para_kmeans;
									score.tra_no_0 = en_no;
									score.tra_no_1 = tra_no;
									score.ratio_f = ratio_f;
									score.ratio_m = ratio_m;
									score.diff_score = diff_temp;
									Score.push_back(score);
								}
							}
						}
					}
				}
			}
	}

	fm_difference_sort(Score, re_seg);
	
	//time end
	chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

	chrono::duration<double, ratio<1,1>> duration_ms_2(t2-t1);
	cout<<"Sort time: "<<duration_ms_2.count()<<" seconds"<<endl;

	cout<<endl<<"fin"<<endl;

	return 0;
}

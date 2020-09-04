/*
 * sax.cpp
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */


#include <iostream>
#include <vector>
#include "sax.h"
#include "saxquantizer.hpp"
#include "struct.h"

using namespace std;

static SaxQuantizer::Sax sax(1, 1, 1);


int Csax(vector<double> &input_data)
{
	sax.train(input_data);

	return 0;
}

//segment data and calculate median
int Sax_seg(vector<double> &input_data, vector<int> &seg, vector<vector <int>> &data_seg_ele, re_sy &re_sym, vector<double> &data_mean, int symbol_len)
{
	vector<int> output_data;
	vector<int>::iterator it;
	int c = 0;

	sax.quantize(input_data, &output_data, symbol_len, false);

	for (int i = 0 ; i < symbol_len; ++i)
	{
		it = find(output_data.begin(), output_data.end(), i);
		if(it != output_data.end())
		{
			++c;
		}
	}
	
	data_seg_ele.resize(c);
	data_mean.resize(c);

	re_sym.data_seg.resize(re_sym.mean.size());

	for(unsigned int i = 0; i < output_data.size(); ++i)
	{
		re_sym.mean[output_data[i]] += input_data[i];
		re_sym.data_seg[output_data[i]].push_back(i);
	}

	for (unsigned int i = 0, j = 0; i < re_sym.data_seg.size(); ++i)
	{
		re_sym.num[i] = re_sym.data_seg[i].size();

		if (re_sym.data_seg[i].size() != 0)
		{
			data_seg_ele[j].insert(data_seg_ele[j].end(), re_sym.data_seg[i].begin(), re_sym.data_seg[i].end());
			++j;
		}
	}

	for (unsigned int i = 0; i< re_sym.mean.size(); ++i)
	{
		if (re_sym.num[i] != 0)
		{
			re_sym.mean[i] = re_sym.mean[i] / (double)re_sym.num[i];
		}
	}

	for (unsigned int i = 0, j = 0; i < re_sym.num.size(); ++i)
	{
		if(re_sym.num[i] != 0)
		{
			data_mean[j] = re_sym.mean[i];
			++j;
		}
	}

	return c;
}


int Sax_seg_0(vector<double> &input_data, vector<int> &seg, vector<vector <int>> &data_seg_ele, re_sy &re_sym, vector<double> &data_mean, int symbol_len)
{
	vector<int> output_data;
	vector<int>::iterator it;
	int c = 0;

	sax.quantize(input_data, &output_data, symbol_len, false);

	for (int i = 0 ; i < symbol_len; ++i)
	{
		it = find(output_data.begin(), output_data.end(), i);
		if(it != output_data.end())
		{
			++c;
		}
	}

	int num = 0;
	vector<int> data_ele_temp;
	double sum_temp = 0.0;

	data_ele_temp.push_back(0);
	++num;
	sum_temp += input_data[0];

	for (unsigned int i = 1; i < output_data.size(); ++i)
	{
		if(output_data[i] == output_data[i-1])
		{
			sum_temp += input_data[i];
			data_ele_temp.push_back(i);
			++num;
		}
		else
		{
			re_sym.data_seg.push_back(data_ele_temp);
			data_seg_ele.push_back(data_ele_temp);
			re_sym.mean.push_back(sum_temp / double(num));
			data_mean.push_back(sum_temp / double(num));
			vector<int>().swap(data_ele_temp);
			re_sym.num.push_back(num);
			data_ele_temp.push_back(i);
			num = 1;
			sum_temp = input_data[i];
		}
	}

	re_sym.data_seg.push_back(data_ele_temp);
	data_seg_ele.push_back(data_ele_temp);
	re_sym.mean.push_back(sum_temp / double(num));
	data_mean.push_back(sum_temp / double(num));
	re_sym.num.push_back(num);

	return data_seg_ele.size();
}


//calculate mean from past data
int Sax_seg_adv(re_sy &re_sym, vector<vector <int>> &data_seg_ele, vector<double> &data_mean, re_sy &re_sym_new)
{
	int size_0 = 0;
	for (unsigned int i = 0; i < re_sym.mean.size(); i += 2)
	{
		if (re_sym.num[i] + re_sym.num[i+1] != 0)
		{
			++size_0;
		}
	}
	data_seg_ele.resize(size_0);
	data_mean.resize(size_0);
	re_sym_new.data_seg.resize(re_sym_new.mean.size());

	for (unsigned int i = 0, j = 0; i < re_sym.mean.size(); i += 2)
	{
		if (re_sym.num[i] + re_sym.num[i+1] == 0)
		{
			re_sym_new.num[i/2] = 0;
			re_sym_new.mean[i/2] = 0;
		}
		else
		{
			re_sym_new.num[i/2] = re_sym.num[i] + re_sym.num[i+1];
			re_sym_new.mean[i/2] =  (re_sym.mean[i] * re_sym.num[i] + re_sym.mean[i+1] * re_sym.num[i+1]) / double(re_sym.num[i] + re_sym.num[i+1]);
			data_mean[j] = re_sym_new.mean[i/2];
			data_seg_ele[j].insert(data_seg_ele[j].end(), re_sym.data_seg[i].begin(), re_sym.data_seg[i].end());
			data_seg_ele[j].insert(data_seg_ele[j].end(), re_sym.data_seg[i+1].begin(), re_sym.data_seg[i+1].end());
			++j;
		}
		re_sym_new.data_seg[i/2].insert(re_sym_new.data_seg[i/2].end(), re_sym.data_seg[i].begin(), re_sym.data_seg[i].end());
		re_sym_new.data_seg[i/2].insert(re_sym_new.data_seg[i/2].end(), re_sym.data_seg[i+1].begin(), re_sym.data_seg[i+1].end());
	}
	
	return size_0;
}



int find_pre(vector<re_sy> re_symbol, int k)
{
	int k_num;

	for (unsigned int i = 0; i < re_symbol.size(); ++i)
	{
		if(re_symbol[i].sy_num== 2 * k)
		{
			k_num = i;
			return k_num;
		}
	}

	return -1;
}




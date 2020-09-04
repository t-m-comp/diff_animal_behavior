/*
 * sort.cpp
 *
 *  Created on: 2017年12月11日
 *      Author: Tian
 */

#include "sort.h"
#include "struct.h"
#include <float.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <typeinfo>

using namespace std;


bool comp(score &score_0, score &score_1)
{
	return score_0.max_score > score_1.max_score;
}


bool fm_comp(score &score_0, score &score_1)
{
	return score_0.diff_score > score_1.diff_score;
}

bool diff_comp(difference_fm &score_0, difference_fm &score_1)
{
	return score_0.score > score_1.score;
}

int score_sort(vector<score> &Score, vector<vector <result>> &re_seg)
{
	vector<vector <score>> Score_group;
	sort(Score.begin(),Score.end(),comp);

	for (vector<score>::iterator it = Score.begin(); it != Score.begin() + 200; ++it)
	{
		cout<<endl<<it->max_score<<" "<<it->tra_no_0<<" "<<it->tra_no_1<<" "<<it->para_sax_0<<" "<<it->para_sax_1<<" "<<it->para_kmeans_0<<" "<<it->para_kmeans_1<<" "<<it->clu_nu_0<<" "<<it->clu_nu_1;
	}

	return 0;
}


int fm_difference_sort(vector<score> &Score, vector<vector <result>> &re_seg)
{
	vector<vector <score>> Score_group;
	sort(Score.begin(),Score.end(), fm_comp);

	for (vector<score>::iterator it = Score.begin(); it != Score.begin() + 200; ++it)
	{
		cout<<endl<<it->diff_score<<" "<<it->ratio_f<<" "<<it->ratio_m<<" "<<it->max_score<<" "<<it->tra_no_0<<" "<<it->tra_no_1<<" "<<it->para_sax_0<<" "<<it->para_sax_1<<" "<<it->para_kmeans_0<<" "<<it->para_kmeans_1<<" "<<it->clu_nu_0<<" "<<it->clu_nu_1;
	}

	return 0;
}

//difference score sort
int difference_sort(vector<difference_fm> &Diff)
{
	vector<vector <difference_fm>> Score_group;
	sort(Diff.begin(), Diff.end(), diff_comp);

	for (vector<difference_fm>::iterator it = Diff.begin(); it != Diff.begin() + 100; ++it)
	{
		cout<<endl<<it->score<<" "<<it->en_no<<" "<<it->mo_no<<" "<<it->female_para_sax<<" "<<it->female_para_kmeans<<" "<<it->clu_no_female<<" "<<it->male_para_sax<<" "<<it->male_para_kmeans<<" "<<it->clu_no_male<<" "<<it->en_para_sax<<" "<<it->en_para_kmeans<<" "<<it->clu_no_en;
	}

	return 0;
}

int score_sort_group(vector<score> &Score, vector<vector <result>> &re_seg, vector<vector <double>> &input, int group_size)
{
	vector<vector <score>> Score_group(group_size);
	//sort
	sort(Score.begin(),Score.end(),comp);

	score_group(Score, Score_group); //put the same feature group into a group
	cout<<"size of group size is : "<<Score_group.size()<<endl;
	for (unsigned i = 0; i < Score_group.size(); ++i)
	{
		cout<<"The length of the group is : "<<Score_group[i].size()<<endl;
		if (Score_group[i].size() > 0)
			cout<<i<<" "<<Score_group[i].size()<<" "<<Score_group[i][0].tra_no_0<<" "<<Score_group[i][0].tra_no_1<<endl;
	}

	score_group_com(re_seg, Score_group);

	for (unsigned i = 0; i < Score_group.size(); ++i)
	{
		if (Score_group[i].size() > 0)
			cout<<i<<" "<<Score_group[i].size()<<" "<<Score_group[i][0].tra_no_0<<" "<<Score_group[i][0].tra_no_1<<endl;
	}

	return 0;
}

int score_group(vector<score> &Score, vector<vector<score>> &Score_group)
{
	int ju;

	for (unsigned int i = 0; i < Score.size(); ++i)
	{
		if (i == 0)
		{
			Score_group[0].push_back(Score[i]);
		}
		else
		{
			for (unsigned int j = 0; j < Score_group.size() && Score_group[j].size() > 0; ++j)
			{
				ju = score_com(Score_group[j][0], Score[i]);
				if (ju == 1) //	same feature
				{
					Score_group[j].push_back(Score[i]);
					break;
				}
			}
			if (ju == 0) //	different features
			{
				for (unsigned int j = 1; j < Score_group.size(); ++j)
				{
					if (Score_group[j].size() == 0)	//exist empty
					{
						//cout<<j<<" "<<Score[i].tra_no_0<<" "<<Score[i].tra_no_1<<endl;
						Score_group[j].push_back(Score[i]);
						break;
					}
				}
			}
		}
	}


	return 0;
}


int score_com(score &score_0, score &score_1)
{
	if (score_0.tra_no_0 == score_1.tra_no_0 && score_0.tra_no_1 == score_1.tra_no_1)
	{
		return 1;	//same feature
	}
	else
	{
		return 0;	//different feature
	}
}



int score_group_com(vector<vector <result>> &re_seg, vector<vector <score>> &Score_group)
{
	for (unsigned int i = 0; i < Score_group.size(); ++i)
	{
		cout<<i<<endl;
		if (Score_group[i].size() > 1)
		{
			for (vector<score>::iterator it = Score_group[i].begin() + 1; it != Score_group[i].end(); ++it)
			{
				//if( score_bit_com(Score_group[i][0].re_clu_0, it->re_clu_0) && score_bit_com(Score_group[i][0].re_clu_1, it->re_clu_1) )//	different cluster result
				//{
					//it = Score_group[i].erase(it);
				//}
			}
		}
	}

	return 0;
}


int score_bit_com(bitset<BITLEN> &seq1, bitset<BITLEN> &seq2)
{
	int seq_xor;
	bitset<BITLEN> bit_xor = seq1 ^ seq2;
	//bitset<BITLEN> bit_or = seq1 | seq2;

	seq_xor = bit_xor.count();

	if (seq_xor <= seq1.count() * 0.1)
	{
		return 0;	//nearly same
	}
	else
	{
		return 1;	//different clustering result
	}
}


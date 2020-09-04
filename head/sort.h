/*
 * sort.h
 *
 *  Created on: 2017年12月11日
 *      Author: april
 */

#ifndef SORT_H_
#define SORT_H_


#include "sort.h"
#include "struct.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

bool comp(score &score_0, score &score_1);
int score_sort(vector<score> &Score, vector<vector <result>> &re_seg);
int score_sort_group(vector<score> &Score, vector<vector <result>> &re_seg, vector<vector <double>> &input, int group_size);
int score_group(vector<score> &Score, vector<vector<score>> &Score_group);
int score_com(score &score_0, score &score_1);
int score_bit_com(bitset<BITLEN> &seq1, bitset<BITLEN> &seq2);
int score_group_com(vector<vector <result>> &re_seg, vector<vector <score>> &Score_group);
int difference_sort(vector<difference_fm> &Diff);
bool diff_comp(difference_fm &score_0, difference_fm &score_1);
bool fm_comp(score &score_0, score &score_1);
int fm_difference_sort(vector<score> &Score, vector<vector <result>> &re_seg);


#endif /* SORT_H_ */

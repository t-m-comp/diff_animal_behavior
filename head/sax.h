/*
 * sax.h
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */

#ifndef SAX_H_
#define SAX_H_

#include <vector>
#include "struct.h"


using namespace std;


int Csax(vector<double> &input_data);
int Sax_seg(vector<double> &input_data, vector<int> &seg, vector<vector <int>> &data_seg_ele, re_sy &re_sym, vector<double> &data_mean, int symbol_len);
int Sax_seg_adv(re_sy &re_sym, vector<vector <int>> &data_seg_ele, vector<double> &data_mean, re_sy &re_sym_new);
int find_pre(vector<re_sy> re_symbol, int k);
int Sax_seg_0(vector<double> &input_data, vector<int> &seg, vector<vector <int>> &data_seg_ele, re_sy &re_sym, vector<double> &data_mean, int symbol_len);

#endif /* SAX_H_ */

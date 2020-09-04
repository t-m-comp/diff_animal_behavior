/*
 * spectral_clustering.h
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */

#ifndef SPECTRAL_CLUSTERING_H_
#define SPECTRAL_CLUSTERING_H_

#include <vector>
#include "struct.h"

using namespace std;

int L_eigen(vector<vector <double>> &La);
int laplacian(vector<vector <int>> &data_seg, vector<double> &data_median, vector<vector <double>> &La);
int re_data(vector<int> &datagroup, vector<vector <int>> &data_seg, int k, vector<int> &input_seg, result &re_temp);
int en_re_data(vector<int> &datagroup, vector<vector <int>> &data_seg, int k, vector<int> &input_seg, en_result &re_temp);

#endif /* SPECTRAL_CLUSTERING_H_ */

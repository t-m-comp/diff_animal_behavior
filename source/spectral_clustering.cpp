/*
 * spectral_clustering.cpp
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "spectral_clustering.h"

extern"C"
{
#include <f2c.h>
#include <clapack.h>
}

using namespace std;


int laplacian(vector<vector <int>> &data_seg, vector<double> &data_median, vector<vector<double>> &La_eigen)
{
	double dis;
	vector<vector<double>> Si(data_seg.size()); //Similarity matrix
	vector<vector<double>> La(data_seg.size()); //Degree & Laplacian matrix

	for (unsigned int i = 0; i < Si.size(); ++i)
	{
		Si[i].resize(data_seg.size());
		La[i].resize(data_seg.size());
	}

	//similarity matrix
	for(unsigned int i = 0; i < data_seg.size(); ++i)
	{
		for(unsigned int j = 0; j < i; ++j)
		{
			if (i - j == 1)
			{
				dis = (data_seg[i].size() * data_seg[j].size()) / fabs(data_median[i] - data_median[j]);
				Si[i][j] = Si[j][i] = dis;
			}
			else
			{
				Si[i][j] = Si[j][i] = 0;
			}
		}
	}

	//degree matrix
	for (unsigned int i = 0; i < Si.size(); ++i)
	{
		double sum = 0;
		for (unsigned int j = 0; j < Si[i].size(); ++j)
		{
			sum += Si[i][j];
		}
		La[i][i] = sum;
	}

	//laplacian matrix
	for (unsigned int i = 0; i < Si.size(); ++i)
	{
		for (unsigned int j = 0; j < Si[i].size(); ++j)
		{
			La[i][j] -= Si[i][j];
		}
	}

	L_eigen(La);

	for (unsigned int i = 0; i < La.size(); ++i)
	{
		for (unsigned j = 1; j <= 2; ++j)
		{
			La_eigen[i].push_back(La[i][j]);
		}
	}

	return 0;
}

int L_eigen(vector<vector <double>> &La)
{
	int n = La.size();
	char jobz = 'V', uplo = 'U';
	integer N = n;
	integer LDA = n;
	float *eigenvalue;
	eigenvalue = new float[n];
	int worksize = n*n;
	float *work;
	work = new float[worksize];
	integer lwork = worksize;
	integer info;

	float *input_a;
	input_a = new float[n * n];

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			input_a[i*n + j] = La[i][j];
		}
	}

	//calculate eigenvalues and eigenvectors (small->large)
	ssyev_(&jobz, &uplo, &N, input_a, &LDA, eigenvalue, work, &lwork, &info);

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			La[i][j] = input_a[i + j*n];
		}
	}

	delete [] input_a;
	delete [] eigenvalue;
	delete [] work;
	return 0;
}

int re_data(vector<int> &datagroup, vector<vector <int>> &data_seg, int k, vector<int> &input_seg, result &re_temp)
{
	vector<vector <int>> k_data(k);
	vector<bitset<BITLEN> >().swap(re_temp.data_seg);
	re_temp.data_seg.resize(k);


	for (unsigned int i = 0; i < data_seg.size(); ++i)
	{
		for(unsigned int j = 0; j < data_seg[i].size(); ++j)
		{
			k_data[datagroup[i]].push_back(data_seg[i][j]);
			re_temp.data_seg[datagroup[i]].set(data_seg[i][j]);
		}
	}


	for (unsigned int i = 0; i < k_data.size(); ++i)
	{
		for (unsigned int m = 0; m < k_data[i].size(); ++m)
		{
			input_seg[k_data[i][m]] = i;
		}
	}
	
	return 0;
}

int en_re_data(vector<int> &datagroup, vector<vector <int>> &data_seg, int k, vector<int> &input_seg, en_result &re_temp)
{
	vector<vector <int>> k_data(k);
	vector<bitset<en_BITLEN> >().swap(re_temp.data_seg);
	re_temp.data_seg.resize(k);


	for (unsigned int i = 0; i < data_seg.size(); ++i)
	{
		for(unsigned int j = 0; j < data_seg[i].size(); ++j)
		{
			k_data[datagroup[i]].push_back(data_seg[i][j]);
			re_temp.data_seg[datagroup[i]].set(data_seg[i][j]);
		}
	}


	for (unsigned int i = 0; i < k_data.size(); ++i)
	{
		for (unsigned int m = 0; m < k_data[i].size(); ++m)
		{
			input_seg[k_data[i][m]] = i;
		}
	}
	
	return 0;
}


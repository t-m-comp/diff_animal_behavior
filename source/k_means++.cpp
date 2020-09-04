/*
 * k_means++.cpp
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <k_means++.h>
#include <random>

using namespace std;


// initial assment
template<typename T>
void KPP<T>::initClusterAssment()
{
	tNode node(-1, -1);
	for(int i = 0; i < num; ++i)
	{
		clusterAssment.push_back(node);
	}
}


template<typename T>
KPP<T>::KPP(int k)
{
	this->k = k;
}


//calculate the nearest distance between cluster point
template<typename T>
double KPP<T>::nearest(vector<T> &v1, int clu_num)
{
	T d1;
	int min_index;
	T min_dis = HUGE_VAL;
	int size = kpp_center.size();
	for(int i = 0; i < size; ++i)
	{
		d1 = distEclud(v1, kpp_center[i]);
		if (d1 < min_dis)
		{
			clusterAssment[clu_num].minIndex = i;
			clusterAssment[clu_num].minDist = d1;
			min_dis = d1;
			min_index = i;
		}
	}
	return min_index;
}



//calculate distance
template<typename T>
double KPP<T>::distEclud(vector<T> &v1 , vector<T> &v2)
{
	T sum = 0;
	//int size = v1.size();
	for(int i=0; i < dim; ++i)
	{
		sum += (v1[i] - v2[i])*(v1[i] - v2[i]);
	}
	return sum;
}

//load dataset
template<typename T>
int KPP<T>::loadData(vector<vector <T>> &input)
{
	//init dataSet
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		dataset.push_back(input[i]);
	}

	
	dim = dataset[0].size();
	num = dataset.size();
	
	return 0;
}

//update the center of cluster
template<typename T>
int KPP<T>::update_center()
{
	for(int i = 0; i < k; ++i)
	{
		vector<T> temp(dim, 0);
		int cnt = 0;
		for (int j = 0; j < num; ++j)
		{
			if (clusterAssment[j].minIndex == i)
			{
				++cnt;
				for (int m = 0; m < dim; ++m)
				{
					temp[m] += dataset[j][m];
				}
			}
		}

		for (int j = 0; j < dim; ++j)
		{
			if (cnt != 0)
				temp[j] /= (double)cnt;
			kpp_center[i][j] = temp[j];
		}
	}
	return 0;
}

//select the center of cluster
template<typename T>
int KPP<T>::kpp()
{
	T sum = 0;
	default_random_engine e;

	//set the first center
	kpp_center.push_back(dataset[e() % num]);

	for (int i = 1; i < k; ++i)
	{
		sum = 0;
		for (int j = 0; j < num; ++j)
		{
			nearest(dataset[j], j);
			sum += clusterAssment[j].minDist;
		}
		uniform_real_distribution<double> u(0, sum);
		sum = u(e);

		//find the next center
		for (int j = 0; j < num; ++j)
		{
			if ((sum -= clusterAssment[j].minDist) >0)
				continue;
			kpp_center.push_back(dataset[j]);
			break;
		}
	}


	for (int i = 0; i < num; ++i)
	{
		nearest(dataset[i], i);
	}

	return 0;
}

template<typename T>
int KPP<T>::kmeanspp()
{
	int min_index;
	int clusterchanged;
	int iteration = 1000;

	initClusterAssment();
	kpp();

	do{
		//calculate the center of each cluster
		update_center();

		clusterchanged = 0;

		for (int i = 0; i < num; ++i)
		{
			min_index = nearest(dataset[i], i);
			if (min_index != clusterAssment[i].minIndex)
			{
				++clusterchanged;
				clusterAssment[i].minIndex = min_index;
			}
		}
		--iteration;
	}while(clusterchanged != 0 && iteration >= 0);
	
	return 0;
}

template<typename T>
int KPP<T>::getgroup(vector<int> &datagroup)
{
	vector<int>::iterator it;
	int c = 0;
	for (unsigned int m = 0; m < clusterAssment.size(); ++m)
	{
		datagroup[m] = clusterAssment[m].minIndex;
	}
	for (int i = 0 ; i < k; ++i)
	{
		it = find(datagroup.begin(), datagroup.end(), i);
		if(it!=datagroup.end())
		{
			++c;
		}
	}
	return c;
}

int kmeans_pp(vector<vector <double>> &input, int k, vector<int> &datagroup)
{
	KPP<double> kmeanspp(k);
	kmeanspp.loadData(input);
	kmeanspp.kmeanspp();
	int c = kmeanspp.getgroup(datagroup);
	
	return c;
}




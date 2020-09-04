/*
 * k_means++.h
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */

#ifndef K_MEANS___H_
#define K_MEANS___H_

#include<iostream>
#include<vector>
#include<map>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<time.h>  //for srand
#include<limits.h> //for INT_MIN INT_MAX

using namespace std;

template<typename T>
class KPP
{
private:
	vector<vector <T>> dataset;
	vector<vector <T>> kpp_center;
	int dim; // dimension
	int num; // num of dataset
	int k; // the number cluster of k-means
	typedef struct Node
	{
		int minIndex; //the index of each node
		double minDist;
		Node(int idx,double dist):minIndex(idx),minDist(dist) {}
	}tNode;
	vector<tNode>  clusterAssment;
public:
	KPP(int k);
	int loadData(vector<vector <T>> &input);
	double distEclud(vector<T> &v1, vector<T> &v2);
	double nearest(vector<T> &v1, int clu_num);
	void initClusterAssment();
	int kpp();
	int kmeanspp();
	int update_center();
	int getgroup(vector<int> &datagroup);
};


int kmeans_pp(vector<vector <double>> &input, int k, vector<int> &datagroup);



#endif /* K_MEANS___H_ */

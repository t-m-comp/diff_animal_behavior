/*
 * struct.h
 *
 *  Created on: 2017年12月8日
 *      Author: april
 */

#ifndef STRUCT_H_
#define STRUCT_H_

#include <vector>
#include <bitset>
using namespace std;


#define BITLEN 		1124415	//1124415	22501//
#define en_BITLEN 	1124415	//1124415	22501//

#define male_BITLEN 	534975	//534975	10782//
#define male_en_BITLEN 	534975	//534975	10782//

#define female_BITLEN 		589440	//589440	11719//
#define female_en_BITLEN 	589440	//589440	11719//


struct re_sy
{
	vector<double> mean;
	vector<int> num;
	vector<vector <int>> data_seg;
	int sy_num;
};

struct result
{
	vector<bitset<BITLEN> > data_seg;
	int para_sax;
	int para_kmeans;
};

struct score
{
	double max_score;
	double diff_score;
	double ratio_f;
	double ratio_m;
	int para_sax_0;
	int para_kmeans_0;
	int para_sax_1;
	int para_kmeans_1;
	int clu_nu_0;
	int clu_nu_1;
	int tra_no_0;
	int tra_no_1;
};


#endif /* STRUCT_H_ */

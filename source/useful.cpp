/*
 * useful.cpp
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */


#include <bitset>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include "useful.h"


using namespace std;

//s
vector<int> bird_female_len = {0, 12104, 25822, 40157, 54674, 66509, 78233, 93269, 111499, 123183, 132612, 145294, 160458, 174331, 190534, 209642, 228194, 248942, 262101, 280142, 302506, 317914, 329736, 341708, 360986, 375809, 393659, 411625, 422254, 433444, 445220, 460647, 474041, 484330, 497396, 514733, 520701, 532932, 551676, 561503, 571105, 587104, 589440};
vector<int> bird_male_len = {0, 13408, 19672, 32686, 44023, 62128, 78727, 95604, 110179, 126832, 144423, 159001, 172881, 186833, 200379, 211808, 228243, 246465, 257284, 274824, 293543, 308956, 331014, 343069, 352661, 364540, 377840, 390827, 401258, 422553, 434491, 453679, 466770, 478502, 495629, 508111, 518151, 534975};

//H
//vector<int> bird_female_len = {0, 236, 501, 779, 1067, 1303, 1522, 1824, 2177, 2414, 2606, 2852, 3148, 3423, 3733, 4100, 4457, 4857, 5140, 5490, 5914, 6229, 6466, 6767, 7128, 7425, 7784, 8160, 8375, 8600, 8833, 9160, 9431, 9636, 9903, 10265, 10389, 10634, 10967, 11150, 11340, 11673, 11719};
//vector<int> bird_male_len = {0, 263, 386, 635, 874, 1221, 1530, 1875, 2151, 2458, 2794, 3075, 3341, 3615, 3883, 4120, 4463, 4850, 5108, 5448, 5852, 6158, 6586, 6836, 7039, 7274, 7550, 7819, 8059, 8491, 8749, 9144, 9437, 9662, 10011, 10242, 10454, 10782};



double useful(bitset<en_BITLEN> &seq1, bitset<BITLEN> &seq2, vector<double> &data_seg, vector<double> &data_num)
{
	double seq_and = 0;//, seq_or = 0, seq_mut = seq1.count() * seq2.count();
	double temp;// = seq1.count() > seq2.count()? seq1.count(): seq2.count();//x> 9? 100: 200;
	double score = 0;
	double corr = 0;
	double freq = 0;
	int data_seg_id = 0;
	en_result seq3;


	bitset<en_BITLEN> bit_and = seq1 & seq2;

	seq_and = bit_and.count();

	if (seq_and == 0)
	{
		return -100.0;
	}


	temp = seq1.count() > seq2.count()? seq1.count(): seq2.count();

	corr = double(seq_and) / double(seq1.count());

	freq = double(temp) / double(seq1.size());
	
	score = corr - (freq * 1 );


	if (corr > 0.70)//if (seq_and > (seq1.size() * 0.05) && corr > 0.5)  //seq1.count() < 85705 &&seq1.count() < seq1.size() * 0.7 &&
	{
		return score;
	}
	else
	{
		return -10000.0;
	}
}


//find out the difference between male seabird and female seabird
double difference_male_female(bitset<female_BITLEN> &female_en, bitset<female_BITLEN> &female_mo, bitset<male_BITLEN> &male_en, bitset<male_BITLEN> &male_mo)
{
	double seq_and_female = 0, seq_and_male = 0;//, seq_or = 0, seq_mut = seq1.count() * seq2.count();
	double temp_female, temp_male;// = seq1.count() > seq2.count()? seq1.count(): seq2.count();//x> 9? 100: 200;
	double score_female = 0, score_male = 0;
	double corr_female = 0, corr_male = 0;
	double freq_female = 0, freq_male = 0;
	double diff = 0.0;

	bitset<female_BITLEN> bit_and_female = female_en & female_mo;
	bitset<male_BITLEN> bit_and_male = male_en & male_mo;
	seq_and_female = bit_and_female.count();
	seq_and_male = bit_and_male.count();

	if (seq_and_female == 0)
	{
		return -100.0;
	}

	temp_female = female_en.count() > female_mo.count()? female_en.count(): female_mo.count();
	temp_male = male_en.count() > male_mo.count()? male_en.count(): male_mo.count();
	corr_female = double(seq_and_female) / double(female_en.count());
	corr_male = double(seq_and_male) / double(male_en.count());
	freq_female = double(temp_female) / double(female_en.size());
	freq_male = double(temp_male) / double(male_en.size());
	//bird
	score_female = corr_female - (freq_female * 1 );//double(seq2.size()) );
	score_male = corr_male - (freq_male * 1 );

	diff = fabs(corr_male - corr_female);

	return diff;
}

int find_maxscore()
{
	return 0;
}

double useful_difference_fm(bitset<en_BITLEN> &seq_en, bitset<BITLEN> &seq_mo, double &diff, double &ratio_f, double &ratio_m)
{
	double seq_and = 0;
	double temp;
	double score = 0;
	double corr = 0;
	double freq = 0;

	if (seq_en.count() < 2000)
	{
		return -100.0;
	}
	if (seq_mo.count() > 0.6*seq_mo.size())
	{
		return -100.0;
	}
	bitset<en_BITLEN> bit_and = seq_en & seq_mo;
	seq_and = bit_and.count();

	if (seq_and == 0)
	{
		return -200.0;
	}

	temp = seq_en.count() > seq_mo.count()? seq_en.count(): seq_mo.count();
	corr = double(seq_and) / double(seq_en.count());
	//cout<<corr<<endl;
	freq = double(temp) / double(seq_en.size());
	//bird
	score = corr - (freq * 1 );

	if (corr > 0.50 && score >= 0.1)
	{
		//calculate difference
		bitset<female_en_BITLEN> seq_female_en(0);
		bitset<female_BITLEN> seq_female_mo(0);
		bitset<male_en_BITLEN> seq_male_en(0);
		bitset<male_BITLEN> seq_male_mo(0);
		double seq_and_female = 0, seq_and_male = 0;//, seq_or = 0, seq_mut = seq1.count() * seq2.count();
		double corr_female = 0, corr_male = 0;
		double corr_female_avg = 0, corr_male_avg = 0;

		fm_transfer(seq_en, seq_mo, seq_female_en, seq_female_mo, seq_male_en, seq_male_mo);

		bitset<female_BITLEN> bit_and_female = seq_female_en & seq_female_mo;
		bitset<male_BITLEN> bit_and_male = seq_male_en & seq_male_mo;
		seq_and_female = bit_and_female.count();
		seq_and_male = bit_and_male.count();

		if (seq_and_female == 0)
		{
			//return -100.0;
		}

		corr_female = double(seq_and_female) / double(seq_female_en.count());
		corr_male = double(seq_and_male) / double(seq_male_en.count());

		corr_female_avg = corr_mean_female(seq_female_en, seq_female_mo);
		corr_male_avg = corr_mean_male(seq_male_en, seq_male_mo);

		diff = fabs(corr_male_avg - corr_female_avg);
		ratio_f = corr_female;
		ratio_m = corr_male;

		return score;
	}

	else
	{
		return -20000.0;
	}
}


int fm_transfer(bitset<en_BITLEN> &seq_en, bitset<BITLEN> &seq_mo, bitset<female_en_BITLEN> &fe_seq_en, bitset<female_BITLEN> &fe_seq_mo, bitset<male_en_BITLEN> &ma_seq_en, bitset<male_BITLEN> &ma_seq_mo)
{
	//female
	for (unsigned int i = 0; i < female_en_BITLEN; ++i)
	{
		if (seq_en[i] == 1)
		{
			fe_seq_en.set(i);
		}
		if (seq_mo[i] == 1)
		{
			fe_seq_mo.set(i);
		}
	}

	for (unsigned int i = 0; i < male_en_BITLEN; ++i)
	{
		if (seq_en[i + female_en_BITLEN] == 1)
		{
			ma_seq_en.set(i);
		}
		if (seq_mo[i + female_en_BITLEN] == 1)
		{
			ma_seq_mo.set(i);
		}
	}

	return 0;
}

//flag, 0: male, 1: female
double corr_mean_female(bitset<female_en_BITLEN> &fe_seq_en, bitset<female_BITLEN> &fe_seq_mo)
{
	vector<double> corr_temp;
	double corr_mean = 0.0;
	vector<int> bird_length;

	for (unsigned int i = 0; i < bird_female_len.size(); ++i)
	{
		bird_length.push_back(bird_female_len[i]);
	}

	for (unsigned int i = 0; i < bird_length.size()-1; ++i)
	{
		double corr = 0;

		int seq_and = 0;
		int seq_en_count = 0;

		for (int j = bird_length[i]; j< bird_length[i+1]; ++j)
		{
			if (fe_seq_en[j] == 1)
				{
					++seq_en_count;
					if (fe_seq_mo[j] == 1)
					{
						++seq_and;
					}
				}
		}
		if (seq_en_count == 0)
		{
			corr = 0.0;
		}
		else
		{
			corr = double(seq_and) / double(seq_en_count);
		}
		corr_temp.push_back(corr);
	}
	corr_mean = accumulate(corr_temp.begin(), corr_temp.end(), 0.0) / corr_temp.size();

	return corr_mean;
}


double corr_mean_male(bitset<male_en_BITLEN> &ma_seq_en, bitset<male_BITLEN> &ma_seq_mo)
{
	vector<double> corr_temp;
	double corr_mean = 0.0;
	vector<int> bird_length;

	for (unsigned int i = 0; i < bird_male_len.size(); ++i)
	{
		bird_length.push_back(bird_male_len[i]);
	}

	for (unsigned int i = 0; i < bird_length.size()-1; ++i)
	{
		double corr = 0;

		int seq_and = 0;
		int seq_en_count = 0;

		for (int j = bird_length[i]; j< bird_length[i+1]; ++j)
		{
			if (ma_seq_en[j] == 1)
				{
					++seq_en_count;
					if (ma_seq_mo[j] == 1)
					{
						++seq_and;
					}
				}
		}
		if (seq_en_count == 0)
		{
			corr = 0.0;
		}
		else
		{
			corr = double(seq_and) / double(seq_en_count);
		}
		corr_temp.push_back(corr);

	}
	corr_mean = accumulate(corr_temp.begin(), corr_temp.end(), 0.0) / corr_temp.size();
	return corr_mean;
}

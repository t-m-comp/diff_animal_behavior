/*
 * useful.h
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */

#ifndef USEFUL_H_
#define USEFUL_H_

#include <bitset>
#include <vector>
#include "struct.h"

using namespace std;


double useful(bitset<en_BITLEN> &seq1, bitset<BITLEN> &seq2, vector<double> &data_seg, vector<double> &data_num);
double difference_male_female(bitset<female_BITLEN> &female_en, bitset<female_BITLEN> &female_mo, bitset<male_BITLEN> &male_en, bitset<male_BITLEN> &male_mo);
double useful_difference_fm(bitset<en_BITLEN> &seq_en, bitset<BITLEN> &seq_mo, double &diff, double &ratio_f, double &ratio_m);
int fm_transfer(bitset<en_BITLEN> &seq_en, bitset<BITLEN> &seq_mo, bitset<female_en_BITLEN> &fe_seq_en, bitset<female_BITLEN> &fe_seq_mo, bitset<male_en_BITLEN> &ma_seq_en, bitset<male_BITLEN> &ma_seq_mo);
double corr_mean_female(bitset<female_en_BITLEN> &fe_seq_en, bitset<female_BITLEN> &fe_seq_mo);
double corr_mean_male(bitset<male_en_BITLEN> &ma_seq_en, bitset<male_BITLEN> &ma_seq_mo);


#endif /* USEFUL_H_ */

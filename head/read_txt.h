/*
 * read_txt.h
 *
 *  Created on: 2017年12月8日
 *      Author: Tian
 */

#ifndef READ_TXT_H_
#define READ_TXT_H_


#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int Read_folder(vector<string> &filelist, vector<vector <double>> &dataset);
int Read_txt(string filename, vector<double> &dataset);
int print(vector<int> &input_seg, string filename);
int ListFiles(char * filepath, vector<string> &filelist);


#endif /* READ_TXT_H_ */

/*
 * read_txt.cpp
 *
 *  Created on: 2017年12月8日
 *      Author: april
 */



#include "read_txt.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <io.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>


using namespace std;

#define MAX_PATH 1024

int Read_folder(vector<string> &filelist, vector<vector <double>> &dataset)
{
	for (unsigned int i = 0; i < filelist.size(); ++i)
	{
		cout<<i<<"  "<<filelist[i]<<endl;
		Read_txt(filelist[i], dataset[i]);
	}

	return 0;
}

int Read_txt(string filename, vector<double> &dataset)
{
    ifstream infile;
    infile.open(filename);
    if(!infile) cout<<"error"<<endl;

    string str;
    double t1;

    while(infile>>t1)             //按空格读取，遇到空白符结束
    {
    	dataset.push_back(t1);
    }
    return 0;
}

int ListFiles(char * filepath, vector<string> &filelist)
{
	char szFind[MAX_PATH];

	strcpy(szFind, filepath);
	string filep = szFind;

	if( NULL == filepath )
	    {
	        cout<<" dir_name is null ! "<<endl;
	        return -1;
	    }

	    // check if dir_name is a valid dir
	    struct stat s;
	    lstat( filepath , &s );
	    if( ! S_ISDIR( s.st_mode ) )
	    {
	        cout<<"dir_name is not a valid directory !"<<endl;
	        return -1;
	    }

	    struct dirent * filename;    // return value for readdir()
	    DIR * dir;                   // return value for opendir()
	    dir = opendir( filepath );
	    if( NULL == dir )
	    {
	        cout<<"Can not open dir "<<filepath<<endl;
	        return -1;
	    }
	    cout<<"Successfully opened the dir !"<<endl;

	    /* read all the files in the dir ~ */
	    while( ( filename = readdir(dir) ) != NULL )
	    {
	        // get rid of "." and ".."
	        if( strcmp( filename->d_name , "." ) == 0 ||
	            strcmp( filename->d_name , "..") == 0    )
	            continue;
	        //cout<<filename ->d_name <<endl;
	        string filen = filename ->d_name;
	        filelist.push_back(filep + filename ->d_name);

	    }
	    sort(filelist.begin(), filelist.end());

	return 0;
}

int print(vector<int> &input_seg, string filename)
{
	ofstream fout;
	fout.open(filename);
	if(!fout)
	{
		cout<<"file res.txt open failed"<<endl;
		exit(0);
	}

	//typename vector< vector<T> > :: iterator it = dataSet.begin();
	vector< int > :: iterator itt = input_seg.begin();
	for(unsigned int i = 0 ; i < input_seg.size(); ++i)
	{
		fout<<(*itt)<<endl;
		++itt;
	}
	return 0;
}

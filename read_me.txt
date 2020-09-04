1. Movement fearures (obtained from GPS data) and environment features should be put into /bird_2019/motion/" and "./bird_2019/en/".

2. The BITLEN and en_BITLEN in "struct.h" are the length of each time-sereis data. 
male_BITLEN and male_en_BITLEN in "struct.h" are the length of male data in each time-sereis data. 
female_BITLEN and female_en_BITLEN in "struct.h" are the length of female data in each time-sereis data. 

3. bird_female_len and bird_male_len in "useful.cpp" are the list of split point of male and female data. The difference between adjacent split points is the length of an individual's data.


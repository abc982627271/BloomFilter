#include <iostream>
#include <sstream>
#include <unistd.h>
#include "BloomFilter.h"
#include "MurmurHash3.h"

void test_bloom_filter(){
    std::string str = "Easy test";
    BloomFilter bf;
    std::cout << bf.Check(str) << std::endl;
    bf.Add(str);
    std::cout << bf.Check(str) << std::endl;
}

void test_mmh3()
{
	std::string str = "xxxaabb";
	uint32_t out;
	MurmurHash3_x86_32(str.c_str(),str.length(),0,&out);
	std::cout << out << std::endl;
}

void test_bloom_filter_dump_read(){
    for(int i=0;i<5;i++){
        std::ostringstream oss;
        BloomFilter* pbf = new BloomFilter();
        for(size_t i=0;i<100000;i++){
            oss.str("");
            oss << i;
            pbf->Add(oss.str());
        }
        pbf->DumpToFile("out.txt");
        delete pbf;
        pbf = nullptr;
        std::cout << "saved" << std::endl;
        sleep(5);

        //test false negative
        pbf = new BloomFilter("out.txt");
        size_t cnt = 0;
        for(size_t i=0; i<100000; i++){
            oss.str("");
            oss << i;
            if(!pbf->Check(oss.str())){
                cnt++;
            }
        }
        std::cout << "False Negitive " << cnt << std::endl;
        
        //test false positive
        cnt = 0;
        for(size_t i=100000; i<200000; i++){
            oss.str("");
            oss << i;
            if(pbf->Check(oss.str())){
                cnt++;
            }
        }
        std::cout << "False Positive " << cnt << std::endl;
        delete pbf;
        pbf = nullptr;
        std::cout << "Tested" << std::endl;
    }
    sleep(20);
}

int main(){
    // test_bloom_filter();
    // test_mmh3();
    test_bloom_filter_dump_read();
    return 0;
}
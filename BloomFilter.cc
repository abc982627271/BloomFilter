#include <fstream>
#include "BloomFilter.h"
#include "MurmurHash3.h"

BloomFilter::BloomFilter(): pbv(nullptr) {
    this->pbv = new BV();
    this->pbv->reset();
}

BloomFilter::BloomFilter(const char* in_path): pbv(nullptr) {
    std::ifstream in(in_path);
    std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

BloomFilter::~BloomFilter(){
    if(this->pbv){
        delete pbv;
        pbv = nullptr;
    }
}

void BloomFilter::DumpToFile(const char* out_path){
    std::ofstream out(out_path);
    out << this->pbv->to_string();
    out.close();
}

void BloomFilter::Add(const std::string& key) {
    uint32_t seed = 0;
    for(size_t i = 0; i < M; i++){
        uint32_t pos = 0;
        MurmurHash3_x86_32(key.c_str(), key.size(), seed, &pos);
        seed = pos;
        pos %= LEN;
        this->pbv->set(pos);
    }
}

bool BloomFilter::Check(const std::string& key) {
    uint32_t seed = 0;
    for(size_t i = 0; i < M; i++){
        uint32_t pos = 0;
        MurmurHash3_x86_32(key.c_str(), key.size(), seed, &pos);
        seed = pos;
        pos %= LEN;
        if(!this->pbv->test(pos))
            return false;
    }
    return true;
}

bool BloomFilter::CheckAndAdd(const std::string& key) {
    if(this->Check(key)){
        return true;
    }
    else {
        this->Add(key);
        return false;
    }
}
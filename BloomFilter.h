#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <bitset>
#include <string>

// BitVector and M
#define LEN 1<<26
#define M 5
typedef ::std::bitset<LEN> BV;

class BloomFilter {
public:
    BloomFilter();
    BloomFilter(const char* in_path);
    ~BloomFilter();

    //Serialize bitset to file
    void DumpToFile(const char* out_path);

    //Add to Bloom Filter and set M bits to be True
    void Add(const std::string& key);

    //Check if this key exists in The Bloom Filter; 
    //if all of the M bits was True -> return True;
    //if any of the M bits was False -> return False;
    bool Check(const std::string& key);

    //Check first, if not exist, add it
    bool CheckAndAdd(const std::string& key);

private:
    BV* pbv;
};

#endif

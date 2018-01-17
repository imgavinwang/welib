#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <sys/time.h>
#include <trie.h>
 
int main(int argc, char* argv[])
{
    std::set<std::string> rbtree_dict;
    std::unordered_map<std::string, std::string> hash_map_dict;
 
    trie t;
    long time_sp = 0, time_sp_rbtree = 0, time_sp_hash_map = 0;
    std::ifstream stream_in("./dict.txt", std::ios::in);
    if (stream_in.is_open())
    {
        int count = 0;
        int lineLength = 1024;
        char* buffer = new char[lineLength];
        while(stream_in.getline(buffer, lineLength))
        {
            count++;
            timeval trie_tv_start, trie_tv_end, rbtree_tv_start, rbtree_tv_end, hashmap_tv_start, hashmap_tv_end;
 
            gettimeofday(&trie_tv_start, NULL);
            long trie_start = ((long)trie_tv_start.tv_sec) * 1000 + (long)trie_tv_start.tv_usec / 1000;
            t.insert(buffer);
            gettimeofday(&trie_tv_end, NULL);
            time_sp += (((long)trie_tv_end.tv_sec) * 1000 + (long)trie_tv_end.tv_usec / 1000) - trie_start;
 
            gettimeofday(&rbtree_tv_start, NULL);
            long rbtree_start = ((long)rbtree_tv_start.tv_sec) * 1000 + (long)rbtree_tv_start.tv_usec / 1000;
            rbtree_dict.insert(buffer);
            gettimeofday(&rbtree_tv_end, NULL);
            time_sp_rbtree += (((long)rbtree_tv_end.tv_sec) * 1000 + (long)rbtree_tv_end.tv_usec / 1000) - rbtree_start;
 
            gettimeofday(&hashmap_tv_start, NULL);
            long hashmap_start = ((long)hashmap_tv_start.tv_sec) * 1000 + (long)hashmap_tv_start.tv_usec / 1000;
            hash_map_dict.insert(std::make_pair(buffer, buffer));
            gettimeofday(&hashmap_tv_end, NULL);
            time_sp_hash_map += (((long)hashmap_tv_end.tv_sec) * 1000 + (long)hashmap_tv_end.tv_usec / 1000) - hashmap_start;
        }
    }
 
    std::cout << "Build dictionary : \n"
        "   Trie      : " << time_sp << " ms.\n" <<
        "   Rbtree    : " << time_sp_rbtree << " ms.\n" <<
        "   HashTable : " << time_sp_hash_map << " ms." << std::endl;
 
    const char* keyword = "zygomaticoauricularis";
 
    timeval trie_find_tv_start, trie_find_tv_end, rbtree_find_tv_start, rbtree_find_tv_end, hashmap_find_tv_start, hashmap_find_tv_end;
 
    gettimeofday(&trie_find_tv_start, NULL);
    std::string status;
    long trie_start = ((long)trie_find_tv_start.tv_sec) * 1000 + (long)trie_find_tv_start.tv_usec / 1000;
    for (int i = 0; i < 10000; i++)
    {
        status = t.find_word_exists(keyword) == true ? "true" : "false";
    }
    gettimeofday(&trie_find_tv_end, NULL);
    long trie_end_time = (((long)trie_find_tv_end.tv_sec) * 1000 + (long)trie_find_tv_end.tv_usec / 1000) - trie_start;
 
    gettimeofday(&rbtree_find_tv_start, NULL);
    long rbtree_start = ((long)rbtree_find_tv_start.tv_sec) * 1000 + (long)rbtree_find_tv_start.tv_usec / 1000;
    for (int i = 0; i < 10000; i++)
    {
        rbtree_dict.find(keyword);
    }
    gettimeofday(&rbtree_find_tv_end, NULL);
    long rbtree_end_time = (((long)rbtree_find_tv_end.tv_sec) * 1000 + (long)rbtree_find_tv_end.tv_usec / 1000) - rbtree_start;
 
    gettimeofday(&hashmap_find_tv_start, NULL);
    long hashtable_start = ((long)hashmap_find_tv_start.tv_sec) * 1000 + (long)hashmap_find_tv_start.tv_usec / 1000;
    for (int i = 0; i < 10000; i++)
    {
        hash_map_dict.find(keyword);
    }
    gettimeofday(&hashmap_find_tv_end, NULL);
    long hashtable_end_time = (((long)hashmap_find_tv_end.tv_sec) * 1000 + (long)hashmap_find_tv_end.tv_usec / 1000) - hashtable_start;
 
    std::cout << "Word <'" << keyword << "'> search result : " << status << ", elapsed time : \n"
        "   Trie : " << trie_end_time << " ms.\n" <<
        "   Rbtree : " << rbtree_end_time << " ms.\n" <<
        "   HashTable : " << hashtable_end_time << " ms." << std::endl;
 
    return 0;
}
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;
 
int compare_string(const void *a,const void *b)
{
    return *((char*)(a)) - *((char*)(b));
}
void FindAnagram(char *file_name)
{
    ifstream in_file(file_name);
    string word_sort;
    string word;
    multimap<string,string> word_map;
    while(in_file>>word)
    {
        word_sort = word;
        qsort(word_sort.begin(),word_sort.length(),sizeof(char),compare_string);
        word_map.insert(make_pair(word_sort,word));
    }
    multimap<string,string>::const_iterator iter = word_map.begin();
    multimap<string,string>::const_iterator iter_end = word_map.end();
    while(iter_end != iter)
    {
        cout<<iter->first<<":"<<iter->second<<endl;
        ++iter;
    }
}
 
int main()
{
    FindAnagram("./data.txt");
    return 0;
}
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<windows.h>
#include <stdio.h> 
#include <stdlib.h> 
using namespace std;
int main(int argc, char* argv[])
{
    
    DWORD start_time = GetTickCount();
    ifstream file;
    file.open(argv[1], ios::in);
    if (!file.is_open())
    {
        cout << "读取文件失败" << endl;
        return 0;
    }
    string buf;
    vector<string> words;
    unordered_map<int, int> length_record;
    unordered_map<string, vector<string>> map;
    while (getline(file, buf)) {
        words.push_back(buf);
    }
    DWORD start_classify_time = GetTickCount();
    long i;

    for (i = 0; i < words.size(); ++i) {
        auto s = words[i];
        sort(s.begin(), s.end());

        map[s].push_back(words[i]);
    }
    DWORD end_classify_time = GetTickCount();
    cout << "分组的运行时间为" << end_classify_time - start_classify_time << "ms" << endl;;

    ofstream ofs;
    string out_file = "out" + string(argv[1]);
    ofs.open(out_file, ios::out);
    DWORD start_tongji_time = GetTickCount();
    for (unordered_map<string, vector<string>>::iterator it = map.begin(); it != map.end(); it++) {
        length_record[it->second.size()]++;

        for (int i = 0; i < (it->second).size(); i++) {
            ofs << it->second[i] << " ";
        }
        ofs << endl;
    }
    DWORD end_tongji_time = GetTickCount();
    cout << "统计长度并写入文件的运行时间为" << end_tongji_time - start_tongji_time << "ms" << endl;
    for (unordered_map<int, int>::iterator it = length_record.begin(); it != length_record.end(); it++) {
        cout << it->first << ":" << it->second << "  ";
    }
    cout << endl;

    DWORD end_time = GetTickCount();
    cout << "总运行时间为" << end_time - start_time << "ms" << endl;
    return 0;
}

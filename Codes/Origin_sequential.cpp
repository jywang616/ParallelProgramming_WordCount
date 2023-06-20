#include <iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

bool compare_same(string s, string t) {
    int record[26] = { 0 };
    for (int i = 0; i < s.size(); i++) {
        record[s[i] - 'a']++;
    }
    for (int i = 0; i < t.size(); i++) {
        record[t[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (record[i] != 0) {
            return false;
        }
    }
    return true;
}


//int main(int argc,char* argv[])
int main()
{
    ifstream file;
    
    file.open("15611.txt", ios::in);
    //file.open(argv[1],ios::in);
    if (!file.is_open())
    {
        cout << "读取文件失败" << endl;
        return 0; 
    }
    string buf;
    vector<vector<string>> result;
    int nums[6] = { 0 };
    while (getline(file, buf)) {
        int flag = 0;
        for (int i = 0; i < result.size(); i++) {
            if (compare_same(buf, result[i][0])) {
                result[i].push_back(buf);
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            vector<string>tmp;
            tmp.push_back(buf);
            result.push_back(tmp);
        }
    }
    for (vector<vector<string>> ::iterator it = result.begin(); it != result.end(); it++) {
        for (vector<string>::iterator vit = (*it).begin(); vit != (*it).end(); vit++) {
            cout << *vit << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < result.size(); i++) {
        nums[result[i].size()-1]++;
    }
    for (int i = 0; i < 6; i++) {
        cout << "长度为" << i+ 1 << "的数组有" << nums[i] << "个" << endl;
    }
        return 0;
}

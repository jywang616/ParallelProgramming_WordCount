#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<windows.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

#define NUMBER_OF_THREAD 5

vector<string> words;
unordered_map<string, vector<string>> map;
unordered_map<int, int> length_record;
int thread_count = NUMBER_OF_THREAD;
sem_t sem;
void* deal_records(void* rank) {
    long long n = words.size();
    long my_rank = *(long*)rank;
    long long my_n = n / thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    for (long long i = my_first_i; i < my_last_i; i++) {
        string s = words[i];
        sort(s.begin(), s.end());
        sem_wait(&sem);
        map[s].push_back(words[i]);
        sem_post(&sem);
    }
    return NULL;
}
int main()
{
    DWORD start_time = GetTickCount();
    ifstream file;
    file.open("15611.txt", ios::in);
    if (!file.is_open())
    {
        cout << "读取文件失败" << endl;
        return 0;
    }
    string buf;
    while (getline(file, buf)) {
        words.push_back(buf);
        //cout << buf << " ";
    }
    pthread_t thread_handles[NUMBER_OF_THREAD];
    
    int x[NUMBER_OF_THREAD];
    sem_init(&sem, 0, 1);
    for (int thread = 0; thread < thread_count; thread++) {
        //cout << thread << " " << thread_count << endl;
        x[thread] = thread;
        pthread_create(&thread_handles[thread], NULL, deal_records, &x[thread]);

    }
    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_handles[i], NULL);
    }
    cout << "finished" << endl;
    //free(thread_handles);
    sem_destroy(&sem);
    ofstream ofs;
    ofs.open("out_15611_test.txt", ios::out);
    for (unordered_map<string, vector<string>>::iterator it = map.begin(); it != map.end(); it++) {
        if (length_record.find(it->second.size()) != length_record.end()) {
            length_record[it->second.size()]++;
        }
        else length_record.insert({ it->second.size(), 1 });
        //cout << (it->second).size() << endl;
        for (int i = 0; i < (it->second).size(); i++) {
            //cout << it->second[i] << endl;
            ofs << (it->second)[i] << " ";
        }
        ofs << endl; 
    }
    for (unordered_map<int, int>::iterator it = length_record.begin(); it != length_record.end(); it++) {
        ofs << "长度为" << it->first << "的字符串组有" << it->second << "个" << endl;
    }
    DWORD end_time = GetTickCount();
    cout << "程序运行时间为：" << (end_time - start_time) << "ms" << endl;
    return 0;
}

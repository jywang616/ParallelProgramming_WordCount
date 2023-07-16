#include<stdio.h>
#include<mpi.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include<windows.h>
#include<omp.h>

using namespace std;


const int MAX_BUFFER = 1024;
int main(int argc, char* argv[]) {
	DWORD start = GetTickCount();
	int myid, numprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	DWORD start_read = GetTickCount();
	int total_word = 0;
	//读文件
	ifstream file;
	file.open(argv[1], ios::in);
	if (!file.is_open())
	{
		cout << "读取文件失败" << endl;
		return 0;
	}
	string buf;
	int i = 0;
	vector<string> words;
	while (getline(file, buf)) {
		words.push_back(buf);
		i++;
	}
	total_word = i;
	DWORD end_read = GetTickCount();
	
	if (myid == 0) {
		//主进程
		string out_file_path = "./hw3_MPI-openmp_out_" + string(argv[1]);
		vector<string>keys(total_word);
		int end = 0;
		char rbuff[MAX_BUFFER];
		MPI_Status status;
		for (int i = 0; i < total_word; i++) {
			MPI_Recv(rbuff, sizeof(rbuff), MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if (status.MPI_TAG >= 0 || status.MPI_TAG < total_word) {
				string key(rbuff);
				keys[status.MPI_TAG] = key;
			}
		}

		//DWORD start_classify = GetTickCount();
		map<string, vector<string>> record_map;
		for (int i = 0; i < words.size(); i++) {
			record_map[keys[i]].push_back(words[i]);
		}

		vector<vector<string>>res;
		for (map<string, vector<string>>::iterator it = record_map.begin(); it != record_map.end(); ++it) {
			res.push_back(it->second);
		}
		//DWORD end_classify = GetTickCount();

		map<int, int> length_count;
		ofstream out_file;
		out_file.open(out_file_path, ios::out);
		if (!out_file.is_open())
		{
			cout << "打开文件失败" << endl;
			return 0;
		}
		DWORD start_count = GetTickCount();
		for (vector<string>& x : res) {
			if (length_count.find(x.size()) == length_count.end()) {
				length_count.insert(pair<int, int>(x.size(), 1));
			}
			else {
				length_count[x.size()]++;
			}
			for (string& y : x) {
				out_file << y << " ";
			}
			out_file << endl;
		}
		out_file << endl;
		out_file << "长度统计结果：" << endl;
		DWORD end_count = GetTickCount();

		for (map<int, int>::iterator it = length_count.begin(); it != length_count.end(); ++it) {
			out_file << it->first << ":";
			out_file << (it->second) << " ";
		}

		DWORD total_end = GetTickCount();
		cout << "读文件时间为" << (end_read - start_read) << "ms" << endl;
		cout << "计数时间为" << end_count - start_count << "ms" << endl;
		cout << "共计用时" << (total_end - start) << "ms" << endl;
	}
	else {
		DWORD start_classify = GetTickCount();
		omp_set_num_threads(4);
		int my_rank = myid - 1;
		int thread_work = ceil((double)total_word / (numprocs - 1));
		int thread_first = my_rank * thread_work;
		int thread_end = (my_rank + 1) * thread_work > total_word ? total_word : (my_rank + 1) * thread_work;
		//cout << myid << " " << thread_first << " " << thread_end << " " << endl;
		char arr_str[MAX_BUFFER];
		vector<string> keys;
		vector<string> strings;
		
		int i;
		#pragma omp parallel for
		for (i = thread_first; i < thread_end; i++) {
			#pragma omp critical
			strings.push_back(words[i]);
			string temp = words[i];
			sort(temp.begin(), temp.end());
			#pragma omp critical
			keys.push_back(temp);
		}

		DWORD end_classify = GetTickCount();
		cout << "统计分组时间为" << (end_classify - start_classify) << "ms" << endl;

		DWORD start_send = GetTickCount();
		for (int i = 0; i < keys.size(); i++) {
			strcpy_s(arr_str, keys[i].c_str());
			MPI_Send(arr_str, sizeof(arr_str), MPI_CHAR, 0, i + thread_first, MPI_COMM_WORLD);

		}
		DWORD end_send = GetTickCount();

	}
	MPI_Finalize();

	return 0;
}

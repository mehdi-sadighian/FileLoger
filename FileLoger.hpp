#pragma once
#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <mutex>
#include <queue>
#include <thread>
#include <mutex>

namespace FileAccess {

	using namespace std;

	class FileLogerV1
	{
	public:
		FileLogerV1(char* LogFile)
		{
			this->LogFile = LogFile;
			thread th = thread(&FileLogerV1::write_to_file, this);
			th.detach();
		}

		char* LogFile;
		
		bool file_exists(const std::string& name);
		void write(const string& line, bool insert_timestamp);

	private:

		std::mutex Queue_Mutex;

		queue <string*> write_queue;

		//functions
		void write_to_file();
		const string currentDateTime();

	};//class FileLogerV1

}//namespace FileAccess

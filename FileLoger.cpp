#include "FileLoger.hpp"

namespace FileAccess {

	bool  FileLogerV1::file_exists(const std::string& name)
	{
		ifstream f(name.c_str());
		return f.good();
	}//file_exists

	void FileLogerV1::write(const string& line,bool insert_timestamp)
	{
		string* msg = nullptr;

		if (insert_timestamp)
		{
			msg = new string(currentDateTime() + " " + line);
		}
		else
		{
			msg = new string(line);
		}
		
		const std::lock_guard<std::mutex> lock(Queue_Mutex);
		write_queue.push(msg);

	}//write

	void FileLogerV1::write_to_file()
	{
		ofstream file_to_write;
		file_to_write.open(LogFile, std::ios_base::app); // append instead of overwrite

		if (!file_exists(LogFile))
		{
			ofstream MyFile(LogFile);
			MyFile.close();
		}

		while (true)
		{
			
			std::unique_lock<mutex> lck(Queue_Mutex);

			if (!write_queue.empty())
			{
				ofstream file_to_write;
				file_to_write.open(LogFile, std::ios_base::app); // append instead of overwrite

				while (!write_queue.empty())
				{
					file_to_write << *write_queue.front() << "\n";
					delete write_queue.front();
					write_queue.pop();
				}

				file_to_write.close();
			}//if (!write_queue.empty())

			lck.unlock();

			sleep(1);
		}
	}//write_to_file

	const string FileLogerV1::currentDateTime()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

		return buf;
	}//currentDateTime

}//namespace FileAccess 

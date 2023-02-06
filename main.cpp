#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>

#include "FileLoger.hpp"

using namespace std;

int main()
{
	FileAccess::FileLogerV1 MainLogFile("mainlog.log");
	FileAccess::FileLogerV1 ErrorsLogFile("Errors.log");

	while (true)
	{
		MainLogFile.write("Hello", true);
		ErrorsLogFile.write("Mehdi", false);
		usleep(100000);
	}
}

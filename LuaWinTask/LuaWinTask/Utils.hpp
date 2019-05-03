#pragma once
namespace utils
{
	bool is_file_exist(const char* fileName)
	{
		std::ifstream infile(fileName);
		return infile.good();
	}
	std::string get_path()
	{
		char result[MAX_PATH];
		auto str = std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
		auto last = str.find_last_of("\\");
		if (last)
			str = str.substr(0, last);
		return str;
	}

}
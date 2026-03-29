#include "utils.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


std::string readFileContents(const std::string& path)
{
	std::ifstream fileStream(path);

	if (!fileStream.is_open())
	{
		std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << fileStream.rdbuf();
	return buffer.str();
}

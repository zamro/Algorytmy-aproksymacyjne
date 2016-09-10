#include "ReaderWriter.hpp"
#include <fstream>

std::vector<std::string> ReaderWriter::read(std::string filename)
{
	std::vector<std::string> out;
	std::ifstream in (filename);
	while(in.good())
	{
		std::string line;
		std::getline(in, line, ';');
		out.push_back(line);
	}
	return out;
}
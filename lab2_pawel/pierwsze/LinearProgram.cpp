#include "LinearProgram.hpp"

namespace{

}


const std::unordered_map<std::string, std::function< void(LinearProgram*, std::string)> > LinearProgram::parseTable {
		{"param", LinearProgram::addParam},
		{"var", LinearProgram::addVariable},
		{"s.t.", LinearProgram::addConstraint}
	};

LinearProgram::LinearProgram(std::vector<std::string> data)
{
	for(auto str : data)
	{
		auto pos = str.find_first_of(" \n\t");
		std::string keyword = str.substr(0, pos);
		if(parseTable.count(keyword))
			std:cout<<keyword<<std::endl<<str.substr
			// parseTable[keyword](str.substr(pos));
		else
			std::cerr<<"Warning: \n"<<str<<"\n unrecognized keyword "<<keyword<<"\n";
	}
}

LinearProgram::addParam(std::string in)
{
}

LinearProgram::addVariable(std::string in)
{
}

LinearProgram::addConstraint(std::string in)
{
}
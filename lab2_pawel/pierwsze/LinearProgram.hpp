#pragma once
#include<string>
#include<vector>
#include<set>
#include <unordered_map>
#include <functional>


class LinearProgram{
	static const std::unordered_map<std::string, std::function< void(LinearProgram*, std::string)> > parseTable;
	std::set<std::string> params;
	std::set<std::string> vars;
	addParam(std::string in);
	addVariable(std::string in);
	addConstraint(std::string in);
public:
	LinearProgram(std::vector<std::string> data);
};
#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

enum Relation{
	Greater,
	Less
};

std::unordered_map<std::string, Relation> relationMap = {
	{">=", Relation::Greater},
	{"<=", Relation::Less}
};

struct Constraint
{
	std::vector<double> weights;
	Relation relation;
	double b;
};

struct SVConstraint
{
	Relation relation;
	double b;
};


bool isMinimalization;
std::vector<double> objective;
std::vector<Constraint> constraints;
std::vector<std::vector<SVConstraint>> SVconstraints;

void error()
{
	std::cerr<<"Error, invalid format. Input format should consist of three numbers - number of variables, number of constraints and number of single variable constraints, followed by \"min\" or \"max\" and n weights for objective function. Then are m rows with constraints - each consisting of n weights, \">=\" or \"<=\" and the number, and o rows of single variable constraints consisting of number of variable followed by \">=\" or \"<=\" and the number";
	abort();
}

void read()
{
	int n, m, o;
	std::cin>>n>>m>>o;
	std::string temp;
	std::cin>>temp;
	if(temp == "min")
		isMinimalization = 1;
	else if (temp == "max")
		isMinimalization = 0;
	else
		error();
	objective.resize(n);
	for(int i=0;i<n;i++)
		std::cin>>objective[i];
	
	constraints.resize(m);
	for(int j=0;j<m;j++)
	{
		Constraint& constraint = constraints[j];
		constraint.weights.resize(n);
		for(int i=0;i<n;i++)
			std::cin>>constraint.weights[i];
		
		std::string temp;
		std::cin>>temp;
		if(relationMap.count(temp)>0)
			constraint.relation = relationMap[temp];
		else
			error();
		std::cin>>constraint.b;
	}
	
	SVconstraints.resize(n);
	for(int j=0;j<o;j++)
	{
		unsigned index;
		Relation relation;
		double b;
		std::cin>>index;
		
		std::string temp;
		std::cin>>temp;
		if(relationMap.count(temp)>0)
			relation = relationMap[temp];
		else
			error();
		std::cin>>b;
		
		SVconstraints[index-1].push_back({relation, b});
	}
}

void write()
{
	std::cout<<objective.size()<<" "<<constraints.size()<<" "<<SVconstraints.size()<<std::endl;
	std::cout<<(isMinimalization?"min":"max");
	for(auto a : objective)
		std::cout<<" "<<a;
	std::cout<<std::endl;
	
	for(auto c : constraints)
	{
		for(auto w : c.weights)
			std::cout<<w<<" ";
		std::cout<<(c.relation==Relation::Greater?">=":"<=")<<" "<<c.b<<std::endl;
	}
	
	for(int i = 0;i<SVconstraints.size();i++)
	{
		for(auto c : SVconstraints[i])
		std::cout<<i+1<<" "<<(c.relation==Relation::Greater?">=":"<=")<<" "<<c.b<<std::endl;
	}
}

void normalizeInequalities()
{
	Relation properRelation = (isMinimalization?Relation::Greater:Relation::Less);
	for(auto& constraint : constraints)
	{
		if(constraint.relation != properRelation)
		{
			for(auto &a:constraint.weights)
				a = -a;
			constraint.relation = properRelation;
			constraint.b = -constraint.b;
		}
	}
}

void addSlackVariableTo(unsigned i)
{
	SVconstraints.push_back({{Relation::Greater,0}});
	
	objective.push_back(-objective[i]);
	for(Constraint &c :constraints)
		c.weights.push_back(-c.weights[i]);
}

void invertVariable(unsigned i)
{
	for( SVConstraint& svConstraint :  SVconstraints[i])
		svConstraint.relation = (svConstraint.relation == Relation::Greater) ? Relation::Less : Relation::Greater;
	for(Constraint &c :constraints)
	{
		c.weights[i]= -c.weights[i];
	}
	objective[i] = -objective[i];
}

void addConstraintFor(unsigned i, Relation relation, double b)
{
	constraints.push_back({});
	Constraint &c = constraints.back();
	c.weights.resize(objective.size());
	c.weights[i] = 1;
	c.relation = relation;
	c.b = b;
}

void markSVInequalityNormal(unsigned i)
{
	SVconstraints[i] = {{Relation::Greater,0}};
}

void normalizeSVInequalities()
{
	for(int i=0;i<SVconstraints.size();i++)
	{
		bool isGreater = false, isLess = false;
		double lessMax = std::numeric_limits<double>::min(),
			   greaterMin = std::numeric_limits<double>::max();
		for(auto &c : SVconstraints[i])
		{
			if(c.relation == Relation::Greater)
			{
				isGreater = true;
				greaterMin = std::min(greaterMin, c.b);
			}
			else
			{
				isLess = true;
				lessMax = std::max(lessMax, c.b);
			}
		}
		
		if( not (isGreater || isLess) ) //unconstrained
		{
			markSVInequalityNormal(i);
			addSlackVariableTo(i);
		}
		else if ( isGreater^isLess ) //constrained from one side
		{
			if(isLess)
				invertVariable(i);
		
			double b = isGreater ? greaterMin : lessMax;
			if(b !=0 )
			{
				addConstraintFor(i, Relation::Greater, b);
				markSVInequalityNormal(i);
			}
			if(b < 0)
				addSlackVariableTo(i);
		}
		else //constrained from both sides
		{
			addConstraintFor(i, Relation::Greater, greaterMin);
			addConstraintFor(i, Relation::Less, lessMax);
			markSVInequalityNormal(i);
			if(greaterMin < 0 && lessMax < 0)
				invertVariable(i);
			else if((greaterMin < 0) ^ (lessMax < 0))
				addSlackVariableTo(i);
		}
	}
}

void normalize()
{
	normalizeSVInequalities();
	normalizeInequalities();
}

void writeDual()
{
	std::cout<<constraints.size()<<" "<<objective.size()<<" "<<constraints.size()<<std::endl;
	std::cout<<(!isMinimalization?"min":"max");
	for(const auto& c : constraints)
		std::cout<<" "<<c.b;
	std::cout<<std::endl;
	
	for(int i=0;i<objective.size();i++)
	{
		for(int j=0;j<constraints.size();j++)
			std::cout<<constraints[j].weights[i]<<" ";
		std::cout<<(isMinimalization?"<=":">=")<<" "<<objective[i]<<std::endl;
	}
	
	for(int i = 0;i<constraints.size();i++)
	{
		std::cout<<i+1<<" >= 0"<<std::endl;
	}
}

int main()
{
	read();
	normalize();
	std::cout<<"normalized primal: \n";
	write();
	std::cout<<"-----\ndual\n";
	writeDual();
}
%{
	#define YYDEBUG 1
	#include <stdio.h>
	#include <string>
	#include <vector>
	#include <iostream>
	#include <unordered_set>
	
    extern "C" int yylex();
	extern int yylineno;
	extern int previousLineNo;
	extern std::string previousLine;
    extern FILE* yyin;
	extern FILE *yyout;
    int yyerror(const char *);

//	std::vector<int> lineNumbers;
//	std::vector<std::string> strings;
	std::unordered_set<std::string> params;
	std::unordered_set<std::string> vars;
%}

%define api.value.type {char*}
%token PARAM VAR ST IDENTIFIER CONSTANT SOLVE END

%start statements
%%

statements
	: statement statements
	| SOLVE ';' END ';'
	{
		std::cout<<"koniec\nparams:\n";
		for( auto a : params)
			std::cout<<a<<std::endl;
		std::cout<<"vars:\n";
		for( auto a : vars)
			std::cout<<a<<std::endl;
	}
	;
	
statement
	: PARAM IDENTIFIER ';'
	{
		params.insert($2);
	}
	| VAR IDENTIFIER ';'
	{
		vars.insert($2);
	}
	;
	
%%
int main(int argc, char *argv[])
{
	yydebug = 0;
	if(argc == 1 || argc > 3)
	{
		printf("Usage: %s inputFile [outputFile = stdout]", argv[0]);
		return 0;
	}

	yyin = fopen( argv[1], "r" );
	if(argc == 3)
		yyout = fopen(argv[2],"w");
	yyparse();
	return 0;
}

int yyerror(const char *s)
{
	fflush(stdout);
	printf("\n\n%s\n", s);
}
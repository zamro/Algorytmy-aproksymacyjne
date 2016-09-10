%option noyywrap		
%option yylineno 		

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%x CCOMMENT
%x CPPCOMMENT

%{
#include <cstdio>
#include <unordered_set>
#include <string>
#include "grammar.tab.h"

extern "C" int yylex();
extern	std::unordered_set<std::string> params;
extern	std::unordered_set<std::string> vars;	

void copyValue();

%}

%%
"/*" {ECHO; BEGIN(CCOMMENT); }
<CCOMMENT>.  {ECHO;}
<CCOMMENT>"*/" {BEGIN(INITIAL); ECHO;}

"//" {ECHO; BEGIN(CPPCOMMENT); }
<CPPCOMMENT>.  {ECHO;}
<CPPCOMMENT>\n {BEGIN(INITIAL); ECHO;}
 
"param"			{ copyValue(); return PARAM;}
"var"			{ copyValue(); return VAR;}
"s.t."			{ copyValue(); return ST;}
"solve"			{ copyValue(); return SOLVE;}
"end"			{ copyValue(); return END;}
";"				{ copyValue(); return(';'); }
{L}({L}|{D})*		{ copyValue(); return(IDENTIFIER); }

0[xX]{H}+{IS}?		{ copyValue(); return(CONSTANT); }
0{D}+{IS}?			{ copyValue(); return(CONSTANT); }
{D}+{IS}?			{ copyValue(); return(CONSTANT); }
L?'(\\.|[^\\'])+'	{ copyValue(); return(CONSTANT); }

{D}+{E}{FS}?			{ copyValue(); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ copyValue(); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ copyValue(); return(CONSTANT); }

[ \t\v\n\f]		{ copyValue(); }
.			{ /* ignore bad characters */ }
%%

void copyValue()
{
	yylval = strdup(yytext);
	ECHO;
}
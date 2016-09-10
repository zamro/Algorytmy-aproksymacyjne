SHELL := /bin/bash

LP: grammar.y lex.l 
	bison -d grammar.y 
	flex lex.l
	g++ -o  LP.exe lex.yy.c grammar.tab.c  -lfl -lstdc++ -std=gnu++11
	
clean:
	rm -f *.o LP.exe lex.yy.c grammar.tab.* 
	
test:	LP
	./LP.exe zad.mod

testAll: kompilator
	for input in run/*.imp; do \
		echo ;\
		echo ;\
		echo ;\
		echo ./kompilator.out $$input $${input%.imp}.mr; \
		./kompilator.out $$input $${input%.imp}.mr; \
	done
	
program0: kompilator interpreter
	./kompilator.out run/program1.imp run/program0.mr
	run/interpreter run/program0.mr
program1: kompilator interpreter
	./kompilator.out run/program1.imp run/program1.mr
	run/interpreter run/program1.mr
program2: kompilator interpreter
	./kompilator.out run/program2.imp run/program2.mr
	run/interpreter run/program2.mr
przysłanianie: kompilator interpreter
	./kompilator.out run/przysłanianie.imp run/przysłanianie.mr
	run/interpreter run/przysłanianie.mr
	

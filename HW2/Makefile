SourceFiles = 131044009_HW2.c
InputFile = m731b.txt

all: clean compile run

compile:
	gcc ${SourceFiles} -o solver -lm
run:
	./solver -i ${InputFile} -m GESP
clean:
	rm -rf solver
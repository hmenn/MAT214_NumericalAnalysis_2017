SourceFiles = 131044009_HW2.c

all: clean compile run

compile:
	gcc ${SourceFiles} -o solver -lm
run:
	./solver -i matrix.txt -m GESP
clean:
	rm -rf solver
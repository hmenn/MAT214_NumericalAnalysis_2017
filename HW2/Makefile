SourceFiles = 131044009_HW2.c
InputFile1 = m621c.txt
InputFile2 = m731a.txt
InputFile3 = m731b.txt

all: clean compile

compile:
	gcc ${SourceFiles} -o solver -lm
run1:
	./solver -i ${InputFile1} -m GESP
run2:
	./solver -i ${InputFile2} -m GESP
run3:
	./solver -i ${InputFile3} -m GESP
run4:
	./solver -i ${InputFile1} -m JCB
run5:
	./solver -i ${InputFile2} -m JCB
run6:
	./solver -i ${InputFile3} -m JCB
clean:
	rm -rf solver
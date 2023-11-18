GENERATES = lab0 lab1 lab1.c lab2 lab2.c lab3 lab3.c

run: lab0 lab1 lab2 lab3
	./lab0
	./lab1 8
	./lab2 " |" 8
	./lab3 1 " |" 8
	./lab3 2 " |" 8

lab0: lab0.c

lab1.c: lab0.c patch1.patch
	cp $< $<.backup
	patch $< < patch1.patch
	mv $< $@
	mv $<.backup $<

lab2.c: lab1.c patch2.patch
	cp $< $<.backup
	patch $< < patch2.patch
	mv $< lab2.c
	mv $<.backup $<

lab3.c: lab2.c patch3.patch
	cp $< $<.backup
	patch $< < patch3.patch
	mv $< $@
	mv $<.backup $<

lab1: lab1.c

lab2: lab2.c

lab3: lab3.c

clean:
	rm -rf $(GENERATES)

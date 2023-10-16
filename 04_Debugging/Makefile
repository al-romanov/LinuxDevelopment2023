GENERATES = range gdb1.out gdb2.out

range: range.c
	$(CC) -Wall -g -O0 range.c -o range

test: range
	gdb --quiet --batch -x gdb1.scenario --args ./range 1 12 | grep -P "^@@@" > gdb1.out
	diff gdb1.test gdb1.out
	gdb --quiet --batch -x gdb2.scenario --args ./range -100 100 3 | grep -P "^@@@" > gdb2.out
	diff gdb2.test gdb2.out

clean:
	rm -f $(GENERATES)

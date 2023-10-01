OBJS = $(wildcard *.o)
TESTS = $(wildcard *.test)
GENERATES = prog prog-a prog-so liboutput.so liboutput_static.a $(OBJS) $(TESTS)

CFLAGS += -fPIC

EMPTY_TEST_CASE =
SINGLE_ARG_TEST_CASE = single_argument
TRIPLE_ARG_TEST_CASE = first_arg 2nd_arg 3

all: prog prog-a prog-so

prog: prog.o fun.o const.o

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

liboutput_static.a: fun.o const.o
	$(AR) -rcs $@ $^

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

liboutput.so: fun.o const.o
	$(CC) -shared $^ -o $@

fun.o: outlib.h

prog.o: outlib.h

# Tests are expected to fail since program names are different.
# To make them work, please remove EMPTY_TEST_CASE testing.
test: prog.test prog-a.test prog-so.test
	cmp prog.test prog-a.test
	cmp prog-a.test prog-so.test

%.test: % FORCE
	./$< $(EMPTY_TEST_CASE) > $@ 2>&1
	./$< $(SINGLE_ARG_TEST_CASE) >> $@ 2>&1
	./$< $(TRIPLE_ARG_TEST_CASE) >> $@ 2>&1

prog-so.test: prog-so FORCE
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH ./$< $(EMPTY_TEST_CASE) > $@ 2>&1
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH ./$< $(SINGLE_ARG_TEST_CASE) >> $@ 2>&1
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH ./$< $(TRIPLE_ARG_TEST_CASE) >> $@ 2>&1

FORCE:

clean:
	rm -f $(GENERATES)

CFLAGS=-Wall -O2
bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c
TESTS=tests

tests:
	echo -en "MD5\n\"abcdef" | ./rhasher | tail -n1 > actual.txt
	echo -n "abcdef" | md5sum | awk '{print $$1 }' > expected.txt
	diff actual.txt expected.txt
	echo -en "SHA1\n\"abcdef" | ./rhasher | tail -n1 > actual.txt
	echo -n "abcdef" | sha1sum | awk '{print $$1 }' > expected.txt
	diff actual.txt expected.txt

clean:
	rm -rf *.o rhasher
	git clean -df

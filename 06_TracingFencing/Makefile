GENERATES = move remove_unprotected.so src.txt srcPROTECTED.txt dest.txt

CC_DEFINES = -D_GNU_SOURCE

all: move remove_unprotected.so

move: move.c

remove_unprotected.so: remove_unprotected.c
	$(CC) $(CC_DEFINES) -shared $< -o $@

test: move remove_unprotected.so
	cp move.c src.txt
	strace -e fault=openat:when=3 ./move src.txt dest.txt 2> /dev/null || test $$? -eq 2
	test -f src.txt
	rm -rf src.txt
	cp move.c src.txt
	strace -e fault=openat:when=4 ./move src.txt dest.txt 2> /dev/null || test $$? -eq 2
	test -f src.txt
	cp move.c src.txt
	cp move.c srcPROTECTED.txt
	LD_PRELOAD=`pwd`/remove_unprotected.so ./move srcPROTECTED.txt dest.txt
	test -f srcPROTECTED.txt

clean:
	rm -rf $(GENERATES)



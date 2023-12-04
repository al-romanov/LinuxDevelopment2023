SUBDIRS = src po

@DX_RULES@

all-local: doxygen-doc

doxygen-doc/man/man1/namegen.1:	doxygen-doc

man1_MANS = doxygen-doc/man/man1/namegen.1

clean:
	git clean -df
	rm -rf src/*.o

http: doxygen-doc
	python3 -m http.server --directory $</html

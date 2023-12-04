SUBDIRS = src po

@DX_RULES@

clean:
	git clean -df
	rm -rf src/*.o

http: doxygen-doc
	python3 -m http.server --directory $</html

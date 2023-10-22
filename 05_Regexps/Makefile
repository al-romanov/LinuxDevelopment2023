GENERATES = esub esub_simple.test sed_simple.test esub_bags.test sed_bags.test esub_backslash.test sed_backslash.test esub_complex.test sed_complex.test

esub: esub.c

test: esub
	./$< 'username' 'qwerty' 'Hello, username' > esub_simple.test
	echo 'Hello, username' | sed -E 's/username/qwerty/' > sed_simple.test
	diff esub_simple.test sed_simple.test
	./$< '([0-9]+)th' '(\1-3)' 'This is 5th test' > esub_bags.test
	echo 'This is 5th test' | sed -E 's/([0-9]+)th/(\1-3)/' > sed_bags.test
	diff esub_bags.test sed_bags.test
	./$< '<your-time>' '01\\01\\24' 'Current time is <your-time>' > esub_backslash.test
	echo 'Current time is <your-time>' | sed -E 's/<your-time>/01\\01\\24/' > sed_backslash.test
	diff esub_backslash.test sed_backslash.test
	./$< 'qwe([a-z]+)rty([0-9]+)' 'q\\w\0e\\1r\1t\\2y\2' 'qweasddsrty2432' > esub_complex.test
	echo 'qweasddsrty2432' | sed -E 's/qwe([a-z]+)rty([0-9]+)/q\\w\0e\\1r\1t\\2y\2/' > sed_complex.test
	diff esub_complex.test sed_complex.test

clean:
	rm -f $(GENERATES)

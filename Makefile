all:
	make -C src all

parser:
	./parser_src/generate-grammar.sh

clean:
	make -C src clean

distclean: clean
	make -C src clean


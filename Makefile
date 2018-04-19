all: dump_frag

dump_frag: dump_frag.c
	gcc -o $@ $<


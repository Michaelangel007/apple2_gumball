TARGETS = dump_list
all: $(TARGETS)

.PHONY: clean

clean:
	$(RM) $(TARGETS)

dump_list: dump_list.c
	gcc -o $@ $<

dump_sym: dump_sym.c
	gcc -o $@ $<


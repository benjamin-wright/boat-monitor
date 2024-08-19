.PHONY: gen
gen:
	mkdir -p include/data
	xxd -i data/index.html > include/data/index.h
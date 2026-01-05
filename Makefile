CFLAGS = -Wall -Wextra -Wpedantic -Wformat=2 \
	-Wno-unused-parameter -Wshadow -Wwrite-strings \
	-Wstrict-prototypes -Wold-style-definition -Wredundant-decls \
	-Wnested-externs -Wmissing-include-dirs -std=c18

default:
	mkdir -p build && gcc -g -Og $(CFLAGS) \
	-fstack-protector-strong -D_FORTIFY_SOURCE=2 \
	src/main.c -o build/main

release:
	mkdir -p build && gcc -static -O3 -DNDEBUG $(CFLAGS) \
	-march=native -mtune=native -flto -ffast-math \
	-funroll-loops -fprefetch-loop-arrays \
	-fomit-frame-pointer -pipe \
	src/main.c -o build/main

clean:
	rm -rf build/*

.PHONY: default release clean

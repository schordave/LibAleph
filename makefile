L=/*                                                                              \n\
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC             \n\
 *                                                                                \n\
 * Permission is hereby granted, free of charge, to any person obtaining a copy   \n\
 * of this software and associated documentation files (the "Software"), to       \n\
 * deal in the Software without restriction, including without limitation the     \n\
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or    \n\
 * sell copies of the Software, and to permit persons to whom the Software is     \n\
 * furnished to do so, subject to the following conditions:                       \n\
 *                                                                                \n\
 * The above copyright notice and this permission notice shall be included in     \n\
 * all copies or substantial portions of the Software.                            \n\
 *                                                                                \n\
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     \n\
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       \n\
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    \n\
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         \n\
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING        \n\
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS   \n\
 * IN THE SOFTWARE.                                                               \n\
 */                                                                               \n
SHELL=/bin/bash
#Notes
#	-Wno-overlength-strings      - only needed if compiling with A_INCLUDE_NAMES
#                                      which is enalbed by default.
#       -DA_INCLUDE_NAMES=0
CC?=gcc

WARN=-Werror -Wall -Wformat-nonliteral -Wformat-security \
	-Wswitch-default -Wundef -Wbad-function-cast \
	-Wwrite-strings
	# -Wconversion
ifeq ($(CC), gcc)
    WARN += -Wlogical-op
endif

NO_WARN=-Wno-overlength-strings

LIB_FLAGS=-DA_NULL_PASSTHROUGH=0 -DA_INCLUDE_IO=1 -DA_INCLUDE_MEM=1 -DA_INCLUDE_NAMES=0

FG=-pedantic $(WARN) $(NO_WARN) -O2 -DNDEBUG $(LIB_FLAGS)
FGD=-pedantic $(WARN) $(NO_WARN) -O0 -g -ggdb $(LIB_FLAGS)
SRC=src/
OUT=build/

$(OUT)libaleph.a: $(OUT)aleph.h $(OUT)aleph.c
	$(CC) $(FG) -c $(OUT)aleph.c -o $(OUT)aleph.o
	@rm -f $(OUT)libaleph.a
	ar -cvq $(OUT)libaleph.a $(OUT)*.o

$(OUT)libalephd.a: $(OUT)aleph.h $(OUT)aleph.c
	$(CC) $(FGD) -c $(OUT)aleph.c -o $(OUT)alephd.o
	@rm -f $(OUT)libalephd.a
	ar -cvq $(OUT)libalephd.a $(OUT)*d.o

$(OUT)aleph.h: .FORCE
	mkdir -p build
	cp $(SRC)aleph.h $(OUT)aleph.h

$(OUT)aleph.c: .FORCE
	mkdir -p build
	@echo "Merging all source files."
	@echo -e '$(L)' > $(OUT)aleph.c
	@echo -e '#include "aleph.h"\n#include <string.h>' >> $(OUT)aleph.c
	@echo -e '#include <stdio.h>\n#include <stdarg.h>' >> $(OUT)aleph.c
	@echo -e '#include <stdlib.h>\n' >> $(OUT)aleph.c
	@find $(SRC) -name '*.c' -print0 | \
	        sort -z | \
		xargs --null awk 'FNR==1{printf("\n\n/* FROM %s */\n\n", ARGV[ARGIND])}1' >> $(OUT)aleph.c
	head -50 $(OUT)aleph.c

.FORCE:

clean:
	@rm -f $(OUT)*.c
	@rm -f $(OUT)*.h
	@rm -f $(OUT)*.o
	@rm -f $(OUT)*.a

test: test.c $(OUT)libaleph.a
	$(CC) $(FG) -o test -I $(OUT) test.c $(OUT)libaleph.a
testd: test.c $(OUT)libalephd.a
	$(CC) $(FGD) -o test -I $(OUT) test.c $(OUT)libalephd.a

aleph_gen: gen/gen.c $(OUT)libaleph.a
	$(CC) $(FG) -o aleph_gen -fwhole-program -I $(OUT) gen/gen.c $(OUT)libaleph.a

gen_names: aleph_gen
	@echo "Generating name table"
	./aleph_gen 1 > $(SRC)a_tbl_names.c
	@echo "a_tbl_names.c generated"

gen_records: aleph_gen
	@echo "Generating records table"
	./aleph_gen 7 > $(SRC)a_tbl_records.c
	@echo "a_tbl_records.c generated"

gen_block: aleph_gen
	@echo "Generating blocks table"
	./aleph_gen 5 > $(SRC)a_tbl_blocks.c
	@echo "a_tbl_blocks.c generated"

verif: $(OUT)libaleph.a
	$(MAKE) -C verif/
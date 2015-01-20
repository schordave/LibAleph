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
#Notes
#	-Wno-overlength-strings      - only needed if compiling with A_INCLUDE_NAMES
#                                      which is enalbed by default.
#       -DA_INCLUDE_NAMES=0
CC=gcc
WARN_ME=-Werror -Wall -Wformat-nonliteral -Wformat-security \
	-Wswitch-default -Wtraditional -Wundef -Wbad-function-cast \
	-Wwrite-strings -Wconversion -Wlogical-op 
NO_WARN=-Wno-overlength-strings
FG=-pedantic $(WARNME) $(NO_WARN) -O2 -DNDEBUG
FGD=-pedantic $(WARNME) $(NO_WARN) -O0 -g -ggdb
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
	cp $(SRC)aleph.h $(OUT)aleph.h

$(OUT)aleph.c: .FORCE
	@echo "Merging all source files."
	@echo -e '$(L)' > $(OUT)aleph.c
	@echo -e '#include "aleph.h"\n' >> $(OUT)aleph.c
	@find $(SRC) -name '*.c' -print0 | \
		xargs --null awk 'FNR==1{printf("\n\n/* FROM %s */\n\n", ARGV[ARGIND])}1' >> $(OUT)aleph.c

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
	$(CC) $(FG) -o aleph_gen -I $(OUT) gen/gen.c $(OUT)libaleph.a

gen_names: aleph_gen
	@echo "Compiling generator"
	./aleph_gen 1 > $(SRC)name_.c
	@echo "name_.c generated"

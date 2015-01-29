UNAME=$(shell uname)

CCFLAGS=-Wall -Wextra -Wno-unused-parameter -O3 -I../build/
ifdef CTEST_COLOR_OK
CCFLAGS+=-DCOLOR_OK
endif

ifeq ($(UNAME), Darwin)
LDFLAGS=-Wl,-flat_namespace,-undefined,dynamic_lookup
endif

manual_list_of_tests=1.utf8_check.o \
                     2.category_check.o \
                     3.blocks_check.o \
                     5.case_insensitivity.o

all: test

remake: clean all

%.o: %.c ctest.h
	$(CC) $(CCFLAGS) -c -o $@ $< 

aleph.o:
	cp ../build/aleph.c aleph.c
	$(CC) -I../build/ -fprofile-arcs -ftest-coverage aleph.c -c -o aleph.o

test: main.o ctest.h $(manual_list_of_tests) aleph.o
	$(CC) $(LDFLAGS) -lgcov -coverage  main.o $(manual_list_of_tests) aleph.o -o test

clean:
	rm -fr test *.o *.gcov *.gcno *.gcda
 

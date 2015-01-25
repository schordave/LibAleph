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
                     5.case_insensitivity.o

all: test

remake: clean all

%.o: %.c ctest.h
	gcc $(CCFLAGS) -c -o $@ $<

test: main.o ctest.h $(manual_list_of_tests) ../build/libaleph.a
	gcc $(LDFLAGS) main.o $(manual_list_of_tests) ../build/libaleph.a -o test

clean:
	rm -f test *.o
 

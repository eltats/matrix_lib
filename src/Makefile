CC= gcc -std=c11 #-Wall -Wextra -Werror# -g
LIBSOURCES= $(wildcard s21_*.c)
LIBOBJECTS= $(LIBSOURCES:.c=.o)
COVERAGE= --coverage
LIB=s21_matrix.a

all: test
	make -j gcov_report

test: $(LIB)
	$(CC) --coverage tests/*.c -L. $(LIB) -lcheck `pkg-config --cflags --libs check`
	./a.out

$(LIB): $(LIBOBJECTS)
	ar rc $(LIB) $^
	ranlib $(LIB)

clean:
	rm -rf $(LIB)
	rm -rf *.o
	rm -rf a.out
	find . -name '*.gcno' -type f -delete
	find . -name '*.gcda' -type f -delete
	find . -name '*.info' -type f -delete
	rm -rf report
	rm -rf *.dSYM

re: clean all

gcov_report: $(LIB) test
	lcov -t "test" -o test.info -c -d . 
	genhtml -o report test.info 

.PHONY: all clean test $(LIB) gcov_report

CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
LDFLAGS= -Wall -Werror -Wextra -lcheck -lpthread -lm

TST_LIBS = $(shell pkg-config --libs check)

all: clean s21_math.a


s21_math.a:
	$(CC) $(CFLAGS) s21_math.c
	ar -rc s21_math.a s21_math.o
	ranlib s21_math.a

test: clean
	$(CC) $(CFLAGS) s21_math.c tests.c
	$(CC) s21_math.o tests.o $(TST_LIBS) -o test
	./test

testlib:
	$(CC) $(CFLAGS) s21_math.c
	ar -rc libs21_math.a s21_math.o
	ranlib libs21_math.a
	gcc tests.c $(TST_LIBS) -L. -ls21_math -o testlib.out
	./testlib.out

gcov_report:
	gcc s21_math.c tests.c -o gcov_check.out $(TST_LIBS) --coverage
	./gcov_check.out
	lcov -t "gcheck" -o gcheck.info -c -d . 
	genhtml -o report gcheck.info
	open ./report/index.html

clang:
	cp ../materials/linters/.clang-format .
# clang-format -i *.c *.h
	clang-format -n *.c
	clang-format -n *.h


clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf s21_math_test
	rm -rf test
	rm -rf report
	rm -rf *.gcda *.gcno *.gcov
	rm -rf .clang-format
	rm -rf *.out
	rm -rf gcheck.info

rebuild: clean all

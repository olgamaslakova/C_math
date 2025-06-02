gcc = gcc 
flags = -Werror -Wall -Wextra -std=c11
gcov_flags = --coverage
check_flag = -lcheck -lm -lpthread 
math_file = ./s21_math.c
test_file = ./test.c
out_file = ./s21_math
library = ./s21_math.a

ifeq ($(shell uname), Linux)
check_flag += -pthread -lcheck_pic -lrt -lm -lsubunit
endif

ifeq ($(shell uname), Darwin)
check_flag += -I$(shell brew --prefix check)/include -L"$(shell brew --prefix check)/lib"
endif

all: clang s21_math.a gcov_report

s21_math.a:
	$(gcc) -c $(flags) $(math_file)
	ar rcs $(library) ./*.o 
	ranlib $(library)
	rm s21_math.o

test: s21_math.a
	$(gcc) $(flags) $(test_file) $(library) -o $(out_file) $(check_flag)
	./s21_math

gcov_report: s21_math.a
	$(gcc) $(flags) $(gcov_flags) $(test_file) $(math_file) -o $(out_file) $(check_flag)
	./s21_math  
	gcov *.c
	lcov -d . -o gcov_report.info -c --no-external
	genhtml -o report gcov_report.info
	open report/index.html  
	make rm_gcov

clean:
	rm -f $(library)
	rm -f $(out_file)
	make rm_report
	make rm_gcov

rebuild:
	make clean
	make all

rm_gcov:
	rm -f *.gcno	
	rm -f *.gcov
	rm -f *.gcda
	rm -f *.info

rm_report:
	rm -rf report

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c *.h

format_check:
	clang-format -n *.c *.h
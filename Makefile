all: clean_all utils all_days each_day
each_day: day1 day2 day3 day4 day5 day6 day7 day8 day9 day10 \
			day11 day12 day13 day14
clean_all: clean_utils clean_runners
clean: clean_runners
all_days:
	clang -Wall src/aoc1.c src/aoc2.c src/aoc3.c src/aoc4.c src/aoc5.c \
				src/aoc6.c src/aoc7.c src/aoc8.c src/aoc9.c src/aoc10.c \
				src/aoc11.c src/aoc12.c src/aoc13.c src/aoc14.c\
				src/runners/all_days.c libs/utils.a \
				-o all_day_runner;
#############################
clean_runners: 
	rm *runner -f
clean_utils:
	rm libs/* -f
#############################
utils:
	mkdir -p libs;
	clang -Wall -c src/utils/file_utils.c -o libs/file_utils.o
	clang -Wall -c src/utils/character_stack.c -o libs/character_stack.o
	clang -Wall -c src/utils/sorting_algorithms.c -o libs/sorting_algorithms.o
	ar -c libs/utils.a \
		-r libs/sorting_algorithms.o libs/character_stack.o libs/file_utils.o
#############################
day1:
	clang -Wall src/runners/day1.c src/aoc1.c \
		libs/utils.a \
		-o day1_runner;
day2:
	clang -Wall \
		src/runners/day2.c src/aoc2.c \
		libs/utils.a \
		-o day2_runner;
day3:
	clang -Wall  \
		src/runners/day3.c src/aoc3.c \
		libs/utils.a \
		-o day3_runner;
day4:
	clang -Wall \
		src/runners/day4.c src/aoc4.c \
		libs/utils.a \
		-o day4_runner;
day5:
	clang -Wall \
		src/runners/day5.c src/aoc5.c \
		libs/utils.a \
		-o day5_runner;
day6:
	clang -Wall \
		src/runners/day6.c src/aoc6.c \
		libs/utils.a \
		-o day6_runner;
day7:
	clang -Wall \
		src/runners/day7.c src/aoc7.c \
		libs/utils.a \
		-o day7_runner;
day8:
	clang -Wall \
		src/runners/day8.c src/aoc8.c \
		libs/utils.a \
		-o day8_runner;
day9:
	clang -Wall \
		src/runners/day9.c src/aoc9.c \
		libs/utils.a \
		-o day9_runner;
day10:
	clang -Wall \
		src/runners/day10.c src/aoc10.c \
		libs/utils.a \
		-o day10_runner;
day11:
	clang -Wall \
		src/runners/day11.c src/aoc11.c \
		libs/utils.a \
		-o day11_runner;
day12:
	clang -Wall \
		src/runners/day12.c src/aoc12.c \
		libs/utils.a \
		-o day12_runner;
day13:
	clang -Wall \
		src/runners/day13.c src/aoc13.c \
		libs/utils.a \
		-o day13_runner; 
day14:
	clang -Wall \
		src/runners/day14.c src/aoc14.c \
		libs/utils.a \
		-o day14_runner; 

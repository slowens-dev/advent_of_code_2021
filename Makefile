all: clean each_day


clean: 
	rm *runner -f
each_day: day1 day2 day3 day4
all_days:
	clang -Wall src/aoc1.c  src/aoc2.c  src/aoc3.c src/aoc4.c \
		src/aoc5.c \
		src/runners/all_days.c -o all_day_runner;
day1:
	clang -Wall src/runners/day1.c src/aoc1.c -lm -o day1_runner;
day2:
	clang -Wall src/runners/day2.c src/aoc2.c -lm -o day2_runner;
day3:
	clang -Wall src/runners/day3.c src/aoc3.c -lm -o day3_runner;
day4:
	clang -Wall src/runners/day4.c src/aoc4.c -lm -o day4_runner;
day5:
	clang -Wall src/runners/day5.c src/aoc5.c -lm -o day5_runner;
day6:
	clang -Wall src/runners/day6.c src/aoc6.c -lm -o day6_runner;
day7:
	clang -Wall src/runners/day7.c src/aoc7.c -lm -o day7_runner;
day8:
	clang -Wall src/runners/day8.c src/aoc8.c -lm -o day8_runner;

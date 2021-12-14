all: clean each_day


clean: 
	rm *runner -f
each_day: day1 day2 day3
all_days:
	clang -Wall src/aoc1.c  src/aoc2.c  src/aoc3.c \
		src/runners/all_days.c -o all_day_runner;
day1:
	clang -Wall src/runners/day1.c src/aoc1.c -lm -o day1_runner;
day2:
	clang -Wall src/runners/day2.c src/aoc2.c -lm -o day2_runner;
day3:
	clang -Wall src/runners/day3.c src/aoc3.c -lm -o day3_runner;

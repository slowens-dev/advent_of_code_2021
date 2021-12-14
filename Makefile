all: clean each_day


clean: clean_objects clean_runners
clean_runners:
	rm *runner -f
clean_objects:
	rm src/libs/*.o -f


each_day: day1 day2 day3
all_days:
	clang -Wall src/runners/all_days.c -c -o src/libs/all_days.o
	clang -Wall src/aoc1.c -c -o src/libs/aoc1.o
	clang -Wall src/aoc2.c -c -o src/libs/aoc2.o
	clang -Wall  src/aoc3.c -c -o src/libs/aoc3.o -lm
	clang -Wall src/libs/aoc*.o src/libs/all_days.o -o all_days_runner -lm
day1:
	clang -Wall src/runners/day1.c -c -o src/libs/day1.o
	clang -Wall src/aoc1.c -c -o src/libs/aoc1.o
	clang -Wall src/libs/day1.o src/libs/aoc1.o -o day1_runner
day2:
	clang -Wall src/runners/day2.c -c -o src/libs/day2.o
	clang -Wall src/aoc2.c -c -o src/libs/aoc2.o
	clang -Wall src/libs/day2.o src/libs/aoc2.o -o day2_runner 
day3:
	clang -Wall src/runners/day3.c -c -o src/libs/day3.o
	clang -Wall  src/aoc3.c -c -o src/libs/aoc3.o -lm
	clang -Wall src/libs/day3.o src/libs/aoc3.o -o day3_runner -lm

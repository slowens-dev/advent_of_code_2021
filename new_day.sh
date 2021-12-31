cp ./src/aocx.c ./src/aoc$1.c
sed -i "s/x/$1/g" ./src/aoc$1.c
cp ./src/headers/aocx.h ./src/headers/aoc$1.h
sed -i "s/x/$1/g" ./src/headers/aoc$1.h
cp ./src/runners/dayx.c ./src/runners/day$1.c
sed -i "s/xx/$1/g" ./src/runners/day$1.c


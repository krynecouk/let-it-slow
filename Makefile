build:
	g++-8 -w -std=c++17 -Wfatal-errors \
	-g \
	./src/*.cpp \
	-o game \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

build-dev:
	g++-8 -w -std=c++17 -Wfatal-errors \
	-g \
	-O0 \
	./src/*.cpp \
	-o game-dev \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

memcheck:
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--log-file=valgrind-out.txt \
	--track-origins=yes \
	--verbose \
	./game-dev;

cachegrind:
	valgrind --tool=cachegrind \
	--branch-sim=yes \
	./game;

clean:
	rm ./game;

run:
	./game;

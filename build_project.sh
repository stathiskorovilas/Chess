CC=g++
LD=g++
CFLAGS="$CFLAGS $(pkg-config --cflags SDL2 GLEW freetype2)"
CFLAGS_DEBUG="$CFLAGS_DEBUG $(pkg-config --cflags SDL2 GLEW freetype2)"
LDFLAGS="$LDFLAGS $(pkg-config --libs SDL2 GLEW freetype2)"
BIN_PATH="bin"
LIB_PATH="sgg/lib"

mkdir -p $BIN_PATH

# Compile the release version
$CC -std=c++17 $CFLAGS $LDFLAGS -L$LIB_PATH -I./sgg/sgg -I./sgg source/main.cpp  source/game.cpp source/BoardSquare.cpp -o $BIN_PATH/main -lsgg -lSDL2_mixer -framework OpenGL

# Compile the debug version
$CC -std=c++17 $CFLAGS_DEBUG $LDFLAGS -L$LIB_PATH -I./sgg/sgg -I./sgg source/main.cpp source/game.cpp source/BoardSquare.cpp -o $BIN_PATH/maind -lsggd -lSDL2_mixer -framework OpenGL

cp -r assets $BIN_PATH

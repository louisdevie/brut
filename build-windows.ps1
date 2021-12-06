. ./WINSETUP.ps1

cd src

g++ -o ../build/brut.exe brut.cpp "-I$SDL2_INCLUDE" "-L$SDL2_LIB" -std=c++11 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -v

cd ..
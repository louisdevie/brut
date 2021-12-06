. ./WINSETUP.ps1

cd src
g++ brut.cpp -I$SDL2_INCLUDE -L$SDL2_LIB -Wall -lmingw32 -lSDL2main -lSDL2 -o ../build/brut brut.cpp

cd ..
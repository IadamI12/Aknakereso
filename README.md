# Aknakereső

Konzolos aknakereső játék C nyelven. A pontos dokumentáció megtalálható,
a docs mappában, dokumentacio.pdf néven.

## Követelmények

- Windows
- MSYS2
- MSYS2 UCRT64
- GCC

## Fordítás GCC-vel

Nyisd meg az MSYS2 UCRT64 terminált, majd lépj be a projekt mappájába.

Fordítsd le a programot:
     g++ -std=c++17 -Wall -Wextra -Iheaders src/main.cpp src/jatekelemek.cpp -o Donald.exe
     
## Indítás

cd data

../Donald.exe

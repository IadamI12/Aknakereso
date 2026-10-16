# Aknakereső

Konzolos aknakereső játék C nyelven. A pontos dokumentáció megtalálható,
a docs mappában, dokumentacio.pdf néven.

## Követelmények

- Windows
- MSYS2
- MSYS2 UCRT64
- GCC

## Fordítás GCC-vel

Nyisd meg az MSYS2 UCRT64 terminált, majd lépj be a projekt mappájába:

Például ha basht használsz:
    cd /c/Users/Asus/Desktop/jatekok/Aknakereso

Fordítsd le a programot:
    gcc -std=c11 -Wall -Wextra -finput-charset=UTF-8 -fexec-charset=UTF-8 -Iheaders src/main.c src/palya.c src/vezerles.c src/megjelenites.c src/econio.c -o aknakereso.exe

## Indítás

./aknakereso.exe

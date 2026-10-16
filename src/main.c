#ifdef _WIN32
#include <windows.h>
#endif
#include "debugmalloc.h"
#include "palya.h"
#include "vezerles.h"
#include "megjelenites.h"

/*A j�t�k �zemeltet�s�t vez�rli, l�trehozza a p�ly�t, ha ez nem siker�lt, jelzi a felhaszn�l�nak, �s kil�p a programb�l. Ha siker�lt
    l�trehozni, akkor kirajzolja a kezdeti p�ly�t, �s elkezdodik a j�t�k vez�rl�se. A v�g�n a dinamikusan foglalt t�mb�ket felszabad�tja
    mem�riasziv�rg�s elker�l�se v�gett*/
int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
    Palya p;
    bool sikeres = palyafugv(&p);
    if (!sikeres)
    {
        printf("Nem sikerult a palyat letrehozni.");
        return 2;
    }
    printf("\x1b[?25l");
    kezdeti(&p);
    vezerles(&p);
    printf("\x1b[?25h");
    free(p.palya[0]);
    free(p.palya);
    return 0;

}

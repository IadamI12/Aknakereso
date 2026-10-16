#ifdef WIN32
#include <windows.h>
#endif
#include "debugmalloc.h"
#include "palya.h"
#include "vezerles.h"
#include "megjelenites.h"

/*A játék üzemeltetését vezérli, létrehozza a pályát, ha ez nem sikerült, jelzi a felhasználónak, és kilép a programból. Ha sikerült
    létrehozni, akkor kirajzolja a kezdeti pályát, és elkezdodik a játék vezérlése. A végén a dinamikusan foglalt tömböket felszabadítja
    memóriaszivárgás elkerülése végett*/
int main() {
    #ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
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

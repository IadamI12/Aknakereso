#include  "vezerles.h"
#include "econio.h"
#include "palya.h"
#include "megjelenites.h"
#include "debugmalloc.h"
#include <time.h>

/*Ez a két függvény segít abban, hogy az őket meghívó függvények ne legyenek túlindexelve, "ne lépjenek le a pályáról".
    A maximalis a lehető legnagyobb, a minimális a lehető legkisebb értékkel tér vissza.*/
static int maximalis(int a, int b){
    return a > b ? a : b;}
static int minimalis(int a, int b){
    return a < b ? a : b;}



/* Megszámolja, hogy egy adott mező körül, hány akna helyezkedik el. Visszatérési értéke int, mely ennek az értékét adja vissza. */
static int kisrobbantas(Palya *p,int a, int b)
{
    int db = 0;
    for (int i = maximalis(a-1,0); i <= minimalis(a+1,p->szelesseg-1); i++)
        for (int j = maximalis(b-1,0); j <= minimalis(b+1,p->magassag-1); j++)
            if (p->palya[i][j].akna)
                db += 1;
    return db;
}

/* A mezők kirobbantásáért felelős függvény. Visszatérési értéke bool, ha aknába lépett a felhasználó "false"-al tér vissza, ezzel jelezve a játék végét.
    Ha nem aknába lépett, az adott mezőt felderítetté teszi, és a kisrobbantas fuggveny segítségével meghatározza a mögötte rejlő számot. Ha
    ez 0 lenne, akkor üres mező jelenik meg, s minden szomszédjára meghívódik a függvény, mely ha náluk is 0-t jelez, rekurzívan meghívja az egészet újra.*/
static bool robbantas(Palya *p,int a, int b)
 {
     if (p->palya[a][b].akna)
            return false;
    else if (!(p->palya[a][b].felderitett)){
        p->palya[a][b].tipus = (Tipus)kisrobbantas(p, a, b);
        p->palya[a][b].felderitett = true;
        Kord hely2 = {a,b};
        kirajz(p,hely2);
        if (p->palya[a][b].tipus == ures){
        for (int i = maximalis(a-1,0); i <= minimalis(a+1,p->szelesseg-1); i++)
            for (int j = maximalis(b-1,0); j <= minimalis(b+1,p->magassag-1); j++){
                int darab = kisrobbantas(p,i,j);
                Kord hely3 = {i,j};
                if ( !(p->palya[i][j].felderitett) && !(p->palya[i][j].akna) ){
                switch (darab)
                        {
                case 0: robbantas(p,i,j); break;
                case 1: p->palya[i][j].tipus = egy; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                case 2: p->palya[i][j].tipus = ketto; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                case 3: p->palya[i][j].tipus = harom; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                case 4: p->palya[i][j].tipus = negy; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                case 5: p->palya[i][j].tipus = ot; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                case 6: p->palya[i][j].tipus = hat; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                case 7: p->palya[i][j].tipus = het; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                case 8: p->palya[i][j].tipus = nyolc; p->palya[i][j].felderitett = true;  kirajz(p,hely3); break;
                        }
                    }
                }
            }
        }
      return true;
 }


/*A mezők "zaszlo" tulajdonságát lehet vele ki/be kapcsolni, mely a változtatás után kirajzolódik.*/
void zaszlo(Palya *p,Kord hely)
{
    if ( !(p->palya[hely.x][hely.y].zaszlo)){
        p->palya[hely.x][hely.y].zaszlo = true;
        kirajz(p,hely);
        }
    else if (p->palya[hely.x][hely.y].zaszlo){
        p->palya[hely.x][hely.y].zaszlo = false;
        kirajz(p,hely);
        }
}

/*Megszámolja, hogy a pályán hány felderített mező van, visszatérési értéke a szám. */
static int felderitett(Palya *p)
{
    int db = 0;
    for (int i = 0; i < p->szelesseg ; i++)
        for (int j = 0; j < p->magassag; j++)
            if (p->palya[i][j].felderitett)
                db++;
    return db;

}

/*Ha a játékos nyert, ez a függvény "true"-val tér vissza, s közli a játékossal, hogy elérte a győzelmet. */
bool nyert(Palya *p)
{
if (felderitett(p) == (p->szelesseg * p->magassag - p->aknak)){
            econio_clrscr();
            econio_textcolor(COL_GREEN);
            printf("Nyertel! :)\n\nJatekido: %.2d:%.2d\n\n",(int)p->ido/60,(int) p->ido%60);
            FILE* ftorol;
            ftorol = fopen("regi.txt","w");
            fclose(ftorol);
            econio_textcolor(COL_YELLOW);
            return true;
    }
    return false;
}
/*A játék vége állapotot kezeli*/
void vesztett(Palya *p)
{
    econio_clrscr();
    econio_textcolor(COL_RED);
    printf("Felrobbantal! :(\n\nJatekido: %.2d:%.2d\n\n",(int)p->ido/60,(int) p->ido%60);
    econio_textcolor(COL_YELLOW);
    FILE* ftorol;
    ftorol = fopen("regi.txt","w");
    fclose(ftorol);
}

/* A játékmenet vezérlésére alkalmas függvény. Benne valósítódik meg a játékidő megjelenítése, a játék végének kezelése, és a kurzor kiemelése.
    Mindezek mellett a különböző gomblenyomások segítségével vezérli az egész játékot. A függvényből kilépés vagy győzelem, veszteség, vagy játék
    mentése esetén lehetséges.*/
void vezerles(Palya *p){
    Kord hely = {0,0};
    econio_gotoxy(0,0);
    econio_rawmode();
    time_t start = time(0);
    time_t eltelt_eredeti = p->ido;
    time_t eltelt;
while(true){
        if(!econio_kbhit()){
            eltelt = difftime(time(0), start) + eltelt_eredeti;
            p->ido = eltelt;
            econio_gotoxy(p->szelesseg/2+((int)p->szelesseg/6),p->magassag);
            econio_textcolor(COL_MAGENTA);
            printf("%.2d:%.2d", (int)eltelt/60, (int)eltelt%60);
            econio_textcolor(COL_RESET);
            econio_gotoxy(hely.x,hely.y);

        if (nyert(p)) break;
        }

        else{
        Kord hely2 = {hely.x/2,hely.y};
        int nyomas = econio_getch();
        kirajz(p, hely2);

        if (nyomas == KEY_UP) {
            hely.y = maximalis(hely.y -1, 0);
        }
        else if (nyomas == KEY_DOWN) {
            hely.y = minimalis(hely.y +1, p->magassag-1);
        }
        else if (nyomas == KEY_RIGHT) {
            hely.x = minimalis(hely.x +2, p->szelesseg*2-2);
        }
        else if (nyomas == KEY_LEFT) {
            hely.x = maximalis(hely.x -2, 0);
        }
        else if (nyomas == KEY_ENTER)
        {
            if(!robbantas(p,hely.x/2,hely.y)){
                    vesztett(p);
                    break;
            }
        }
        else if (nyomas == KEY_TAB)
        {
            Kord hely2 = {hely.x/2,hely.y};
            zaszlo(p,hely2);
        }
        else if (nyomas == KEY_ESCAPE)
            {
            econio_clrscr();
            econio_textcolor(COL_LIGHTBLUE);
            if (mentes(p))
                printf("A jatek mentese sikeres volt.\n\nJatekido: %.2d:%.2d\n\n",(int)p->ido/60,(int) p->ido%60);
            econio_textcolor(COL_YELLOW);
            break;
            }
        Kord hely3 = {hely.x/2,hely.y};
        econio_textbackground(COL_MAGENTA);
        kirajz(p, hely3);
        econio_textbackground(COL_RESET);
        econio_gotoxy(hely.x,hely.y);
        }
        }
}

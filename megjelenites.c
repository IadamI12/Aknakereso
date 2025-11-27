#include "palya.h"
#include "econio.h"
#include "debugmalloc.h"

/*A pálya adott koordinátáján lévő mező felfedésére/zászlózására alkalmas függvény. Ha zászlózás történik elöször azt kezeli, majd a
    pályaelem típusa alapján dönti el, hogy mit kell megjeleníteni az adott mezőn.*/
void kirajz(Palya *p,Kord hely)
        {
            const char* cella = "\xE2\x97\xBC";
            const char* zaszlo = "\xE2\x9A\x91";
            if (p->palya[hely.x][hely.y].zaszlo && !(p->palya[hely.x][hely.y].felderitett)){
                econio_gotoxy(hely.x*2,hely.y);     econio_textcolor(COL_RED);     printf(zaszlo);
            }
            else{
            switch(p->palya[hely.x][hely.y].tipus)
            {
                case ures:
                if (p->palya[hely.x][hely.y].felderitett){
                    econio_gotoxy(hely.x*2,hely.y);      econio_textcolor(COL_BLACK);        printf(cella);  break;
                }
                else{
                    econio_gotoxy(hely.x*2,hely.y);     econio_textcolor(COL_GREEN);         printf(cella); break;
                }
                case egy:                               econio_gotoxy(hely.x*2,hely.y);        econio_textcolor(COL_GREEN);         printf("%d",1);  break;
                case ketto:                             econio_gotoxy(hely.x*2,hely.y);        econio_textcolor(COL_LIGHTBLUE); printf("%d",2);  break;
                case harom:                         econio_gotoxy(hely.x*2,hely.y);         econio_textcolor(COL_LIGHTCYAN);              printf("%d",3);  break;
                case negy:                              econio_gotoxy(hely.x*2,hely.y);       econio_textcolor(COL_YELLOW);        printf("%d",4);  break;
                case ot:                                econio_gotoxy(hely.x*2,hely.y);          econio_textcolor(COL_LIGHTRED);    printf("%d",5);  break;
                case hat:                               econio_gotoxy(hely.x*2,hely.y);         econio_textcolor(COL_RED);                printf("%d",6); break;
                case het:                               econio_gotoxy(hely.x-2,hely.y);         econio_textcolor(COL_MAGENTA);     printf("%d",7);  break;
                case nyolc:                            econio_gotoxy(hely.x*2,hely.y);        econio_textcolor(COL_WHITE);           printf("%d",8);  break;
                default: break;
            }
            }
        }


/*A kezdeti pályát kirajzoló függvény, mely végigmegy a pálya listán, és kirajzolja az adott elemekhez tartozó mezőket. */
void kezdeti(Palya *p) {
    econio_set_title("Aknakereso jatek");

    econio_clrscr();
    Kord hely = {0,0};
        for (int i = 0; i < p->szelesseg; i +=1){
            for (int j = 0; j < p->magassag; j+=1)
                {
                Kord koordinata = {  (hely.x+i)  ,  (hely.y+j)  };
                kirajz(p,koordinata);
                }
        }
}

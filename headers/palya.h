#ifndef PALYA_H
#define PALYA_H

#include <stdbool.h>
/*P�lyamezok t�pus�t megnevezo felsorolt t�pus.*/
typedef enum Tipus {
    ures,
    egy,
    ketto,
    harom,
    negy,
    ot,
    hat,
    het,
    nyolc,
} Tipus;

/*A p�lyamezok, �s azok tulajdons�gait t�rol� strukt�ra.*/
typedef struct Mezo {
    bool felderitett;
    bool akna;
    bool zaszlo;
    Tipus tipus;
} Mezo;

/*A p�lya adatait t�rol� strukt�ra. */
typedef struct Palya{
    Mezo** palya;
    int magassag;
    int szelesseg;
    int aknak;
    int ido;
} Palya;

/*A koordin�t�k (p�lyamezok) szelesseg �s magassag adatjainak t�rol�s�t eloseg�to t�pus. */
typedef struct Kord{
    int x,y;
}Kord;


bool palyafugv(Palya *p);
bool mentes(Palya *p);
#endif

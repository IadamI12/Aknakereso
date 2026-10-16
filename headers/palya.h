#ifndef PALYA_H
#define PALYA_H

#include <stdbool.h>
/*Pályamezok típusát megnevezo felsorolt típus.*/
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

/*A pályamezok, és azok tulajdonságait tároló struktúra.*/
typedef struct Mezo {
    bool felderitett;
    bool akna;
    bool zaszlo;
    Tipus tipus;
} Mezo;

/*A pálya adatait tároló struktúra. */
typedef struct Palya{
    Mezo** palya;
    int magassag;
    int szelesseg;
    int aknak;
    int ido;
} Palya;

/*A koordináták (pályamezok) szelesseg és magassag adatjainak tárolását elosegíto típus. */
typedef struct Kord{
    int x,y;
}Kord;


bool palyafugv(Palya *p);
bool mentes(Palya *p);
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "debugmalloc.h"

#include "palya.h"

/* Ez a függvény alapján tudjuk eldönteni, hogy a felhasználó új játékot szeretett-e volna kezdeni.
   Visszatérési értéke ezért is "bool", hisz ha új játékot szeretne kezdeni, akkor "true"-val tér vissza, ha nem
    akkor pedig "false"-szal*/
static bool uj(void)
{
    char valasz;
    int db;
    do {
    printf("Uj jatekot szeretnel kezdeni? (I/N) ");
    scanf("%c",&valasz);
    db = 0;
    while(getchar() != '\n')
        db++;
    } while ((valasz != 'I' && valasz != 'i' && valasz != 'N' && valasz != 'n') || db > 0);
        if (valasz == 'I' || valasz == 'i')
            return true;
        else
            return  false;
}

/* Ez a függvény segít az aknák randomizált elhelyezésében. Nincs visszatérési értéke
   hisz a függvény csak akkor hívódhat meg ha a felhasználó megfelelő pályaméretet és akna-
    számot adott meg. A függvényben oda kell figyelni arra, hogy ne rakjunk egy helyre több aknát,
    erre a "duplicate" nevű bool változóban van lehetőség.*/
static void akna_randomizalas(Palya *p)
{
    srand(time(0));
    int db = 0;
    int a,b;
    bool duplicate;
    while (db != (p->aknak))
    {
        a = rand()%(p->szelesseg);
        b = rand()%(p->magassag);
        duplicate = false;
            if (p->palya[a][b].akna)
                duplicate = true;
        if (!duplicate)
        {
            db += 1;
            p->palya[a][b].akna = true;
        }
    }
}

/*Ez  a függvény felelős a játékpálya létrehozásáért. Ha új játék, akkor az alapján hozza létre, ha régi, akkor betölti egy fileból (abban az esetben ha lehetséges).
    Visszatérési értéke bool, ha nem sikerült létrehozni a pályát, azt közölni fogja az őt meghívó függvénnyel.*/
bool palyafugv(Palya *p){
    bool uj_jatek = uj();
    int magassag = 0,szelesseg,aknak,ido;
    if (uj_jatek)
    {
    do {
    printf("Mekkora legyen a tabla? \"szelesseg magassag\" formatumban: ");
    scanf("%d %d",&szelesseg,&magassag);
    while(getchar() != '\n');
    } while (szelesseg <= 0 || magassag <= 0);
    do {
    printf("Mennyi akna legyen a palyan? ");
    scanf("%d",&aknak);
    while(getchar() != '\n');
    } while (szelesseg*magassag <= aknak || aknak <=0);

        p->magassag = magassag;
        p->szelesseg = szelesseg;
        p->aknak = aknak;
        p->ido = 0;

            p->palya = (Mezo**) malloc((p->szelesseg) * sizeof(Mezo*));
            p->palya[0] = (Mezo*) malloc((p->magassag) * (p-> szelesseg) * sizeof(Mezo));
            if (p->palya == NULL || p->palya[0] == NULL)
                return false;
            for (int i = 1; i < p->szelesseg; i++)
                p->palya[i] = p->palya[0] + i * p->magassag;

            for (int i = 0; i < p->szelesseg; i++){
                for (int j = 0; j < p->magassag; j++){
                    p->palya[i][j].tipus = ures;
                    p->palya[i][j].felderitett = false;
                    p->palya[i][j].akna = false;
                    p->palya[i][j].zaszlo = false;
                }
            }

        akna_randomizalas(p);
    }
    else
    {
        FILE* fbe;
        fbe = fopen("regi.txt","r");
        if (fbe == NULL)
        {
            perror("Nem sikerult a regi palyat betolteni.");
            return false;
        }
        fscanf(fbe,"%d %d %d %d",&szelesseg,&magassag,&aknak,&ido);
        if (magassag == 0)
            return false;
        p->magassag = magassag;
        p->szelesseg = szelesseg;
        p->aknak = aknak;
        p->ido = ido;

        p->palya = (Mezo**) malloc(p->szelesseg * sizeof(Mezo*));
        p->palya[0] = (Mezo*) malloc(p->magassag * p->szelesseg * sizeof(Mezo));
        if (p->palya == NULL || p->palya[0] == NULL)
            return false;
        for (int i = 1; i < p->szelesseg; i++)
            p->palya[i] = p->palya[0] + i * p->magassag;


        for (int i = 0; i < p->szelesseg; i++)
            for (int j = 0; j < p->magassag; j++)
        {
            int c1,c2,c3,c4;
            fscanf(fbe,"%d %d %d %d ",&c1,&c2,&c3,&c4);
            p->palya[i][j].felderitett = (bool) c1;
            p->palya[i][j].akna = (bool) c2;
            p->palya[i][j].zaszlo = (bool) c3;
            p->palya[i][j].tipus = (Tipus) c4;
        }
    fclose(fbe);
    }
    return true;
    }

/*A játékpálya elmentésére alkalmas függvény, melyet majd az ESCAPE gomb lenyomása után tud meghívni a felhasználó.
    Visszatérési értéke bool, ha nem sikerült menteni a pályát, akkor azt közli a felhasználóval, illetve ha sikerült, azt is.*/
bool mentes(Palya *p){
    FILE* fki;
    fki = fopen("regi.txt","w");
    if (fki == NULL)
        {
        perror("A jatek mentese nem volt sikeres.");
        return false;
        }
    fprintf(fki,"%d %d %d %d\n",p->szelesseg,p->magassag,p->aknak,p->ido);
    for (int i = 0; i < p->szelesseg; i++){
        for (int j = 0; j < p->magassag; j++)
                fprintf(fki,"%d %d %d %d ", p->palya[i][j].felderitett,p->palya[i][j].akna, p->palya[i][j].zaszlo, p->palya[i][j].tipus);
            fprintf(fki,"\n");
            }
    fclose(fki);
    return true;
}

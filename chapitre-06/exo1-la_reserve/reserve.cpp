#include <stdio.h>
#include <stdint.h>

#include <NKThreading/NkThread.h>
#include <NKThreading/NkThreadPool.h>
#include <NKTime/NkChrono.h>

using namespace nkentseu;
using namespace nkentseu::threading;

// PARAMETRES DE L'EXERCICE
#define NOMBRE_TACHES 200
#define NOMBRE_MESURES 3
#define TACHE_COURTE 1000
#define TACHE_LONGUE 100000

// STOCKAGE DES RESULTATS SANS CONTENEUR STL
static uint64_t resultatsReserve[NOMBRE_TACHES];
static uint64_t resultatsFils[NOMBRE_TACHES];

// CALCULE UNE SOMME POUR SIMULER LE TRAVAIL D'UNE TACHE
uint64_t CalculerSomme(uint64_t nombreAdditions)
{
    volatile uint64_t somme = 0;

    for (uint64_t i = 1; i <= nombreAdditions; ++i)
    {
        somme = somme + i;
    }

    return somme;
}

// ADDITIONNE LES RESULTATS POUR VERIFIER LES CALCULS
uint64_t TotalResultats(uint64_t* resultats)
{
    uint64_t total = 0;

    for (int i = 0; i < NOMBRE_TACHES; ++i)
    {
        total += resultats[i];
    }

    return total;
}

// MESURE LE TEMPS DU POOL DE THREADS
double MesurerReserve(uint64_t nombreAdditions)
{
    NkThreadPool reserve;
    NkChrono chrono;

    // INITIALISE LES RESULTATS
    for (int i = 0; i < NOMBRE_TACHES; ++i)
    {
        resultatsReserve[i] = 0;
    }

    // ENVOIE LES TACHES AU POOL
    for (int i = 0; i < NOMBRE_TACHES; ++i)
    {
        reserve.Enqueue([i, nombreAdditions]()
        {
            resultatsReserve[i] = CalculerSomme(nombreAdditions);
        });
    }

    // ATTEND LA FIN DE TOUTES LES TACHES
    reserve.Join();

    // RECUPERE LE TEMPS ECOULE EN MILLISECONDES
    double temps = chrono.Elapsed().ToMilliseconds();

    // VERIFIE QUE LES CALCULS ONT ETE EFFECTUES
    printf("    Verification reserve : %llu\n",
           (unsigned long long)TotalResultats(resultatsReserve));

    return temps;
}

// MESURE LE TEMPS DES THREADS CREES MANUELLEMENT
double MesurerFils(uint64_t nombreAdditions)
{
    NkThread fils[NOMBRE_TACHES];
    NkChrono chrono;

    // INITIALISE LES RESULTATS
    for (int i = 0; i < NOMBRE_TACHES; ++i)
    {
        resultatsFils[i] = 0;
    }

    // CREE UN THREAD POUR CHAQUE TACHE
    for (int i = 0; i < NOMBRE_TACHES; ++i)
    {
        fils[i] = NkThread([i, nombreAdditions](void*)
        {
            resultatsFils[i] = CalculerSomme(nombreAdditions);
        });
    }

    // ATTEND LA FIN DE TOUS LES THREADS
    for (int i = 0; i < NOMBRE_TACHES; ++i)
    {
        fils[i].Join();
    }

    // RECUPERE LE TEMPS ECOULE EN MILLISECONDES
    double temps = chrono.Elapsed().ToMilliseconds();

    // VERIFIE QUE LES CALCULS ONT ETE EFFECTUES
    printf("    Verification fils    : %llu\n",
           (unsigned long long)TotalResultats(resultatsFils));

    return temps;
}

int main()
{
    double tempsReserve[NOMBRE_MESURES];
    double tempsFils[NOMBRE_MESURES];

    printf("========================================\n");
    printf("       EXERCICE 1 : LA RESERVE\n");
    printf("========================================\n\n");

    printf("Tache : %d taches de %d additions\n",
           NOMBRE_TACHES, TACHE_COURTE);

    // PRECHAUFFE LES DEUX METHODES
    MesurerReserve(TACHE_COURTE);
    MesurerFils(TACHE_COURTE);

    // MESURE TROIS FOIS LE POOL
    printf("\nReserve :\n");

    for (int i = 0; i < NOMBRE_MESURES; ++i)
    {
        tempsReserve[i] = MesurerReserve(TACHE_COURTE);

        printf("  Mesure %d : %.3f ms\n",
               i + 1, tempsReserve[i]);
    }

    // MESURE TROIS FOIS LES THREADS MANUELS
    printf("\nFils :\n");

    for (int i = 0; i < NOMBRE_MESURES; ++i)
    {
        tempsFils[i] = MesurerFils(TACHE_COURTE);

        printf("  Mesure %d : %.3f ms\n",
               i + 1, tempsFils[i]);
    }

    // COMPARE LES DEUX METHODES AVEC DES TACHES LONGUES
    printf("\nTache longue : %d additions par tache\n",
           TACHE_LONGUE);

    double tempsReserveLong = MesurerReserve(TACHE_LONGUE);
    double tempsFilsLong = MesurerFils(TACHE_LONGUE);

    printf("  Reserve : %.3f ms\n", tempsReserveLong);
    printf("  Fils    : %.3f ms\n", tempsFilsLong);

    // AFFICHE LE NOMBRE DE THREADS DU POOL
    printf("\nOuvriers : ");

    NkThreadPool reserve;
    printf("%u\n", (unsigned int)reserve.GetNumWorkers());

    // EXPLIQUE LA DIFFERENCE ENTRE LES DEUX METHODES
    printf("\nPourquoi :\n");
    printf("Le pool reutilise un groupe de threads.\n");
    printf("Les threads manuels sont crees pour chaque tache.\n");
    printf("La creation de nombreux threads ajoute un cout.\n");
    printf("Pour les taches longues, le calcul prend plus de temps.\n");
    printf("Le cout de creation des threads pese alors moins.\n");

    printf("\n========================================\n");
    printf("             FIN DU TEST\n");
    printf("========================================\n");

    return 0;
}
#include <stdio.h>
#include <stdint.h>


#include <NKThreading/NkThreadPool.h>
#include <NKTime/NkChrono.h>
#include <NKThreading/NkThread.h>

using namespace nkentseu;
using namespace nkentseu::threading;

// PARAMETRES DE L'EXERCICE
#define NOMBRE_FILS 8
#define NOMBRE_INCREMENTATIONS 1000000

// COMPTEUR PARTAGE SANS PROTECTION
static uint64_t compteur = 0;

// EXECUTE LE TEST AVEC UN NOMBRE DE FILS DONNE
uint64_t ExecuterTest(int nombreFils)
{
    NkThread fils[NOMBRE_FILS];

    // REINITIALISE LE COMPTEUR
    compteur = 0;

    // CREE LES FILS AVEC UNE LAMBDA
    for (int i = 0; i < nombreFils; ++i)
    {
        fils[i] = NkThread([](void*)
        {
            for (uint64_t j = 0;
                 j < NOMBRE_INCREMENTATIONS;
                 ++j)
            {
                compteur += 1;
            }
        });
    }

    // ATTEND LA FIN DE TOUS LES FILS
    for (int i = 0; i < nombreFils; ++i)
    {
        fils[i].Join();
    }

    // RETOURNE LE TOTAL APRES LES JOINTURES
    return compteur;
}

int main()
{
    // CALCULE LE TOTAL ATTENDU POUR HUIT FILS
    uint64_t totalAttendu =
        (uint64_t)NOMBRE_FILS * NOMBRE_INCREMENTATIONS;

    printf("========================================\n");
    printf("       EXERCICE 2 : LA COURSE\n");
    printf("========================================\n\n");

    // TEST AVEC HUIT FILS
    uint64_t total = ExecuterTest(NOMBRE_FILS);

    printf("Test avec huit fils :\n");
    printf("Total obtenu : %llu\n",
           (unsigned long long)total);

    printf("Total attendu : %llu\n",
           (unsigned long long)totalAttendu);

    // TEST AVEC UN SEUL FIL
    uint64_t totalUnFil = ExecuterTest(1);

    printf("\nTest avec un seul fil :\n");
    printf("Total obtenu : %llu\n",
           (unsigned long long)totalUnFil);

    printf("Total attendu : %d\n",
           NOMBRE_INCREMENTATIONS);

    printf("\n========================================\n");
    printf("             FIN DU TEST\n");
    printf("========================================\n");

    return 0;
}
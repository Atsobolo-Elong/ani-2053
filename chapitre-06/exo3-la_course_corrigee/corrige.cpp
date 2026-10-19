#include <new>
#include <stdio.h>
#include <stdint.h>

#include <NKThreading/NkThread.h>
#include <NKThreading/NkMutex.h>
#include <NKThreading/NkScopedLock.h>
#include <NKCore/NkAtomic.h>
#include <NKTime/NkChrono.h>

using namespace nkentseu;
using namespace nkentseu::threading;

// ============================================================
// CONFIGURATION
// ============================================================

static const int NOMBRE_THREADS = 4;
static const int NOMBRE_ADDITIONS = 250000;
static const int NOMBRE_MESURES = 3;

typedef uint64_t Compteur;

// ============================================================
// STRUCTURE DES RESULTATS
// ============================================================

struct Resultat
{
    Compteur total;
    double tempsMs;
};

// ============================================================
// VARIANTE 1 : COMPTEUR PARTAGE SANS PROTECTION
// ============================================================

Resultat MesurerSansProtection()
{
    Compteur compteur = 0;
    NkThread fils[NOMBRE_THREADS];

    NkChrono chrono;

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i] = NkThread([&compteur](void*)
        {
            for (int j = 0; j < NOMBRE_ADDITIONS; ++j)
            {
                ++compteur;
            }
        });
    }

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i].Join();
    }

    Resultat resultat;
    resultat.total = compteur;
    resultat.tempsMs = chrono.Elapsed().ToMilliseconds();

    return resultat;
}

// ============================================================
// VARIANTE 2 : COMPTEUR PROTEGE PAR UN MUTEX
// ============================================================

Resultat MesurerMutex()
{
    Compteur compteur = 0;
    NkMutex mutexCompteur;
    NkThread fils[NOMBRE_THREADS];

    NkChrono chrono;

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i] = NkThread([&compteur, &mutexCompteur](void*)
        {
            for (int j = 0; j < NOMBRE_ADDITIONS; ++j)
            {
                nkentseu::threading::NkScopedLock<NkMutex> verrou(mutexCompteur);
                ++compteur;
            }
        });
    }

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i].Join();
    }

    Resultat resultat;
    resultat.total = compteur;
    resultat.tempsMs = chrono.Elapsed().ToMilliseconds();

    return resultat;
}

// ============================================================
// VARIANTE 3 : COMPTEUR ATOMIQUE
// ============================================================

Resultat MesurerAtomique()
{
    NkAtomicInt compteur(0);
    NkThread fils[NOMBRE_THREADS];

    NkChrono chrono;

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i] = NkThread([&compteur](void*)
        {
            for (int j = 0; j < NOMBRE_ADDITIONS; ++j)
            {
                compteur.FetchAdd(1);
            }
        });
    }

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i].Join();
    }

    Resultat resultat;
    resultat.total = static_cast<Compteur>(compteur);
    resultat.tempsMs = chrono.Elapsed().ToMilliseconds();

    return resultat;
}

// ============================================================
// VARIANTE 4 : COMPTEUR LOCAL A CHAQUE THREAD
// ============================================================

Resultat MesurerLocal()
{
    Compteur compteursLocaux[NOMBRE_THREADS] = {};
    NkThread fils[NOMBRE_THREADS];

    NkChrono chrono;

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i] = NkThread([&compteursLocaux, i](void*)
        {
            Compteur compteurLocal = 0;

            for (int j = 0; j < NOMBRE_ADDITIONS; ++j)
            {
                ++compteurLocal;
            }

            compteursLocaux[i] = compteurLocal;
        });
    }

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        fils[i].Join();
    }

    Compteur total = 0;

    for (int i = 0; i < NOMBRE_THREADS; ++i)
    {
        total += compteursLocaux[i];
    }

    Resultat resultat;
    resultat.total = total;
    resultat.tempsMs = chrono.Elapsed().ToMilliseconds();

    return resultat;
}

// ============================================================
// CALCUL DE LA MEDIANE DE TROIS VALEURS
// ============================================================

double Mediane(double a, double b, double c)
{
    if (a > b)
    {
        double temporaire = a;
        a = b;
        b = temporaire;
    }

    if (b > c)
    {
        double temporaire = b;
        b = c;
        c = temporaire;
    }

    if (a > b)
    {
        double temporaire = a;
        a = b;
        b = temporaire;
    }

    return b;
}

// ============================================================
// REALISER TROIS MESURES
// ============================================================

Resultat MesurerTroisFois(Resultat (*fonction)())
{
    Resultat mesures[NOMBRE_MESURES];

    for (int i = 0; i < NOMBRE_MESURES; ++i)
    {
        mesures[i] = fonction();
    }

    Resultat resultat;

    // LE TOTAL PROVIENT DE LA DERNIERE EXECUTION
    resultat.total = mesures[NOMBRE_MESURES - 1].total;

    // LE TEMPS RETENU EST LA MEDIANE DES TROIS MESURES
    resultat.tempsMs = Mediane(
        mesures[0].tempsMs,
        mesures[1].tempsMs,
        mesures[2].tempsMs
    );

    return resultat;
}

// ============================================================
// PROGRAMME PRINCIPAL
// ============================================================

int main()
{
    Resultat sansProtection = MesurerTroisFois(MesurerSansProtection);
    Resultat mutex = MesurerTroisFois(MesurerMutex);
    Resultat atomique = MesurerTroisFois(MesurerAtomique);
    Resultat local = MesurerTroisFois(MesurerLocal);

    printf("=== EXERCICE 3 : COMPARAISON DES COMPTEURS ===\n\n");

    printf("Sans protection :\n");
    printf("Total : %llu | Temps median : %.3f ms\n\n",
        static_cast<unsigned long long>(sansProtection.total),
        sansProtection.tempsMs);

    printf("Mutex :\n");
    printf("Total : %llu | Temps median : %.3f ms\n\n",
        static_cast<unsigned long long>(mutex.total),
        mutex.tempsMs);

    printf("Atomique :\n");
    printf("Total : %llu | Temps median : %.3f ms\n\n",
        static_cast<unsigned long long>(atomique.total),
        atomique.tempsMs);

    printf("Local :\n");
    printf("Total : %llu | Temps median : %.3f ms\n\n",
        static_cast<unsigned long long>(local.total),
        local.tempsMs);

    return 0;
}
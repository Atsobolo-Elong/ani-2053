#include <new> // NECESSAIRE POUR LE PLACEMENT NEW

#include <NKThreading/NkThread.h>
#include <NKThreading/NkMutex.h>
#include <NKThreading/NkScopedLock.h>
#include <NKTime/NkChrono.h>

#include <iostream>

using namespace nkentseu;
using namespace nkentseu::threading;

int main()
{
    NkMutex m1;
    NkMutex m2;

    // =========================================================
    // VERSION INITIALE : INTERBLOCAGE (DEADLOCK)
    // =========================================================
    // Pour reproduire le blocage, les deux threads doivent
    // acquerir les mutex dans des ordres opposes.
    //
    // Thread A : m1 puis m2
    // Thread B : m2 puis m1
    //
    // Chaque thread peut alors attendre indefiniment le mutex
    // que l'autre thread detient.

    /*
    NkThread a([&](void*)
    {
        nkentseu::threading::NkScopedLock<NkMutex> verrou1(m1);

        NkChrono::SleepMilliseconds(100);

        nkentseu::threading::NkScopedLock<NkMutex> verrou2(m2);

        std::cout << "Thread A : mutex acquis." << std::endl;
    });

    NkThread b([&](void*)
    {
        nkentseu::threading::NkScopedLock<NkMutex> verrou2(m2);

        NkChrono::SleepMilliseconds(100);

        nkentseu::threading::NkScopedLock<NkMutex> verrou1(m1);

        std::cout << "Thread B : mutex acquis." << std::endl;
    });

    a.Join();
    b.Join();
    */

    // =========================================================
    // VERSION CORRIGEE : ORDRE IDENTIQUE DES MUTEX
    // =========================================================
    // Les deux threads prennent toujours m1 puis m2.
    // Cela supprime le cycle d'attente responsable du deadlock.

    NkThread a([&](void*)
    {
        nkentseu::threading::NkScopedLock<NkMutex> verrou1(m1);

        std::cout << "Thread A : mutex m1 acquis." << std::endl;

        NkChrono::SleepMilliseconds(100);

        nkentseu::threading::NkScopedLock<NkMutex> verrou2(m2);

        std::cout << "Thread A : mutex m2 acquis." << std::endl;
    });

    NkThread b([&](void*)
    {
        nkentseu::threading::NkScopedLock<NkMutex> verrou1(m1);

        std::cout << "Thread B : mutex m1 acquis." << std::endl;

        NkChrono::SleepMilliseconds(100);

        nkentseu::threading::NkScopedLock<NkMutex> verrou2(m2);

        std::cout << "Thread B : mutex m2 acquis." << std::endl;
    });

    // ATTENDRE LA FIN DES DEUX THREADS
    a.Join();
    b.Join();

    std::cout << "Programme termine sans interblocage." << std::endl;

    return 0;
}
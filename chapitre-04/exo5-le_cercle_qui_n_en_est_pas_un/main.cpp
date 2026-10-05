#include <cmath>
#include <iostream>

/*
    ON MESURE L'ECART ENTRE LE CERCLE REEL ET SA CORDE.
    LE PROGRAMME RESTE ENTIEREMENT INDEPENDANT DE NKCANVAS.
*/

int main()
{
    const double PI = 3.14;

    int nombreCercles;
    std::cin >> nombreCercles;

    int visibles = 0;
    int refuses = 0;

    for (int i = 0; i < nombreCercles; ++i)
    {
        long long rayon;
        long long segments;

        std::cin >> rayon >> segments;

        // MOINS DE TROIS SEGMENTS NE PEUVENT PAS FORMER UN CERCLE.
        if (segments < 3)
        {
            std::cout << rayon << ' ' << segments << " REFUSE\n";
            ++refuses;
            continue;
        }

        // UN RAYON NUL DONNE UN ECART EXACTEMENT NUL.
        if (rayon == 0)
        {
            std::cout << rayon << ' ' << segments << " 0 JAMAIS\n";
            continue;
        }

        // LA FORMULE DONNE L'ECART MAXIMAL AU MILIEU D'UNE CORDE.
        const double angle = PI / static_cast<double>(segments);
        const double ecart = static_cast<double>(rayon) * (1.0 - std::cos(angle));

        // L'ECART EST DEMANDE EN MILLIEMES, ARRONDI VERS LE BAS.
        const long long ecartMilliemes = static_cast<long long>(std::floor(ecart * 1000.0));

        // LE ZOOM EST ARRONDI VERS LE HAUT.
        const long long zoom = static_cast<long long>(std::ceil(100.0 / ecart));

        const bool visible = zoom <= 100;

        std::cout << rayon << ' '<< segments << ' '<< ecartMilliemes << ' '<< zoom << ' '<< (visible ? "VISIBLE" : "INVISIBLE") << '\n';

        if (visible)
            ++visibles;
    }

    std::cout << "VISIBLES " << visibles << '\n';
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}
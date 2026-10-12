#include <iostream>
#include <string>
#include <vector>

// STRUCTURE POUR DECRIRE UN FORMAT D'IMAGE
struct FormatImage
{
    std::string nom;
    long long octetsParPixel;
    bool couleur;
    bool transparence;
    bool flottants;
};

// RECHERCHER UN FORMAT DANS LA TABLE DES SIX FORMATS
bool trouverFormat(const std::string& nom, FormatImage& resultat)
{
    // TABLE DES FORMATS AUTORISES
    const FormatImage formats[] =
    {
        {"GRAY8",     1,  false, false, false},
        {"GRAY_A16",  2,  false, true,  false},
        {"RGB24",     3,  true,  false, false},
        {"RGBA32",    4,  true,  true,  false},
        {"RGB96F",    12, true,  false, true},
        {"RGBA128F",  16, true,  true,  true}
    };

    // PARCOURIR LES FORMATS DISPONIBLES
    for (const FormatImage& format : formats)
    {
        if (format.nom == nom)
        {
            resultat = format;
            return true;
        }
    }

    return false;
}

// CALCULER LA MEMOIRE NECESSAIRE A UNE IMAGE
long long calculerMemoire(
    long long largeur,
    long long hauteur,
    long long octetsParPixel)
{
    return largeur * hauteur * octetsParPixel;
}

// DETERMINER LES PERTES LORS D'UNE CONVERSION
std::string determinerPertes(
    const FormatImage& source,
    const FormatImage& cible)
{
    std::string pertes;

    // VERIFIER LA PERTE DE TRANSPARENCE
    if (source.transparence && !cible.transparence)
    {
        pertes = "TRANSPARENCE";
    }

    // VERIFIER LA PERTE DE COULEUR
    if (source.couleur && !cible.couleur)
    {
        if (!pertes.empty())
        {
            pertes += "+";
        }

        pertes += "COULEUR";
    }

    // VERIFIER LA PERTE DE PRECISION DES FLOTTANTS
    if (source.flottants && !cible.flottants)
    {
        if (!pertes.empty())
        {
            pertes += "+";
        }

        pertes += "ETENDUE";
    }

    // AUCUNE CARACTERISTIQUE N'A ETE PERDUE
    if (pertes.empty())
    {
        return "AUCUNE";
    }

    return pertes;
}

int main()
{
    long long largeur;
    long long hauteur;
    int nombreConversions;

    // LIRE LES DIMENSIONS DE L'IMAGE
    if (!(std::cin >> largeur >> hauteur))
    {
        return 0;
    }

    // LIRE LE NOMBRE DE CONVERSIONS
    if (!(std::cin >> nombreConversions) || nombreConversions < 0)
    {
        return 0;
    }

    long long total = 0;
    int sansPerte = 0;
    int refuses = 0;

    // TRAITER CHAQUE CONVERSION DANS L'ORDRE DE LECTURE
    for (int i = 0; i < nombreConversions; ++i)
    {
        std::string nomSource;
        std::string nomCible;

        // LIRE LES DEUX FORMATS
        if (!(std::cin >> nomSource >> nomCible))
        {
            return 0;
        }

        FormatImage source;
        FormatImage cible;

        // VERIFIER QUE LES DEUX FORMATS SONT AUTORISES
        const bool sourceConnue =
            trouverFormat(nomSource, source);

        const bool cibleConnue =
            trouverFormat(nomCible, cible);

        // REFUSER LA CONVERSION SI UN FORMAT EST INCONNU
        if (!sourceConnue || !cibleConnue)
        {
            std::cout << nomSource << " "
                      << nomCible << " REFUSE\n";

            ++refuses;
            continue;
        }

        // CALCULER LA MEMOIRE DE LA SOURCE
        const long long octetsSource =
            calculerMemoire(
                largeur,
                hauteur,
                source.octetsParPixel);

        // CALCULER LA MEMOIRE DE LA CIBLE
        const long long octetsCible =
            calculerMemoire(
                largeur,
                hauteur,
                cible.octetsParPixel);

        // DETERMINER LES PERTES DE LA CONVERSION
        const std::string pertes =
            determinerPertes(source, cible);

        // AFFICHER LE RESULTAT DE LA CONVERSION
        std::cout << nomSource << " "
                  << nomCible << " "
                  << octetsSource << " "
                  << octetsCible << " "
                  << pertes << '\n';

        // AJOUTER LA MEMOIRE CIBLE AU TOTAL
        total += octetsCible;

        // COMPTER LES CONVERSIONS SANS PERTE
        if (pertes == "AUCUNE")
        {
            ++sansPerte;
        }
    }

    // AFFICHER LES BILANS
    std::cout << "TOTAL " << total << '\n';
    std::cout << "SANS_PERTE " << sansPerte << '\n';
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}
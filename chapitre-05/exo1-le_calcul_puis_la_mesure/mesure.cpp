#include <cstdio>
#include <cstdint>
#include <limits>

#include <NKImage/NKImage.h>

// STRUCTURE POUR DECRIRE UNE IMAGE A CHARGER
struct ImageInfo
{
    const char* nom;
    const char* chemin;
};

// CHARGE LES IMAGES ET AFFICHE LEURS INFORMATIONS
void chargerImages()
{
    // LISTE DES CINQ IMAGES A ANALYSER
    const ImageInfo images[] =
    {
        {"image_1.jpg", "C:/Users/missa/Nkentseu/Nkentseu/Applications/Pworkspace/HelloNKCanvas/src/images/image_1.jpg"},
        {"image_2.jpg", "C:/Users/missa/Nkentseu/Nkentseu/Applications/Pworkspace/HelloNKCanvas/src/images/image_2.jpg"},
        {"image_3.jpg", "C:/Users/missa/Nkentseu/Nkentseu/Applications/Pworkspace/HelloNKCanvas/src/images/image_3.jpg"},
        {"image_4.jpg", "C:/Users/missa/Nkentseu/Nkentseu/Applications/Pworkspace/HelloNKCanvas/src/images/image_4.jpg"},
        {"image_5.jpg", "C:/Users/missa/Nkentseu/Nkentseu/Applications/Pworkspace/HelloNKCanvas/src/images/image_5.jpg"}
    };

    // CALCUL DU NOMBRE D'IMAGES
    const std::size_t nombreImages =
        sizeof(images) / sizeof(images[0]);

    std::printf("========================================\n");
    std::printf(" ANALYSE DES IMAGES AVEC NKIMAGE\n");
    std::printf("========================================\n\n");

    // PARCOURIR ET ANALYSER CHAQUE IMAGE
    for (std::size_t i = 0; i < nombreImages; ++i)
    {
        // CREER UNE IMAGE QUI RESTERA EN VIE JUSQU'A LA FIN DU TOUR
        nkentseu::NkImage image;

        std::printf("----------------------------------------\n");
        std::printf("IMAGE %zu : %s\n", i + 1, images[i].nom);
        std::printf("----------------------------------------\n");

        // CHARGER L'IMAGE DEPUIS SON CHEMIN
        const bool chargementReussi = image.Load(images[i].chemin);

        // VERIFIER QUE LE CHARGEMENT A REUSSI
        if (!chargementReussi || !image.IsValid())
        {
            std::printf("[ERREUR] Impossible de charger : %s\n",
                        images[i].chemin);
            std::printf("Verifie le chemin et le fichier.\n\n");
            continue;
        }

        // RECUPERER LES CARACTERISTIQUES DE L'IMAGE
        const int largeur = image.Width();
        const int hauteur = image.Height();
        const int octetsParPixel = image.BytesPP();

        // VERIFIER QUE LES DIMENSIONS ET LE FORMAT SONT VALIDES
        if (largeur <= 0 || hauteur <= 0 || octetsParPixel <= 0)
        {
            std::printf("[ERREUR] Caracteristiques invalides.\n\n");
            continue;
        }

        // EVITER UN DEPASSEMENT LORS DU CALCUL
        const std::uint64_t largeur64 =
            static_cast<std::uint64_t>(largeur);

        const std::uint64_t hauteur64 =
            static_cast<std::uint64_t>(hauteur);

        const std::uint64_t octetsParPixel64 =
            static_cast<std::uint64_t>(octetsParPixel);

        if (largeur64 >
            std::numeric_limits<std::uint64_t>::max() / hauteur64)
        {
            std::printf("[ERREUR] Depassement pendant le calcul.\n\n");
            continue;
        }

        const std::uint64_t nombrePixels = largeur64 * hauteur64;

        if (nombrePixels >
            std::numeric_limits<std::uint64_t>::max() /
            octetsParPixel64)
        {
            std::printf("[ERREUR] Depassement pendant le calcul.\n\n");
            continue;
        }

        // CALCULER LA MEMOIRE THEORIQUE DES PIXELS
        const std::uint64_t memoireTheorique =
            nombrePixels * octetsParPixel64;

        // AFFICHER LES INFORMATIONS POUR LE COMPTE RENDU
        std::printf("Chemin              : %s\n", images[i].chemin);
        std::printf("Largeur             : %d pixels\n", largeur);
        std::printf("Hauteur             : %d pixels\n", hauteur);
        std::printf("Octets par pixel    : %d\n", octetsParPixel);
        std::printf("Nombre de pixels    : %llu\n",
                    static_cast<unsigned long long>(nombrePixels));
        std::printf("Calcul theorique    : %llu octets\n",
                    static_cast<unsigned long long>(memoireTheorique));

        // AFFICHER UNE CONVERSION APPROXIMATIVE EN MIO
        const double memoireMio =
            static_cast<double>(memoireTheorique) / (1024.0 * 1024.0);

        std::printf("Calcul theorique    : %.2f Mio\n", memoireMio);

        std::printf(
            "[INFO] L'image reste chargee jusqu'a la fin de ce tour.\n\n"
        );
    }

    std::printf("========================================\n");
    std::printf(" FIN DE L'ANALYSE\n");
    std::printf("========================================\n");
}

int main()
{
    // LANCER L'ANALYSE DES CINQ IMAGES
    chargerImages();

    return 0;
}
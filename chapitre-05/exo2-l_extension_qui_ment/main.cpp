#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cctype>

// CONVERTIR UN CARACTERE HEXADECIMAL EN VALEUR NUMERIQUE
int valeurHexa(char caractere)
{
    if (caractere >= '0' && caractere <= '9')
        return caractere - '0';

    if (caractere >= 'a' && caractere <= 'f')
        return caractere - 'a' + 10;

    if (caractere >= 'A' && caractere <= 'F')
        return caractere - 'A' + 10;

    return -1;
}

// DECODER LA CHAINE HEXADECIMALE EN OCTETS
std::vector<int> decoderHexa(const std::string& texte)
{
    std::vector<int> octets;

    // LE TIRET REPRESENTE UNE ABSENCE D'OCTETS
    if (texte == "-")
        return octets;

    // LIRE LES CARACTERES DEUX PAR DEUX
    for (std::size_t i = 0; i + 1 < texte.size(); i += 2)
    {
        const int chiffre1 = valeurHexa(texte[i]);
        const int chiffre2 = valeurHexa(texte[i + 1]);

        // IGNORER UNE PAIRE INVALIDE
        if (chiffre1 == -1 || chiffre2 == -1)
            return {};

        // RECONSTRUIRE L'OCTET ENTRE 0 ET 255
        octets.push_back(chiffre1 * 16 + chiffre2);
    }

    return octets;
}

// VERIFIER LA PRESENCE D'UNE SIGNATURE A UNE POSITION DONNEE
bool signatureEgale(
    const std::vector<int>& octets,
    std::size_t position,
    const std::vector<int>& signature)
{
    if (position + signature.size() > octets.size())
        return false;

    for (std::size_t i = 0; i < signature.size(); ++i)
    {
        if (octets[position + i] != signature[i])
            return false;
    }

    return true;
}

// RECONNAITRE LE FORMAT SELON L'ORDRE IMPOSE PAR L'ENONCE
std::string reconnaitreFormat(
    std::uint64_t taille,
    const std::vector<int>& octets)
{
    // REGLE 1 : UN FICHIER DE MOINS DE QUATRE OCTETS EST REFUSE
    if (taille < 4)
        return "";

    // REGLE 2 : PNG
    if (taille >= 8 &&
        signatureEgale(octets, 0, {0x89, 0x50, 0x4E, 0x47}))
        return "PNG";

    // REGLE 3 : JPEG
    if (signatureEgale(octets, 0, {0xFF, 0xD8, 0xFF}))
        return "JPEG";

    // REGLE 4 : BMP
    if (signatureEgale(octets, 0, {0x42, 0x4D}))
        return "BMP";

    // REGLE 5 : QOI
    if (signatureEgale(octets, 0, {0x71, 0x6F, 0x69, 0x66}))
        return "QOI";

    // REGLE 6 : GIF
    if (signatureEgale(octets, 0, {0x47, 0x49, 0x46, 0x38}))
        return "GIF";

    // REGLE 7 : ICO
    if (octets.size() >= 4 &&
        octets[0] == 0x00 &&
        octets[1] == 0x00 &&
        (octets[2] == 0x01 || octets[2] == 0x02) &&
        octets[3] == 0x00)
        return "ICO";

    // REGLE 8 : HDR
    if (taille >= 10 &&
        signatureEgale(octets, 0, {0x23, 0x3F}))
        return "HDR";

    // REGLE 9 : EXR
    if (signatureEgale(octets, 0, {0x76, 0x2F, 0x31, 0x01}))
        return "EXR";

    // REGLE 10 : PBM, PGM OU PPM
    if (octets.size() >= 2 &&
        octets[0] == 0x50 &&
        octets[1] >= 0x31 &&
        octets[1] <= 0x36)
    {
        switch (octets[1])
        {
            case 0x31:
            case 0x34:
                return "PBM";

            case 0x32:
            case 0x35:
                return "PGM";

            case 0x33:
            case 0x36:
                return "PPM";
        }
    }

    // REGLE 11 : TGA
    if (taille >= 18 && octets.size() >= 3)
    {
        const int type = octets[2];

        if (type == 0x00 ||
            type == 0x01 ||
            type == 0x02 ||
            type == 0x03 ||
            type == 0x09 ||
            type == 0x0A ||
            type == 0x0B)
        {
            return "TGA";
        }
    }

    // REGLE 12 : SVG
    std::size_t position = 0;

    // IGNORER LE BOM UTF-8 S'IL EST PRESENT AU DEBUT
    if (signatureEgale(octets, 0, {0xEF, 0xBB, 0xBF}))
        position = 3;

    // IGNORER LES ESPACES ET CARACTERES BLANCS AUTORISES
    while (position < octets.size())
    {
        const int octet = octets[position];

        if (octet == 0x20 ||
            octet == 0x09 ||
            octet == 0x0A ||
            octet == 0x0D)
        {
            ++position;
        }
        else
        {
            break;
        }
    }

    // RECONNAITRE LES DEUX DEBUTS SVG AUTORISES
    if (signatureEgale(
            octets, position,
            {0x3C, 0x3F, 0x78, 0x6D, 0x6C}))
        return "SVG";

    if (signatureEgale(
            octets, position,
            {0x3C, 0x73, 0x76, 0x67}))
        return "SVG";

    // AUCUNE SIGNATURE RECONNUE
    return "";
}

// EXTRAIRE L'EXTENSION APRES LE DERNIER POINT
std::string extraireExtension(const std::string& nom)
{
    const std::size_t position = nom.find_last_of('.');

    // SANS POINT, L'EXTENSION EST VIDE
    if (position == std::string::npos)
        return "";

    std::string extension = nom.substr(position + 1);

    // CONVERTIR L'EXTENSION EN MINUSCULES
    std::transform(
        extension.begin(),
        extension.end(),
        extension.begin(),
        [](unsigned char caractere)
        {
            return static_cast<char>(std::tolower(caractere));
        });

    return extension;
}

// VERIFIER SI L'EXTENSION CORRESPOND AU FORMAT RECONNU
bool extensionCorrecte(
    const std::string& format,
    const std::string& extension)
{
    if (format == "PNG")
        return extension == "png";

    if (format == "JPEG")
        return extension == "jpg" || extension == "jpeg";

    if (format == "BMP")
        return extension == "bmp";

    if (format == "QOI")
        return extension == "qoi";

    if (format == "GIF")
        return extension == "gif";

    if (format == "ICO")
        return extension == "ico" || extension == "cur";

    if (format == "HDR")
        return extension == "hdr";

    if (format == "EXR")
        return extension == "exr";

    if (format == "PBM")
        return extension == "pbm";

    if (format == "PGM")
        return extension == "pgm";

    if (format == "PPM")
        return extension == "ppm";

    if (format == "TGA")
        return extension == "tga";

    if (format == "SVG")
        return extension == "svg";

    return false;
}

int main()
{
    int nombreFichiers;

    // LIRE LE NOMBRE DE FICHIERS
    if (!(std::cin >> nombreFichiers) || nombreFichiers < 0)
        return 0;

    int lus = 0;
    int mensonges = 0;
    int refuses = 0;

    // TRAITER LES FICHIERS DANS L'ORDRE DE LECTURE
    for (int i = 0; i < nombreFichiers; ++i)
    {
        std::string nom;
        std::uint64_t taille;
        std::string texteHexa;

        if (!(std::cin >> nom >> taille >> texteHexa))
            return 0;

        // DECODER LES OCTETS FOURNIS
        const std::vector<int> octets = decoderHexa(texteHexa);

        // RECONNAITRE LE FORMAT DU FICHIER
        const std::string format = reconnaitreFormat(taille, octets);

        // REFUSER LE FICHIER SI AUCUN FORMAT N'EST RECONNU
        if (format.empty())
        {
            std::cout << nom << " REFUSE\n";
            ++refuses;
            continue;
        }

        // EXTRAIRE L'EXTENSION DU NOM
        const std::string extension = extraireExtension(nom);

        // COMPARER L'EXTENSION AU FORMAT RECONNU
        if (extensionCorrecte(format, extension))
        {
            std::cout << nom << " " << format << " OK\n";
        }
        else
        {
            std::cout << nom << " " << format << " MENT\n";
            ++mensonges;
        }

        // LE FICHIER EST RECONNU, MEME SI SON EXTENSION MENT
        ++lus;
    }

    // AFFICHER UNIQUEMENT LES TROIS COMPTEURS DEMANDES
    std::cout << "LUS " << lus << '\n';
    std::cout << "MENSONGES " << mensonges << '\n';
    std::cout << "REFUSES " << refuses << '\n';

    return 0;
}
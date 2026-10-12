#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Piste {
    string type;
    string code;
};

struct Fichier {
    string nom;
    vector<int> octets;
    vector<Piste> pistes;
};

// CONVERTIR UN GROUPE DE DEUX CHIFFRES HEXADECIMAUX EN OCTET
int convertirOctet(const string& texte, size_t position) {
    return stoi(texte.substr(position, 2), nullptr, 16);
}

// DECODER LA CHAINE HEXADECIMALE
vector<int> decoderHexa(const string& texte) {
    vector<int> octets;

    if (texte == "-") {
        return octets;
    }

    for (size_t i = 0; i + 1 < texte.size(); i += 2) {
        octets.push_back(convertirOctet(texte, i));
    }

    return octets;
}

// VERIFIER UNE SIGNATURE A UNE POSITION DONNEE
bool signatureEgale(
    const vector<int>& octets,
    size_t position,
    const vector<int>& signature
) {
    if (position + signature.size() > octets.size()) {
        return false;
    }

    for (size_t i = 0; i < signature.size(); i++) {
        if (octets[position + i] != signature[i]) {
            return false;
        }
    }

    return true;
}

// RECONNAITRE LE CONTENEUR A PARTIR DES OCTETS
string reconnaitreConteneur(const vector<int>& octets) {
    size_t n = octets.size();

    // RECONNAITRE MP4
    if (n >= 12 &&
        signatureEgale(octets, 4, {0x66, 0x74, 0x79, 0x70})) {
        return "MP4";
    }

    // RECONNAITRE WEBM
    if (n >= 4 &&
        signatureEgale(octets, 0, {0x1A, 0x45, 0xDF, 0xA3})) {
        return "WEBM";
    }

    // RECONNAITRE WAV
    if (n >= 12 &&
        signatureEgale(octets, 0, {0x52, 0x49, 0x46, 0x46}) &&
        signatureEgale(octets, 8, {0x57, 0x41, 0x56, 0x45})) {
        return "WAV";
    }

    // RECONNAITRE OGG
    if (n >= 4 &&
        signatureEgale(octets, 0, {0x4F, 0x67, 0x67, 0x53})) {
        return "OGG";
    }

    // RECONNAITRE FLAC
    if (n >= 4 &&
        signatureEgale(octets, 0, {0x66, 0x4C, 0x61, 0x43})) {
        return "FLAC";
    }

    // RECONNAITRE MP3 AVEC ID3
    if (n >= 3 &&
        signatureEgale(octets, 0, {0x49, 0x44, 0x33})) {
        return "MP3";
    }

    // RECONNAITRE MP3 AVEC UNE SIGNATURE DE TRAME
    if (n >= 2 &&
        octets[0] == 0xFF &&
        octets[1] >= 0xE0) {
        return "MP3";
    }

    return "INCONNU";
}

// CONVERTIR UN CODE DE PISTE EN NOM DE CODEC
string reconnaitreCodec(const string& code) {
    if (code == "mp4a") return "aac";

    if (code == "Opus" || code == "opus") return "opus";

    if (code == "avc1" || code == "avc3") return "h264";

    if (code == "hvc1" || code == "hev1") return "h265";

    if (code == "vp08") return "vp8";

    if (code == "vp09") return "vp9";

    if (code == "mp4v") return "mpeg4";

    if (code == ".mp3") return "mp3";

    if (code == "twos" || code == "sowt" || code == "lpcm") {
        return "pcm";
    }

    return code;
}

// VERIFIER SI LE CODE VIDEO EST PRIS EN CHARGE PAR LE LECTEUR
bool codecVideoLisible(const string& code) {
    return code == "mjpa" ||
           code == "jpeg" ||
           code == "MJPG" ||
           code == "avc1" ||
           code == "avc3" ||
           code == "hvc1" ||
           code == "hev1" ||
           code == "av01";
}

int main() {
    int N;
    cin >> N;

    int nombreMP4 = 0;
    int nombreLisibles = 0;
    int nombreInconnus = 0;

    for (int i = 0; i < N; i++) {
        Fichier fichier;
        string donneesHexa;
        int P;

        // LIRE LE NOM, LES OCTETS ET LE NOMBRE DE PISTES
        cin >> fichier.nom >> donneesHexa >> P;

        fichier.octets = decoderHexa(donneesHexa);

        // LIRE TOUTES LES PISTES, QUEL QUE SOIT LE CONTENEUR
        for (int j = 0; j < P; j++) {
            Piste piste;
            cin >> piste.type >> piste.code;
            fichier.pistes.push_back(piste);
        }

        // RECONNAITRE ET AFFICHER LE CONTENEUR
        string conteneur = reconnaitreConteneur(fichier.octets);

        cout << fichier.nom << ' ' << conteneur << '\n';

        if (conteneur == "INCONNU") {
            nombreInconnus++;
        }

        // IGNORER LES PISTES SI LE CONTENEUR N'EST PAS MP4
        if (conteneur != "MP4") {
            continue;
        }

        nombreMP4++;

        bool imageTrouvee = false;
        bool lecteurLisible = false;
        int numeroPiste = 0;

        // AFFICHER LES PISTES ET EXAMINER LA PREMIERE PISTE VIDEO
        for (const Piste& piste : fichier.pistes) {
            numeroPiste++;

            string typeAffiche;

            if (piste.type == "vide") {
                typeAffiche = "VIDEO";

                if (!imageTrouvee) {
                    imageTrouvee = true;
                    lecteurLisible = codecVideoLisible(piste.code);
                }
            } else {
                typeAffiche = "AUDIO";
            }

            cout << fichier.nom << " PISTE "
                 << numeroPiste << ' '
                 << typeAffiche << ' '
                 << reconnaitreCodec(piste.code) << '\n';
        }

        // AFFICHER LE VERDICT DU LECTEUR
        if (!imageTrouvee) {
            cout << fichier.nom << " LECTEUR SANS_IMAGE\n";
        } else if (lecteurLisible) {
            cout << fichier.nom << " LECTEUR LISIBLE\n";
            nombreLisibles++;
        } else {
            cout << fichier.nom << " LECTEUR ECHEC\n";
        }
    }

    // AFFICHER LES BILANS
    cout << "MP4 " << nombreMP4 << '\n';
    cout << "LISIBLES " << nombreLisibles << '\n';
    cout << "INCONNUS " << nombreInconnus << '\n';

    return 0;
}
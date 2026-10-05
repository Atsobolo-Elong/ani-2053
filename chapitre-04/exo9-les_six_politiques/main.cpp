#include <iostream>

using i64 = long long;

struct Zone
{
    i64 x;
    i64 y;
    i64 largeur;
    i64 hauteur;
    i64 mondeLargeur;
    i64 mondeHauteur;
};


  //  ARRONDIT A / B A L'ENTIER LE PLUS PROCHE.
   // UNE MOITIE MONTE.

i64 arrondi(i64 a, i64 b)
{
    return (2 * a + b) / (2 * b);
}


//    CALCULE LE VIEWPORT LETTERBOX ET LE MONDE DE REFERENCE.

Zone letterbox(i64 rw, i64 rh, i64 w, i64 h)
{
    Zone z{};

    z.mondeLargeur = rw;
    z.mondeHauteur = rh;

    if (w * rh <= h * rw)
    {
        z.largeur = w;
        z.hauteur = arrondi(rh * w, rw);
    }
    else
    {
        z.hauteur = h;
        z.largeur = arrondi(rw * h, rh);
    }

    z.x = (w - z.largeur) / 2;
    z.y = (h - z.hauteur) / 2;

    return z;
}


//    CALCULE LE MODE INTEGER_SCALE.

Zone integerScale(i64 rw, i64 rh, i64 w, i64 h)
{
    if (w < rw || h < rh)
        return letterbox(rw, rh, w, h);

    const i64 facteurHorizontal = w / rw;
    const i64 facteurVertical = h / rh;

    const i64 facteur = facteurHorizontal < facteurVertical ? facteurHorizontal : facteurVertical;

    if (facteur == 0)
        return letterbox(rw, rh, w, h);

    Zone z{};

    z.largeur = rw * facteur;
    z.hauteur = rh * facteur;
    z.x = (w - z.largeur) / 2;
    z.y = (h - z.hauteur) / 2;
    z.mondeLargeur = rw;
    z.mondeHauteur = rh;

    return z;
}


//    CALCULE LE MODE FIT_CROP.

Zone fitCrop(i64 rw, i64 rh, i64 w, i64 h)
{
    Zone z{};

    z.x = 0;
    z.y = 0;
    z.largeur = w;
    z.hauteur = h;

    if (w * rh > h * rw)
    {
        z.mondeLargeur = rw;
        z.mondeHauteur = arrondi(rw * h, w);
    }
    else
    {
        z.mondeLargeur = arrondi(rh * w, h);
        z.mondeHauteur = rh;
    }

    return z;
}


//    AFFICHE UNE POLITIQUE DANS LE FORMAT STRICT DEMANDE.

void afficher(const char* nom, const Zone& z)
{
    std::cout << nom << ' ' << z.x << ' '<< z.y << ' '<< z.largeur << ' ' << z.hauteur << ' '<< z.mondeLargeur << ' ' << z.mondeHauteur << '\n';
}

int main()
{
    i64 rw;
    i64 rh;
    i64 ancienneLargeur;
    i64 ancienneHauteur;
    i64 w;
    i64 h;

    std::cin >> rw >> rh>> ancienneLargeur>> ancienneHauteur>> w>> h;

    const bool referenceValide = rw != 0 && rh != 0;

    
    //    SANS REFERENCE, QUATRE POLITIQUES DEVIENNENT FOLLOW_WINDOW.
    
    Zone follow{0, 0, w, h, w, h};

    Zone stretch;
    Zone fit;
    Zone integer;
    Zone crop;
    Zone manual{
        0, 0,
        ancienneLargeur,
        ancienneHauteur,
        ancienneLargeur,
        ancienneHauteur
    };

    if (!referenceValide)
    {
        stretch = follow;
        fit = follow;
        integer = follow;
        crop = follow;
    }
    else
    {
        stretch = {
            0, 0,
            w, h,
            rw, rh
        };

        fit = letterbox(rw, rh, w, h);
        integer = integerScale(rw, rh, w, h);
        crop = fitCrop(rw, rh, w, h);
    }

    afficher("FOLLOW_WINDOW", follow);
    afficher("STRETCH", stretch);
    afficher("FIT_LETTERBOX", fit);
    afficher("INTEGER_SCALE", integer);
    afficher("FIT_CROP", crop);
    afficher("MANUAL", manual);

    
      //  UNE BANDE EXISTE SI LE VIEWPORT EST PLUS PETIT
    //    QUE LA FENETRE SUR AU MOINS UN AXE.
    
    int bandes = 0;

    const Zone politiques[] = {
        follow,
        stretch,
        fit,
        integer,
        crop,
        manual
    };

    for (const Zone& zone : politiques)
    {
        if (zone.largeur < w || zone.hauteur < h)
            ++bandes;
    }

    const bool deformation =
        referenceValide && (w * rh != h * rw);

    std::cout << "BANDES " << bandes << '\n';
    std::cout << "DEFORMATION "
              << (deformation ? "OUI" : "NON")
              << '\n';

    return 0;
}
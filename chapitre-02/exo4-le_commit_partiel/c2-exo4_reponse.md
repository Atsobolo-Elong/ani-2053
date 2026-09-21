# Exercice 4 — Le commit partiel

## Objectif

J'ai modifié deux choses sans rapport dans le même fichier
premier_fichier.txt, puis je les ai enregistrées dans deux commits
séparés avec git add -p.

## Préparation

J'ai d'abord préparé le fichier pour pouvoir avoir deux modifications
éloignées dans le même fichier.

Commande :

    git commit -m "Prépare le fichier pour l'exercice 4"

Le commit obtenu est :

    2d09c4a Prépare le fichier pour l'exercice 4

## Première modification

J'ai utilisé :

    git add -p premier_fichier.txt

Git a présenté deux hunks.

Pour le premier hunk, j'ai répondu :

    y

Pour le deuxième hunk, j'ai répondu :

    n

Ainsi, seule la première modification a été placée dans l'index.

La commande :

    git diff --cached

montrait uniquement :

    "premiere modification"

Tandis que :

    git diff

montrait uniquement :

    "deuxieme modification"

J'ai ensuite créé le premier commit :

    git commit -m "Ajout de la première modification"

Le commit obtenu est :

    09c0ef8 Ajout de la première modification

La commande :

    git show HEAD~1

a montré que ce commit contient uniquement la première modification.

## Deuxième modification

La deuxième modification était toujours présente dans le fichier
mais n'avait pas encore été ajoutée à l'index.

J'ai utilisé à nouveau :

    git add -p premier_fichier.txt

Cette fois, Git n'avait qu'un seul hunk à proposer. J'ai répondu :

    y

La commande :

    git diff --cached

montrait alors uniquement :

    "deuxieme modification"

La commande :

    git diff

ne montrait plus de modification.

J'ai ensuite créé le deuxième commit :

    git commit -m "Ajout de la deuxième modification"

Le commit obtenu est :

    b70283d Ajout de la deuxième modification

La commande :

    git show HEAD

a montré que ce commit contient uniquement la deuxième modification.

## Vérification de l'historique

La commande :

    git log --oneline -3

a donné :

    b70283d (HEAD -> main) Ajout de la deuxième modification
    09c0ef8 Ajout de la première modification
    2d09c4a Prépare le fichier pour l'exercice 4

Les deux modifications du même fichier sont donc bien présentes dans
deux commits séparés.

## Conclusion

git add -p m'a permis de sélectionner une partie des modifications
d'un même fichier pour le premier commit, puis de sélectionner la
modification restante pour le deuxième commit.

La vérification avec git show HEAD et git show HEAD~1 confirme que
chaque commit contient uniquement son propre sujet.
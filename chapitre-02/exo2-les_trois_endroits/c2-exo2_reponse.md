# Exercice 2 — Les trois endroits

## .  reponse
1. apres la modification
Commande :

```
git status
```
Résultat :
```
On branch main
Your branch is based on 'origin/main', but the upstream is gone.

Changes not staged for commit:
    modified: premier_fichier.txt

no changes added to commit
```
ici le fichier est modifie dans le rpertoire de travail.
La modification n’est pas encore dans l’index.

2. Après git add

Commandes :
```
git add premier_fichier.txt
git status
```
Résultat :
```
On branch main
Your branch is based on 'origin/main', but the upstream is gone.

Changes to be committed:
    modified: premier_fichier.txt
```

maintenant la modification est dans l’index (stage).
Elle est prête à être enregistree dans le prochain commit.

3. Après git commit

Commandes :
```
git commit -m "Modification du premier fichier"
git status
```
Résultat :
```
On branch main
Your branch is based on 'origin/main', but the upstream is gone.

nothing to commit, working tree clean
```
ici la modification est enregistrée dans le dépôt
dans un commit.

### Ce qui change

Après la modification, Git indique que le fichier est modifié
mais non indexé : il se trouve dans le répertoire de travail.
Après git add, Git indique que la modification est prête
à être commitée : elle se trouve dans l’index (stage).
Après git commit, Git indique que le répertoire de travail
est propre : la modification est maintenant enregistrée
dans le dépôt.

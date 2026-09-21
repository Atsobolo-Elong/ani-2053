# Exercice 6 — Le conflit provoqué

## Objectif


## 1. État initial

Dans le répertoire de travail utilisé pour la première série de commandes,ar l’exercice.indiquait que premier_fichier.txt avait été modifié.

Une autre différence était présente sous la forme d'un fichier non suivi :

```
text
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        premier_fichier1.txt
no changes added to commit (use "git add" and/or "git commit -a")
```
Le fichier premier_fichier1.txt était donc présent dans le répertoire de travail mais n’a pas été ajouté au commit.




2. Commit de résolution
Le fichier premier_fichier.txt a ensuite été ajouté à l’index :
```
git add premier_fichier.txt
```
Puis un commit a été créé :
```
git commit -m "Résout le conflit sur premier_fichier.txt"
```
Git a affiché :
```
[main d0aff34] Résout le conflit sur premier_fichier.txt
 1 file changed, 2 insertions(+), 1 deletion(-)
Le commit créé est donc :
d0aff34 Résout le conflit sur premier_fichier.txt
```


3. Vérification de l’état du dépôt
Après le commit :
```
git status
```
a affiché :
```
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        premier_fichier1.txt

nothing added to commit but untracked files present (use "git add" to track)
```
Le commit d0aff34 était donc uniquement présent localement à ce moment-là et devait encore être poussé vers le dépôt distant.
Le fichier premier_fichier1.txt restait non suivi et n’a pas été inclus dans le commit.



4. Historique Git
La commande :
```
git log --oneline --graph --all
```
a donné :
```
* d0aff34 (HEAD -> main) Résout le conflit sur premier_fichier.txt
* 7c1c75d (origin/main, origin/HEAD) Modification depuis le clone B
| * 8050cf4 (exo5-mesure) Modification depuis le clone A
| * c64077b Ajout de la troisième modification
| * dd7ff70 Ajout de la deuxième modification
| * 9d0f566 Ajout de la première modification
|/
* b70283d Ajout de la deuxième modification
* 09c0ef8 Ajout de la première modification
* 2d09c4a Prépare le fichier pour l'exercice 4
* bdc442b Modification du premier fichier
* 69f376e ajout du troisieme fichier
* dbba191 ajout du deuxieme fichier
* 43cd19b ajout du premier fichier
```
Cet historique montre que d0aff34 est placé directement après 7c1c75d.
La branche exo5-mesure possède une autre partie de l’historique, mais elle correspond à l’exercice 5 et ne constitue pas le conflit de l’exercice 6.



5. Modification depuis l’autre répertoire de travailDans l’autre répertoire de travail, le dépôt était initialement propre :
```
git status
```
Résultat :
```
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```
Le fichier premier_fichier.txt a ensuite été modifié.
La commande :
```
git diff
```
a affiché notamment :
```
diff --git a/premier_fichier.txt b/premier_fichier.txt
index e47a88f..5090612 100644
--- a/premier_fichier.txt
+++ b/premier_fichier.txt
@@ -1,6 +1,7 @@
 "premier fichier"
 ```
Le fichier a ensuite été ajouté et commité :
```
git add premier_fichier.txt
git commit -m "Modification depuis le clone B"
```
Git a créé :
```
[main 7c1c75d] Modification depuis le clone B
 1 file changed, 2 insertions(+), 1 deletion(-)
```


6. Push de la modification
Le commit 7c1c75d a ensuite été poussé vers GitHub :
```
git push
```
Résultat :
```
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 8 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 341 bytes | 341.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 2), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/Atsobolo-Elong/essai_chap_2
   b70283d..7c1c75d  main -> main
```
Le push a donc réussi.


7. Vérification avec git pull
Après le push, la commande :
```
git pull
```
a donné :
```
Already up to date.
```
Puis :
```
git status
```
a donné :
```
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```
Cela signifie qu’à ce moment-là le dépôt local et le dépôt distant étaient synchronisés.


8. Analyse du scénario obtenu
Les résultats obtenus montrent bien plusieurs éléments importants du fonctionnement de Git :
une modification de premier_fichier.txt a été commitée ;
le commit 7c1c75d a été poussé vers le dépôt distant ;
le dépôt a ensuite été synchronisé avec git pull ;
le commit d0aff34 a ensuite été créé localement ;
le fichier premier_fichier1.txt est resté non suivi.
Cependant, l’historique obtenu ne montre pas de véritable conflit Git au sens d’une fusion de deux historiques divergents.
En particulier, l’historique :
```
* d0aff34 (HEAD -> main) Résout le conflit sur premier_fichier.txt
* 7c1c75d (origin/main, origin/HEAD) Modification depuis le clone B
```
est linéaire.
De même, la commande :
```
git pull
```
a répondu :
```
Already up to date.
```
et aucun message CONFLICT ou Automatic merge failed n’apparaît dans les sorties fournies.
Le scénario obtenu ne permet donc pas de démontrer, avec les sorties disponibles, les trois étapes centrales demandées par l’exercice :
le refus d’un git push ;
le conflit provoqué par git pull ou la fusion ;
la résolution effective d’un conflit Git.
Le commit nommé :
```
Résout le conflit sur premier_fichier.txt
```
indique une intention de résolution, mais son nom seul ne permet pas de prouver qu’un conflit Git était vraiment présent mince.
en conclusion
Les commandes montrent correctement la création et la publication de commits ainsi que l’utilisation de git status, git diff, git add, git commit, git push, git pull et git log --oneline --graph --all.
Cependant, les sorties conservées ne montrent pas un conflit Git complet malheureusement pour moi🥲😓. Pour satisfaire exactement l’énoncé.
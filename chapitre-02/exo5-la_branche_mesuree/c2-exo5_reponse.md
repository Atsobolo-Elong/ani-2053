# Exercice 5 — La branche mesurée

## 1. État initial du dépôt

La commande suivante permet de vérifier l’état du dépôt avant de commencer :

```
git status
Résultat :
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        premier_fichier1.txt

nothing added to commit but untracked files present (use "git add" to track)
```
Le dépôt est sur la branche main et celle-ci est à jour avec origin/main.
Le fichier premier_fichier1.txt est présent dans le répertoire de travail mais n’est pas suivi par Git. Il n’est donc pas pris en compte dans les commits.




2. Création de la branche
La commande suivante permet de créer une nouvelle branche et de se placer directement dessus :
```
git switch -c exo5-mesure
```
Résultat :
```
Switched to a new branch 'exo5-mesure'
```
J’ai ensuite vérifié les branches avec :
```
git branch
```
Résultat :
```
* exo5-mesure
  main
```
La branche exo5-mesure a donc été créée à partir de main. Elle permet de réaliser les trois nouveaux commits sans modifier directement la branche main.


3. Premier commit sur la branche
J’ai créé et modifié le fichier mesure.txt, puis je l’ai ajouté à l’index avec :
```
git add mesure.txt
```
J’ai ensuite créé le premier commit :
```
git commit -m "Ajout de la première modification"
```
Résultat :
```
[exo5-mesure 9d0f566] Ajout de la première modification
 1 file changed, 1 insertion(+)
 create mode 100644 mesure.txt
Le premier commit est donc :
9d0f566 Ajout de la première modification
```



4. Deuxième commit sur la branche
J’ai ensuite modifié à nouveau mesure.txt, puis exécuté :
```
git add mesure.txt
git commit -m "Ajout de la deuxième 
modification"
```
Résultat :
```[exo5-mesure dd7ff70] Ajout de la deuxième modification
 1 file changed, 1 insertion(+)
Le deuxième commit est donc :
dd7ff70 Ajout de la deuxième modification
```



5. Troisième commit sur la branche
J’ai enfin modifié une troisième fois mesure.txt, puis exécuté :
```
git add mesure.txt
git commit -m "Ajout de la troisième modification"
```
Résultat :
```
[exo5-mesure c64077b] Ajout de la troisième modification
 1 file changed, 2 insertions(+), 1 deletion(-)
Le troisième commit est donc :
c64077b Ajout de la troisième modification
```


6. Vérification de l’historique
Pour vérifier les trois commits et leur position dans l’historique, j’ai utilisé :
```
git log --oneline --graph --all -5
```
Résultat :
```
* c64077b (HEAD -> exo5-mesure) Ajout de la troisième modification
* dd7ff70 Ajout de la deuxième modification
* 9d0f566 Ajout de la première modification
* b70283d (origin/main, main) Ajout de la deuxième modification
* 09c0ef8 Ajout de la première modification
```
Cet historique montre que les trois nouveaux commits appartiennent à la branche exo5-mesure.
La branche main reste sur le commit :
```
b70283d Ajout de la deuxième modification
```
La branche exo5-mesure possède donc trois commits supplémentaires :
```
9d0f566 → dd7ff70 → c64077b
```


7. Mesure de l’espace occupé après les commits
Après les trois commits, j’ai mesuré la taille du dossier .git avec :
```
$tailleApres = (Get-ChildItem .git -Recurse -File | Measure-Object -Property Length -Sum).Sum
"{0:N2} Mo" -f ($tailleApres / 1MB)
```
Résultat :
```
0,03 Mo
```
Le dossier .git occupe donc environ 0,03 Mo après les trois commits.
J’ai ensuite calculé la différence entre la taille après les commits et la taille avant les commits :
```
$tailleApres - $tailleAvant
```
Résultat :
```
34758
```
L’augmentation est donc de 34 758 octets.
Convertie en mégaoctets :
```
"{0:N2} Mo" -f (($tailleApres - $tailleAvant) / 1MB)
```
Résultat :
```
0,03 Mo
```


8. Observation des objets 
 J’ai également utilisé :
```
git count-objects -v
```
Résultat :
```
count: 31
size: 3
in-pack: 0
packs: 0
size-pack: 0
prune-packable: 0
garbage: 0
size-garbage: 0
```
La commande indique notamment que Git possède actuellement 31 objets non empaquetés (count: 31).



9. Explication du résultat
La création de la branche exo5-mesure ne crée pas une copie complète du dépôt. Une branche est une référence vers un commit.
Les trois commits réalisés sur exo5-mesure ont alors créé de nouvelles données dans le dépôt Git. Cela explique pourquoi la taille du dossier .git a augmenté.
La mesure effectuée montre une augmentation de :
```
34 758 octets
```
soit environ :
```
0,03 Mo
```
Cette augmentation ne signifie pas que Git a créé trois copies complètes du projet.
Git conserve les informations nécessaires pour représenter les nouveaux états du projet et réutilise les données déjà présentes lorsque cela est possible. Les trois commits ajoutent donc des objets à l’historique, mais la branche elle-même reste une référence légère.
# Exercice 2

pour chaque touche pressée, nous avons la lettre produite ainsi que le code correspondant à sa position physique.

Une deuxième expérience consiste à changer la disposition du clavier dans le système, puis à refaire les mêmes manipulations afin d’observer ce qui change.

1. Première configuration


Résultats observés
```
Lettre : q | Code physique converti : 41 | Code physique non converti : 41
Lettre : w | Code physique converti : 42 | Code physique non converti : 42
Lettre : e | Code physique converti : 43 | Code physique non converti : 43
Lettre : r | Code physique converti : 44 | Code physique non converti : 44
Lettre : t | Code physique converti : 45 | Code physique non converti : 45
Lettre : y | Code physique converti : 46 | Code physique non converti : 46

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (6.11s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
Le programme s’est terminé normalement après ce premier test.

2. Deuxième configuration

La disposition du clavier a ensuite été changée dans le système. Le programme a été relancé et les mêmes positions physiques ont été testées.

Résultats observés
 du clavier dans le système, puis à refaire les mêmes manipulations afin d’observer ce qui change.

1. Première configuration

Résultats observés

```
Lettre : a | Code physique converti : 41 | Code physique non converti : 41
Lettre : z | Code physique converti : 42 | Code physique non converti : 42
Lettre : e | Code physique converti : 43 | Code physique non converti : 43
Lettre : r | Code physique converti : 44 | Code physique non converti : 44
Lettre : t | Code physique converti : 45 | Code physique non converti : 45
Lettre : y | Code physique converti : 46 | Code physique non converti : 46

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (6.33s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
Le programme s’est également terminé normalement après ce deuxième test.

3. Comparaison des deux configurations

|Position testée|Première configuration|Deuxième configuration|Code physique|
|---------------|----------------------|----------------------|------------:|
|1              |q                     |a                     |41           |
|2              |w                     |z                     |42           |
|3              |e                     |e                     |43           |
|4              |r                     |r                     |44           |
|5              |t                     |t                     |45           |
|6              |y                     |y                     |46           |

4. Observation

Le changement de disposition du clavier a modifié les lettres produites pour certaines positions physiques.

Cela montre, dans les résultats obtenus, que le changement de disposition peut modifier la lettre produite alors que le code associé à la position physique reste le même.

5. Conversion du code

Pour chaque touche testée, le terminal affiche également :
```
 .le code physique converti ;
 . le code physique non converti.
```
Dans les résultats obtenus, les deux valeurs sont identiques pour chaque touche :
41 = 41
42 = 42
43 = 43
44 = 44
45 = 45
46 = 46

La conversion utilisée dans le programme ne change donc pas la valeur numérique affichée dans ces essais.

## Conclusion

L’expérience réalisée montre une différence entre la lettre produite par le clavier et le code utilisé pour représenter la position physique de la touche.

Après changement de disposition :
```
 . les lettres produites peuvent changer ;
 . les codes physiques observés restent identiques pour les positions testées.
```
Les résultats présentés dans ce document correspondent aux deux essais réellement effectués dans le terminal.
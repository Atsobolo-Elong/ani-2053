# C1-EXO2 - Comptage des fichiers source

## Mesures effectuées
- Fichiers .cpp : 1465
- Fichiers .hpp : 2483
- Fichiers .c : 60
- Fichiers .h : 311
- Total : ~4319 fichiers source
- Lignes utiles (sans vides / sans // / sans /* ) : 1 592 986 lignes

Commandes :
```powershell
(Get-ChildItem -Path . -Filter *.cpp -Recurse).Count
(Get-ChildItem -Path . -Filter *.hpp -Recurse).Count
(Get-ChildItem -Path . -Filter *.h -Recurse).Count


on constate une difference avec les chiffres du chapitre 1, nous pensons aue cela est du aux workspace supplementaitres crees par nous "l'individu ayant cloner le repos de Nkentseu", en plus de des fichiers .hpp et .c, sans oublier les test/**.cpp
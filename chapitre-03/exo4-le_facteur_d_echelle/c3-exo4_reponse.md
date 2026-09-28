# Chapitre 03 — Exercice 4


## Montage réalisé

Le programme crée une véritable fenêtre NkWindow, puis une véritable cible de rendu NkRenderWindow associée à cette fenêtre.
La fenêtre est demandée avec :
```
800 x 600
```
Le programme affiche les mesures dès le démarrage et à chaque redimensionnement.
Le point essentiel de la correction est que le facteur d’échelle n’est pas calculé comme le rapport de deux tailles.
Il est demandé directement à la fenêtre avec :
```
const float dpiScale = window.GetDpiScale();
```
C’est cette valeur qui constitue la mesure du facteur d’échelle.



## Pourquoi mon premier calcul était incorrect : 🥲

Dans ma première version, je faisais :
```
float scaleX = renderSize.x / windowWidth;
float scaleY = renderSize.y / windowHeight;
```
Ce calcul ne mesure pas le DPI.
Les deux dimensions utilisées provenaient du même état de la fenêtre et de la cible de rendu. Dans cette situation, le rapport pouvait donc être égal à 1, sans démontrer quoi que ce soit sur le facteur d’échelle du système.
La correction consiste donc à supprimer ce calcul et à utiliser directement :
```
window.GetDpiScale()
```



## Résultat de référence de ma première exécution

Lors de la première version, le programme affichait :
```
Fenetre       : 794 x 583
Cible de rendu: 794 x 583
Facteur       : 1.000000 x 1.000000
```
Ce résultat ne permettait pas de conclure que le facteur DPI était toujours égal à 1.
La nouvelle version ne fait plus cette conclusion à partir d’un rapport entre deux tailles.


## Ce que je dois vérifier avec la version corrigée

Réglage Windows initial :
```
Fenetre (zone cliente) : 794 x 583
Cible de rendu         : 794 x 583
Facteur d'echelle DPI  : 1.50
```

Après modification de l’échelle Windows :
```
Fenetre (zone cliente) : 792 x 575
Cible de rendu         : 792 x 575
Facteur d'echelle DPI  : 1.75
```

## Interprétation des dimensions

Il faut distinguer les différentes zones de la fenêtre.

La zone cliente est la partie utilisable par l’application pour son contenu. La fenêtre native possède également une zone non cliente, qui comprend notamment la barre de titre et les bordures/décorations gérées par Windows.

C’est pourquoi une taille demandée à la création comme :
```
800 x 600
```
peut être associée à une zone cliente réellement mesurée différemment.
Cette différence ne doit pas être confondue avec le facteur DPI.
Le facteur DPI est obtenu directement avec :
```
window.GetDpiScale()
```

alors que la différence entre les zones de la fenêtre concerne la géométrie de la fenêtre native.



## Pourquoi GetDpiScale() est la bonne mesure

Le facteur d’échelle est une information liée au réglage d’affichage du système.

Il ne faut donc pas le reconstruire artificiellement à partir de deux dimensions qui peuvent avoir des significations différentes.🥲




## Journal moteur de la première exécution

Le journal de ma première exécution indiquait notamment :
``
[NkOpenGL][DBG] surface valid=1 794x583
[NkOpenGL] WGL OK (GL 4.6 Core)
[NkOpenGL] Ready - Intel(R) UHD Graphics 620
```

Puis le programme affichait :
```
Fenetre : 794 x 583
Cible de rendu : 794.000000 x 583.000000
Facteur :1.000000 x 1.000000
``

Ce journal confirme les dimensions observées lors de cette exécution, mais il ne permet pas à lui seul de déterminer le facteur DPI.



## Limite de la première version et correction

La première version n’affichait les mesures qu’après réception d’un événement de redimensionnement.
La version corrigée effectue également une mesure au démarrage, puis une nouvelle mesure après chaque redimensionnement.



## Conclusion

La correction principale est d’abandonner le calcul :
```
renderSize / windowSize
```

comme prétendu facteur DPI.
```
Le programme utilise maintenant directement :
```
window.GetDpiScale()
```


La différence observée entre la taille demandée à la fenêtre et la zone cliente doit, elle, être analysée séparément : elle concerne la géométrie de la fenêtre native, notamment la distinction entre zone cliente et zone non cliente, et ne constitue pas une mesure du DPI.
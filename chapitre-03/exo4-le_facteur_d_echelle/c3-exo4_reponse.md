# Exercice 4

Le guide NKWindow fournit notamment la méthode GetDpiScale() pour obtenir le facteur d’échelle associé à la fenêtre. Le guide NKCanvas indique également que la cible de rendu travaille avec les dimensions nécessaires au rendu en pixels physiques.


Dans le programme, j’ai créé une fenêtre avec les dimensions initiales :
```
 . largeur : 800
 . hauteur : 600
```

J’ai ensuite créé une NkRenderWindow à partir de cette fenêtre et affiché les valeurs obtenues pendant l’exécution.

Le programme utilise directement :
```
float dpiScale = window.GetDpiScale();
```

plutôt que de déduire le facteur uniquement à partir du rapport entre deux tailles. (ce que j'ai fais avant 🤣)

# Résultat obtenu

Le terminal affiche finalement :
```
Fenetre       : 794 x 583
Cible de rendu: 794.000000 x 583.000000
Facteur       : 1.000000 x 1.000000
```

Le log de création du contexte confirme également :
surface valid=1 794x583

Le programme se termine normalement :
FIN D'EXECUTION — termine normalement (8.43s)

# Tableau des résultats

|Élément                             |Valeur     |
|------------------------------------|----------:|
|Taille demandée à la création       |`800 x 600`|
|Taille effectivement observée       |`794 x 583`|
|Taille de la cible de rendu         |`794 x 583`|
|Facteur retourné par `GetDpiScale()`|`1.0 x 1.0`|

# Mon Analyse

Le résultat 1.0 x 1.0 est cohérent avec ce que le programme rapporte, mais il ne signifie pas que la taille demandée à la création de la fenêtre est exactement celle de la surface rendue.

J’ai demandé :
```
800 x 600
```
mais la surface effectivement créée est :
```
794 x 583
```
Il existe donc une différence de :
```

 . largeur : 800 - 794 = 6 pixels
 . hauteur : 600 - 583 = 17 pixels
```
On peut donc constater que la taille réellement utilisable pour le rendu n’est pas exactement la taille initialement renseignée dans NkWindowConfig.

# Interprétation avec la documentation

Le point important à vérifier dans la documentation est que la taille de la fenêtre et la taille utilisée pour le rendu ne sont pas nécessairement identiques.

Une fenêtre native possède une structure système autour de sa zone de rendu. En particulier, la barre de titre et les éléments de décoration de la fenêtre occupent de l’espace.

Cela permet d’expliquer pourquoi une fenêtre configurée avec :
800 x 600

peut aboutir à une surface effectivement observée de :
794 x 583

La différence observée est donc réelle dans cette exécution.

# Calcul du rapport à partir des dimensions initiales

Si l’on reprend les dimensions demandées à la création (800 x 600) et les dimensions effectivement obtenues (794 x 583), on peut calculer les rapports :

Largeur :
```
794 / 800 = 0,9925
```

Hauteur :
```
583 / 600 = 0,9716
```

Ces rapports ne correspondent pas au facteur DPI retourné par GetDpiScale().

Ils mesurent simplement la différence entre la taille demandée à la création de la fenêtre et la taille effectivement obtenue pour cette exécution.🥲

Ce que montre réellement l’expérience

Il faut donc distinguer deux choses :

 1. Le facteur d’échelle DPI de la fenêtre, obtenu avec :
window.GetDpiScale()

 2. La différence entre la taille demandée à la création et la taille réelle de la surface, qui donne ici :
800 x 600  →  794 x 583

# Rendu du terminale :

```
[2026-09-25 16:04:05.983] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 16:04:05.985] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 16:04:05.986] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=0000023805dcf758 ? 8   ?8  
[2026-09-25 16:04:05.987] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 16:04:05.987] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 16:04:05.987] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 16:04:05.988] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 16:04:05.988] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 794x583
[2026-09-25 16:04:06.090] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 16:04:06.091] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 16:04:06.091] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 16:04:06.092] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 16:04:06.092] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-25 16:04:06.120] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=000000dae8   ??  -> id=1
[2026-09-25 16:04:06.121] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 16:04:06.123] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL

 
 Fenetre : 794  x  583
 Cible de rendu : 794.000000  x  583.000000  
 Facteur : 1.000000  x  1.000000 
 [2026-09-25 16:04:14.031] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 16:04:14.069] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (8.43s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```


# Conclusion

Sur ma machine, NkWindow::GetDpiScale() retourne :
1.0 malheureusement

et la modification du réglage de mise à l’échelle du système n’a pas permis d’obtenir une autre valeur. (initialement à 150, je l'ai passé à 175 puis à 125 et meme à 225)

En revanche, l’expérience met en évidence un autre point important : une fenêtre demandée en 800 x 600 ne produit pas ici une surface de rendu de 800 x 600. Le terminal rapporte 794 x 583.
Le résultat obtenu permet donc de vérifier expérimentalement que la taille demandée à la fenêtre et la taille effectivement utilisée pour le rendu peuvent être différentes, tandis que le facteur DPI proprement dit reste 1.0 dans cette configuration.

Cette distinction est importante pour comprendre le fonctionnement de NkWindow et de NkRenderWindow à mon avis.
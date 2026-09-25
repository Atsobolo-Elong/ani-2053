# Exercice 3


Le programme utilise NkWindowConfig et les propriétés minWidth et minHeight.


Le programme crée successivement deux fenêtres.

## Premier test

La première fenêtre est créée avec :
```
cfg.width = 800;
cfg.height = 600;
cfg.minWidth = 400;
cfg.minHeight = 350;
```

J’ai ensuite réduit progressivement la fenêtre à l’aide de la souris, tout en affichant dans le terminal chaque nouvelle dimension reçue par NkWindowResizeEvent.

Le programme utilise NkWindowConfig et les propriétés minWidth et minHeight.

La valeur 400 x 350 est finalement répétée plusieurs fois, ce qui montre que la fenêtre ne continue plus à se réduire lorsque cette limite est atteinte.

Résultat du premier test
```
 . Taille initiale : 800 x 600
 . Largeur minimale configurée : 400
 . Hauteur minimale configurée : 350
 . Plus petite taille observée : 400 x 350
```
` Le système a donc respecté les deux bornes configurées.`

## Deuxième test

Pour le deuxième test, j’ai utilisé :
```
cfg.width = 800;
cfg.height = 600;
cfg.minWidth = 500;
cfg.minHeight = 450;
```

J’ai à nouveau réduit progressivement la fenêtre.

Le terminal indique notamment :
```
Nouvelle taille : 605 x 450
Nouvelle taille : 583 x 394
.
.
.
Nouvelle taille : 500 x 450
Nouvelle taille : 500 x 450
```
```
Taille minimale observee : 500 x 450
```

À partir de 500 x 450, la fenêtre ne descend plus en dessous de cette taille.

Résultat du deuxième test
```
 .Taille initiale : 800 x 600
 . Largeur minimale configurée : 500
 . Hauteur minimale configurée : 450
 . Plus petite taille observée : 500 x 450
```

## Comparaison des deux expériences

|Test|Taille initiale|`minWidth`|`minHeight`|Taille minimale observée|
|----|--------------:|---------:|----------:|-----------------------:|
|1   |`800 x 600`    |`400`     |`350`      |**`400 x 350`**         |
|2   |`800 x 600`    |`500`     |`450`      |**`500 x 450`**         |

Les deux expériences donnent un résultat cohérent : la taille minimale observée correspond aux valeurs définies avec minWidth et minHeight.

### Vérification dans le terminal :

```

[2026-09-25 12:15:04.074] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 12:15:04.075] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 12:15:04.075] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=000001f2dafbac58  ??   ? ??  
[2026-09-25 12:15:04.077] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 12:15:04.077] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 12:15:04.077] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 12:15:04.077] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 12:15:04.078] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 794x583
[2026-09-25 12:15:04.130] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 12:15:04.130] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 12:15:04.131] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 12:15:04.131] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 12:15:04.131] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-25 12:15:04.147] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=0000009a187fede4 ??  ???   -> id=1
[2026-09-25 12:15:04.148] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 12:15:04.148] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL

 Nouvelle taille : 794  x  583 

 Nouvelle taille : 816  x  626 

 Nouvelle taille : 794  x  570 

 Nouvelle taille : 816  x  589 

 Nouvelle taille : 794  x  533 

 Nouvelle taille : 816  x  552 

 Nouvelle taille : 794  x  496 

 Nouvelle taille : 816  x  490 

 Nouvelle taille : 794  x  434 

 Nouvelle taille : 816  x  462 

 Nouvelle taille : 794  x  406 

 Nouvelle taille : 816  x  383 

 Nouvelle taille : 794  x  327 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 794  x  294 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 816  x  350 

 Nouvelle taille : 810  x  350 

 Nouvelle taille : 788  x  294 

 Nouvelle taille : 753  x  350 

 Nouvelle taille : 731  x  294 

 Nouvelle taille : 674  x  350 

 Nouvelle taille : 652  x  294 

 Nouvelle taille : 583  x  350 

 Nouvelle taille : 561  x  294 

 Nouvelle taille : 466  x  350 

 Nouvelle taille : 444  x  294 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 378  x  294 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 400  x  350 

 Nouvelle taille : 400  x  350 

 Taille minimale observee : 400  x 350 
[2026-09-25 12:15:13.521] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 12:15:13.542] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK

[2026-09-25 12:15:13.569] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 12:15:13.569] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 12:15:13.570] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=000001f2db396458 ?;?   ?;?  
[2026-09-25 12:15:13.570] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 12:15:13.570] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 12:15:13.570] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 12:15:13.570] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 12:15:13.570] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 800x600
[2026-09-25 12:15:13.605] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 12:15:13.605] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 12:15:13.605] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 12:15:13.605] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 12:15:13.607] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-25 12:15:13.619] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=0000009a187fede4 ???   ???   -> id=1
[2026-09-25 12:15:13.620] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 12:15:13.620] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL

 Nouvelle taille : 800  x  600 

 Nouvelle taille : 822  x  609 

 Nouvelle taille : 800  x  553 

 Nouvelle taille : 822  x  521 

 Nouvelle taille : 800  x  465 

 Nouvelle taille : 822  x  450 

 Nouvelle taille : 800  x  394 

 Nouvelle taille : 822  x  450 

 Nouvelle taille : 822  x  450 

 Nouvelle taille : 822  x  450 

 Nouvelle taille : 822  x  450 

 Nouvelle taille : 822  x  450 

 Nouvelle taille : 821  x  450 

 Nouvelle taille : 799  x  394 

 Nouvelle taille : 820  x  450 

 Nouvelle taille : 798  x  394 

 Nouvelle taille : 605  x  450 

 Nouvelle taille : 583  x  394 

 Nouvelle taille : 500  x  450 

 Nouvelle taille : 478  x  394 

 Nouvelle taille : 500  x  450 

 Nouvelle taille : 500  x  450 

 Nouvelle taille : 500  x  450 

 Nouvelle taille : 500  x  450 

 Nouvelle taille : 500  x  450 

 Taille minimale observee : 500  x 450 
[2026-09-25 12:15:30.582] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 12:15:30.595] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (26.74s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```


# Conclusion

L’expérience montre que minWidth et minHeight fixent une borne au redimensionnement de la fenêtre.

Dans le premier test, la fenêtre ne descend pas en dessous de 400 x 350.

Dans le deuxième test, la fenêtre ne descend pas en dessous de 500 x 450.

Les résultats observés correspondent donc aux bornes minimales configurées dans NkWindowConfig.
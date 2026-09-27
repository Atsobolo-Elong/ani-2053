# Exercice 7

## Principe de la capture
La capture de la souris permet à la fenêtre de continuer à recevoir les événements de souris pendant un glisser, même lorsque le curseur sort de la fenêtre.
Dans le programme, la capture est activée avec :
```
window.CaptureMouse(true);
et désactivée avec :
window.CaptureMouse(false);
```
La variable :
```
constexpr bool CAPTURE_ACTIVE = false;
```
permet de choisir le mode du test.
```
false : glisser sans capture ;
true : glisser avec capture.
```

## Fonctionnement du programme
Le programme crée une fenêtre de 900 × 600 et affiche un rectangle.
Lorsque le bouton gauche est pressé sur le rectangle, le glisser commence :
```
glisser = true;
```
Si la capture est activée, le programme appelle également :
```
window.CaptureMouse(true);
```
Pendant le déplacement, les coordonnées de la souris sont récupérées avec :
```
mouvement->GetX();
mouvement->GetY();
```
Le rectangle est alors déplacé à la position du curseur.
Le programme affiche également les coordonnées dans le terminal avec printf() afin d’observer les mouvements de la souris.
Lorsque le bouton gauche est relâché, le glisser est terminé et, lorsque la capture était active, elle est désactivée :
```
window.CaptureMouse(false);
```

## Test sans capture
Pour effectuer le premier test, la valeur suivante a été utilisée :
```
constexpr bool CAPTURE_ACTIVE = false;
```
## Le terminal indique :
```

[2026-09-27 15:51:53.356] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-27 15:51:53.359] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-27 15:51:53.359] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=0000019154b276a8 ??T?   0??T?  
[2026-09-27 15:51:53.360] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-27 15:51:53.360] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-27 15:51:53.360] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-27 15:51:53.360] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-27 15:51:53.360] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 894x583
[2026-09-27 15:51:53.554] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-27 15:51:53.555] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-27 15:51:53.556] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-27 15:51:53.556] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-27 15:51:53.556] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-27 15:51:53.668] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000002ba9feb44 @??    ?    -> id=1
[2026-09-27 15:51:53.670] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-27 15:51:53.670] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL

=== EXERCICE 7 ===
Mode : SANS CAPTURE

[SOURIS] Debut du glisser : x=443 y=307
[SOURIS] Mouvement : x=446 y=306
[SOURIS] Mouvement : x=455 y=305
[SOURIS] Mouvement : x=463 y=304
[SOURIS] Mouvement : x=471 y=304
[SOURIS] Mouvement : x=488 y=301
[SOURIS] Mouvement : x=504 y=300
[SOURIS] Mouvement : x=515 y=299
[SOURIS] Mouvement : x=525 y=297
[SOURIS] Mouvement : x=529 y=297
[SOURIS] Mouvement : x=545 y=294
[SOURIS] Mouvement : x=560 y=293
[SOURIS] Mouvement : x=566 y=293
[SOURIS] Mouvement : x=574 y=292
[SOURIS] Mouvement : x=583 y=290
[SOURIS] Mouvement : x=596 y=289
[SOURIS] Mouvement : x=607 y=288
[SOURIS] Mouvement : x=612 y=288
[SOURIS] Mouvement : x=618 y=288
[SOURIS] Mouvement : x=624 y=286
[SOURIS] Mouvement : x=635 y=286
[SOURIS] Mouvement : x=649 y=286
[SOURIS] Mouvement : x=655 y=286
[SOURIS] Mouvement : x=666 y=285
[SOURIS] Mouvement : x=674 y=284
[SOURIS] Mouvement : x=680 y=284
[SOURIS] Mouvement : x=683 y=283
[SOURIS] Mouvement : x=691 y=281
[SOURIS] Mouvement : x=702 y=279
[SOURIS] Mouvement : x=711 y=277
[SOURIS] Mouvement : x=719 y=276
[SOURIS] Mouvement : x=724 y=276
[SOURIS] Mouvement : x=732 y=275
[SOURIS] Mouvement : x=738 y=274
[SOURIS] Mouvement : x=746 y=271
[SOURIS] Mouvement : x=748 y=269
[SOURIS] Mouvement : x=756 y=267
[SOURIS] Mouvement : x=763 y=265
[SOURIS] Mouvement : x=770 y=263
[SOURIS] Mouvement : x=782 y=261
[SOURIS] Mouvement : x=794 y=260
[SOURIS] Mouvement : x=806 y=260
[SOURIS] Mouvement : x=812 y=260
[SOURIS] Mouvement : x=825 y=260
[SOURIS] Mouvement : x=850 y=255
[SOURIS] Mouvement : x=874 y=255
[SOURIS] Mouvement : x=884 y=255

[SOURIS] Programme termine.
[2026-09-27 15:52:05.425] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-27 15:52:05.446] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (12.77s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## Test avec capture
Pour le deuxième test, la valeur suivante a été utilisée :
```
constexpr bool CAPTURE_ACTIVE = true;
```
## Le terminal indique :
```
[2026-09-27 15:53:55.456] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-27 15:53:55.458] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-27 15:53:55.458] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=0000018a8e5cf718 ??   ? ??  
[2026-09-27 15:53:55.458] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-27 15:53:55.458] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-27 15:53:55.458] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-27 15:53:55.459] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-27 15:53:55.459] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 894x583
[2026-09-27 15:53:55.518] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-27 15:53:55.519] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-27 15:53:55.519] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-27 15:53:55.519] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-27 15:53:55.519] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-27 15:53:55.536] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000085649feef4  :??   ???   -> id=1
[2026-09-27 15:53:55.536] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-27 15:53:55.536] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL

=== EXERCICE 7 ===
Mode : AVEC CAPTURE

[SOURIS] Debut du glisser : x=496 y=283
[SOURIS] Capture activee
[SOURIS] Mouvement : x=509 y=285
[SOURIS] Mouvement : x=523 y=285
[SOURIS] Mouvement : x=534 y=285
[SOURIS] Mouvement : x=540 y=285
[SOURIS] Mouvement : x=555 y=282
[SOURIS] Mouvement : x=574 y=279
[SOURIS] Mouvement : x=591 y=274
[SOURIS] Mouvement : x=605 y=270
[SOURIS] Mouvement : x=644 y=260
[SOURIS] Mouvement : x=677 y=251
[SOURIS] Mouvement : x=730 y=241
[SOURIS] Mouvement : x=753 y=238
[SOURIS] Mouvement : x=783 y=233
[SOURIS] Mouvement : x=824 y=231
[SOURIS] Mouvement : x=852 y=229
[SOURIS] Mouvement : x=863 y=230
[SOURIS] Mouvement : x=879 y=231
[SOURIS] Mouvement : x=898 y=234
[SOURIS] Mouvement : x=917 y=237
[SOURIS] Mouvement : x=925 y=239
[SOURIS] Mouvement : x=938 y=241
[SOURIS] Mouvement : x=949 y=242
[SOURIS] Mouvement : x=960 y=243
[SOURIS] Mouvement : x=966 y=245
[SOURIS] Mouvement : x=980 y=249
[SOURIS] Mouvement : x=994 y=250
[SOURIS] Mouvement : x=1005 y=250
[SOURIS] Mouvement : x=1014 y=250
[SOURIS] Mouvement : x=1030 y=250
[SOURIS] Mouvement : x=1046 y=250
[SOURIS] Mouvement : x=1066 y=250
[SOURIS] Mouvement : x=1071 y=250
[SOURIS] Mouvement : x=1081 y=250
[SOURIS] Mouvement : x=1093 y=250
[SOURIS] Mouvement : x=1108 y=250
[SOURIS] Mouvement : x=1111 y=250
[SOURIS] Mouvement : x=1122 y=250
[SOURIS] Mouvement : x=1132 y=250
[SOURIS] Mouvement : x=1141 y=250
[SOURIS] Mouvement : x=1143 y=250
[SOURIS] Mouvement : x=1151 y=250
[SOURIS] Mouvement : x=1155 y=250
[SOURIS] Mouvement : x=1160 y=250
[SOURIS] Mouvement : x=1162 y=250
[SOURIS] Mouvement : x=1165 y=250
[SOURIS] Mouvement : x=1166 y=250
[SOURIS] Fin du glisser : x=1168 y=250
[SOURIS] Capture desactivee

[SOURIS] Programme termine.
[2026-09-27 15:54:03.053] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-27 15:54:03.066] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (8.25s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## Comparaison

Les mouvements continuent jusqu’à x=1166 y=250 et le relâchement est reçu à x=1168 y=250
La différence observée est donc que la capture permet au glisser de continuer à recevoir les mouvements de souris plus loin à l’extérieur de la fenêtre, et permet ici de recevoir explicitement la fin du glisser.
Du point de vue de l’utilisateur, le rectangle peut ainsi continuer à être déplacé alors que le curseur a quitté la fenêtre.

## Résultat
L’expérience montre l’intérêt de la capture pour un glisser qui doit continuer en dehors de la fenêtre.
Sans capture, le programme ne reçoit pas les mêmes événements lorsque le curseur poursuit son déplacement hors de la zone de la fenêtre.
Avec capture, la fenêtre continue à recevoir les mouvements pendant le glisser et reçoit également le relâchement dans l’expérience réalisée.La capture est donc particulièrement utile lorsqu’une interaction doit rester active pendant que la souris sort temporairement de la fenêtre.


## Observation complémentaire
Les coordonnées affichées par GetX() et GetY() permettent de suivre concrètement les mouvements reçus par le programme.
Les résultats présentés ici correspondent aux deux essais réalisés le 27/09/2026. Ils décrivent les événements effectivement observés dans le terminal et ne constituent pas une valeur universelle pour toutes les plateformes ou toutes les manipulations.
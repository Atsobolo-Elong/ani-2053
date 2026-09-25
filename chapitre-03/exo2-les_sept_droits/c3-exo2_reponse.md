# Exercice 2 — Les sept droits

## Principe utilisé
Pour chaque fenêtre, j’ai utilisé un champ booléen de NkWindowConfig et je l’ai placé à false.
Les droits testés sont :

1. Redimensionnement resizable = false
2. Déplacement movable = false
3. Minimisation minimizable = false
4. Maximisation maximizable = false
5. Passage en plein écran canFullscreen = false
6. Glisser-déposer dropEnabled = false
7. Fermeture closable = false


# Organisation du programme
Les sept configurations sont créées dans nkmain() :
```
NkWindowConfig cfg1;
cfg1.title = "FENETRE 1 redimentionnement interdit";
cfg1.width = 800;
cfg1.height = 600;
cfg1.resizable = false;

ouvrirFenetre(cfg1);
```
Le même principe est ensuite utilisé pour les six autres fenêtres. Cela permet de tester les droits les uns après les autres sans créer sept programmes différents.

## Observations lors de l’exécution

J’ai exécuté le programme et testé les actions correspondant aux droits que j’avais désactivés.
Cependant, contrairement à ce qui était attendu, j’ai constaté que les actions restaient possibles sur les fenêtres. Par exemple, malgré les configurations :
```
cfg1.resizable = false;
cfg2.movable = false;
cfg3.minimizable = false;
```
je pouvais encore effectuer les actions correspondantes. 🥲

Il en est de même pour les autres configurations testées.

### Résultat de l’observation

1. resizable = false Le redimensionnement restait possible
2. movable = false Le déplacement restait possible
3. minimizable = false La minimisation restait possible
4. maximizable = false La maximisation restait possible
5. canFullscreen = false Le passage en plein écran restait possible ou n’a pas pu être validé comme bloqué
6. dropEnabled = false Le comportement du glisser-déposer n’a pas permis de confirmer clairement le blocage.
7. closable = false La fermeture restait possible ou le comportement n’a pas correspondu à l’interdiction attendue Il est donc important de distinguer la configuration demandée de l’effet réellement observé.

## Vérification avec le terminal

```
[2026-09-25 05:37:03.872] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 05:37:03.872] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 05:37:03.873] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=00000184f5cd2a38 W?? 0W??
[2026-09-25 05:37:03.874] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 05:37:03.874] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 05:37:03.875] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 05:37:03.875] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 05:37:03.876] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 794x583
[2026-09-25 05:37:03.941] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 05:37:03.941] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 05:37:03.942] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 05:37:03.942] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 05:37:03.942] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-25 05:37:03.958] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000060b71fe9e4 "?  ??`   -> id=1
[2026-09-25 05:37:03.959] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 05:37:03.959] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-25 05:37:28.928] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 05:37:28.960] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK

[2026-09-25 05:37:29.025] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 05:37:29.025] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 05:37:29.026] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=00000184f3b9ee78  Z? 0 Z?
[2026-09-25 05:37:29.027] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 05:37:29.027] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 05:37:29.027] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 05:37:29.027] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 05:37:29.027] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 800x600
[2026-09-25 05:37:29.074] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 05:37:29.075] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 05:37:29.075] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 05:37:29.075] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 05:37:29.076] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-25 05:37:29.088] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000060b71fe9e4 I ??   ??`   -> id=1
[2026-09-25 05:37:29.089] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 05:37:29.089] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-25 05:37:44.571] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 05:37:44.596] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK

[2026-09-25 05:37:44.660] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 05:37:44.661] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 05:37:44.662] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=00000184f3b9ee78 %???   ???  
[2026-09-25 05:37:44.662] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 05:37:44.662] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 05:37:44.662] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 05:37:44.662] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 05:37:44.662] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 800x600
[2026-09-25 05:37:44.708] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 05:37:44.709] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 05:37:44.709] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 05:37:44.709] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 05:37:44.709] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-25 05:37:44.722] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000060b71fe9e4 ??   ??`   -> id=1
[2026-09-25 05:37:44.723] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 05:37:44.723] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-25 05:38:02.024] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 05:38:02.046] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK

[2026-09-25 05:38:02.091] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 05:38:02.091] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 05:38:02.091] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=00000184f3b9ee78  Z?   Z?
[2026-09-25 05:38:02.091] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 05:38:02.091] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 05:38:02.091] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 05:38:02.091] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 05:38:02.092] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 800x600
[2026-09-25 05:38:02.130] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 05:38:02.131] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 05:38:02.131] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 05:38:02.131] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 05:38:02.131] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
??   ??`   -> id=102.144] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000060b71fe9e4  
[2026-09-25 05:38:02.144] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 05:38:02.144] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-25 05:38:09.670] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 05:38:09.691] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK

[2026-09-25 05:38:09.732] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 05:38:09.732] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 05:38:09.732] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=00000184f3b9ee78 *???   ??  
[2026-09-25 05:38:09.732] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 05:38:09.732] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 05:38:09.733] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 05:38:09.733] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 05:38:09.733] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 800x600
[2026-09-25 05:38:09.786] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 05:38:09.786] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 05:38:09.787] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 05:38:09.787] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 05:38:09.787] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-25 05:38:09.802] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000060b71fe9e4  ???   ??`   -> id=1
[2026-09-25 05:38:09.802] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 05:38:09.802] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-25 05:38:15.493] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 05:38:15.503] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK

[2026-09-25 05:38:15.545] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 05:38:15.545] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 05:38:15.546] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=00000184f3b9ee78         Z? P    Z?
[2026-09-25 05:38:15.546] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 05:38:15.546] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 05:38:15.546] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 05:38:15.546] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 05:38:15.546] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 800x600
[2026-09-25 05:38:15.583] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 05:38:15.583] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 05:38:15.584] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 05:38:15.584] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 05:38:15.584] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
??   ??`   -> id=115.596] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000060b71fe9e4  
[2026-09-25 05:38:15.597] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 05:38:15.597] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-25 05:38:19.955] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 05:38:19.983] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK

[2026-09-25 05:38:20.028] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-25 05:38:20.028] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-25 05:38:20.029] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=00000184f6550a88  ???   @ ???  
[2026-09-25 05:38:20.029] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-25 05:38:20.029] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-25 05:38:20.030] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-25 05:38:20.030] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-25 05:38:20.030] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 800x600
[2026-09-25 05:38:20.062] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-25 05:38:20.062] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-25 05:38:20.062] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-25 05:38:20.062] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-25 05:38:20.063] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
??   ??`   -> id=120.076] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=00000060b71fe9e4  
[2026-09-25 05:38:20.076] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-25 05:38:20.076] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-25 05:38:22.629] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-25 05:38:22.647] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (79.45s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
### Conclusion

Le principe de l’exercice a été mis en place : les sept fenêtres sont configurées dans le même programme et chaque configuration désactive un champ différent de NkWindowConfig.
Cependant, lors du test, les interdictions configurées n’ont pas produit le comportement attendu : les actions restaient possibles. Le résultat obtenu montre donc que la configuration des champs est bien présente dans le code, mais que leur effet sur la fenêtre n’est pas confirmé par l’exécution.
Le retour du terminal confirme que les fenêtres et les contextes OpenGL sont correctement créés et détruits, mais il ne permet pas à lui seul de vérifier les sept droits.
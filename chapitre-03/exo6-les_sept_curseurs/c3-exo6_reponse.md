# Exercice 6 — Les sept curseurs



## La solution réalisée conserve le modèle NKCanvas avec :
```
 .NkRectangleShape pour représenter les sept zones ;
 . NkRenderWindow pour le rendu ;
 . NkContextDesc ;
 . NkGraphicsApi avec OpenGL ;
 . nkentseu::renderer ;
 . NkEvents().PollEvent() pour récupérer les mouvements de souris ;
 . NkMouseMoveEvent et GetX()/GetY() pour déterminer la zone survolée ;
 . SetCursor() pour appliquer le curseur correspondant.
```

## Réalisation

La fenêtre est organisée en sept rectangles colorés placés côte à côte. Chaque rectangle correspond à un curseur différent :
```
 1. Arrow
 2. TextInput
 3. Hand
 4. ResizeNS
 5. ResizeWE
 6. ResizeNWSE
 7. ResizeNESW
```
La position de la souris est récupérée lors d’un NkMouseMoveEvent. Un test avec GetGlobalBounds() permet de déterminer quel rectangle est survolé, puis le curseur correspondant est appliqué avec window.SetCursor().

Le rendu suit le modèle :
```
Clear → Draw → Display
```
Les rectangles sont donc dessinés à chaque image avec target.Draw().

## Remarque sur le découpage de la fenêtre

Je n’ai pas trouvé une méthode permettant de diviser directement la fenêtre elle-même en sept zones natives.

La solution réalisée ne divise donc pas réellement la fenêtre en sept sous-fenêtres ou régions natives. Elle construit plutôt sept objets NkRectangleShape placés dans la fenêtre, qui servent de représentation visuelle des sept zones.

Autrement dit, les zones sont des objets graphiques dans une seule fenêtre et non une modification de la structure interne de la fenêtre, j'ignore si cela vous convient.🥲

Cette solution permet néanmoins de réaliser la logique demandée : la souris peut survoler chacune des sept zones et le programme peut associer un curseur différent à chaque zone.

## Test et résultat du terminal

```

[2026-09-27 08:06:50.428] [WRN] [default] [NkContextFactory.cpp:46 in Create] -> [NkContextFactory][DBG] Create begin api=OpenGL
[2026-09-27 08:06:50.429] [INF] [default] [NkGpuPolicy.cpp:114 in ApplyPreContext] -> [NkGpuPolicy] api=OpenGL pref=Default vendor=Any adapterIndex=-1
[2026-09-27 08:06:50.429] [WRN] [default] [NkContextFactory.cpp:95 in Create] -> [NkContextFactory][DBG] Context allocated ptr=0000024529e96278 ??   ???  
[2026-09-27 08:06:50.430] [WRN] [default] [NkContextFactory.cpp:97 in Create] -> [NkContextFactory][DBG] Initialize begin
[2026-09-27 08:06:50.431] [WRN] [default] [NkOpenGLContext.cpp:199 in Initialize] -> [NkOpenGL][DBG] Initialize enter
[2026-09-27 08:06:50.431] [WRN] [default] [NkOpenGLContext.cpp:204 in Initialize] -> [NkOpenGL][DBG] before mDesc copy
[2026-09-27 08:06:50.431] [WRN] [default] [NkOpenGLContext.cpp:206 in Initialize] -> [NkOpenGL][DBG] after mDesc copy
[2026-09-27 08:06:50.431] [WRN] [default] [NkOpenGLContext.cpp:226 in Initialize] -> [NkOpenGL][DBG] surface valid=1 1044x483
[2026-09-27 08:06:50.488] [INF] [default] [NkOpenGLContext.cpp:749 in InitWGL] -> [NkOpenGL] WGL OK (GL 4.6 Core)

[2026-09-27 08:06:50.488] [INF] [default] [NkOpenGLContext.cpp:280 in Initialize] -> [NkOpenGL] Ready - Intel(R) UHD Graphics 620 | 4.6.0 - Build 31.0.101.2135 | Intel

[2026-09-27 08:06:50.489] [WRN] [default] [NkContextFactory.cpp:103 in Create] -> [NkContextFactory][DBG] Initialize success
[2026-09-27 08:06:50.489] [INF] [default] [NkContextFactory.cpp:105 in Create] -> [NkContextFactory] Context created: OpenGL

[2026-09-27 08:06:50.489] [INF] [default] [NkRenderer2DFactory.cpp:39 in Create] -> [NkRenderer2DFactory] Creating 2D renderer for API: OpenGL
[2026-09-27 08:06:50.503] [INF] [default] [NkOpenGLRenderer2D.cpp:633 in CreateGLTexture] -> [NkGL2D] CreateGLTexture w=1 h=1 rgba=0000004a157feb64 ?'1E    ?J   -> id=1
[2026-09-27 08:06:50.505] [INF] [default] [NkOpenGLRenderer2D.cpp:410 in Initialize] -> [NkGL2D] Initialized (white tex=1)
[2026-09-27 08:06:50.505] [INF] [default] [NkRenderer2DFactory.cpp:103 in Create] -> [NkRenderer2DFactory] 2D renderer created: OpenGL
[2026-09-27 08:07:11.468] [INF] [default] [NkOpenGLRenderer2D.cpp:439 in Shutdown] -> [NkGL2D] Shutdown
[2026-09-27 08:07:11.490] [INF] [default] [NkOpenGLContext.cpp:385 in Shutdown] -> [NkOpenGL] Shutdown OK


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (21.91s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
## Observation

Le terminal ne donne pas directement le résultat visuel du changement de curseur. Le comportement du curseur est donc vérifié principalement en observant la fenêtre pendant l’exécution.

## Deuxième partie de l’exercice

L’exercice demande ensuite de ne poser le curseur qu’une seule fois au démarrage.

Dans ce cas, le programme effectue seulement une initialisation du type :
```
window.SetCursor(curseurs[0]);
```
Le curseur reste alors sur cette forme initiale lorsque la souris passe d’une zone à l’autre.

Cette observation montre que SetCursor() doit être rappelé avec le curseur voulu pour modifier la forme affichée pendant le déplacement de la souris.

## Conclusion

L’exercice est fonctionnel avec une représentation composée de sept NkRectangleShape.
La principale limite de la solution est que les sept zones sont des objets graphiques dans une seule fenêtre et non sept divisions natives de la fenêtre.
Je n’ai pas trouvé de méthode permettant de découper directement la fenêtre elle-même en sept zones natives.

Donc Cette approche reste adaptée pour démontrer le principe demandé : associer une zone survolée à une forme de curseur différente.
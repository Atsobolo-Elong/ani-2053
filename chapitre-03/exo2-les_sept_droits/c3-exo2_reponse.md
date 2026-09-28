# Exercice 2 — Les sept droits
Résultat des observations :
```

| Droit | Effet attendu | Effet observé |
|---|---|---|
| frame | Modifier la présence du cadre | Le cadre est bien pris en compte sous Windows. |
| resizable | Interdire le redimensionnement | Le comportement attendu n’est pas appliqué sous Windows. |
| minimizable | Interdire la minimisation | Le comportement attendu n’est pas appliqué sous Windows. |
| movable | Interdire le déplacement | Le comportement attendu n’est pas appliqué sous Windows. |
| closable | Interdire la fermeture | Le comportement attendu n’est pas appliqué sous Windows. |
| maximizable | Interdire la maximisation | Le comportement attendu n’est pas appliqué sous Windows. |
| canFullscreen | Interdire le plein écran | Le comportement attendu n’est pas appliqué sous Windows. |

```
Le comportement attendu n’est pas appliqué sous Windows.
   Le journal d’exécution confirme que les fenêtres et les contextes OpenGL sont correctement créés puis détruits. Les écarts observés ne viennent donc pas de la création des fenêtres.

# Vérification des dimensions
Les mesures obtenues présentent deux écarts constants :
816 - 794 = 22 pixels en largeur ;
350 - 294 = 56 pixels en hauteur ;
822 - 800 = 22 pixels en largeur ;
450 - 394 = 56 pixels en hauteur.
Ces différences montrent que les deux valeurs mesurées ne correspondent pas exactement à la même partie de la fenêtre : l’une inclut les décorations de la fenêtre, l’autre correspond à sa surface utile.
# Conclusion
Sous Windows, le backend n’applique réellement qu’une partie des droits annoncés par NkWindowConfig. Le droit du cadre est pris en compte, tandis que les autres droits ne sont pas exploités par cette couche Windows, conformément à l’inspection du moteur.
Les écarts ne proviennent donc pas du programme de test : ils sont liés à l’implémentation du backend.
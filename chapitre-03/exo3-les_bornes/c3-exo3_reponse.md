## EXERCICE 3

# resultat

| Test | Borne configurée | Taille minimale observée |
|---|---:|---:|
| 1 | 400 x 350 | 400 x 639 |
| 2 | 500 x 450 | 822 x 450 |
| 3 | Aucune borne (`0 x 0`) | 198 x 656 |

Pour le premier test, la largeur ne peut pas descendre sous 400, ce qui correspond à la borne minimale configurée. Pour le deuxième test, la hauteur ne peut pas descendre sous 450, là encore conformément à la borne demandée.

Les valeurs du journal montrent également un écart entre les dimensions rapportées selon les mesures : par exemple 822 x 450 et 800 x 394. Cela explique pourquoi certaines dimensions observées peuvent être inférieures à la borne configurée : elles ne représentent pas nécessairement la même partie de la fenêtre.

Le troisième test est celui demandé après suppression des bornes. Avec minWidth = 0 et minHeight = 0, la fenêtre ne peut pourtant pas être réduite jusqu'à zéro. Le journal indique une taille minimale observée de `198 x 656`.

Le programme termine normalement après les trois expérimentations. Le résultat montre donc que retirer une borne du programme ne supprime pas toutes les contraintes : une taille minimale reste imposée par le système ou le backend.

# conclusion

Cette expérimentation montre que les dimensions minimales d’une fenêtre dépendent à la fois des bornes configurées dans NkWindowConfig et des contraintes imposées par le système. Avec les bornes 400 x 350 puis 500 x 450, les dimensions configurées sont respectées sur les valeurs observées. En supprimant les bornes avec 0 x 0, la fenêtre peut être réduite davantage, mais elle conserve tout de même une limite imposée par le système ou le backend.

Lors du troisième test, la plus petite taille observée est de 198 x 656. Le programme s’est également terminé normalement après les trois expérimentations. L’objectif de l’exercice est donc atteint : la comparaison permet de distinguer les limites définies par le programme des limites qui restent imposées par l’environnement d’exécution.

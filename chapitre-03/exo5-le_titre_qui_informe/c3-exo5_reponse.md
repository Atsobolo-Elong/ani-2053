# Exercice 5

Le titre doit être mis à jour uniquement lorsque l’état du document ou la taille de la fenêtre change, et non à chaque image.

1. Réalisation

Le programme utilise NkWindow::SetTitle() pour modifier le titre de la fenêtre et NkWindow::GetSize() pour récupérer sa taille initiale.

Une fonction MettreAJourTitre() utilise la construction du titre. Elle reçoit :
```
 . le nom du document ;
 . l’état de modification du document ;
 . la largeur ;
 . la hauteur.
```

Lorsque documentModifie vaut true, la fonction ajoute  * après le nom du document.

Le titre obtenu est donc par exemple :
```
MonDocument - 800 x 600
```

2. alternative pour la mise à jour du titre

Je n’ai pas trouvé  pour cet exercice une méthode permettant de modifier directement le contenu d’un document.🥲

J’ai donc choisi une modification simple permettant de vérifier le comportement demandé : 
`le document est considéré comme modifié lorsque l’utilisateur appuie sur la touche Entrée.`

Le code détecte NkKeyPressEvent et vérifie si la touche reçue est NkKey::NK_ENTER. Dans ce cas, documentModifie passe de false à true, puis le titre est actualisé.

3. Mise à jour lors du redimensionnement

Lorsqu’un NkWindowResizeEvent est reçu, le programme récupère la nouvelle largeur et la nouvelle hauteur avec :
```
resize->GetWidth();
resize->GetHeight();
```

Puis la fonction MettreAJourTitre() est appelée afin d’actualiser le titre.

Par exemple, après un redimensionnement :
```
MonDocument * - 1024 x 768
```

3. Observations

Aucune information particulière n’est affichée dans le terminal pendant l’exécution. Donc je n'ai rien à coller cette fois comme preuve. 🥲

`Les résultats de l’exercice sont donc directement observables dans le titre de la fenêtre`

# Conclusion

L’exercice est réalisé en mettant à jour le titre uniquement aux moments nécessaires :

```
 . au démarrage de la fenêtre ;
 . lorsque le document est marqué comme modifié par l’appui sur entrer ;
 . lors d’un redimensionnement de la fenêtre.
```
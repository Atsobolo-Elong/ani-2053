# Exercice 4 

## Observation

Avec `PollEvent()`, j'ai volontairement conservé le pointeur du premier
événement puis récupéré un deuxième événement dans la même frame.

# retour du terminale:
```
[POLL] Evenement recu : NK_WINDOW_CREATE
[POLL] Deuxieme evenement dans la meme frame : NK_WINDOW_FOCUS_GAINED
[POLL] Contenu du pointeur conserve apres le second PollEvent : NK_WINDOW_CREATE
[POLL] Evenement recu : NK_WINDOW_FOCUS_GAINED
[POLL] Deuxieme evenement dans la meme frame : NK_WINDOW_SHOWN
[POLL] Contenu du pointeur conserve apres le second PollEvent : NK_WINDOW_FOCUS_GAINED
[POLL] Evenement recu : NK_WINDOW_RESTORE
[POLL] Deuxieme evenement dans la meme frame : NK_WINDOW_MOVE
[POLL] Contenu du pointeur conserve apres le second PollEvent : NK_WINDOW_RESTORE
[POLL] Evenement recu : NK_WINDOW_PAINT
[POLL] Deuxieme evenement dans la meme frame : NK_WINDOW_RESIZE
[POLL] Contenu du pointeur conserve apres le second PollEvent : NK_WINDOW_PAINT
[POLL] Evenement recu : NK_WINDOW_MOVE
[POLL] Evenement recu : NK_KEY_PRESSED
[POLL] Deuxieme evenement dans la meme frame : NK_TEXT_INPUT
[POLL] Contenu du pointeur conserve apres le second PollEvent : NK_KEY_PRESSED
[POLL] Evenement recu : NK_KEY_RELEASED
[POLL] Evenement recu : NK_KEY_PRESSED
[POLL] Echap recue : fin de la phase 1.

========================================
PHASE 1 TERMINEE
========================================
[COPY] Evenement copie : NK_KEY_RELEASED
[COPY] Evenement copie : NK_KEY_PRESSED
[COPY] Evenement copie : NK_TEXT_INPUT
[COPY] Evenement copie : NK_KEY_RELEASED
[COPY] Evenement copie : NK_KEY_PRESSED
[COPY] Echap recue.
[COPY] La copie reste valide pendant son utilisation.
[COPY] Fin du programme.

========================================
FIN D'EXECUTION
========================================

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (8.91s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
Dans mes tests, le pointeur conservé affichait toujours le premier événement.
Correction
J’ai ensuite utilisé PollEventCopy().
Le programme a affiché plusieurs copies d’événements et a confirmé :
[COPY] La copie reste valide pendant son utilisation.


## Conclusion
PollEvent() fournit un pointeur vers l’événement courant, tandis que
PollEventCopy() permet de conserver une copie de l’événement.
Dans mon test, aucun problème visible n’est apparu avec le pointeur conservé,
mais PollEventCopy() permet de travailler avec une copie indépendante.
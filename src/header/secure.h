#ifndef SECURE_H
#define SECURE_H

#include "data_struct.h"

#ifdef DEBUG_MODE
#define MASK  1  /**< Maschera di bit per l'attivazione dei livelli di tracing. */

#define DBG(A, B) {if ((A) & MASK) {B; } }		/**< Macro per l'attivazione di funzioni 
												  * in base al livello selezionato  */
#else
#define DBG(A, B)								/**< Macro usata nel caso il debugging sia disattivato. */
#endif

/* Dichiarazioni non necessarie inserite per comodita' */
#define DEFCON1(a) DBG(1, a)				/**< Macro per definire il livello più critico di debug. */
#define DEFCON2(a) DBG(2, a)				/**< Macro per definire il livello intermedio di debug. */
#define DEFCON4(a) DBG(4, a)				/**< Macro per definire il livello meno critico, e piu' verboso, di debug. */

/** Funzione di sicurezza. Controlla che il puntatore alla lista del
  * personaggio, non sia NULL. Qualora lo fosse, ferma il programma e
  * stampa a video in quale funzione e' sorto questo problema.
  * Funzione attiva solo in caso di DEFCON1.
  * @param c puntatore alla lista del personaggio.
  * @param name_f stringa contenente il nome della funzione chiamante.
  */
void secure_player(GList *c, const char name_f[]);

/** Funzione di sicurezza. Controlla che il l'indirizzo dell'oggetto
  * non sia NULL. Qualora lo fosse, ferma il programma e
  * stampa a video in quale funzione e' sorto questo problema.
  * Funzione attiva solo in caso di DEFCON1.
  * @param c oggetto da valutare.
  * @param name_f stringa contenente il nome della funzione chiamante.
  */
void secure_object(Object c, const char name_f[]);

/** Funzione di sicurezza. Controlla che i puntatori ai suoni di gioco
  * non siano NULL. Qualora lo fossero, ferma il programma e
  * stampa a video in quale funzione e' sorto questo problema.
  * Funzione attiva solo in caso di DEFCON1.
  * @param c array di puntatori contententi i suoni di gioco.
  * @param name_f stringa contenente il nome della funzione chiamante.
  */
void secure_sample(ALLEGRO_SAMPLE *c[], const char name_f[]);

/** Funzione di sicurezza. Controlla che il puntatore all'immagine
  * non sia NULL. Qualora lo fosse, ferma il programma e
  * stampa a video in quale funzione e' sorto questo problema.
  * Funzione attiva solo in caso di DEFCON1.
  * @param c puntatore all'immagine.
  * @param name_f stringa contenente il nome della funzione chiamante.
  */
void secure_image(ALLEGRO_BITMAP *pic, const char name_f[]);

/** Funzione di sicurezza. Controlla che il puntatore al font
  * non sia NULL. Qualora lo fosse, ferma il programma e
  * stampa a video in quale funzione e' sorto questo problema.
  * Funzione attiva solo in caso di DEFCON1.
  * @param c puntatore al font utilizzato per la stampa a video in game.
  * @param name_f stringa contenente il nome della funzione chiamante.
  */
void secure_font(ALLEGRO_FONT *f, const char name_f[]);

#endif /* SECURE_H */

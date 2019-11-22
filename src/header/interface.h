#ifndef INTERFACCIA_H
#define INTERFACCIA_H

#include "data_struct.h"
#include "secure.h"
#include "inits.h"
#include "game_functions.h"
#include "IOfile.h"

/**
  * La funzione permette il movimento del personaggio gestito dal giocatore.
  * Utilizzata nel livello senza la gravita'.
  * @param key_state parametro contenente i tasti premuti.
  * @param p puntatore alla lista del personaggio.
  * @param active flag per l'aggiornamento del'immagine del personaggio. Se false il personaggio non ha movimento.
  */
void player_movement(ALLEGRO_KEYBOARD_STATE &key_state, GList *&p, bool &active);

/**
  * La funzione permette il movimento del personaggio gestito dal giocatore.
  * Utilizzata nel livello in presenza di gravita'.
  * @param key_state parametro contenente i tasti premuti.
  * @param p puntatore alla lista del personaggio.
  * @param active flag per l'aggiornamento del'immagine del personaggio. Se false il personaggio non ha movimento.
  * @param jump variabile booleana che definisce il salto del personaggio.
  */
void player_movement_gravity(ALLEGRO_KEYBOARD_STATE &key_state, GList *&p, bool &active, bool &jump);

/**
  * La funzione carica il menu' iniziale di gioco.
  * Al suo interno viene gestito il caricamento dell'ultimo salvataggio e la scelta del personaggio.
  * @param font_1 puntatore al font utilizzato per le scritte a schermo.
  * @param event_queue coda degli eventi gestiti dalla libreria allegro.
  * @param p puntatore alla lista del personaggio.
  * @param display puntatore alla finestra di gioco.
  * @param level variabile che segna il livello attuale.
  */
void menu_pre_game(ALLEGRO_FONT *font_1, ALLEGRO_EVENT_QUEUE *event_queue, GList *&p,
	ALLEGRO_DISPLAY *display, unsigned int &level);

/**
  * La funzione carica il menu' di fine livello.
  * Al suo interno viene gestito il salvataggio della partita e l'eventuale prosecuzione.
  * @param p puntatore alla lista del personaggio.
  * @param background struct per la stampa dello sfondo.
  * @param font_1 puntatore al font utilizzato per le scritte a schermo.
  * @param display puntatore alla finestra di gioco.
  * @param level variabile che segna il livello attuale.
  * @param done variabile per segnare la prosecuzione del gioco o l'accesso al menu' di uscita.
  */
void make_your_choice(GList *p, Background background, ALLEGRO_FONT *font_1, ALLEGRO_DISPLAY *display, unsigned int &level, bool &done);

/**
  * La funzione gestisce fade e cambio di backgroud a fine livello.
  * @param p puntatore alla lista del personaggio.  
  * @param e puntatore alla lista del nemico.
  * @param fade struct per la dissolvenza.
  * @param background struct per la stampa dello sfondo.
  * @param lvl variabile che segna il livello attuale.
  */
void end_level(GList *&p, GList *&e, Fader &fade, Background &background, unsigned int &lvl);

/**
  * La funzione gestisce gli eventi causati dalla morte del giocatore.
  * Viene gestita la dissolvenza, il caricamento del backgroud, l'aggiornamento delle liste dei personaggi
  * e l'uscita dalla sessione di gioco.
  * @param fade struct per la dissolvenza.
  * @param background struct per la stampa dello sfondo.
  * @param p puntatore alla lista del personaggio.
  * @param e puntatore alla lista del nemico.
  * @param done variabile booleana per segnare la prosecuzione del gioco o l'accesso al menu' di uscita.
  */
void death_fade(Fader &fade, Background &background, GList *&p, GList *&e, bool &done);

/**
  *	La funzione gestisce lo sparo del giocatore.
  * @param p puntatore alla lista del personaggio.
  * @param key_state parametro contenente i tasti premuti.
  */
void player_fire(GList *&p, ALLEGRO_KEYBOARD_STATE &key_state);

/**
  *	La funzione gestisce l'aggiornamento dei frame.
  * Viene valutato il cambio del frame dei personaggi e delle esplosioni.
  * @param p puntatore alla lista del personaggio.  
  * @param e puntatore alla lista del nemico.
  * @param m puntatore alla lista dei minion.
  * @param b_exp struct relativa alle esplosioni dei proiettili.
  * @param p_exp struct relativa alle esplosioni dei personaggi.
  * @param active flag per l'aggiornamento del'immagine del personaggio. Se false il personaggio non ha movimento.
  */
void change_frame(GList *&p, GList *&e, GList *&m, Explosion &b_exp, Explosion &p_exp, bool active);

/**
  *	La funzione gestisce lo spawn dei minion e del nemico a fine livello.
  * Dopo 4 minion uccisi il nemico compare il nemico.
  * @param m puntatore alla lista dei minion.
  * @param e puntatore alla lista del nemico.
  * @param p puntatore alla lista del personaggio.
  * @param run variabile booleana che definisce lo spawn dei minion o del nemico.
  * Se false un minion è creato, altrimenti il nemico.
  * @param lvl variabile che segna il livello attuale. 
  * @param done variabile booleana per segnare la prosecuzione del gioco o l'accesso al menu' di uscita.
  */
void spawn_minions(GList *&m, GList *&e, GList *&p, bool &run, Fader &fade, Background &background, unsigned int &lvl, bool &done);

/**
  *La funzione disegna sul display tutte i componenti grafici necessari per il gioco.
  * @param m puntatore alla lista dei minion.
  * @param e puntatore alla lista del nemico.
  * @param p puntatore alla lista del personaggio.
  * @param b_exp struct relativa alle esplosioni dei proiettili.
  * @param p_exp struct relativa alle esplosioni dei personaggi.
  * @param fade struct per la dissolvenza.
  * @param font_1 puntatore al font utilizzato per le scritte a schermo.
  * @param obj puntatori agli oggetti di gioco
  */
void draw(Background background, GList *p, GList *e, GList *m, Explosion b_exp, Explosion p_exp, Fader &fade,
	ALLEGRO_FONT *font_1, Object obj[]);

/**
  *	La funzione gestisce la modifica della camera.
  * @param camera struttura dati, appartenente alla libreria allegro, per la gestione della camera.
  * @param camera_position puntatore alla posizione della camera.
  * @param p puntatore alla lista del personaggio.
  */
void mod_camera(ALLEGRO_TRANSFORM &camera, float *camera_position, GList *&p);

#endif /* INTERFACCIA_H */


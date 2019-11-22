#ifndef INITS_H
#define INITS_H

#include "data_struct.h"
#include "secure.h"
#include "game_functions.h"

/**
  *	La funzione inizializza il personaggio principale.
  *	@param p puntatore alla lista personaggio.
  *	Per maggiorni informazioni controllare le struct ::Player e ::Object
  */
void init_player(GList *&p, const char sex);

/**
  *	La funzione inizializza il nemico. 
  *	@param p puntatore alla lista del nemico.
  * Per maggiorni informazioni controllare le struct ::Player e ::Object
  */
void init_enemy(GList *&e);

/**
  *	La funzione inizializza la piccola esplosione.
  *	@param l_e oggetto da inizializzare.
  * Per maggiorni informazioni controllare la struct ::Explosion
  */
void init_little_explosion(Explosion &l_e);

/**
  *	La funzione inizializza l'esplosione in seguito alla morte del personaggio.
  *	@param p_e oggetto da inizializzare.
  * Per maggiorni informazioni controllare la struct ::Explosion
  */
void init_player_explosion(Explosion &p_e);

/**
  *	La funzione inizializza la schermata iniziale.
  *	@param starter oggetto da inizializzare
  * Per maggiorni informazioni controllare la struct ::Background
  */
void init_starter(Background &starter);

/**
  *	La funzione inizializza lo sfondo del primo livello.
  *	@param background oggetto da inizializzare.
  * Per maggiorni informazioni controllare la struct ::Background
  */
void init_background_1(Background &background);

/**
  *	La funzione inizializza la dissolvenza.
  *	@param fade oggetto da inizializzare.
  * Per maggiorni informazioni controllare la struct ::Fade
  */
void init_fade(Fader &fade);

/**
  *	La funzione inizializza il carattere utilizzato per stampare le statistiche dei personaggi.
  *	@param font_1 oggetto da inizializzare.
  * Per maggiorni informazioni controllare la struct ::Font
  */

/**
  *	La funzione inizializza il font utilizzato per le scritte a schermo.
  * @param font_1 oggetto da inizializzare.
  * Per maggiorni informazioni controllare la struct ::Font
  */
void init_font(ALLEGRO_FONT *&font_1);

/**
  *	La funzione inizializza tutti i suoni utilizzati nel gioco.
  *	@param sound_effect e' un array di puntatori, ciascuno contentente
  * un proprio suono.
  */
void init_sound(ALLEGRO_SAMPLE *sound_effect[]);

/**
  *	La funzione sceglie in maniera randomica quale armature spawnare
  *	in caso la funzione ::random_spawn scelga come tipo di oggetto 
  *	un'armatura.
  *	@param obj oggetto da inizializzare.
  * Per maggiori informazioni controllare la struct ::Object
  */
void init_general_armor(Object &obj);

/**
  *	La funzione sceglie in maniera randomica quale proiettile spawnare
  *	in caso la funzione ::random_spawn scelga come tipo di oggetto 
  *	un proiettile.
  *	@param obj oggetto da inizializzare.
  * Per maggiori informazioni controllare la struct ::Object
  */
void init_general_bullet(Object &obj);

/**
  *	La funzione sceglie in maniera randomica quale pozione spawnare
  *	in caso la funzione ::random_spawn scelga come tipo di oggetto 
  *	una pozione.
  *	@param obj oggetto da inizializzare.
  * Per maggiori informazioni controllare la struct ::Object
  */
void init_general_potion(Object &obj);

/**
  *	La funzione inizializza i minion del primo livello.
  * @param m Puntatore alla lista personaggio.
  * Per maggiori informazioni controllare le struct ::Player e ::Object
  */
void init_minion(GList *&m);

/**
  *	La funzione inizializza lo sfondo del secondo livello.
  *	@param background oggetto da inizializzare.
  * Per maggiorni informazioni controllare la struct ::Background
  */
void init_background_2(Background &background);

/**
  *	La funzione re-inizializza alcuni campi del player, per
  * adattarlo al secondo livello.
  *	@param p puntatore alla lista personaggio
  * Per maggiorni informazioni controllare le struct ::Player e ::Object
  */
void init_player_2(GList *&p);

/**
  *	La funzione re-inizializza alcuni campi del nemico, per
  * adattarlo al secondo livello.
  *	@param e puntatore alla lista personaggio.
  * Per maggiorni informazioni controllare le struct ::Player e ::Object
  */
void init_enemy_2(GList *&e);

/**
  *	La funzione re-inizializza alcuni campi dei minion, per
  * adattarli al secondo livello.
  *	@param m puntatore alla lista personaggio
  * Per maggiorni informazioni controllare le struct ::Player e ::Object
  */
void init_minion_2(GList *&m);

/**
  * La funzione gestisce la deallocazione del player,
  * del nemico e dei minion.
  * @param p puntatore al player.
  * @param e puntatore al nemico.
  * @param m puntatore ai minion.
  */
void pg_deallocation(GList *&p, GList *&e, GList *&m);

/**
  * La funzione gestisce la deallocazione di tutto cio' che non e' personaggio.
  * @param display puntatore al display di gioco. 
  * @param timer puntatore al timer che gestisce il movimento e gli eventi di gioco.
  * @param frame_timer puntatore al timer che gestisce le animazioni del gioco.
  * @param b_exp struct per l'esplosione dei proiettili.
  * @param p_exp struct per l'esplosione del player.
  * @param fade struct per la dissolvenza.
  * @param font_1 puntatore al font per la scrittura a schermo.
  * @param event_queue puntatore alla coda di eventi di allegro.
  * @param sound_effect array di puntatori contenente i suoni di gioco.
  * @param song_instance puntatore alla musica di base del gioco.
  * @param thunder_instance puntatore alla seconda musica di base del gioco.
  */
void destroy(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_TIMER *frame_timer, Explosion &b_exp, Explosion &p_exp,
	Fader &fade, ALLEGRO_FONT *&font_1, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_SAMPLE *sound_effect[],
	ALLEGRO_SAMPLE_INSTANCE *song_instance, ALLEGRO_SAMPLE_INSTANCE *thunder_instance);

#endif /* INITS_H */

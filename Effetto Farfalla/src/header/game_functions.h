#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "data_struct.h"
#include "inits.h"
#include "secure.h"

#define START_MOV_CAMERA 382. /**< Coordinata iniziale spostamento camera */
#define END_MOV_CAMERA 3583.  /**< Coordinata finale spostamento camera */

/**
  * La funzione calcola la forza del personaggio, in base all'arma equipaggiata.
  * Per altre informazioni controllare la struct ::Player
  * @param p puntatore alla lista del personaggio.
  * @return il valore della forza.
  */
float strenght_calc(GList *p);

/**
  * La funzione calcola il valore della difesa del personaggio.
  * Per altre informazioni controllare la struct ::Player
  * @param p puntatore al personaggio.
  * @return il valore della difesa calcolata in percentuale.
  */
float armor_calc(GList *p);

/**
  * La funzione modifica il valore della salute del personaggio colpito.
  * I danni vengono calcolati togliendo la percentuale dovuta alla difesa del personaggio colpito.
  * Per altre informazioni controllare la struct ::Player
  * @param p puntatore alla lista del personaggio in difesa.
  * @param e puntatore alla lista del personaggio in attacco.
  */
void health_bullet(GList *&p, GList *e);

/**
  *	La funzione restituisce al puntatore all'oggetto.
  *	@param p puntatore alla lista del personaggio da analizzare.
  * @param type variabile contenente il tipo di oggetto da cercare.
  * @return il puntatore all'oggetto, se non trovato ritorna il puntatore al primo elemento della lista.
  *	In caso di ricerca del proiettile la precedenza e' data
  *	all'arma secondaria qualora essa sia equipaggiata.
  */
GList* search_obj(GList *p, Type_Obj type);

/**
  *	La funzione stabilisce l'orientamento e le coordinate iniziali del proiettile del personaggio.
  *	@param p personaggio di cui aggiornare il priettile.
  */
void dir_bullet(GList *&p);

/**
  * Funzione generale che chiama le varie update bullet,
  * al fine di aggiornare tutti i proiettili presenti
  * sullo schermo.
  * @param p player di cui aggiornare il proiettile
  * @param e nemico di cui aggiornare il proiettile
  * @param m minion di cui aggiornare il proiettile
  */
void general_update_bullet(GList *&p, GList *&e, GList *&m);

/**
  * Funzione generale che chiama le varie collisioni
  * al fine di controllare se vi e' collisione o meno
  * tra tutte le entita' presenti a schermo.
  * @param p puntatore al player
  * @param e puntatore al nemico
  * @param m puntatore ai minion
  * @param b_exp struct relativa all'esplosione dei proiettili
  * @param p_exp struct relativa all'esplosione del personaggio
  * @param obj puntatore agli oggetti di gioco
  * @param sound_effect puntatore agli effetti sonori di gioco
  */
void general_collision(GList *&p, GList *&e, GList *&m, Explosion &b_exp, Explosion &p_exp, Object obj[], ALLEGRO_SAMPLE * sound_effect[]);

/**
  *	La funzione gestisce il movimento, e lo sparo, del nemico finale del primo
  * livello. 
  *	@param e puntatore alla lista del personaggio di cui gestire il movimento.
  * @param p puntatore alla lista del personaggio mosso dal giocatore.
  */
void casual_movement_enemy(GList *&e, GList *p);

/**
  * Funzione generale che chiama le random_spawn al fine di gestire
  * lo spawn randomico degli oggetti nei vari livelli.
  * @param obj puntatori agli oggetti di gioco
  * @param lvl variabile che segna il livello attuale
  */
void general_random_spawn(Object obj[], unsigned int lvl);

/**
  * Funzione che gestisce il movimento casuale, e lo sparo, dei minion
  * del primo livello.
  * @param m puntatore ai minion che vengono mossi
  */
void casual_movement_minion(GList *&m);

/**
  * Funzione che gestisce il movimento casuale, e lo sparo, dei minion
  * del secondo livello. Quello che cambia dal primo, e' che in questo
  * livello vi e' la gravita', e quindi il movimento tiene conto di piu'
  * parametri.
  * @param m puntatore ai minion mossi
  * @param jump variabile booleana che permette, o meno, il salto.
  */
void casual_movement_gravity(GList *&m, bool &jump);

#endif /* GAME_FUNCTIONS_H */

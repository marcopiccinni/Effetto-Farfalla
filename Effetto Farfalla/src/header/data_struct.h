#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <glib.h>
#include<iostream>

using namespace std;

#define SCREENWIDTH 800 		/**< Definizione della lunghezza del display. */
#define SCREENHEIGHT 600		/**< Definizione dell'altezza del display. */
#define BACKGROUNDWIDTH 4000	/**< Definizione della lunghezza della mappa. */
#define LIMIT_WALK_UP 350		/**< Definizione del limite per lo spostamento verticale del primo livello. */
#define LIMIT_JUMP 555          /**< Definizione del limite sulle y dell'altezza del salto */
#define GRAVITY 1				/**< Definizione della forza di gravita'. */
#define NUMBER_SAMPLE 6			/**< Definizione del numero di tracce audio utilizzate. */
#define NUM_OBJ 4				/**< Definizione del numero di oggetti utilizzati. */

/** 
  * Definizione per accedere al campo data del primo elemento della lista del personaggio. 
  *	Per maggiori dettagli guardare ::Player o ::init_player. 
  */
#define PLAYER (static_cast<Player *>(p->data))

/** 
  * Definizione per accedere al campo data del primo elemento della lista del nemico.
  *	Per maggiori dettagli guardare ::Player e ::init_enemy. 
  */
#define ENEMY (static_cast<Player *>(e->data))

/** Definizione per accedere al campo data del primo elemento della lista del minion.
  *	Per maggiori dettagli guardare ::Player e ::init_minion. 
  */
#define MINION (static_cast<Player *>(m->data))

/** Definizione per accedere al campo data degli elementi Object della lista del personaggio. 
  *	Per maggiori dettagli guardare ::Object e ::init_player.*/
#define OBJECT_P (static_cast<Object *>(p->data))

/** Definizione per accedere al campo data degli elementi Object della lista del personaggio. 
  *	Per maggiori dettagli guardare ::Object e ::init_enemy.*/
#define OBJECT_E (static_cast<Object *>(e->data))

/** Definizione per accedere al campo data degli elementi Object della lista del personaggio. 
  *	Per maggiori dettagli guardare ::Object e ::init_minion.*/
#define OBJECT_M (static_cast<Object *>(m->data))

#define AMBRA al_map_rgb(255, 191, 0) 		/**< Definizione del colore ambra per i font delle scritte sul display. */
#define AZZURRO al_map_rgb(204, 229, 255) 	/**< Definizione del colore azzurro per i font delle scritte sul display. */
#define NERO al_map_rgb(0, 0, 0) 			/**< Definizione del colore nero utilizzato per la pulizia 
										 	  *  del buffer per il disegno sul display. */

enum Direction { DOWN, LEFT, RIGHT, UP }; /**< Definizione delle direzioni utilizzabili in partita. */

enum Type_Obj { ST_BULLET, BULLET, POTION, ARMOR }; /**< Definizione dei tipi di oggetto che e' possibile trovare nel gioco. */

/** Struttura dati relativa alle esplosioni. */
struct Explosion
{
	ALLEGRO_BITMAP *image;		/**< Identifica il puntatore all'immagine usata. */
	float x;					/**< identifica la coordinata dell'esplosione lungo l'asse orizzontale. */
	float y;					/**< identifica la coordinata dell'esplosione lungo l'asse verticale. */
	float pX;					/**< identifica la lunghezza del singolo frame. */
	float pY;					/**< identifica l'altezza del singolo frame. */
	float sourceX;				/**< identifica l'indice orizzontale del frame da disegnare. */
	float sourceY;				/**< identifica l'indice verticale del frame da disegnare. */
	bool visible;				/**< identifica la possibilita' dell'oggetto di essere disegnato. */
	int flag;					/**< identifica il numero di frame per gestire l'animazione di esplosione. */
};

/** Struttura dati relativa allo sfondo. */
struct Background			
{
	ALLEGRO_BITMAP *image;		/**< identifica il puntatore all'immagine usata. */
	float x;					/**< identifica la coordinata dello sfondo lungo l'asse orizzontale. */
	float y;					/**< identifica la coordinata dello sfondo lungo l'asse verticale. */
};

/** 
  * Struttura dati relativa agli oggetti collezionabili durante la partita.
  * Un'oggetto equipaggiato e' inserito a partire dal secondo nodo della lista del rispettivo personaggio.  
  * Un campo non necessario per un'oggetto creato è inizializzato a 0.
  */
struct Object
{
	ALLEGRO_BITMAP *image;	/**< identifica il puntatore all'immagine usata. */
	float x;				/**< identifica la coordinata dell'oggetto lungo l'asse orizzontale. */
	float y;				/**< identifica la coordinata dell'oggetto lungo l'asse verticale. */
	float pX;				/**< identifica la lunghezza del singolo frame. */
	float pY;				/**< identifica l'altezza del singolo frame. */
	float sourceX;			/**< identifica l'indice orizzontale del frame da disegnare. */
	float sourceY;			/**< identifica l'indice verticale del frame da disegnare. */
	float speed;			/**< identifica la velocita' di spostamento di un'oggetto. */
	Direction dir;			/**< identifica la direzione dell'oggetto. */
	bool visible;			/**< identifica la possibilita' dell'oggetto di essere disegnato. */
	Type_Obj type;			/**< identifica il tipo dell'oggetto. I tipi sono definiti in ::Type_Obj */
	float ammo;				/**< contiene il numero di munizioni ancora a disposizione per l'arma equipaggiata. */
	float strenght; 		/**< identifica la forza dell'arma, altrimenti e' inizializzata a 0.
							  *	 Per il calcolo della forza guardare ::strenght_calc.*/
	float health;			/**< identifica il valore della vita da aggiungere al personaggio con le pozioni, 
							  *	 altrimenti e' inizializzato a 0. Per il calcolo della vita guardare ::health_bullet.*/
	float healthmax;		/**< identifica il valore massimo della vita da aggiungere al personaggio con le pozioni, 
							  *	 altrimenti e' inizializzato a 0. */
	float armor; 			/**< identifica il valore della difesa da aggiungere al personaggio 
							  *	 quando l'oggetto è equipaggiato. Per il calcolo della difesa guardare ::armor_calc. */
	char bullet_path[128];	/**< contiene il percorso dell'immagine utilizzata per l'enetuale arma allocata o equipaggiata.*/
};

/** 
  * Struttura dati relativa ai personaggi. 
  * Player è il campo del primo nodo di ogni lista dei personaggi. 
  *	Un campo non necessario per il livello in cui ci si trova è inizializzato a 0.
  */
struct Player
{
	ALLEGRO_BITMAP *image;	/**< identifica il puntatore all'immagine usata. */
	char sex;				/**< identifica il sesso del personaggio selezionato dal giocatore. */
	float x;				/**< identifica la coordinata del personaggio lungo l'asse orizzontale. */
	float y;				/**< identifica la coordinata del personaggio lungo l'asse verticale. */
	float pX;				/**< identifica la lunghezza del singolo frame. */
	float pY;				/**< identifica l'altezza del singolo frame. */
	float sourceX;			/**< identifica l'indice orizzontale del frame da disegnare. */
	float sourceY;			/**< identifica l'indice verticale del frame da disegnare. */
	float speed;			/**< identifica la velocita' di spostamento del personaggio. Utilizzata nel primo livello */
	float pos_fire;			/**< identifica la posizione iniziale, sull'asse orizzontale, del proiettile sparato. */
	Direction dir;			/**< identifica la direzione dell'oggetto. */
	float armor; 			/**< identifica l'armatura base del persoanggio. 
							  *	 Per il calcolo della difesa guardare ::armor_calc. */
	float health;			/**< identifica il valore della vita del personaggio. 
							  *  Per il calcolo della vita guardare ::health_bullet.*/
	float healthmax;		/**< identifica il valore massimo della vita del personaggio. */
	unsigned int cooldown;	/**< identifica il numero di cicli da attendere prima di poter sparare un nuovo proiettile. */
	float velx;				/**< identifica la velocita' orizzontale del personaggio. Parametro tilizzato nel secondo livello. */
	float vely; 			/**< identifica la velocita' verticale del personaggio. Parametro tilizzato nel secondo livello. */
	float jump_speed;		/**< identifica la velocita' durante il salto. Parametro tilizzato nel secondo livello. */
};

/** Struttura dati relativa alle dissolvenze. */
struct Fader
{
	ALLEGRO_BITMAP *image;	/**< identifica il puntatore all'immagine usata. */
	float shade;			/**< identifica il valore della trasparenza. */
	bool visible;			/**< identifica la possibilita' della dissolvenza di essere disegnata. */
	bool flag;				/**< per evitare la stampa di parametri durante le schermate intermedie.*/
};

#endif /* DATA_STRUCT_H */

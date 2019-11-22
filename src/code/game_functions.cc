#include "../header/game_functions.h"

#include <random>
#include <cstring>
#include <cmath>
#include <ctime>

#define BULLET_T (static_cast<Object *>( bullet->data))

float strenght_calc(GList *p)
{
	DEFCON1(secure_player(p, "Strenght_calc"));
	p = search_obj(p, BULLET); // ricerco il miglior proiettile disponibile
							   // dal player

	float val = OBJECT_P->strenght; // valore che memorizza la forza dell'arma
									// attualmente in uso dal player

	p = g_list_first(p);   // riporta il puntatore del player alla testa della lista
	return val;
}

float armor_calc(GList *p)
{
	DEFCON1(secure_player(p, "Armor_calc"));
	p = g_list_first(p); // riporta il puntatore del player alla testa della lista
	GList *bullet = NULL; // puntatore d'appoggio per accedere al primo oggetto
                          // della lista
	float def = PLAYER->armor;	// valore che memorizza la difesa attuale
 								// del player
	bullet = search_obj(p, ARMOR);

	if (bullet != p && BULLET_T->type == ARMOR)
			def += BULLET_T->armor;

	if (def > 100.)   // 100-> max difesa.
		def = 100.;

	p = g_list_first(p); // riporta il puntatore del player alla testa della lista
	return def;
}

void health_bullet(GList *&p, GList *e)
{
	DEFCON1(secure_player(p, "Health_bullet::player"));
	DEFCON1(secure_player(p, "Health_bullet::enemy"));
	p = g_list_first(p); // riporta il puntatore p alla testa della lista
	e = g_list_first(e); // riporta il puntatore e alla testa della lista
	PLAYER->health -= strenght_calc(e) *(100. - armor_calc(p)) / 100.; //Dalla semplificazione della formula atk - (def*atk)/100; da proporzione.

	if (PLAYER->health <= 0.)
	{
		PLAYER->health = 0.;
		return;
	}
}

GList* search_obj(GList *p, Type_Obj type)
{
	DEFCON1(secure_player(p, "Search_obj::inizio"));

	p = g_list_first(p); // riporta il puntatore p alla testa della lista
	p = g_list_next(p);  // porta p all'elemento successivo, quindi al primo
						// oggetto in lista (st_bullet).

	while (g_list_length(p))
	{
		if (OBJECT_P->type == type)
		{
			if (type != BULLET || OBJECT_P->ammo >= 0.)
				return p;
			else
			{
				DEFCON1(cout << "Eliminazione proiettile" << endl);
				DEFCON1(al_rest(2));
				GList*t = NULL;
				t = p; // puntatore d'appoggio alla lista p
				al_destroy_bitmap(OBJECT_P->image);

				p = g_list_first(p);
				type = ST_BULLET;

				if (t->next == NULL)					//caso coda
				{
					t->prev->next = NULL;   // t punta all'elemento precedente e ne modifica il puntatore al successivo
					t->prev = NULL;
				}
				else if (t->prev == NULL)			//caso testa
				{
					t->next->prev = NULL;   // t punta all'elemento successivo e ne modifica il puntatore al precedente
					t->next = NULL;
				}
				else								//caso centrale
				{
					t->prev->next = t->next;
					t->next->prev = t->prev;
					t->next = t->prev = NULL;
				}
				g_list_free(t);  // dealloca il campo data della lista d'appoggio
			}
		}

		if (p->next == NULL)
		{
			if (type == BULLET)
			{
				p = g_list_first(p);
				type = ST_BULLET;  //se non ho trovato nessun proiettile
								   // passo alla ricerca dello st_bullet
			}
			else
				break;
		}

		p = g_list_next(p);
	}

	p = g_list_first(p);

	DEFCON1(secure_player(p, "Search_obj::fine"));
	return p;
}

void dir_bullet(GList *&p)
{
	DEFCON1(secure_player(p, "Dir_bullet"));
	p = g_list_first(p); // porta il puntatore p all'inizio della lista
	GList *bullet = search_obj(p, BULLET);

	BULLET_T->visible = true;

	if (PLAYER->cooldown <= 0)
	{
		PLAYER->cooldown = 80;

		switch (PLAYER->dir)
		{
		case static_cast<int>(DOWN) :
			BULLET_T->x = PLAYER->x + PLAYER->pX / 2 - BULLET_T->pX / 2;
			BULLET_T->y = PLAYER->y + PLAYER->pY / 2 - BULLET_T->pY / 2;
			BULLET_T->sourceX = BULLET_T->sourceY = 0.;
			BULLET_T->dir = DOWN;
			break;
		case static_cast<int>(LEFT) :
			BULLET_T->x = PLAYER->x + PLAYER->pX / 2 - BULLET_T->pX; // bullet_t->p.X per non far partire 
																	// il proiettile da dietro la schiena
																	// del giocatore
			BULLET_T->y = PLAYER->y + PLAYER->pY / 2 - BULLET_T->pY / 2;
			BULLET_T->sourceX = BULLET_T->pX;
			BULLET_T->sourceY = 0.;
			BULLET_T->dir = LEFT;
			break;
		case static_cast<int>(RIGHT) :
			BULLET_T->x = PLAYER->x + BULLET_T->pX / 2 + BULLET_T->pX / 2;
			BULLET_T->y = PLAYER->y + PLAYER->pY / 2 - BULLET_T->pY / 2;
			BULLET_T->sourceX = 2 * BULLET_T->pX;
			BULLET_T->sourceY = 0.;
			BULLET_T->dir = RIGHT;
			break;
		case static_cast<int>(UP) :
			BULLET_T->x = PLAYER->x + PLAYER->pX / 2 - BULLET_T->pX / 2;
			BULLET_T->y = PLAYER->y + PLAYER->pY / 2 - BULLET_T->pY / 2;
			BULLET_T->sourceX = 3 * BULLET_T->pX;
			BULLET_T->sourceY = 0.;
			BULLET_T->dir = UP;
			break;
		}
	}
}

static void update_bullet(GList *&p)
{
	DEFCON1(secure_player(p, "Update_bullet"));
	p = g_list_first(p); // porta il puntatore p alla testa della lista
	GList *bullet = search_obj(p, BULLET); // creo un puntatore d'appoggio per
										// accedere agli oggetti in coda

	if (PLAYER->cooldown > 0)
		PLAYER->cooldown--;

	switch (BULLET_T->dir)
	{
	case static_cast<int>(DOWN) :
		if (BULLET_T->y >= SCREENHEIGHT)
			BULLET_T->visible = false;
		if (BULLET_T->visible)
			BULLET_T->y += BULLET_T->speed;
		break;
	case static_cast<int>(LEFT) :
		if (BULLET_T->x <= 0 || BULLET_T->x <= PLAYER->pos_fire - SCREENWIDTH)
			BULLET_T->visible = false;
		if (BULLET_T->visible)
			BULLET_T->x -= BULLET_T->speed;
		break;
	case static_cast<int>(RIGHT) :
		if (PLAYER->x <= START_MOV_CAMERA) // se x del giocatore minore uguale del
									// punto di inizio di movimento della camera
		{
			if (BULLET_T->x >= SCREENWIDTH)
				BULLET_T->visible = false;
		}
		else if (PLAYER->x >= END_MOV_CAMERA) // se x del giocatore maggiore uguale della
										//fine del movimento della camera
		{
			if (BULLET_T->x >= BACKGROUNDWIDTH) // se x del giocatore maggiore uguale
											// del limite dell'immagine di sfondo
				BULLET_T->visible = false;
		}
		else
			if (BULLET_T->x >= PLAYER->pos_fire + START_MOV_CAMERA) // se x del giocatore
									// maggiore uguale alla posizione di fuoco + meta' schermo
				BULLET_T->visible = false;

		if (BULLET_T->visible)
			BULLET_T->x += BULLET_T->speed;
		break;
	case static_cast<int>(UP) :
		if (BULLET_T->y <= 0)
			BULLET_T->visible = false;
		if (BULLET_T->visible)
			BULLET_T->y -= BULLET_T->speed;
		break;
	}
}

void general_update_bullet(GList *&p, GList *&e, GList *&m)
{
	update_bullet(p);
	update_bullet(e);
	update_bullet(m);
}

static void collision_obj(GList *&p, Object &obj, ALLEGRO_SAMPLE *sound_effect[])
{
	DEFCON1(secure_player(p, "Collision_obj"));
	DEFCON1(secure_object(obj, "Collision_obj"));
	DEFCON1(secure_sample(sound_effect, "Collision_obj"));

	p = g_list_first(p); // porta il puntatore p all'inizio della lista
	GList *bullet = NULL; // puntatore d'appoggio per accedere agli oggetti della
						// lista

	if (PLAYER->health > 0 && obj.visible &&
		((obj.x + obj.pX) >= PLAYER->x) && (obj.x <= (PLAYER->x + PLAYER->pX)) &&
		((obj.y + obj.pY) >= PLAYER->y) && (obj.y <= (PLAYER->y + PLAYER->pY)))
	{						// se i rettangoli creati dagli estremi delle immagini
							// dei personaggi e degli oggetti si intersecano,
							// allora c'e' collisione

		/* il secondo parametro e' l'audio, 3.0 rappresenta
		* il volume corrente. Il terzo da dove viene l'audio.
		* < 0.0 sx, > 0.0 dx, 0.0 centrale. Il quarto la velocita'
		* di riproduzione.
		*/
		al_play_sample(sound_effect[3], 3.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

		switch (obj.type)
		{
		case static_cast<int>(POTION) :
			PLAYER->health += obj.health;
			PLAYER->healthmax += obj.healthmax;
			if (PLAYER->healthmax < PLAYER->health)
				PLAYER->health = PLAYER->healthmax;
			DEFCON1(cout << "Pozione raccolta" << endl);
			DEFCON1(al_rest(1));
			break;
		case static_cast<int>(BULLET) :
			bullet = search_obj(p, BULLET);
			if (BULLET_T->type == BULLET) // sostuituiamo il vecchio proiettile
			{
				if (BULLET_T->image != NULL)
					al_destroy_bitmap(BULLET_T->image); // se vi e' gia' un proiettile
										// distruggiamo l'immagine precedente prima
										// di cambiare il puntatore
				BULLET_T->image = obj.image;
				BULLET_T->strenght = obj.strenght;
				BULLET_T->visible = false;
				BULLET_T->pX = obj.pX;
				BULLET_T->pY = obj.pY;
				BULLET_T->type = obj.type;
				BULLET_T->speed = obj.speed;
				BULLET_T->ammo = obj.ammo;
				BULLET_T->sourceX = BULLET_T->sourceY = BULLET_T->x = BULLET_T->y = 0.;
				BULLET_T->dir = obj.dir;
				BULLET_T->health = BULLET_T->healthmax = BULLET_T->armor = 0.;
				strcpy(BULLET_T->bullet_path, obj.bullet_path); // copiamo il percorso del proiettile
																// per eventuale successivo caricamento
				DEFCON1(cout << "Proiettile sostituito" << endl);
				DEFCON1(al_rest(3));
			}
			else
			{
				Object *d = new Object; // creiamo un nuovo proiettile
				d->image = obj.image;
				d->pX = obj.pX;
				d->pY = obj.pY;
				d->ammo = obj.ammo;
				d->speed = obj.speed;
				d->type = BULLET;
				d->strenght = obj.strenght;
				d->visible = false;
				d->x = d->y = d->sourceX = d->sourceY = 0.;
				d->dir = obj.dir;
				d->health = d->healthmax = d->armor = 0.;
				strcpy(d->bullet_path, obj.bullet_path);
				DEFCON1(cout << "Lunghezza coda(pre-aggiunta) = " << g_list_length(p) << endl);
				p = g_list_append(p, d); // aggiungiamo il proiettile in coda alla lista
				DEFCON1(cout << "Proiettile aggiunto in coda " << endl);
				DEFCON1(cout << "Nuova lunghezza coda = " << g_list_length(p) << endl);
				DEFCON1(al_rest(3));
			}
			break;

		case static_cast<int>(ARMOR) :
			bullet = search_obj(p, ARMOR);
			if (bullet != p && BULLET_T->type == ARMOR) // sostituiamo la vecchia armatura
                                                    // bullet != p perche' se la search_obj
													// non trova oggetti ritorna p
			{
				BULLET_T->image = NULL;
				BULLET_T->armor = obj.armor;
				BULLET_T->healthmax = obj.healthmax;
				BULLET_T->visible = false;
				BULLET_T->pX = BULLET_T->pY = 0.;
				BULLET_T->type = obj.type;
				BULLET_T->sourceX = BULLET_T->sourceY = BULLET_T->x = BULLET_T->y = 0.;
				BULLET_T->speed = 0;
				BULLET_T->dir = UP;
				BULLET_T->ammo = BULLET_T->strenght = BULLET_T->health = BULLET_T->healthmax = 0.;
				strcpy(BULLET_T->bullet_path, "");
				DEFCON1(cout << "Armatura sostituita" << endl);
				DEFCON1(al_rest(3));
			}
			else 
			{
				Object *d = new Object; // creiamo una nuova armatura
				d->image = NULL;
				d->pX = d->pY = 0.;
				d->sourceX = d->sourceY = 0.;
				d->armor = obj.armor;
				d->type = ARMOR;
				d->visible = false;
				d->sourceX = d->sourceY = d->x = d->y = 0.;
				d->speed = 0;
				d->dir = UP;
				d->ammo = d->strenght = d->health = d->healthmax = 0.;
				strcpy(d->bullet_path, "");
				DEFCON1(cout << "Lunghezza coda(pre-aggiunta) = " << g_list_length(p) << endl);
				p = g_list_append(p, d);
				DEFCON1(cout << "Armatura aggiunta in coda " << endl);
				DEFCON1(cout << "Nuova lunghezza coda = " << g_list_length(p) << endl);
				DEFCON1(al_rest(3));
			}
			break;
		default:
			break;
		}

		obj.visible = false; // l'oggetto e' stato raccolto e puo' ora sparire
	}
}

/*	1 - p -> e bull
	2 - e -> p bull
	3 - p -> e
*/
static void collision(GList *&p, GList *&e, Explosion &l_e, Explosion &p_e, ALLEGRO_SAMPLE *sound_effect[])
{
	DEFCON1(secure_player(p, "Collision::player"));
	DEFCON1(secure_player(p, "Collision::enemy"));
	// -- 1 ----
	e = g_list_first(e); // porta il puntatore e alla testa della lista
	p = g_list_first(p); // porta il puntatore p alla testa della lista
	GList * bullet = search_obj(e, BULLET);

	if (PLAYER->health > 0 && BULLET_T->visible &&
		((BULLET_T->x + BULLET_T->pX) >= PLAYER->x) && (BULLET_T->x <= (PLAYER->x + PLAYER->pX)) &&
		((BULLET_T->y + BULLET_T->pY) >= PLAYER->y) && (BULLET_T->y <= (PLAYER->y + PLAYER->pY)))
	{
		BULLET_T->visible = false;
		p_e.x = PLAYER->x;
		p_e.y = PLAYER->y;
		p_e.visible = true;

		/* il secondo parametro e' l'audio, 1.0 rappresenta
		* il volume corrente. Il terzo da dove viene l'audio.
		* < 0.0 sx, > 0.0 dx, 0.0 centrale. Il quarto la velocita'
		* di riproduzione.
		*/
		al_play_sample(sound_effect[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

		health_bullet(p, e);			//funzione collisione vita
	}

	//--- 2 -----------   
	p = g_list_first(p);
	bullet = search_obj(p, BULLET);

	if (ENEMY->health > 0 && BULLET_T->visible &&
		((BULLET_T->x + BULLET_T->pX) >= ENEMY->x) && (BULLET_T->x <= (ENEMY->x + ENEMY->pX)) &&
		((BULLET_T->y + BULLET_T->pY) >= ENEMY->y) && (BULLET_T->y <= (ENEMY->y + ENEMY->pY)))
	{						// se i rettangoli creati dagli estremi delle immagini
							// dei personaggi e dei proiettili si intersecano,
							// allora c'e' collisione

		BULLET_T->visible = false;
		l_e.x = ENEMY->x;
		l_e.y = ENEMY->y;
		l_e.visible = true;

		/* il secondo parametro e' l'audio, 1.0 rappresenta
		* il volume corrente. Il terzo da dove viene l'audio.
		* < 0.0 sx, > 0.0 dx, 0.0 centrale. Il quarto la velocita'
		* di riproduzione.
		*/
		al_play_sample(sound_effect[1], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

		health_bullet(e, p);
	}

	//--- 3 -----------
	// Entrambi i puntatori alle liste puntano al primo elemento (struct PLayer)
	if (ENEMY->health > 0 &&
		((PLAYER->x + PLAYER->pX) >= ENEMY->x) && (PLAYER->x <= (ENEMY->x + ENEMY->pX)) &&
		((PLAYER->y + PLAYER->pY) >= ENEMY->y) && (PLAYER->y <= (ENEMY->y + ENEMY->pY)))
	{
		PLAYER->health = 0;
	}
}

void general_collision(GList *&p, GList *&e, GList *&m, Explosion &b_exp, Explosion &p_exp, Object obj[], ALLEGRO_SAMPLE *sound_effect[])
{
	collision(p, e, b_exp, p_exp, sound_effect);
	collision(p, m, b_exp, p_exp, sound_effect);
	collision_obj(p, obj[0], sound_effect);
	collision_obj(p, obj[1], sound_effect);
	collision_obj(p, obj[2], sound_effect);
	collision_obj(p, obj[3], sound_effect);
}

void casual_movement_enemy(GList *&e, GList *p)
{
	DEFCON1(secure_player(p, "Casual_movement_enemy::player"));
	DEFCON1(secure_player(e, "Casual_movement_enemy::enemy"));
	e = g_list_first(e); // porta il puntatore e alla testa della lista
	p = g_list_first(p); // porta il puntatore p alla testa della lista
	GList *bullet = search_obj(e, BULLET); // puntatore d'appoggio per accedere
										// agli oggetti della lista

	srand(time(0)); //genera il seme

	if (ENEMY->health > 0)
	{
		bool movement = true;

		if (((PLAYER->y + PLAYER->pY >= ENEMY->y) && (PLAYER->y + PLAYER->pY <= ENEMY->y + ENEMY->pY))
			|| ((PLAYER->x + PLAYER->pX >= ENEMY->x) && (PLAYER->x + PLAYER->pX <= ENEMY->x + ENEMY->pX)))   // * Se player nell'area coperta dalla lunghezza o larghezza del nemico
		{
			if (PLAYER->x + PLAYER->pX < ENEMY->x) // se personaggio e' alla sinistra del nemico
				ENEMY->dir = LEFT;

			else if (PLAYER->x > ENEMY->x + ENEMY->pX) // se e' a destra..
				ENEMY->dir = RIGHT;

			else if (PLAYER->y + PLAYER->pY < ENEMY->y) // se personaggio e' sopra al nemico
				ENEMY->dir = UP;
			else								// se e' a destra..
				ENEMY->dir = DOWN;

			movement = false; // disattiva il movimento del nemico, lasciandolo fermo per sparare

			if (!BULLET_T->visible && ENEMY->cooldown <= 0 && PLAYER->health > 0) // messa qui la funzione di sparo. Ora spara solo quando sa che c'e' il player.
			{
				ENEMY->pos_fire = ENEMY->x;
				dir_bullet(e);
			}
		}
		else
			ENEMY->dir = static_cast<Direction>(rand() % 4); // movimento casuale se non c'e' incrocio col player

		ENEMY->sourceY = ENEMY->dir * ENEMY->pY; // in base alla direzione scelta, sceglie la giusta colonna dell'immagine

		if (movement)
			for (int i = 0; i < 2; i++)
			{
				int mov = rand() % 2; // sceglie casualmente la distanza che il
									// nemico deve coprire muovendosi

				switch (ENEMY->dir)
				{
				case 1:
					mov = -mov;
				case 2:
					if (ENEMY->x > BACKGROUNDWIDTH - ENEMY->pX)
						ENEMY->x = BACKGROUNDWIDTH - ENEMY->pX;
					else if (ENEMY->x < 0.)
						ENEMY->x = 0.;
					ENEMY->x += mov;
					break;
				case 3:
					mov = -mov;
				case 0:
					if (ENEMY->y > SCREENHEIGHT - ENEMY->pY)
						ENEMY->y = SCREENHEIGHT - ENEMY->pY;
					else if (ENEMY->y < 0.)
						ENEMY->y = 0.;
					ENEMY->y += mov;
					break;
				}
			}
	}
}

void casual_movement_minion(GList *&m)
{
	DEFCON1(secure_player(m, "Casual_movement_minion"));
	srand(time(0)); //genera il seme

	GList *bullet = search_obj(m, BULLET); // puntatore d'appoggio per accedere
										// agli oggetti della struct

	if (MINION->health > 0 && !BULLET_T->visible && MINION->cooldown <= 0)
	{
		MINION->pos_fire = MINION->x; // salva la posizione di sparo. 
								// Serve per la gittata massima dei proiettili.
		dir_bullet(m);
	}

	MINION->dir = static_cast<Direction>(rand() % 4);
	MINION->sourceY = MINION->dir * MINION->pY; // in base alla direzione scelta, sceglie la giusta colonna dell'immagine

	for (int i = 0; i < 2; i++)
	{
		int mov = rand() % 2;

		switch (MINION->dir)
		{
		case static_cast<int>(LEFT) :
			mov = -mov;
		case static_cast<int>(RIGHT) :
			if (MINION->x > BACKGROUNDWIDTH - MINION->pX)
				MINION->x = BACKGROUNDWIDTH - MINION->pX;
			else if (MINION->x < 0.)
				MINION->x = 0.;
			MINION->x += mov;
			break;
		case static_cast<int>(UP) :
			if (MINION->y < LIMIT_WALK_UP - MINION->pY / 2)
				MINION->y = LIMIT_WALK_UP - MINION->pY / 2;
			mov = -mov;
		case static_cast<int>(DOWN) :
			if (MINION->y > SCREENHEIGHT - MINION->pY)
				MINION->y = SCREENHEIGHT - MINION->pY;
			else if (MINION->y < 0.)
				MINION->y = 0.;
			MINION->y += mov;
			break;
		}
	}
}

static void choose_type_obj(Object &obj)
{
	random_device rd; // genera un oggetto per l'utilizzo di rd() per valori randomici
	unsigned int scelta = 0;

	scelta = 1 + rd() % 3;

	switch (scelta)
	{
	case static_cast<int>(BULLET) :
		init_general_bullet(obj);
		break;
	case static_cast<int>(POTION) :
		init_general_potion(obj);
		break;
	case static_cast<int>(ARMOR) :
		init_general_armor(obj);
		break;
	}

	DEFCON1(secure_object(obj, "Choose_type_obj"));
}

static void random_spawn(Object &obj, int i)
{
	random_device rd; // genera un oggetto per l'utilizzo di rd() per valori randomici

	if (i == 0)
	{
		obj.x = 750.;
		obj.y = LIMIT_WALK_UP + rd() % (SCREENHEIGHT - LIMIT_WALK_UP - 50);  // 50 tiene conto dell'altezza degli oggetti 
	}
	else if (i == 1)
	{
		obj.x = 1550.;
		obj.y = LIMIT_WALK_UP + rd() % (SCREENHEIGHT - LIMIT_WALK_UP - 50);
	}
	else if (i == 2)
	{
		obj.x = 2400.;
		obj.y = LIMIT_WALK_UP + rd() % (SCREENHEIGHT - LIMIT_WALK_UP - 50);
	}
	else
	{
		obj.x = 3200.;
		obj.y = LIMIT_WALK_UP + rd() % (SCREENHEIGHT - LIMIT_WALK_UP - 50);
	}
	choose_type_obj(obj);
	DEFCON1(secure_object(obj, "Random_spawn"));
}

static void random_spawn_2(Object &obj, int i)
{
	random_device rd; // genera un oggetto per l'utilizzo di rd() per valori randomici

	obj.y = 555 - obj.pY;

	if (i == 0)
		obj.x = 750.;
	else if (i == 1)
		obj.x = 1550.;
	else if (i == 2)
		obj.x = 2400.;
	else
		obj.x = 3200.;

	choose_type_obj(obj);
	DEFCON1(secure_object(obj, "Random_spawn_2"));
}

void general_random_spawn(Object obj[], unsigned int lvl)
{
	if (lvl == 1)
		for (int k = 0 ; k < NUM_OBJ ; k++)
			random_spawn(obj[k], k);		// passa l'oggetto ed un indice, utilizzato
											// per decidere le sue coordinate
	else if (lvl == 3)
		for (int k = 0 ; k < NUM_OBJ ; k++)  
			random_spawn_2(obj[k], k);     // passa l'oggetto ed un indice, utilizzato
											// per decidere le sue coordinate
}

void casual_movement_gravity(GList *&m, bool &jump)
{
	DEFCON1(secure_player(m, "Casual_movement_gravity"));
	srand(time(0)); // genera il seme per l'utilizzo di rand()

	GList *bullet = search_obj(m, BULLET);

	if (MINION->health > 0 && !BULLET_T->visible && MINION->cooldown <= 0)
	{
		MINION->pos_fire = MINION->x; // memorizza la posizione di sparo.
								// Utilizzata per determinare la gittata massima
								// del proiettile
		dir_bullet(m);
	}

	m = g_list_first(m); // porta il puntatore m all'inizio della lista
	MINION->dir = static_cast<Direction>(1 + rand() % 3);

	if (MINION->dir == LEFT || MINION->dir == RIGHT)
		MINION->sourceY = MINION->dir * MINION->pY; // in base alla direzione scelta, sceglie la giusta colonna dell'immagine

	switch (MINION->dir)
	{
	case static_cast<int>(LEFT) :
		MINION->velx = -MINION->speed;
		break;
	case static_cast<int>(RIGHT) :
		if (MINION->x > BACKGROUNDWIDTH - MINION->pX)
		{
			MINION->x = BACKGROUNDWIDTH - MINION->pX;
			MINION->velx = MINION->speed;
			break;
		}
		MINION->velx = MINION->speed;
		break;
	case static_cast<int>(UP) :
		if (jump)
		{
			MINION->vely = -(MINION->jump_speed); // componente verticale della velocita'.
							// Gli si da una velocita' negativa per far saltare il personaggio.
							// Successivamente gli verra' sommata la gravita' (positiva)
							// per riportarlo a terra
			jump = false;
		}
		break;
	default:
		break;
	}
	if (!jump)
	{
		DEFCON2(cout << "Jump enemy " << MINION->y + MINION->pY << endl);
		DEFCON2(cout << "vely enemy = " << MINION->vely << endl);
		MINION->vely += GRAVITY; // componente verticale della velocita', serve
								// per riportare a terra il personaggio una volta
								// che esso salta
	}
	else
		MINION->vely = 0;

	MINION->x += MINION->velx;
	MINION->y += MINION->vely;

	jump = (MINION->y + MINION->pY >= 555); // definisce l'altezza massima del salto

	if (jump)
		MINION->y = 555 - MINION->pY; // non permette di saltare piu' in alto di quanto previsto
}

#include "../header/interface.h"

#define OBJECT_E (static_cast<Object *>(e->data))
#define OBJECT_M (static_cast<Object *>(m->data))

void player_movement(ALLEGRO_KEYBOARD_STATE &key_state, GList *&p, bool &active)
{
	DEFCON1(secure_player(p,"Player_movement"));
	if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))  // se sto premendo il tasto DOWN
	{
		if (PLAYER->y > SCREENHEIGHT - PLAYER->pY)
			PLAYER->y = SCREENHEIGHT - PLAYER->pY;

		PLAYER->y += PLAYER->speed;
		PLAYER->dir = DOWN;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_UP)) // se sto premendo il tasto UP
	{
		if (PLAYER->y < LIMIT_WALK_UP - PLAYER->pY / 2)
			PLAYER->y = LIMIT_WALK_UP - PLAYER->pY / 2;

		PLAYER->y -= PLAYER->speed;
		PLAYER->dir = UP;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT)) // se sto premendo il tasto RIGHT
	{
		if (PLAYER->x > BACKGROUNDWIDTH - PLAYER->pX)
			PLAYER->x = BACKGROUNDWIDTH - PLAYER->pX;

		PLAYER->x += PLAYER->speed;
		PLAYER->dir = RIGHT;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT)) // se sto premendo il tasto LEFT
	{
		if (PLAYER->x < 0)
			PLAYER->x = 0;

		PLAYER->x -= PLAYER->speed;
		PLAYER->dir = LEFT;
	}
	else
		active = false; // il personaggio e' fermo e quindi non avverranno animazioni
}

void menu_pre_game(ALLEGRO_FONT *font_1, ALLEGRO_EVENT_QUEUE *event_queue, GList *&p, ALLEGRO_DISPLAY *display, unsigned int &level)
{	
	bool start = false;
	Background starter;
	init_starter(starter); // inizializza schermata iniziale

	while (!start)
	{
		al_draw_bitmap(starter.image, starter.x, starter.y, 0);
		al_draw_text(font_1, AMBRA, starter.x, ALLEGRO_ALIGN_LEFT, 0, "Premere un tasto qualsiasi per iniziare a giocare");
		al_flip_display();	// per mostrare a display
		al_clear_to_color(NERO); // per pulire il display una volta disegnato

		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);  //aspetto un evento

		if (events.type == ALLEGRO_EVENT_KEY_UP) //evento->un tasto viene premuto e rilasciato
			start = true;	// fa iniziare il gioco
	}

	read_save(p, start, level, display);
	al_flush_event_queue(event_queue);

	while (start)
	{
		al_draw_bitmap(starter.image, starter.x, starter.y, 0); //dobbiamo creare una nuova immagine coi due personaggi
		al_draw_text(font_1, AMBRA, starter.x, ALLEGRO_ALIGN_LEFT, 0, "Premere M per scegliere il maschio o F per la femmina");
		al_flip_display(); // per mostrare a display
		al_clear_to_color(NERO); // per pulire il display una volta disegnato

		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_DOWN && events.keyboard.keycode == ALLEGRO_KEY_F)  // controlla che il tasto F sia premuto in quell'istante
		{
			init_player(p, 'f');
			start = false;
		}
		else if (events.type == ALLEGRO_EVENT_KEY_DOWN && events.keyboard.keycode == ALLEGRO_KEY_M) // controlla che il tasto M sia premuto in quell'istante
		{
			init_player(p, 'm');
			start = false;
		}
	}
	al_flush_event_queue(event_queue); // svuota la event queue
}

void make_your_choice(GList *p, Background background, ALLEGRO_FONT *font_1, ALLEGRO_DISPLAY *display, unsigned int &level, bool &done)
{
	DEFCON1(secure_player(p,"Make_your_choice"));
	al_draw_bitmap(background.image, background.x, background.y, 0);

	al_draw_text(font_1, AMBRA, background.x, ALLEGRO_ALIGN_LEFT, 0, "FINE PRIMO LIVELLO");

	al_flip_display(); // per mostrare a display
	al_clear_to_color(NERO); // per pulire il display una volta disegnato


	switch (al_show_native_message_box(display, "SCELTA SALVATAGGIO", "DOMANDA:", "SALVARE?",
		"Salva e continua|Continua senza salvare|Salva ed esci|Esci senza salvare", ALLEGRO_MESSAGEBOX_WARN))
	{
	case 1:
		write_save(p, level); // salva..
	case 2:
		level++;     // ...e continua
		break;   	
	case 3:
		write_save(p, level);  // salva..
	case 4:
		done = true;  // ...ed esci
		break;
	}
}

void death_fade(Fader &fade, Background &background, GList *&p, GList *&e, bool &done)
{
	DEFCON1(secure_player(p,"Death_fade::player"));
	DEFCON1(secure_player(e,"Death_fade::enemy"));
	DEFCON4(cout << "FADE SHADE DEATH = " << fade.shade << endl);
	fade.visible = true;
	if (fade.shade < 255 && !fade.flag) // 255 -> limite colore rgb
		fade.shade += 1.;
	else
	{
		al_destroy_bitmap(background.image);	// distruggo il puntatore precedente
		background.image = al_load_bitmap("../media/images/background/game_over.png"); // carico una nuova immagine di background
		if (PLAYER->x >= START_MOV_CAMERA && PLAYER->x < END_MOV_CAMERA)
			background.x = PLAYER->x - 600;  // Per centrare scritta "sei morto" dopo inizio spostamento camera
		else if (PLAYER->x >= END_MOV_CAMERA)
			background.x = BACKGROUNDWIDTH - 1000; // Per centrare scritta "sei morto" dopo fine spostamento camera
		else
			background.x = -200.; // per centrare scritta "sei morto" negli altri casi
		fade.flag = true;   // fade presente, stop a disegni oggetti/personaggi
		fade.shade -= 3.;
		if (fade.shade <= 0.)
		{
			fade.shade = 0.;
			done = true;
		}
	}
}

void draw(Background background, GList *p, GList *e, GList *m, Explosion b_exp, Explosion p_exp, Fader &fade,
	ALLEGRO_FONT *font_1, Object obj[])
{
	DEFCON1(secure_player(p,"Draw::player"));
	DEFCON1(secure_player(e,"Draw::enemy"));
	DEFCON1(secure_player(m,"Draw::minion"));
	al_draw_bitmap(background.image, background.x, background.y, 0);

	if (!fade.flag)
	{
		float x = PLAYER->x - START_MOV_CAMERA;
		if (PLAYER->x <= START_MOV_CAMERA)
			x = ALLEGRO_ALIGN_LEFT;  //per tenere la camera allineata e non
									// andare oltre il bordo sinistro dell'immagine
		else if (PLAYER->x >= END_MOV_CAMERA)
			x = BACKGROUNDWIDTH - SCREENWIDTH; // per tenere la camera allineata e non
											// andare oltre il bordo destro dell'immagine

		al_draw_textf(font_1, AMBRA, x, ALLEGRO_ALIGN_LEFT, 0, "Life: %-6.2f | %-6.2f", PLAYER->health, PLAYER->healthmax);
		al_draw_textf(font_1, AMBRA, x + 180, ALLEGRO_ALIGN_LEFT, 0, "Armor: %-6.0f", armor_calc(p));
		al_draw_textf(font_1, AMBRA, x + 280, ALLEGRO_ALIGN_LEFT, 0, "Strenght: %-6.0f", strenght_calc(p));

		p = search_obj(p, BULLET);

		if (OBJECT_P->type == BULLET)
			al_draw_textf(font_1, AMBRA, x + 400, ALLEGRO_ALIGN_LEFT, 0, "Bullets: %-6.0f", OBJECT_P->ammo);
		else
			al_draw_text(font_1, AMBRA, x + 400, ALLEGRO_ALIGN_LEFT, 0, "Bullets: Inf");

		if (ENEMY->health > 0)
		{
			al_draw_textf(font_1, AZZURRO, x + 700, ALLEGRO_ALIGN_LEFT, 0, "Life: %-6.2f", ENEMY->health);
			DEFCON4(al_draw_textf(font_1, AZZURRO, x + 700, 20, 0, "Armor: %-6.0f", armor_calc(e));
				al_draw_textf(font_1, AZZURRO, x + 700, 40, 0, "Strenght: %-6.0f", strenght_calc(e)));
		}
		DEFCON4(if (MINION->health > 0)
		{
			al_draw_textf(font_1, AZZURRO, x + 700, ALLEGRO_ALIGN_LEFT, 0, "Life: %-6.0f", MINION->health);
			al_draw_textf(font_1, AZZURRO, x + 700, 20, 0, "Armor: %-6.0f", armor_calc(m));
			al_draw_textf(font_1, AZZURRO, x + 700, 40, 0, "Strenght: %-6.0f", strenght_calc(m));
		});

		if (obj[0].visible)
		{
			if (obj[0].type != BULLET)
				al_draw_bitmap(obj[0].image, obj[0].x, obj[0].y, 0);
			else
				al_draw_bitmap_region(obj[0].image, obj[0].sourceX, obj[0].sourceY, obj[0].pX, obj[0].pY, obj[0].x, obj[0].y, 0);
		}
		if (obj[1].visible)
		{
			if (obj[1].type != BULLET)
				al_draw_bitmap(obj[1].image, obj[1].x, obj[1].y, 0);
			else
				al_draw_bitmap_region(obj[1].image, obj[1].sourceX, obj[1].sourceY, obj[1].pX, obj[1].pY, obj[1].x, obj[1].y, 0);
		}
		if (obj[2].visible)
		{
			if (obj[2].type != BULLET)
				al_draw_bitmap(obj[2].image, obj[2].x, obj[2].y, 0);
			else
				al_draw_bitmap_region(obj[2].image, obj[2].sourceX, obj[2].sourceY, obj[2].pX, obj[2].pY, obj[2].x, obj[2].y, 0);
		}
		if (obj[3].visible)
		{
			if (obj[3].type != BULLET)
				al_draw_bitmap(obj[3].image, obj[3].x, obj[3].y, 0);
			else
				al_draw_bitmap_region(obj[3].image, obj[3].sourceX, obj[3].sourceY, obj[3].pX, obj[3].pY, obj[3].x, obj[3].y, 0);
		}
		if ((p = search_obj(p, BULLET)) != NULL && OBJECT_P->visible)
			al_draw_bitmap_region(OBJECT_P->image, OBJECT_P->sourceX, OBJECT_P->sourceY, OBJECT_P->pX, OBJECT_P->pY, OBJECT_P->x, OBJECT_P->y, 0);

		if ((e = search_obj(e, ST_BULLET)) != NULL && OBJECT_E->visible)
			al_draw_bitmap_region(OBJECT_E->image, OBJECT_E->sourceX, OBJECT_E->sourceY, OBJECT_E->pX, OBJECT_E->pY, OBJECT_E->x, OBJECT_E->y, 0);

		if ((m = search_obj(m, ST_BULLET)) != NULL && OBJECT_M->visible)
			al_draw_bitmap_region(OBJECT_M->image, OBJECT_M->sourceX, OBJECT_M->sourceY, OBJECT_M->pX, OBJECT_M->pY, OBJECT_M->x, OBJECT_M->y, 0);

		p = g_list_first(p); // riporta il puntatore p alla testa della lista
		if (PLAYER->health > 0)
		{
			al_draw_bitmap_region(PLAYER->image, PLAYER->sourceX, PLAYER->sourceY * al_get_bitmap_height(PLAYER->image) / 4,
				PLAYER->pX, PLAYER->pY, PLAYER->x, PLAYER->y, 0);
		}
		e = g_list_first(e); // riporta il puntatore e alla testa della lista
		if (ENEMY->health > 0)
			al_draw_bitmap_region(ENEMY->image, ENEMY->sourceX, ENEMY->sourceY, ENEMY->pX, ENEMY->pY, ENEMY->x, ENEMY->y, 0);

		m = g_list_first(m); // riporta il puntatore m alla testa della lista
		if (MINION->health > 0)
			al_draw_bitmap_region(MINION->image, MINION->sourceX, MINION->sourceY, MINION->pX, MINION->pY, MINION->x, MINION->y, 0);
	}

	if (b_exp.visible)
	{
		if (ENEMY->health > 0)
			al_draw_bitmap_region(b_exp.image, b_exp.sourceX, 0, b_exp.pX, b_exp.pY, b_exp.x + ENEMY->pX / 2 - b_exp.pX / 2,
				b_exp.y + ENEMY->pY / 2 - b_exp.pY / 2, 0);
		else
			al_draw_bitmap_region(b_exp.image, b_exp.sourceX, 0, b_exp.pX, b_exp.pY, b_exp.x + MINION->pX / 2 - b_exp.pX / 2,
				b_exp.y + MINION->pY / 2 - b_exp.pY / 2, 0);
	}
	if (p_exp.visible)
		al_draw_bitmap_region(p_exp.image, p_exp.sourceX, p_exp.sourceY, p_exp.pX, p_exp.pY, p_exp.x + PLAYER->pX / 2 - p_exp.pX / 2,
			p_exp.y + PLAYER->pY / 2 - p_exp.pY / 2, 0);

	if (fade.visible)
	{
		al_draw_tinted_bitmap(fade.image, al_map_rgba(0, 0, 0, fade.shade), 0, 0, 0);
		if (fade.shade == 1 && fade.flag && PLAYER->health <= 0)
		{
			al_rest(2);  // ferma il gioco per due secondi
			fade.visible = false; // fade finito
		}
	}
	al_flip_display(); // per mostrare a display
	al_clear_to_color(NERO); // per pulire il display una volta disegnato
}

static void camera_update(float *camera_position, GList *p)
{
	DEFCON1(secure_player(p, "Camera_update"));
	p = g_list_first(p); // porta il puntatore p alla testa della lista

	camera_position[0] = -(SCREENWIDTH / 2) + (PLAYER->x + PLAYER->pX / 2); // se centro di p compreso tra 400 e 3600
																			// la camera si sposta. 400 = SCREENWIDTH /2
	if (camera_position[0] < 0)
		camera_position[0] = 0;
	if (camera_position[0] > BACKGROUNDWIDTH - SCREENWIDTH)
		camera_position[0] = BACKGROUNDWIDTH - SCREENWIDTH;
}

void mod_camera(ALLEGRO_TRANSFORM &camera, float *camera_position, GList *&p)
{
	DEFCON1(secure_player(p,"Mod_camera"));
	camera_update(camera_position, p); // aggiornamento camera

	al_identity_transform(&camera); // per camera
	al_translate_transform(&camera, -camera_position[0], 0); // per movimento camera solo orizzontale
	al_use_transform(&camera); // per camera
}

void player_fire(GList *&p, ALLEGRO_KEYBOARD_STATE &key_state)
{
	DEFCON1(secure_player(p,"Player_fire"));
	if (PLAYER->health > 0 && PLAYER->cooldown <= 0 && al_key_down(&key_state, ALLEGRO_KEY_SPACE))
	{
		PLAYER->pos_fire = PLAYER->x;
		DEFCON4(cout << "Player x = " << PLAYER->x << "&& Player posfire = " << PLAYER->pos_fire<<endl);
		p = search_obj(p, BULLET);

		if (OBJECT_P->type == BULLET)
			OBJECT_P->ammo--;

		if (!OBJECT_P->visible) //  condizioni per lo sparo
			dir_bullet(p);
	}

	p = g_list_first(p); //porta il puntatore p alla testa della lista
						// da fare per via della search_obj.
}

void change_frame(GList *&p, GList *&e, GList *&m, Explosion &b_exp, Explosion &p_exp, bool active)
{
	DEFCON1(secure_player(p,"Change_frame::player"));
	DEFCON1(secure_player(e,"Change_frame::enemy"));
	DEFCON1(secure_player(m,"Change_frame::minion"));
	if (b_exp.visible)
	{
		if (b_exp.flag <= al_get_bitmap_width(b_exp.image) / b_exp.pX) // 13-> numero di frame immagine b_exp.image
		{
			b_exp.sourceX += b_exp.pX; // mando avanti di un frame
			b_exp.flag++; // per sapere quando smettere di cambiare frame
		}
		else
		{
			b_exp.flag = 0;
			b_exp.visible = false;
			b_exp.sourceX = 0; // riporta al primo frame dell'esplosione
		}
	}

	if (p_exp.visible)
	{
		if (p_exp.flag > 0 && p_exp.flag < (al_get_bitmap_width(p_exp.image) / p_exp.pX)) // 5 -> numero di frame immagine p_exp.image
			p_exp.sourceX += p_exp.pX; // mando avanti di un frame di riga
		else if (p_exp.flag == (al_get_bitmap_width(p_exp.image) / p_exp.pX))
		{
			p_exp.sourceY += p_exp.pY; // mando avanti di un frame di colonna
			p_exp.flag = 0;
			p_exp.sourceX = 0;  // riporta al primo frame di riga
		}

		if (p_exp.sourceY >= p_exp.pY * (al_get_bitmap_height(p_exp.image) / p_exp.pY)) // *4->numero di colonne dell'immagine
		{
			p_exp.visible = false;
			p_exp.sourceY = 0; // riporta al primo frame di colonna
		}
		p_exp.flag++;
	}

	e = g_list_first(e);	// riporta il puntatore e alla testa della lista
	p = g_list_first(p);	// riporta il puntatore p alla testa della lista

	if (MINION->health > 0)
		MINION->sourceX += MINION->pX;	// manda avanti di un frame i minion

	if (ENEMY->health > 0)
		ENEMY->sourceX += ENEMY->pX; // manda avanti di un frame il nemico

	if (active)
		PLAYER->sourceX += PLAYER->pX;  // per frame in movimento
	else
		PLAYER->sourceX = 2 * PLAYER->pX; // per frame fermo

	if (PLAYER->sourceX >= al_get_bitmap_width(PLAYER->image))  // se arrivato a fine riga...
		PLAYER->sourceX = 0;									// ...riporta all'inizio
	if (MINION->sourceX >= al_get_bitmap_width(MINION->image)) // se arrivato a fine riga..
		MINION->sourceX = 0;									// ...riporta all'inizio
	if (ENEMY->sourceX >= al_get_bitmap_width(ENEMY->image))	// se arrivato a fine riga...
		ENEMY->sourceX = 0;										// ...riporta all'inizio

	PLAYER->sourceY = PLAYER->dir;	// Sceglie la giusta colonna dell'immagine in base alla direzione
}

void end_level(GList *&p, GList *&e, Fader &fade, Background &background, unsigned int &lvl)
{
	DEFCON1(secure_player(p,"End_level::player"));
	DEFCON1(secure_player(e,"End_level::enemy"));
	DEFCON4(cout << "FADE SHADE END LEVEL = " << fade.shade << endl);
	fade.visible = true;

	if (fade.shade < 255 && !fade.flag) // 255 -> limite colore rgb
		fade.shade += 1;
	else
	{
		al_destroy_bitmap(background.image);
		background.image = al_load_bitmap("../media/images/background/start.png");
		PLAYER->x = 0;
		fade.flag = true;
		fade.shade -= 3;
		if (fade.shade <= 0)
		{
			fade.shade = 0;
			lvl++;
			fade.visible = false; // fade finito
			if (ENEMY->health > 0)
				al_destroy_bitmap(ENEMY->image);
			return;
		}
	}
}

void spawn_minions(GList *&m, GList *&e, GList *&p, bool &run, Fader &fade, Background &background, unsigned int &lvl, bool &done)
{
	DEFCON1(secure_player(p, "Spawn_minions::player"));
	DEFCON1(secure_player(e, "Spawn_minions::enemy"));
	DEFCON1(secure_player(m, "Spawn_minions::minion"));
	static int minion_counter = 0;

	if (minion_counter > 0 && PLAYER->health <= 0)
		minion_counter = 0;

	if (ENEMY->health <= 0 && run)
		end_level(p, e, fade, background, lvl);

	if (minion_counter >= 3 && MINION->health <= 0)
	{
		/* L'ultimo minion e' stato spawnato, quindi rendo visibile il boss finale.
		 * Qui finisce la funzione di spawn
		 */
		al_destroy_bitmap(MINION->image);
		ENEMY->health = ENEMY->healthmax = 200.;
		run = true;
		minion_counter = 0;
		return;
	}

	if (!run)
	{
		m = g_list_first(m);
		e = g_list_first(e);


		/* Se il minion e' morto, spawno il successivo 800(SCREENWIDTH)
		 * piu' avanti
 		 */
		if (MINION->health <= 0. && ENEMY->health <= 0.)
		{
			MINION->x += SCREENWIDTH;
			MINION->health = 100.;
			minion_counter++;
		}
	}
}

void player_movement_gravity(ALLEGRO_KEYBOARD_STATE &key_state, GList *&p, bool &active, bool &jump)
{
	DEFCON1(secure_player(p,"Player_movement_gravity"));
	if (al_key_down(&key_state, ALLEGRO_KEY_UP))
	{
		if (PLAYER->y < LIMIT_WALK_UP - PLAYER->pY / 2)
			PLAYER->y = LIMIT_WALK_UP - PLAYER->pY / 2;  // per tenere il personaggio sulla
														// giusta riga
		else if (PLAYER->x < 0)
			PLAYER->x = 0;
		else if (PLAYER->x > BACKGROUNDWIDTH - PLAYER->pX)
			PLAYER->x = BACKGROUNDWIDTH - PLAYER->pX;
		active = false;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
	{
		if (PLAYER->x > BACKGROUNDWIDTH - PLAYER->pX)
			PLAYER->x = BACKGROUNDWIDTH - PLAYER->pX;

		PLAYER->velx = PLAYER->speed;

		PLAYER->dir = RIGHT;
	}
	else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
	{
		if (PLAYER->x < 0)
			PLAYER->x = 0;

		PLAYER->velx = -(PLAYER->speed);

		PLAYER->dir = LEFT;
	}
	else
	{
		PLAYER->velx = 0;
		active = false;
	}

	if (al_key_down(&key_state, ALLEGRO_KEY_UP) && jump)
	{
		PLAYER->vely = -(PLAYER->jump_speed); // velocita' negativa a cui poi verra'
											// addizionata la gravita' per riportare il
											// personaggio a terra dopo il salto
		jump = false;
	}

	if (!jump)
	{
		DEFCON2(cout << "Jump player " << PLAYER->y + PLAYER->pY << endl);
		DEFCON2(cout << "vely player = " << PLAYER->vely << endl);
		PLAYER->vely += GRAVITY; // riporta il personaggio a terra dopo il salto
	}
	else
		PLAYER->vely = 0;

	PLAYER->x += PLAYER->velx;
	PLAYER->y += PLAYER->vely;

	jump = (PLAYER->y + PLAYER->pY >= LIMIT_JUMP); // 555->limite salto

	if (jump)
		PLAYER->y = LIMIT_JUMP - PLAYER->pY;
}

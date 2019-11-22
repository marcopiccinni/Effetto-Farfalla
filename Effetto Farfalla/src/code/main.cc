/** @mainpage <div style="background-color:Red"><b><div align="Center">EFFETTO FARFALLA</b></div></div>
  *
  * <img src="http://i65.tinypic.com/ohvgus.png"></img>
  
  * <span style ="color:Blue"><i>Videogioco a scorrimento orizzontale, suddiviso in piu' livelli,
  * ed immerso in un'ambientazione fantasy.</i></span>
  
  * @subsection first
  * All'avvio e' possibile scegliere se utilizzare un personaggio maschile o uno femminile,
  * ognuno dei quali avra' un proprio tipo di proiettile.<br>
  * Durante il gioco e' possibile raccogliere oggetti per modificare le proprie statistiche.<br>
  * Il movimento dei nemici e la scelta degli oggetti e' generato in modo randomico.
  * Il gioco dispone di una funzione di salvataggio e caricamento per riprendere
  * la sessione una volta interrotta.

  * @subsection  first1
  * <span style="color:Blue">Livello 1:</span> Permette al giocatore di familiarizzare con le meccaniche   
  * di gioco, immergendolo in un livello dalla difficolta' non troppo complessa.

  * @subsection first2
  * <span style="color:Blue">Livello 2:</span> Livello decisamente piu' complesso del precedente.<br>
  * &emsp;&emsp;&emsp;&emsp;&ensp; Il gameplay cambia grazie all'introduzione della gravita', permettendo al giocatore e ai nemici
  * di saltare per schivare i proiettili. 
  *
  * @subsection info
  * <span style="color:Blue">Informazioni:</span> EFFETTO FARFALLA e' un progetto open-source,
  * che lascia a chiunque la possibilita' di aggiungere livelli e funzionalita' in modo semplice ed efficace.<br>
  * Il gioco e' suddiviso in piu' moduli: <br>
  *
  * - secure.h : Contiene le funzioni per il debugging. <br>  
  * - data_struct.h : Contiene le strutture dati necessarie per il corretto funzionamento del gioco. <br>
  * - inits.h : Contiene tutte le inizializzazioni e le deallocazioni delle istanze utilizzate. <br>
  * - game_functions.h : Contiene le funzioni di cui si serve il gioco. <br>
  * - interface.h : Contiene tutte le funzioni necessarie alla corretta visualizzazione dell'interfaccia grafica. <br>  
  * - IOfile.h : Contiene le funzioni necessarie per il salvataggio ed il caricamento da file. <br><br><br>
  *
  * <div align="Center"><span style =" font-size: 40px; color:Blue"><b>Be the change that you wish to see in the world.</b></span></div>
  * <div align="Right">Mahatma Gandhi&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;</div> <br><br>
  * 
  *
  * @authors Daniele Tortoli <br> Marco Piccinni
  * @version 1.1
  */

#include"../header/secure.h"
#include "../header/inits.h"
#include "../header/interface.h"
#include "../header/game_functions.h"
#include "../header/data_struct.h"

int main()
{
	ALLEGRO_DISPLAY *display;

	const float FPS = 60.0;
	const float frameFPS = 15.0;

	if  (!al_init())				// Funzione base di allegro
	{
		DEFCON1(cout<<"Inizializzazione allegro fallita"<< endl); 
		DEFCON1(al_rest(5); abort());
	}
	display = al_create_display(SCREENWIDTH, SCREENHEIGHT);		//Creazione del display di gioco

	if (!display) 												//Controllo sulla coorretta allocazione del display
	{
		DEFCON1(cout << "Inizializzazione display fallita" << endl);
		DEFCON1(al_rest(5); abort());
	}

	al_set_window_position(display, 200, 50);					//Vengono settati titolo e coordinate
	al_set_window_title(display, "EFFETTO FARFALLA");

	if (!al_install_keyboard())									//Funzione di Allegro per l'utilizzo della tastiera
	{
		DEFCON1(cout<<"Inizializzazione allegro fallita"<< endl); 
		DEFCON1(al_rest(5); abort());
	}
	
	if (!al_init_image_addon())									//Funzione di Allegro per l'utilizzo di immagini
	{
		DEFCON1(cout<<"Inizializzazione allegro fallita"<< endl); 
		DEFCON1(al_rest(5); abort());
	}
	
	al_init_font_addon();										//Funzione di Allegro per l'utilizzo di font
																//ritorna void
	
	if(!al_init_ttf_addon())									//Funzione di Allegro per l'utilizzo di font
	{
		DEFCON1(cout<<"Inizializzazione allegro fallita"<< endl); 
		DEFCON1(al_rest(5); abort());
	}
	
	if(!al_install_audio())											//Funzione di Allegro per l'utilizzo di suoni
	{
		DEFCON1(cout<<"Inizializzazione allegro fallita"<< endl); 
		DEFCON1(al_rest(5); abort());
	}
	
	if(!al_init_acodec_addon())										//Funzione di Allegro per l'utilizzo di suoni
	{
		DEFCON1(cout<<"Inizializzazione allegro fallita"<< endl); 
		DEFCON1(al_rest(5); abort());
	}
	
	//Dichiarazione delle pricipali strutture dati presenti nel gioco
	Background background;
	Explosion b_exp;
	Explosion p_exp;
	Fader fade;
	ALLEGRO_FONT *font_1;
	Object obj[NUM_OBJ];

	/* Da mettere prima della definizione dei SAMPLE.
	 * Serve per allocare i sample.	*/
	al_reserve_samples(NUMBER_SAMPLE);

	ALLEGRO_SAMPLE *sound_effect[NUMBER_SAMPLE];		// Dichiarazione dell'array dei suoni

	init_sound(sound_effect);							// I suoni vengono inizializzati

	// Vengono create due istanze per le musiche di gioco.
	ALLEGRO_SAMPLE_INSTANCE *song_instance = al_create_sample_instance(sound_effect[4]);
	ALLEGRO_SAMPLE_INSTANCE *thunder_instance = al_create_sample_instance(sound_effect[2]);

	ALLEGRO_KEYBOARD_STATE key_state;			// Variabile per lo stato dei tasti premuti
	ALLEGRO_TRANSFORM camera; 					// Variabile per la camera 
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);				//Timer base. Con 60 FPS
	ALLEGRO_TIMER *frame_timer = al_create_timer(1.0 / frameFPS);	// Timer utilizzato per le animazioni
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();		//Istanza di Allegro per la coda di eventi

	//Funzioni per collegare event_queue con gli elementi generatori di eventi
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(frame_timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	//Le istanze di suoni vengono collegate al mixer 
	al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());
	al_set_sample_instance_playmode(thunder_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(thunder_instance, al_get_default_mixer());

	//I timer cominciano a scorrere
	al_start_timer(frame_timer);
	al_start_timer(timer);

	init_font(font_1);
	init_little_explosion(b_exp);
	init_player_explosion(p_exp);
	init_fade(fade);

	bool new_game = false;

	do {
		new_game = false;
		
		GList *p = NULL, *e = NULL, *m = NULL; // allocate le liste dei personaggi

		init_background_1(background);
		init_minion(m);
		init_enemy(e);

		bool done = false, active = false;
		float camera_position[1] = { 0 }; // per camera
		bool jump = false, jump_e = false, jump_m = false;
		bool stop_music = false;

		/* FUNZIONE SCHERMATA INIZIALE */
		/* Disegno schermata iniziale e aspetto per pressione tasto */

		bool run = false, in = false;

		al_play_sample_instance(song_instance);
		unsigned int level = 1;
		general_random_spawn(obj, level);
		menu_pre_game(font_1, event_queue, p, display, level);

		while (!done)
		{
			if (level == 1)
			{
				if (PLAYER->health <= 0)
				{
					al_stop_sample_instance(song_instance);
					/* il secondo parametro e' l'audio, 1.0 rappresenta
					* il volume corrente. Il terzo da dove viene l'audio.
					* < 0.0 sx, > 0.0 dx, 0.0 centrale. Il quarto la velocita'
					* di riproduzione.
					*/
					if (!stop_music)
					{
						if (PLAYER->sex == 'm')
							al_play_sample(sound_effect[0], 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						else
							al_play_sample(sound_effect[5], 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						stop_music = true;
					}
				}
				spawn_minions(m, e, p, run, fade, background, level, done);
				p = g_list_first(p); // porto il puntatore p in testa alla lista
				e = g_list_first(e); // porto il puntatore e in testa alla lista
				m = g_list_first(m); // porto il puntatore m in testa alla lista

				ALLEGRO_EVENT events;
				al_wait_for_event(event_queue, &events);
				al_get_keyboard_state(&key_state);

				if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					done = true;

				else if (events.type == ALLEGRO_EVENT_TIMER)
				{
					draw(background, p, e, m, b_exp, p_exp, fade,font_1, obj);

					if (events.timer.source == timer)
					{
						active = true;

						casual_movement_enemy(e, p);
						casual_movement_minion(m);

						p = g_list_first(p); // porta il puntatore p in testa alla lista
						e = g_list_first(e); // porta il puntatore e in testa alla lista

						if (PLAYER->health > 0)
							player_movement(key_state,p, active);  // movimento personaggio
						else
							death_fade(fade, background, p, e, done); // dissolvenza e cambio di sfondo in caso di morte

						if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))  // tasto ESCAPE per chiudere il gioco
							break;
						else if (al_key_down(&key_state, ALLEGRO_KEY_Z)) // per sviluppatori:
																// Tasto Z per passare subito al secondo livello
						{
							ENEMY->health = 0;
							run = true;
						}

						mod_camera(camera, camera_position, p); // funzione generale che chiama le funzioni per la
																// modifica della camera

						general_collision(p, e, m, b_exp, p_exp, obj, sound_effect); // funzione generale che
																									   // chiama tutte le collisioni

						player_fire(p, key_state);  // gestisce lo sparo da parte del giocatore

						general_update_bullet(p, e, m); // funzione generale che chiama le funzioni per 
													 // l'aggiornamento delle posizioni dei proiettili

					}
					else if (events.timer.source == frame_timer)
						change_frame(p, e, m, b_exp, p_exp, active); // funzione per la corretta animazione delle
																  // immagini (cambia i vari frame)
				}
			}
			else if (!(level % 2))
			{
				if (level == 4)
				{
					al_draw_bitmap(background.image, background.x, background.y, 0);
					al_draw_text(font_1, AMBRA, background.x, ALLEGRO_ALIGN_LEFT, 0, "FINE GIOCO! HAI VINTO!");
					al_flip_display();
					al_clear_to_color(NERO);
					al_rest(2);
					done = true;
				}
				else
					make_your_choice(p, background, font_1, display, level, done);
				
				al_flush_event_queue(event_queue);
			}
			else if (level == 3)
			{
				al_play_sample_instance(thunder_instance);

				p = g_list_first(p); // porta il puntatore p in testa alla lista
				e = g_list_first(e); // porta il puntatore e in testa alla lista
				m = g_list_first(m); // porta il puntatore m in testa alla lista

				if (!in)
				{
					init_background_2(background);
					init_player_2(p);
					init_minion_2(m);
					init_enemy_2(e);
					general_random_spawn(obj, level);
					fade.flag = false;
					run = false;
					in = true;
					stop_music = false;
				}

				if (PLAYER->health <= 0)
				{
					al_stop_sample_instance(song_instance);
					al_stop_sample_instance(thunder_instance);

					if (!stop_music)
					{
						if (PLAYER->sex == 'm')
							al_play_sample(sound_effect[0], 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						else
							al_play_sample(sound_effect[5], 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						stop_music = true;
					}
				}

				spawn_minions(m, e, p, run, fade, background, level, done);

				ALLEGRO_EVENT events;
				al_wait_for_event(event_queue, &events);
				al_get_keyboard_state(&key_state);

				if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					done = true;
				else if (events.type == ALLEGRO_EVENT_TIMER)
				{
					if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE)) // tasto ESCAPE per uscire dal gioco
						break;

					draw(background, p, e, m, b_exp, p_exp, fade, font_1, obj);

					if (events.timer.source == timer)
					{
						active = true;

						mod_camera(camera, camera_position, p);

						if (PLAYER->health > 0)
							player_movement_gravity(key_state, p, active, jump);  // movimento personaggio
						else
							death_fade(fade, background, p, e, done); // dissolvenza e cambio di sfondo in caso di morte

						if (MINION->health > 0)
							casual_movement_gravity(m, jump_m);
						if (ENEMY->health > 0)
							casual_movement_gravity(e, jump_e);

						general_collision(p, e, m, b_exp, p_exp, obj, sound_effect); // funzione generale che
																	   // chiama tutte le collisioni

						player_fire(p, key_state);  // gestisce lo sparo da parte del giocatore

						general_update_bullet(p, e, m); // funzione generale che chiama le funzioni per 
														// l'aggiornamento delle posizioni dei proiettili
					}
					else if (events.timer.source == frame_timer)
					{
						change_frame(p, e, m, b_exp, p_exp, active);
					}
				}
			}
		}

		p = g_list_first(p);
		PLAYER->x = 0;
		mod_camera(camera, camera_position, p);
		end_level(p, e, fade, background, level);
		if ((fade.shade <= 0) && al_show_native_message_box(display, "RICOMINCIA", "", "VUOI RICOMINCIARE L'AVVENTURA?", "SI' | NO", ALLEGRO_MESSAGEBOX_QUESTION) == 1)
		{
			new_game = true;
			done = false;
			fade.flag = false;
		}

		pg_deallocation(p, e, m);
		al_destroy_bitmap(background.image);

	} while (new_game);

	destroy(display, timer, frame_timer, b_exp, p_exp, fade, font_1, event_queue, sound_effect, song_instance, thunder_instance);

	return 0;
}



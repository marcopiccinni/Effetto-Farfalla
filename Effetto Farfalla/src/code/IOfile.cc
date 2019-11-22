#include "../header/IOfile.h"
#include <fstream>

void read_save(GList *&p, bool &start, unsigned int &lvl, ALLEGRO_DISPLAY *display)
{
	ifstream sav(SAVE_FILE);				//aperto file in lettura.

	if (sav && (al_show_native_message_box(display, "CARICAMENTO", "PUNTO DI SALVATAGGIO TROVATO", "RICARICARE IL LIVELLO?", "Si|No", ALLEGRO_MESSAGEBOX_QUESTION)== 1) )
	{												//se Sì il message_box torna 1, se No torna 2
		start = false;

		sav >> lvl;
		Player *pl = new Player;

		int num_el;
		sav >> num_el;

		sav >> pl->sex;
		if (pl->sex == 'm')
			pl->image = al_load_bitmap("../media/images/sprites/Protagonista.png");
		else
			pl->image = al_load_bitmap("../media/images/sprites/Arielpink.png");
		pl->pX = al_get_bitmap_width(pl->image) / 4;
		pl->pY = al_get_bitmap_height(pl->image) / 4;
		pl->sourceX = pl->sourceY = 0.;
		sav >> pl->x;
		sav >> pl->y;  // coordinate

		sav >> pl->speed;  // velocita' di movimento persoanggio
		sav >> pl->pos_fire; //posizione del pg allo sparo
		pl->dir = RIGHT;
		pl->health = pl->healthmax = 100.;
		sav >> pl->cooldown;
		sav >> pl->velx >> pl->vely; //componente orizzontale(x) e verticale(y) della velocita', per gravita'
		sav >> pl->jump_speed;
		sav >> pl->armor;

		p = g_list_append(p, pl);			// pl viene aggiunto in coda alla lista p

		DEFCON1(cout << "Livello = " << lvl << endl);
		DEFCON1(cout << "Elementi in coda: " << num_el << endl);
		DEFCON1(cout << "Caricamento Player state bit:"
			<< "\nEofbit = " << sav.eof()
			<< "\nFailbit " << sav.fail()
			<< "\nBadbit " << sav.bad() << endl);
		DEFCON1(al_rest(3));

  		for (int i = 1 ; i < num_el ; i++)			//Ciclo per caricare gli oggetti equipaggiati dal personaggio
		{
			Object *sb = new Object;
			sav >> sb->x >> sb->y;
			sav >> sb->sourceX >> sb->sourceY;
			int c; sav >> c;
			sb->type = static_cast<Type_Obj>(c);
			if (sb->type == BULLET)
				sav >> sb->bullet_path;

			if (sb->type == ST_BULLET)
			{
				if (pl->sex == 'm')
					sb->image = al_load_bitmap("../media/images/objects/bullets/Missile.png");
				else
					sb->image = al_load_bitmap("../media/images/objects/bullets/w_bullet.png");
			}
			else if (sb->type == BULLET)
				sb->image = al_load_bitmap(sb->bullet_path);

			if (sb->type == ST_BULLET || sb->type == BULLET) {
				sb->pX = al_get_bitmap_width(sb->image) / 4;
				sb->pY = al_get_bitmap_height(sb->image);
			}

			sav >> sb->speed;
			sb->dir = RIGHT;
			sav >> sb->visible;
			sav >> sb->ammo;
			sav >> sb->strenght;
			sav >> sb->health;
			sav >> sb->healthmax;
			sav >> sb->armor;
			strcpy(sb->bullet_path, "");
			p = g_list_append(p, sb);

			DEFCON1(cout << "Caricamento Oggetto " << i << " state bit:"
				<< "\nEofbit = " << sav.eof()
				<< "\nFailbit " << sav.fail()
				<< "\nBadbit " << sav.bad() << endl);
			DEFCON1(al_rest(3));
		}
	}
	sav.close();							//Chiusura del file
}

void write_save(GList *&p, unsigned int lvl)
{
	DEFCON1(secure_player(p,"Write_save"));
	ofstream sav(SAVE_FILE);					//Apertura del file in scrittura
	DEFCON1(if (!sav)
	{
		cout << "Write_save::apertura file in scrittura fallita" << endl;
		al_rest(5);
		abort();
	});
	sav << lvl + 1 << endl;
	sav << g_list_length(p) << endl;
	p = g_list_first(p);
	sav << PLAYER->sex << endl;

	sav << PLAYER->x << endl << PLAYER->y << endl;  // coordinate
	sav << PLAYER->speed << endl;  // velocita' di movimento persoanggio
	sav << PLAYER->pos_fire << endl; //posizione del pg allo sparo
	sav << PLAYER->cooldown << endl;
	sav << PLAYER->velx << endl << PLAYER->vely << endl; //componente orizzontale(x) e verticale(y) della velocita', per gravita'
	sav << PLAYER->jump_speed << endl;
	sav << PLAYER->armor << endl;

	DEFCON1(cout << "Salvataggio Player state bit:"
		<< "\nEofbit = " << sav.eof()
		<< "\nFailbit " << sav.fail()
		<< "\nBadbit " << sav.bad() << endl);
	DEFCON1(al_rest(3));

	p = g_list_next(p);						// p= p->next
	for (int i = 1 ; g_list_length(p) > 0; i++)
	{
		sav << OBJECT_P->x << endl << OBJECT_P->y << endl;
		sav << OBJECT_P->sourceX << endl << OBJECT_P->sourceY << endl;
		sav << OBJECT_P->type << endl;

		if (OBJECT_P->type == BULLET)
			sav << OBJECT_P->bullet_path << endl;

		sav << OBJECT_P->speed << endl;
		sav << OBJECT_P->visible << endl;
		sav << OBJECT_P->ammo << endl;
		sav << OBJECT_P->strenght << endl;
		sav << OBJECT_P->health << endl;
		sav << OBJECT_P->healthmax << endl;
		sav << OBJECT_P->armor << endl;

		DEFCON1(cout << "Salvataggio Oggetto " << i << " state bit:"
			<< "\nEofbit = " << sav.eof()
			<< "\nFailbit " << sav.fail()
			<< "\nBadbit " << sav.bad() << endl);
		DEFCON1(al_rest(3));

		if (p->next == NULL)
			break;
		p = g_list_next(p);				//p=p->next
	}
	sav.close();						//chiusura del file aperto
}

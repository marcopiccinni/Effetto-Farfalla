#include "../header/inits.h"
#include <random>

void init_player(GList *&p, const char sex)
{
	if (p != NULL)
	{
		g_list_free(p); // libera il campo data
		p = NULL;
	}

	Player *pl = new Player;
	pl->sex = sex;
	if (pl->sex == 'm')
		pl->image = al_load_bitmap("../media/images/sprites/Protagonista.png");
	else
		pl->image = al_load_bitmap("../media/images/sprites/Arielpink.png");
	DEFCON1(secure_image(pl->image, "Init_player"));
	pl->x = 20.;
	pl->y = 400.;
	pl->pX = al_get_bitmap_width(pl->image) / 4;
	pl->pY = al_get_bitmap_height(pl->image) / 4;
	pl->sourceX = pl->sourceY = 0.;
	pl->speed = 5.;
	pl->pos_fire = pl->x;
	pl->dir = RIGHT;
	pl->cooldown = 0;
	pl->armor = 5.;
	pl->healthmax = 100.;
	pl->health = pl->healthmax;
	pl->velx = pl->vely = 0.;
	pl->jump_speed = 0.;

	Object *mb = new Object;
	if (pl->sex == 'm')
	{
		strcpy(mb->bullet_path, "../media/images/objects/bullets/Missile.png");
		mb->image = al_load_bitmap(mb->bullet_path);
	}
	else
	{
		strcpy(mb->bullet_path, "../media/images/objects/bullets/w_bullet.png");
		mb->image = al_load_bitmap(mb->bullet_path);
	}
	DEFCON1(secure_image(mb->image, "Init_player::st_bullet"));
	mb->x = mb->y = 0.;
	mb->pX = al_get_bitmap_width(mb->image) / 4;
	mb->pY = al_get_bitmap_height(mb->image);
	mb->speed = 10.;
	mb->sourceX = mb->sourceY = 0.;
	mb->dir = RIGHT;
	mb->visible = false;
	mb->type = ST_BULLET;
	mb->strenght = 15.;
	mb->ammo = mb->health = mb->healthmax = mb->armor = 0.;

	p = g_list_append(p, pl);		// inserisce pl in coda alla lista p
	p = g_list_append(p, mb);		// inserisce mb in coda alla lista p
	DEFCON1(secure_player(p, "Init_player"));
}

void init_enemy(GList *&e)
{
	if (e != NULL)
	{
		g_list_free(e); // libera il campo data
		e = NULL;
	}

	Player *en = new Player;
	en->image = al_load_bitmap("../media/images/sprites/Enemy.png");
	DEFCON1(secure_image(en->image, "Init_enemy"));
	en->x = BACKGROUNDWIDTH;
	en->y = 20.;
	en->pX = al_get_bitmap_width(en->image) / 3;
	en->pY = al_get_bitmap_height(en->image) / 4;
	en->sourceX = en->sourceY = 0.;
	en->speed = 5.;
	en->pos_fire = en->x;
	en->dir = LEFT;
	en->cooldown = 0;
	en->healthmax = 0.;
	en->health = en->healthmax;
	en->armor = 10.;
	en->sex = 0 ;

	Object *mb = new Object;
	mb->image = al_load_bitmap("../media/images/objects/bullets/e_bullet.png");
	DEFCON1(secure_image(mb->image, "Init_enemy::st_bullet"));
	mb->x = mb->y = 0.;
	mb->pX = al_get_bitmap_width(mb->image) / 4;
	mb->pY = al_get_bitmap_height(mb->image);
	mb->speed = 13.;
	mb->visible = false;
	mb->sourceX = mb->sourceY = 0.;
	mb->dir = LEFT;
	mb->type = ST_BULLET;
	mb->strenght = 25.;
	mb->ammo = mb->health = mb->healthmax = mb->armor = 0.;
	strcpy(mb->bullet_path, "");

	e = g_list_append(e, en); // inseriesce en in coda alla lista e
	e = g_list_append(e, mb); //  inseriesce mb in coda alla lista e
	DEFCON1(secure_player(e, "Init_enemy"));
}

void init_minion(GList *&m)
{
	if (m != NULL)
	{
		g_list_free(m); // libera il campo data
		m = NULL;
	}
	Player *min = new Player;

	min->image = al_load_bitmap("../media/images/sprites/arpia.png");
	DEFCON1(secure_image(min->image, "Init_minion"));
	min->x = 750.;
	min->y = 400.;
	min->pX = al_get_bitmap_width(min->image) / 3;
	min->pY = al_get_bitmap_height(min->image) / 4;
	min->sourceX = min->sourceY = 0.;
	min->speed = 5.;
	min->pos_fire = min->x;
	min->dir = RIGHT;
	min->armor = 2.;
	min->cooldown = 0;
	min->healthmax = 100.;
	min->health = min->healthmax;
	min->sex = 0 ;

	Object *mb = new Object;
	mb->image = al_load_bitmap("../media/images/objects/bullets/m_bullet.png");
	DEFCON1(secure_image(mb->image, "Init_minion::st_bullet"));
	mb->x = mb->y = 0.;
	mb->pX = al_get_bitmap_width(mb->image) / 4;
	mb->pY = al_get_bitmap_height(mb->image);
	mb->speed = 10.;
	mb->visible = false;
	mb->sourceX = mb->sourceY = 0.;
	mb->dir = LEFT;
	mb->armor = 0.;
	mb->type = ST_BULLET;
	mb->strenght = 10.;
	mb->ammo = mb->health = mb->healthmax = mb->armor = 0.;
	strcpy(mb->bullet_path, "");

	m = g_list_append(m, min); // inserisce min in coda alla lista m
	m = g_list_append(m, mb);  // inserisce mb in coda alla lista m
	DEFCON1(secure_player(m, "Init_minion"));
}

void init_little_explosion(Explosion &l_e)
{
	l_e.image = al_load_bitmap("../media/images/objects/explosions/explosion1.png");
	DEFCON1(secure_image(l_e.image, "Init_little_explosion"));
	l_e.x = l_e.y = 0.;
	l_e.pX = al_get_bitmap_width(l_e.image) / 13;
	l_e.pY = al_get_bitmap_height(l_e.image);
	l_e.sourceX = l_e.sourceY = 0.;
	l_e.visible = false;
	l_e.flag = 0;
}

void init_player_explosion(Explosion &p_e)
{
	p_e.image = al_load_bitmap("../media/images/objects/explosions/explosion-sprite.png");
	DEFCON1(secure_image(p_e.image, "Init_player_explosion"));
	p_e.x = p_e.y = 0.;
	p_e.pX = al_get_bitmap_width(p_e.image) / 5;
	p_e.pY = al_get_bitmap_height(p_e.image) / 4;
	p_e.sourceX = p_e.sourceY = 0.;
	p_e.visible = false;
	p_e.flag = 0;
}

void init_starter(Background &starter)
{
	starter.image = al_load_bitmap("../media/images/background/start.png");
	DEFCON1(secure_image(starter.image, "Init_starter"));
	starter.x = starter.y = 0.;
}

void init_background_1(Background &background)
{
	background.image = al_load_bitmap("../media/images/background/Background1.png");
	DEFCON1(secure_image(background.image, "Init_background"));
	background.x = background.y = 0.;
}

void init_fade(Fader &fade)
{
	fade.image = al_load_bitmap("../media/images/background/Fade.png");
	DEFCON1(secure_image(fade.image, "Init_fade"));
	fade.shade = 1.;
	fade.visible = false;
	fade.flag = false;
}

void init_font(ALLEGRO_FONT *&font_1)
{
	font_1  = al_load_font("../media/fonts/rainyhearts.ttf", 23, 0);  // Carico il font (il secondo parametro e' la dimensione)
	DEFCON1(secure_font(font_1, "Init_font"));
}

void init_sound(ALLEGRO_SAMPLE *sound_effect[])
{
	sound_effect[0] = al_load_sample("../media/sounds/239900__thesubber13__scream-1.ogg");
	sound_effect[1] = al_load_sample("../media/sounds/Big_Explosion.wav");
	sound_effect[2] = al_load_sample("../media/sounds/rain-and-thunder.wav");
	sound_effect[3] = al_load_sample("../media/sounds/253172__suntemple__retro-bonus-pickup-sfx.wav");
	sound_effect[4] = al_load_sample("../media/sounds/music_1_lv.ogg");
	sound_effect[5] = al_load_sample("../media/sounds/220295_gabrielaupf_screaming-woman-joyiii.wav");
	DEFCON1(secure_sample(sound_effect, "Init_sound"));
}

static void init_magic(Object &obj)
{
	random_device rd;
	strcpy(obj.bullet_path, "../media/images/objects/bullets/magic.png");
	DEFCON1(secure_image(obj.image, "Init_magic"));
	obj.image = al_load_bitmap(obj.bullet_path);
	
	obj.strenght = 20 + rd() % 20;
	DEFCON2(cout << "Magic :: strenght =  " << obj.strenght << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image) / 4;
	obj.pY = al_get_bitmap_height(obj.image);
	obj.sourceX = obj.sourceY = 0;
	obj.type = BULLET;
	obj.speed = 15;
	obj.ammo = 8;
	obj.health = obj.healthmax = obj.armor = 0;
	DEFCON1(secure_object(obj, "Init_magic"));
}

static void init_magic_2(Object &obj)
{
	random_device rd;
	strcpy(obj.bullet_path, "../media/images/objects/bullets/magic_2.png");
	obj.image = al_load_bitmap(obj.bullet_path);
	DEFCON1(secure_image(obj.image, "Init_magic_2"));

	obj.strenght = 25 + rd() % 25;
	DEFCON2(cout << "Magic_2 :: strenght =  " << obj.strenght << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image) / 4;
	obj.pY = al_get_bitmap_height(obj.image);
	obj.sourceX = obj.sourceY = 0.;
	obj.type = BULLET;
	obj.speed = 15.;
	obj.ammo = 8.;
	obj.health = obj.healthmax = obj.armor = 0;
	DEFCON1(secure_object(obj, "Init_magic_2"));
}

static void init_shuriken(Object &obj)
{
	random_device rd;
	strcpy(obj.bullet_path, "../media/images/objects/bullets/shuriken.png");
	obj.image = al_load_bitmap(obj.bullet_path);
	DEFCON1(secure_image(obj.image, "Init_shuriken"));

	obj.strenght = 22 + rd() % 22;
	DEFCON2(cout << "Shuriken :: strenght =  " << obj.strenght << endl);

	obj.visible = true;
	obj.dir = UP;
	obj.pX = al_get_bitmap_width(obj.image) / 4;
	obj.pY = al_get_bitmap_height(obj.image);
	obj.sourceX = obj.sourceY = 0;
	obj.type = BULLET;
	obj.speed = 15.;
	obj.ammo = 8.;
	obj.health = obj.healthmax = obj.armor = 0;
	DEFCON1(secure_object(obj, "Init_shuriken"));
}

static void init_bomb(Object &obj)
{
	random_device rd;
	strcpy(obj.bullet_path, "../media/images/objects/bullets/bomb.png");
	obj.image = al_load_bitmap(obj.bullet_path);
	DEFCON1(secure_image(obj.image, "Init_bomb"));

	obj.strenght = 30. + rd() % 30;
	DEFCON2(cout << "Bomb :: strenght =  " << obj.strenght << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image) / 4;
	obj.pY = al_get_bitmap_height(obj.image);
	obj.sourceX = obj.sourceY = 0.;
	obj.type = BULLET;
	obj.speed = 15.;
	obj.ammo = 5.;
	obj.health = obj.healthmax = obj.armor = 0;
	DEFCON1(secure_object(obj, "Init_bomb"));
}

void init_general_bullet(Object &obj)
{
	random_device rd;
	unsigned int scelta = 0;
	scelta = rd() % 4;
	switch (scelta)
	{
	case 0:
		init_magic(obj);
		break;
	case 1:
		init_magic_2(obj);
		break;
	case 2:
		init_shuriken(obj);
		break;
	case 3:
		init_bomb(obj);
		break;
	}
}

static void init_shield(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/shields/shield.png");
	DEFCON1(secure_image(obj.image, "Init_shield"));

	obj.armor = 6 + rd() % 5;
	DEFCON2(cout << "Shield :: armor =  " << obj.armor << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = ARMOR;
	obj.sourceX = obj.sourceY = 0;
	obj.strenght = obj.health = obj.healthmax = obj.ammo = 0.;
	DEFCON1(secure_object(obj, "Init_shield"));
}

static void init_shield_2(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/shields/shield_2.png");
	DEFCON1(secure_image(obj.image, "Init_shield_2"));

	obj.armor = 12 + rd() % 8;
	DEFCON2(cout << "Shield_2 :: armor =  " << obj.armor << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = ARMOR;
	obj.sourceX = obj.sourceY = 0;
	obj.strenght = obj.health = obj.healthmax = obj.ammo = 0.;
	DEFCON1(secure_object(obj, "Init_shield_2"));
}

static void init_armor(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/shields/armor.png");
	DEFCON1(secure_image(obj.image, "Init_armor"));

	obj.armor = 9 + rd() % 5;
	DEFCON2(cout << "Armor :: armor =  " << obj.armor << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = ARMOR;
	obj.sourceX = obj.sourceY = 0;
	obj.strenght = obj.health = obj.healthmax = obj.ammo = 0.;
	DEFCON1(secure_object(obj, "Init_armor"));
}

static void init_armor_2(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/shields/armor_2.png");
	DEFCON1(secure_image(obj.image, "Init_armor_2"));

	obj.armor = 20 + rd() % 8;
	DEFCON2(cout << "Armor_2 :: armor =  " << obj.armor << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = ARMOR;
	obj.sourceX = obj.sourceY = 0;
	obj.strenght = obj.health = obj.healthmax = obj.ammo = 0.;
	DEFCON1(secure_object(obj, "Init_armor2"));
}

void init_general_armor(Object &obj)
{
	random_device rd;
	unsigned int scelta = 0;
	scelta = rd() % 4;
	switch (scelta)
	{
	case 0:
		init_shield(obj);
		break;
	case 1:
		init_shield_2(obj);
		break;
	case 2:
		init_armor(obj);
		break;
	case 3:
		init_armor_2(obj);
		break;
	}
}

static void init_green_potion(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/potions/green_potion.png");
	DEFCON1(secure_image(obj.image, "Init_green_potion"));

	obj.health = 0;
	obj.healthmax = 20 + rd() % 100; // Aumenta la salute attuale
	DEFCON2(cout << "Green :: health =  " << obj.health << " && healthmax = " << obj.healthmax << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = POTION;
	DEFCON1(secure_object(obj, "Init_green_potion"));
}

static void init_red_potion(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/potions/red_potion.png");
	DEFCON1(secure_image(obj.image, "Init_red_potion"));

	obj.health = 20 + rd() % 100; // da 0 a 100
	obj.healthmax = 0;
	DEFCON2(cout << "RED :: health =  " << obj.health << " && healthmax = " << obj.healthmax << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = POTION;
	DEFCON1(secure_object(obj, "Init_red_potion"));
}

static void init_yellow_potion(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/potions/yellow_potion.png");
	DEFCON1(secure_image(obj.image, "Init_yellow_potion"));

	obj.health = +25 + static_cast<float>(rd() % 100);			// Aumenta o diminuisce salute attuale
	obj.healthmax = +15 + static_cast<float>(rd() % 100);		// Aumenta o diminuisce salute massima	
	DEFCON2(cout << "Yellow :: health =  " << obj.health << " && healthmax = " << obj.healthmax << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = POTION;
	DEFCON1(secure_object(obj, "Init_yellow_potion"));
}

static void init_grey_potion(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/potions/grey_potion.png");
	DEFCON1(secure_image(obj.image, "Init_grey_potion"));

	
	obj.health = +40. + static_cast<float>(rd() % 100);
	obj.healthmax = +40. + static_cast<float>(rd() % 100);
	DEFCON2(cout << "Grey :: health =  " << obj.health << " && healthmax = " << obj.healthmax << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = POTION;
	DEFCON1(secure_object(obj, "Init_grey_potion"));
}

static void init_purple_potion(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/potions/purple_potion.png");
	DEFCON1(secure_image(obj.image, "Init_purple_potion"));

	obj.health = -(static_cast<float>((1 + rd() % 30)));   // veleno, diminuisce la vita
	obj.healthmax = 0;
	DEFCON2(cout << "Purple :: health =  " << obj.health << " && healthmax = " << obj.healthmax << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = POTION;
	DEFCON1(secure_object(obj, "Init_purple_potion"));
}

static void init_orange_potion(Object &obj)
{
	random_device rd;
	obj.image = al_load_bitmap("../media/images/objects/potions/orange_potion.png");
	DEFCON1(secure_image(obj.image, "Init_orange_potion"));

	obj.health = 50. + static_cast<float>(rd() % 100); // Puo' diminuire o aumentare la salute attuale
	obj.healthmax = 90. + rd() % 100; // Aumenta notevolmente la salute massima
	DEFCON2(cout << "Orange :: health =  " << obj.health << " && healthmax = " << obj.healthmax << endl);

	obj.visible = true;
	obj.pX = al_get_bitmap_width(obj.image);
	obj.pY = al_get_bitmap_height(obj.image);
	obj.type = POTION;
	DEFCON1(secure_object(obj, "Init_orange_potion"));
}

void init_general_potion(Object &obj)
{
	random_device rd;
	unsigned int scelta = 0;
	scelta = rd() % 6;
	switch (scelta)
	{
	case 0:
		init_green_potion(obj);
		break;
	case 1:
		init_red_potion(obj);
		break;
	case 2:
		init_yellow_potion(obj);
		break;
	case 3:
		init_grey_potion(obj);
		break;
	case 4:
		init_purple_potion(obj);
		break;
	case 5:
		init_orange_potion(obj);
		break;
	}
}

void init_background_2(Background &background)
{
	al_destroy_bitmap(background.image);
	background.image = al_load_bitmap("../media/images/background/Background_2.png"); // carico una nuova immagine di background
	DEFCON1(secure_image(background.image, "Init_background_2"));
	background.x = background.y = 0.;
}

void init_player_2(GList *&p)
{
	DEFCON1(secure_player(p, "Init_player_2"));
	PLAYER->health = PLAYER->healthmax = 100.;
	PLAYER->y = 505.;
	PLAYER->x = 5.;
	PLAYER->speed = 5.;
	PLAYER->jump_speed = 15.;
	PLAYER->velx = PLAYER->vely = 0.;
	PLAYER->dir = RIGHT;
	PLAYER->armor = 10.;
}

void init_enemy_2(GList *&e)
{
	DEFCON1(secure_player(e, "Init_enemy_2"));
	ENEMY->image = al_load_bitmap("../media/images/sprites/Enemy_2.png");
	DEFCON1(secure_image(ENEMY->image, "Init_enemy_2"));
	ENEMY->x = 3800.;
	ENEMY->jump_speed = 19.;
	ENEMY->velx = ENEMY->vely = 0.;
	ENEMY->pX = al_get_bitmap_width(ENEMY->image) / 4;
	ENEMY->pY = al_get_bitmap_height(ENEMY->image) / 4;
	ENEMY->y = 555 - ENEMY->pY;
	ENEMY->speed = 1.;
	ENEMY->health = 0.;
	ENEMY->dir = RIGHT;
	ENEMY->sourceX = 0;
	ENEMY->sourceY = LEFT * ENEMY->pY;
	ENEMY->armor = 15.;
	e = search_obj(e, ST_BULLET);
	OBJECT_E->strenght = 30.;
	OBJECT_E->visible = false;
	e = g_list_first(e); // riporta il puntatore e alla testa della lista
}

void init_minion_2(GList *&m)
{
	DEFCON1(secure_player(m, "Init_minion_2"));
	MINION->image = al_load_bitmap("../media/images/sprites/Behemot.png");
	DEFCON1(secure_image(MINION->image, "Init_minion_2"));
	MINION->jump_speed = 15.;
	MINION->velx = MINION->vely = 0.;
	MINION->speed = 1.5;
	MINION->x = 900.;
	MINION->y = 459.;
	MINION->pX = al_get_bitmap_width(MINION->image) / 4;
	MINION->pY = al_get_bitmap_height(MINION->image) / 4;
	MINION->healthmax = MINION->health = 100.;
	MINION->dir = RIGHT;
	MINION->sourceX = 0.;
	MINION->sourceY = LEFT * MINION->pY;
	MINION->armor = 3.;
	m = search_obj(m, ST_BULLET);
	OBJECT_M->strenght = 12.;
	OBJECT_M->visible = false;
	m = g_list_first(m); // riporta il puntatore m alla testa della lista
}

void pg_deallocation(GList *&p, GList *&e, GList *&m)
{
	DEFCON1(secure_player(p, "Pg_deallocation::player"));
	DEFCON1(secure_player(e, "Pg_deallocation::enemy"));
	DEFCON1(secure_player(m, "Pg_deallocation::minion"));
	p = g_list_first(p);	// riporta il puntatore p alla testa della lista
	al_destroy_bitmap(PLAYER->image);
	p = search_obj(p, BULLET);
	al_destroy_bitmap(OBJECT_P->image);
	e = search_obj(e, ST_BULLET);
	al_destroy_bitmap(OBJECT_E->image);
	m = search_obj(m, ST_BULLET);
	al_destroy_bitmap(OBJECT_M->image);
	p = g_list_first(p); // riporta il puntatore p alla testa della lista
	g_list_free(p);		 // libera il campo data
	e = g_list_first(e); // riporta il puntatore e alla testa della lista
	g_list_free(e);      // libera il campo data
	m = g_list_first(m); // riporta il puntatore m alla testa della lista
	g_list_free(m);		 // libera il campo data
}

void destroy(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_TIMER *frame_timer, Explosion &b_exp, Explosion &p_exp,
	Fader &fade, ALLEGRO_FONT *&font_1, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_SAMPLE *sound_effect[],
	ALLEGRO_SAMPLE_INSTANCE *song_instance, ALLEGRO_SAMPLE_INSTANCE *thunder_instance)
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(frame_timer);
	al_destroy_bitmap(b_exp.image);
	al_destroy_bitmap(p_exp.image);
	al_destroy_bitmap(fade.image);
	al_destroy_font(font_1);
	al_destroy_event_queue(event_queue);
	al_destroy_sample(sound_effect[0]);
	al_destroy_sample(sound_effect[1]);
	al_destroy_sample(sound_effect[2]);
	al_destroy_sample(sound_effect[3]);
	al_destroy_sample(sound_effect[4]);
	al_destroy_sample_instance(song_instance);
	al_destroy_sample_instance(thunder_instance);
}

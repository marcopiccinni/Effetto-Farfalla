#include"../header/secure.h"

void secure_player(GList *c, const char name_f[])
{
	if (c == NULL)
	{
		cout << "Secure_player ha trovato un puntatore NULL in " << name_f << endl;
		al_rest(5);					//ferma il gioco per 5 secondi
		abort();					//Termina l'esecuzione
	}

	return;
}

void secure_object(Object c, const char name_f[])
{
	if (c.image == NULL)
	{
		cout << "Secure_object ha trovato un puntatore NULL in " << name_f << endl;
		al_rest(5);					//ferma il gioco per 5 secondi
		abort();					//Termina l'esecuzione
	}
	return;
}

void secure_sample(ALLEGRO_SAMPLE *c[], const char name_f[])
{
	bool flag = false;

	for (int i = 0; i < NUMBER_SAMPLE; i++)
		if (c[i] == NULL)
		{
			cout << "Secure_sample ha trovato un puntatore NULL in " << name_f << " sample: "<<i<<endl;
			flag = true;
		}
	if (flag)
	{
		al_rest(5);					//ferma il gioco per 5 secondi
		abort();					//Termina l'esecuzione
	}
	return;
}

void secure_image(ALLEGRO_BITMAP *pic, const char name_f[])
{
	if (pic  == NULL)
	{
		cout << "Secure_image ha trovato un puntatore NULL in " << name_f << endl;
		al_rest(5);					//ferma il gioco per 5 secondi
		abort();					//Termina l'esecuzione
	}
	return;
}

void secure_font(ALLEGRO_FONT *f, const char name_f[])
{
	if (f == NULL)
	{
		cout << "Secure_font ha trovato un puntatore NULL in " << name_f << endl;
		al_rest(5);					//ferma il gioco per 5 secondi
		abort();					//Termina l'esecuzione
	}
	return;
}

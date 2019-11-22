#ifndef IOFILE_H
#define	IOFILE_H

#include "data_struct.h"
#include "secure.h"

#define SAVE_FILE "../bin/Effetto farfalla.sav" /**< Percorso file di salvataggio */

/**
  * Funzione di caricamento. Serve per caricare i propri progressi contenuti nel
  * file di salvataggio o per passare all'inizializzazione di una nuova partita
  * (settando start a false).
  * @param p puntatore al player da caricare.
  * @param variabile booleana che serve per non entrare nel ciclo di inizializzazione.
  * di una nuova partita quando si sono caricati i dati.
  * @param variabile contenente il livello da caricare.
  * @param display puntatore al display di gioco.
  */
void read_save(GList *&p, bool &start, unsigned int &lvl, ALLEGRO_DISPLAY *display);

/**
  * Funzione di salvataggio. Serve per salvare i propri progressi, in vista di un
  * successivo caricamento, a fine di ogni livello.
  * @param p puntatore al player da salvare
  * @param lvl variabile contentente il livello attuale da salvare
  */
void write_save(GList *&p, unsigned int lvl);

#endif /* IOFILE_H */

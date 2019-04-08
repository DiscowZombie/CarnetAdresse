/*
 * Carnet d'adresse - Programme C simple
 * Copyright (C) 2019  Mathéo CIMBARO
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <ncurses.h>
#define BREAK_SPACE_DISPLAY_CONTACT 3

/*
Création d'une énumération pour représenter le mode d'affichage des informations de saisie
*/
typedef enum {
  LINE, COLUMN
} displayInstructionFormat;

// Variables en fonction de la taille de l'écran
unsigned int ncurseXSize, ncurseYSize; // x : numéro de colonne / y : numéro de ligne
unsigned int midY;

/*
fonction: Mettre à jour la taille de l'écran et son "pseudo-centre"
*/
void refreshScreenSize() {
  // Mise à jour de la taille de l'écran
  getmaxyx(stdscr, ncurseYSize, ncurseXSize);

  // Mise à jour du centre de l'écran
  // Milieu de Y moins 2 (de manière à avoir une liste "pseudo-centrée")
  midY = ((int)(ncurseYSize / 2)) - 3;
}

/*
fonction: Afficher les instructions à l'écran
*/
void displayInstruction(displayInstructionFormat format) {
  // Mise à jour de la taille de l'écran
  refreshScreenSize();

  // Affichage en fonction du format
  switch (format) {
    case LINE:
      mvprintw(ncurseYSize-2, 0, "(q)uitter, (a)fficher tout, (i)nserer contact, (s)upprimer un contact, (c)hercher, (r)echerche avancé, (l)icence");
      break;

    case COLUMN:
      mvprintw(midY, 1, "(q)uitter - Quitter le programme");
      mvprintw(midY+1, 1, "(a)fficher - Afficher tous les contact");
      mvprintw(midY+2, 1, "(i)nsérer - Insérer un nouveau contact");
      mvprintw(midY+3, 1, "(s)uppresion - Suppresion d'un contact");
      mvprintw(midY+4, 1, "(c)hercher - Chercher des contacts par nom");
      mvprintw(midY+5, 1, "(r)echerche avancé - Recherche avancé par nom de conjoint");
      mvprintw(midY+6, 1, "(l)icence - Afficher la licence du programme");
      break;

    default: break;
  }
}

int fromAsciiIntToInt(int asciiCode) {
  if (asciiCode < 48 || asciiCode > 57)
    return -1;

  return (asciiCode - 48);
}

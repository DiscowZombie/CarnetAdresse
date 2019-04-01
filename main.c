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

#include "keys.c"

/*
Ligne de compilation : gcc -Wall main.c -o carnet_adresse -lncurses && ./carnet_adresse
*/

int main() {
  // Initialisation de l'affichage (ncurses)
  initscr();

  // Store pressed key code
  int instructionKey;

  // Ecrire le menu
  displayInstruction(COLUMN);
  refresh();

  // Valeur par défaut
  contact ownerContact = { "CIMBARO", "Mathéo", M, "330102030405", "330102030405", NULL };
  addContactToRepertoire(&ownerContact);

  do {
    instructionKey = getch();

    handle(instructionKey);
  } while (instructionKey != QUIT_KEY);

  /*
   Read-Me - Important :

   Aucun free() n'est fait à la fin (sauf si on removeContact) car ca serait plus couteux
   que de laisser le programme se finir tranquillement (l'OS va de toute façon nettoyer)
   */

  // Fermeture de l'affichage (ncurses)
  endwin();

  // Sortir du programme avec un status zéro
  return 0;
}

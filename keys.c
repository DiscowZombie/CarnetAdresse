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

#include "manager.c"
#define QUIT_KEY 113
#define A_KEY 97
#define C_KEY 99
#define L_KEY 108
#define R_KEY 114
#define I_KEY 105
#define Y_KEY 121
#define N_KEY 110
#define S_KEY 115

/*
Read-Me - Important :

Le programme n'a pas été conçu pour fonctionner avec les majuscules
*/

/*
fonction: Handle a key pressed
*/
void handle(int key) {
  // Coordonnées de l'endroit pour afficher la question
  short infoBarX = 7, infoBarZ = 3;

  // Nettoyage de l'écran
  clear();

  switch (key) {
    case A_KEY:
      displayContacts();
      break;

    case C_KEY:
      // Nettoyage de l'écran
      clear();

      // Demande d'un caractère
      mvprintw(infoBarZ, infoBarZ, "Veuillez saisir un caractère...");

      // Sauvegarde du caractère
      int car = getch();

      displayContactsNameStartBy((char)car);
      break;

    case I_KEY:
      createContactGUI(infoBarX, infoBarZ, Y_KEY, N_KEY);
      break;

    case S_KEY:
      // Nettoyage de l'écran
      clear();

      int id;
      do {
        // Demande d'un nombre
        mvprintw(infoBarX, infoBarZ, "Veuillez saisir un ID (entre 0 et 9)");

        int charAscii = getch();

        id = fromAsciiIntToInt(charAscii);
      } while (id == -1);

      int deleteAmount = removeContact(id);

      // Re-nottoyage de l'écran
      clear();

      // Afficher le status
      mvprintw(infoBarX, infoBarZ, "%u contact supprimé", deleteAmount);

      displayInstruction(LINE);
      break;

    case R_KEY:
      // Nettoyage de l'écrar
      clear();

      // Demande de caractères
      char toFind[10] = { '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0' }; // Maximum size is 10 letters
      unsigned int letterIndex = 0;
      char lastChar;

      do {
        // Nettoyage de l'écran
        clear();

        mvprintw(infoBarX, infoBarZ, "Veuillez saisir un caractère...");
        mvprintw(infoBarX+1, infoBarZ, "Saisie actuelle : %s", toFind);

        lastChar = getch();

        toFind[letterIndex] = lastChar;
        ++letterIndex;
      } while(lastChar != 10 && letterIndex < 10); // Char 10 is Break line

      displayContactsNameConjStartBy(toFind, letterIndex);
      break;

    case L_KEY:
      mvprintw(midY - 1, 1, "Carnet d'adresse  Copyright (C) 2019  Mathéo CIMBARO");
      mvprintw(midY, 1, "This program comes with ABSOLUTELY NO WARRANTY; for details show LICENSE file.");
      mvprintw(midY + 1, 1, "This is free software, and you are welcome to redistribute it");
      mvprintw(midY + 2, 1, "under certain conditions; show LICENSE file for details.");

      displayInstruction(LINE);
      break;

    default:
      mvprintw(infoBarZ, infoBarX, "Caractère inconnu : %c (%u)", key, key);
      displayInstruction(COLUMN);
      break;
  }

  // Pour éviter tout problème, on refresh l'écran
  refresh();
}

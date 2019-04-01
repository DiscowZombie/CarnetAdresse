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

#include <string.h>
#include "memory.c"
#include "ncurses-tools.c"

/*
fonction: Affichage d'un contact précis
*/
void displayContact(contact c) {
  // Mise à jour de la taille de l'écran
  refreshScreenSize();

  // Affichage de toutes les informations sur le contacts
  mvprintw(midY, BREAK_SPACE_DISPLAY_CONTACT, "Nom et Prénom: %s %s", c.nom, c.prenom);
  mvprintw(midY+1, BREAK_SPACE_DISPLAY_CONTACT, "Sexe: %s", sexeName(c.sex));
  mvprintw(midY+2, BREAK_SPACE_DISPLAY_CONTACT, "Téléphone (fixe): %s", c.telephoneFixe);
  mvprintw(midY+3, BREAK_SPACE_DISPLAY_CONTACT, "Téléphone (portable): %s", c.telephonePortable);
  mvprintw(midY+4, BREAK_SPACE_DISPLAY_CONTACT, "Conjoint: %p", c.conjoint);

  // Affichage du bandeau avec les informations de saisie de caractères
  displayInstruction(LINE);

  // Mise à jour de l'écran côté ncurses
  refresh();
}

/*
Demander un input à l'utilisateur et l'écrire dans une variable
*/
void askInput(char* destInput, char* message) {
  // Coordonnées de l'endroit pour afficher la question
  int infoBarX = 7, infoBarZ = 3;

  // Nettoyage de l'écran
  clear();

  // Affichage du message à l'écran
  mvprintw(infoBarZ, infoBarX, message);

  // Déplacement du curseur d'écriture
  mvprintw(3*infoBarZ, infoBarX, "");

  // Ecrire ce qu'il entre dans la variable
  getstr(destInput);
}

/*
fonction: demander une chaine de caractère dynamiquement
*/
char* askStringDyn(int maxLenght) {
  // Pointe vers la chaineen mémoire (la taille peut-être trouvé par strlen (ne compte pas le \0))
  char* ptr_area = malloc(1 * sizeof(char));
  ptr_area[0] = '\0';

  while (1) {
    // Ask for new char
    int enteredChar = getch();

    // Line-return
    if (enteredChar == 10) break;

    // Ma nouvelle zone doit avoir strlen size ('azeare') + 1 '\0' et encore 1 pour celui que je vais écrire
    char* newArea = malloc((strlen(ptr_area) + 2) * sizeof(char));

    // Copy old char to new area (only text, not the `\0`)
    int idx = 0;
    for (; idx < strlen(ptr_area); idx++) {
      newArea[idx] = ptr_area[idx];
    }

    // Ecrire le nouveau caractère
    newArea[idx] = enteredChar;
    newArea[idx+1] = '\0';

    // Clean-UP
    free(ptr_area);
    ptr_area = newArea;

    if (strlen(ptr_area) == maxLenght) break;
  }

  return ptr_area;
}

char* askInputString(char* message, int maxLenght) {
  // Coordonnées de l'endroit pour afficher la question
  int infoBarX = 7, infoBarZ = 3;

  // Nettoyage de l'écran
  clear();

  // Affichage du message à l'écran
  mvprintw(infoBarZ, infoBarX, message);

  // Déplacement du curseur d'écriture
  mvprintw(3*infoBarZ, infoBarX, "");

  // Zone de mémoire dynamique pour sa variable
  return askStringDyn(maxLenght);
}

/*
fonction: Création d'un contact
*/
contact* createContact() {
  // Important : Pas super (les 24 * sizeof...) on perds à nouveau des octets en mémoire

  // Récupération d'un nom
  char* nom = askInputString("Nom de famille du contact", 24); // malloc(24 * sizeof(char)); // TDOO: FREE ME sur le removeContact!
  // askInput(nom, "Nom de famille du contact");

  // Récupération d'un prénom
  char* prenom = malloc(24 * sizeof(char));
  askInput(prenom, "Prénom du contact");

  // Récupération du sexe
  char* sexChar = malloc(sizeof(char));
  do {
    askInput(sexChar, "Choix du sexe (M ou F)");
  } while (sexChar[0] != 'M' && sexChar[0] != 'F');

  sexe sex = M;
  switch (sexChar[0]) {
    case 'M':
      sex = M;
      break;
    case 'F':
      sex = F;
      break;
    default: break;
  }
  free(sexChar);

  // Récupération du numéro de téléphone fixe
  char* telephoneFixe = malloc(11 * sizeof(char));
  askInput(telephoneFixe, "Numéro de téléphone fixe (format à 11 chiffres)");

  // Récupération du numéro de téléphone portable
  char* telephonePortable = malloc(11 * sizeof(char));
  askInput(telephonePortable, "Numéro de téléphone portable (format à 11 chiffres)");

  // Création d'un contact dans l'espace mémoire
  contact* contact_ptr = (contact*) malloc(sizeof(contact));
  contact_ptr->nom = nom;
  contact_ptr->prenom = prenom;
  contact_ptr->sex = sex;
  contact_ptr->telephoneFixe = telephoneFixe;
  contact_ptr->telephonePortable = telephonePortable;
  contact_ptr->conjoint = NULL;

  return contact_ptr;
}

int removeContact(int index) {
   // Entrée invalide dans le répertoire
   if (index >= repertoireLenght) {
     return 0;
   }

   // Nouveau répertoire
   contact* newRepertoire = (contact*) malloc((repertoireLenght - 1) * sizeof(contact));

   // Copie de tous les anciens contacts dans le nouveau répértoire
   for (int i = 0; i < index; i++) {
     newRepertoire[i] = repertoire[i];
   }
   for (int i = index; i < (repertoireLenght - 1); i++) {
     newRepertoire[i] = repertoire[i+1];
   }

   // Libération de l'ancien répertoire
   free(repertoire);

   // Nouveau répértoire
   repertoire = newRepertoire;
   --repertoireLenght;

   // 1 contact supprimé avec succès
   return 1;
 }

/*
fonction: Ajout d'un contact à la fin du carnet d'adresses
*/
void addContactToRepertoire(contact* cptr) {
  // Création d'un nouveau répertoire en mémoire (d'une taille d'un de plus que l'ancien)
  contact* newRepertoire = (contact*) malloc((repertoireLenght + 1) * sizeof(contact));

  // Copie de tous les anciens contact vers le nouveau répertoire
  for (int i = 0; i < repertoireLenght; i++) {
    newRepertoire[i] = repertoire[i];
  }

  // Libération de l'ancien répertoire
  free(repertoire);

  // Ajout du nouveau contact à la fin du nouveau repertoire
  newRepertoire[repertoireLenght] = *cptr;

  // Redonner une valeur à repertoire et ajouter 1 au nombre de contact
  repertoire = newRepertoire;
  ++repertoireLenght;
}

/*
fonction: Afficher tous les contacts à l'écran
*/
void displayContacts() {
  // Nettoyage de l'écran
  clear();

  // Index Y de début d'affichage
  int beginY = midY - 3;

  for (int i = 0; i < repertoireLenght; i++) {
    contact c = repertoire[i];

    mvprintw(beginY + i, 5, "%u - %s %s", i, c.nom, c.prenom);
  }

  // Affichage du bandeau avec les informations de saisie de caractères
  displayInstruction(LINE);

  // Mise à jour de l'écran côté ncurses
  refresh();
}

/*
fonction: Afficher tous les contacts dont nom commence par une certaine lettre
*/
void displayContactsNameStartBy(char ch) {
  // Nettoyage de l'écran
  clear();

  // Index Y de début d'affichage
  int beginY = midY - 3;

  // Compter le nombre de contactes qui matchent
  int match = 0;

  for (int i = 0; i < repertoireLenght; i++) {
    contact c = repertoire[i];

    // La première lettre du nom ne commence pas par la même
    if (c.nom[0] != ch) continue;

    mvprintw(beginY + i, 5, "%u - %s %s", i, c.prenom, c.nom);
    ++match;
  }

  // Afficher le nombre de contacts qui matchent
  mvprintw(beginY - 1, 5, "%u contact(s) trouvé(s) pour la lettre %c :", match, ch);

  // Affichage du bandeau avec les informations de saisie de caractères
  displayInstruction(LINE);

  // Mise à jour de l'écran côté ncurses
  refresh();
}

/*
fonction: Afficher les contacts dont le nom démarre par certaines lettres
*/
void displayContactsNameConjStartBy(char* letters, int numbersLetters) {
  // Nettoyage de l'écran
  clear();

  // Index Y de début d'affichage
  int beginY = midY - 3;

  // Compter le nombre de contactes qui matchent
  int match = 0;

  for (int i = 0; i < repertoireLenght; i++) {
    contact c = repertoire[i];

    // La première lettre du nom ne commence pas par la même
    int match = 1;

    for (int i = 0; i < numbersLetters; i++) {
      if (c.nom[i] != letters[i] && c.prenom[i] != letters[i]) match = 0;
    }

    if (!match) continue;

    mvprintw(beginY + i, 5, "%u - %s %s", i, c.prenom, c.nom);
    ++match;
  }

  // Afficher le nombre de contacts qui matchent
  mvprintw(beginY - 1, 5, "%u contact(s) trouvé(s) pour %s :", match, letters);

  // Affichage du bandeau avec les informations de saisie de caractères
  displayInstruction(LINE);

  // Mise à jour de l'écran côté ncurses
  refresh();
}

void createContactGUI(int infoBarX, int infoBarZ, int yKey, int nKey) {
  contact* c_ptr = createContact();
  char car;

  do {
    // Nettoyage de l'écran
    clear();

    // Affichage
    mvprintw(infoBarZ, infoBarX, "%s sera ajouté aux contacts. [y/n]", c_ptr->prenom);

    // Confirmation
    car = getch();
  } while (car != yKey && car != nKey);

  clear();

  if (car == yKey) {
    mvprintw(infoBarZ, infoBarX, "%s ajouté aux contacts !", c_ptr->prenom);

    addContactToRepertoire(c_ptr);
  }

  displayInstruction(LINE);
}

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

#include <stdlib.h>
#define LENGHT_PHONE 11

/*
Enumération représentant le sexe d'une personne
*/
typedef enum {
  M, F
} sexe;

/*
Représentation d'un contact (entrée dans la carnet de contacts)
*/
typedef struct {
  char* nom;
  char* prenom;
  sexe sex;
  char* telephoneFixe;
  char* telephonePortable;
  void* conjoint;
} contact;

// Adresse du premier élement
contact* repertoire = NULL;
// Nombre total d'élements
unsigned int repertoireLenght = 0;

/*
Affichage du sexe sous forme d'une chaine de caractères
*/
char* sexeName(sexe sex) {
  switch (sex) {
    case M:
    return "Masculin";
    break;
    case F:
    return "Féminin";
    break;
    default: break;
  }

  return "(indéfini)";
}

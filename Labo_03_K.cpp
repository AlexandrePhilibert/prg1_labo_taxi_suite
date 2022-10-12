//---------------------------------------------------------
// Fichier        : Labo_03_K.cpp
// Classe         : PRG1_E
// Auteur(s)      : ValentinRicard, MussieSirak
//                  Cedric Gerber, Alexandre Philibert
// But            : Création d'une application de calcul de prix de Taxi
// Modifications  : Changement du prix du supplément bagage de 2.50 à 2.60
//                  Ajout de directives define pour supprimer les lignes dupliquées
//                  Ajout de tarifs de jour et de nuit
// Remarque(s)    : NILL
// Compilateur    : g++ 11.2.0
// Standard C++   : c++ 20
//---------------------------------------------------------

#include <iostream>  // cout & cin
#include <cstdlib>   // EXIT_SUCCESS
#include <cmath>     // ceil(...)
#include <limits>    // numeric_limits<streamsize>
#include <iomanip>   // setw(...) et setprecision(...)

using namespace std; // Permet d'éviter de mettre std:: partout

#define AFFICHER_MESSAGE_FIN cout << "presser ENTREE pour quitter" << endl
#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

// Initialise les constantes (définies dans les données)
const float BASE_PRICE = 5.00f,
            PER_LUGGAGE_TAX = 2.60f,
            TARIF_JOUR = 1.00f,
            TARIF_NUIT = 1.60f;

const unsigned short NOMBRE_BAGAGE_MIN = 0,
            NOMBRE_BAGAGE_MAX = 4,
            DISTANCE_KM_MIN = 0,
            DISTANCE_KM_MAX = 500,
            VITESSE_KMH_MIN = 30,
            VITESSE_KMH_MAX = 120,
            MINUTES_DEBUT_TARIF_JOUR = 480, // 8 * 60
            MINUTES_FIN_TARIF_JOUR = 1200;  // 20 * 60


int main() {
   // Affiche le message de bienvenue
   cout << "bonjour, ce programme..." << endl
        << "voici les conditions" << endl
        << "=========================" << endl;
   // Affiche les constantes du programme
   // (avec une limite de précision de 2, pour éviter les erreurs d'encodage des valeurs flottantes)
   cout << fixed << setprecision(2)
        << " - prise en charge  : " << BASE_PRICE      << endl
        << " - supp par bagag   : " << PER_LUGGAGE_TAX << endl
        << " - tarif/min (jour) : " << TARIF_JOUR      << endl
        << " - tarif/min (nuit) : " << TARIF_NUIT      << endl
        << " - tarif jour       : " << "08h00 - 20h00" << endl;


   // Demande à l'utilisateur les entrées du programme
   cout << "votre commande" << endl
        << "==============" << endl;
   // Un entier est choisi, il n'est pas possible d'avoir 2.4 bagages.
   int nombreBagages;
   cout << "- nbre de baggage [" << NOMBRE_BAGAGE_MIN << " - " << NOMBRE_BAGAGE_MAX << "] :" ;
   cin >> nombreBagages;
   VIDER_BUFFER;

   if (nombreBagages < NOMBRE_BAGAGE_MIN || nombreBagages > NOMBRE_BAGAGE_MAX) {
      //TODO: Utiliser cerr ? L'ordre dans lequel les buffers s'affichent n'est pas garanti
      cout << "Le nombre de bagages doit être compris entre " << NOMBRE_BAGAGE_MIN << " et " << NOMBRE_BAGAGE_MAX << endl;
      AFFICHER_MESSAGE_FIN;
      VIDER_BUFFER;
      return EXIT_FAILURE;
   }

   float distanceKm;
   cout << "- distance [km] [" << DISTANCE_KM_MIN << " - " << DISTANCE_KM_MAX << "] :" ;
   cin >> distanceKm;
   VIDER_BUFFER;

   if (distanceKm < DISTANCE_KM_MIN || distanceKm > DISTANCE_KM_MAX) {
      cout << "La distance doit être comprise entre " << DISTANCE_KM_MIN << " et " << DISTANCE_KM_MAX << endl;
      AFFICHER_MESSAGE_FIN;
      VIDER_BUFFER;
      return EXIT_FAILURE;
   }

   float vitesseKmH;
   cout << "- vitesse [km/h] [" << VITESSE_KMH_MIN << " - " << VITESSE_KMH_MAX << "] :" ;
   cin >> vitesseKmH;
   VIDER_BUFFER;

   if (vitesseKmH < VITESSE_KMH_MIN || vitesseKmH > VITESSE_KMH_MAX) {
      cout << "La vitesse doit être comprise entre " << VITESSE_KMH_MIN << " et " << VITESSE_KMH_MAX << endl;
      AFFICHER_MESSAGE_FIN;
      VIDER_BUFFER;
      return EXIT_FAILURE;
   }

   unsigned int heureDepart, minutesDepart;
   cout << "- depart [hh:mm] : ";
   cin >> heureDepart;
   cin.ignore(numeric_limits<streamsize>::max(), ':');
   cin >> minutesDepart;
   VIDER_BUFFER;

   // TODO: Vérifier si >= 0 ou pas ?
   if (heureDepart > 23 || minutesDepart > 59) {
      cout << "L'heure de départ doit être comprise entre [0-23]:[0:59]" << endl;
      AFFICHER_MESSAGE_FIN;
      VIDER_BUFFER;
      return EXIT_FAILURE;
   }

   int tempsTrajet = ceil((distanceKm / vitesseKmH) * 60.0);
   unsigned int heureDepartMinutes = heureDepart * 60 + minutesDepart;
   unsigned int tempsTrajetJourMinutes,
                tempsTrajetNuitMinutes;

   // Détermine dans quel tarif la course a débutée
   if (heureDepartMinutes >= MINUTES_DEBUT_TARIF_JOUR && heureDepartMinutes < MINUTES_FIN_TARIF_JOUR) {
      // tarif jour
      tempsTrajetJourMinutes = MINUTES_FIN_TARIF_JOUR - heureDepartMinutes;

      // tarif nuit
      tempsTrajetNuitMinutes = heureDepartMinutes + tempsTrajetJourMinutes > MINUTES_FIN_TARIF_JOUR
         ? tempsTrajet - tempsTrajetJourMinutes
         : 0;
   } else {
      // tarif nuit
      tempsTrajetNuitMinutes = MINUTES_DEBUT_TARIF_JOUR - heureDepartMinutes;

      // tarif jour
      tempsTrajetJourMinutes = (heureDepartMinutes + tempsTrajetNuitMinutes) % 1440 >= MINUTES_DEBUT_TARIF_JOUR
         ? tempsTrajet - tempsTrajetNuitMinutes
         : 0;
   }

   float luggagePrice = PER_LUGGAGE_TAX * (float) nombreBagages;
   float totalTrajetJour = (float) tempsTrajetJourMinutes * TARIF_JOUR;
   float totalTrajetNuit = (float) tempsTrajetNuitMinutes * TARIF_NUIT;
   float totalPrice = BASE_PRICE + luggagePrice + totalTrajetJour + totalTrajetNuit;

   // Affiche les résultats
   cout << fixed << setprecision(2) << endl
        << "votre ticket" << endl
        << "============" << endl
        << " - prise en charge     : " << BASE_PRICE << endl
        << " - supp bagages        : " << luggagePrice << endl
        << " - temps de la course" << endl
        << "  " << tempsTrajetJourMinutes << "' @ " << TARIF_JOUR << " : " << totalTrajetJour << endl
        << "  " << tempsTrajetNuitMinutes << "' @ " << TARIF_NUIT << " : " << totalTrajetNuit << endl
        << "---------------   -----------"
        << " TOTAL : " << totalPrice << endl;

   // Laisse l'utilisateur appuyer sur ENTREE pour fermer le programme
   AFFICHER_MESSAGE_FIN;
   VIDER_BUFFER;

   return EXIT_SUCCESS;
}

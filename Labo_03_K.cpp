//---------------------------------------------------------
// Fichier        : Labo_03_K.cpp
// Classe         : PRG1_E
// Auteur(s)      : ValentinRicard, MussieSirak
// But            : Création d'une application de calcul de prix de Taxi
// Modifications  : Changement du prix du supplément bagage de 2.50 à 2.60
// Remarque(s)    : NILL
//---------------------------------------------------------

#include <iostream>  // cout & cin
#include <cstdlib>   // EXIT_SUCCESS
#include <cmath>     // ceil(...)
#include <limits>    // numeric_limits<streamsize>
#include <iomanip>   // setw(...) et setprecision(...)

using namespace std; // Permet d'éviter de mettre std:: partout

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
        // TODO: Mettre tarif jour en constante
        << " - tarif jour       : " << "08h00 - 20h00" << endl;


   // Demande à l'utilisateur les entrées du programme
   cout << "votre commande" << endl
        << "==============" << endl;
   // Un entier est choisi, il n'est pas possible d'avoir 2.4 bagages.
   int luggageCount;
   cout << "- nbre de baggage [" << NOMBRE_BAGAGE_MIN << " - " << NOMBRE_BAGAGE_MAX << "] :" ;
   cin >> luggageCount;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   // Nous n'avons pas forcément besoin de plus de 6 chiffres significatifs dans les entrées
   float travelDistance;
   cout << "- distance [km] [" << DISTANCE_KM_MIN << " - " << DISTANCE_KM_MAX << "] :" ;
   cin >> travelDistance;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   float vitesseKmH;
   cout << "- vitesse [km/h] [" << VITESSE_KMH_MIN << " - " << VITESSE_KMH_MAX << "] :" ;
   cin >> vitesseKmH;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   unsigned int heureDepart,
                minutesDepart;
   cout << "- depart [hh:mm] : ";
   cin >> heureDepart;
   cin.ignore(numeric_limits<streamsize>::max(), ':');
   cin >> minutesDepart;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   int tempsTrajet = ceil((travelDistance / vitesseKmH) * 60.0);
   unsigned int tempsDepartMinutes = minutesDepart * 60 + minutesDepart;

   if (tempsDepartMinutes >= MINUTES_DEBUT_TARIF_JOUR && tempsDepartMinutes < MINUTES_FIN_TARIF_JOUR) {
      // tarif jour
   } else {
      // tarif nuit
   }

   float luggagePrice = PER_LUGGAGE_TAX * (float) luggageCount;
   float travelPrice = 3 * (float) tempsTrajet;
   float totalPrice = BASE_PRICE + luggagePrice + travelPrice;

   // Affiche les résultats
   cout << fixed << setprecision(2) << endl
        << "votre ticket" << endl
        << "============" << endl
        << " - prise en charge     : " << BASE_PRICE     << endl
        << " - supp bagages        : " << luggagePrice   << endl
        << " - temps de la course"                       << endl
        << "    xxx' @ " << TARIF_JOUR << " : " << "XXX" << endl
        << "    yyy0 @ " << TARIF_NUIT << " : " << "YYY" << endl
        << "---------------   -----------"
        << " TOTAL : " << totalPrice << endl;

   // Laisse l'utilisateur appuyer sur ENTREE pour fermer le programme
   cout << "presser ENTREE pour quitter" << endl;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   // Fin de programme :tada:
   return EXIT_SUCCESS;
}

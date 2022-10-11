//---------------------------------------------------------
// Demo           : taxi
// Fichier        : taxi.cpp
// Classe         : PRG1_E
// Auteur(s)      : ValentinRicard, MussieSirak
// But            : Création d'une application de calcul de prix de Taxi
// Modifications  :
// Remarque(s)    : NILL
//---------------------------------------------------------

#include <iostream>  // cout & cin
#include <cstdlib>   // EXIT_SUCCESS
#include <cmath>     // ceil(...)
#include <limits>    // numeric_limits<streamsize>
#include <iomanip>   // setw(...) et setprecision(...)

using namespace std; // Permet d'éviter de mettre std:: partout

// Initialise les constantes (définies dans les données)
const float BASE_PRICE = 5.00f;
const float PER_LUGGAGE_TAX = 2.50f;
const float PER_MINUTE_PRICE = 1.20f;

int main() {
   // Affiche le message de bienvenue
   cout << "bonjour, ce programme..." << endl
        << "voici les conditions" << endl
        << "=========================" << endl;
   // Affiche les constantes du programme
   // (avec une limite de précision de 2, pour éviter les erreurs d'encodage des valeurs flottantes)
   cout << fixed << setprecision(2)
        << " - prise en charge  : " << BASE_PRICE << endl
        << " - supp par bagag   : " << PER_LUGGAGE_TAX << endl
        << " - tarif/minute     : " << PER_MINUTE_PRICE << endl;


   // Demande à l'utilisateur les entrées du programme
   cout << "votre commande" << endl
        << "==============" << endl;
   // Un entier est choisi, il n'est pas possible d'avoir 2.4 bagages.
   int luggageCount;
   cout << "- nbre de baggage     : ";
   cin >> luggageCount;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   // Nous n'avons pas forcément besoin de plus de 6 chiffres significatifs dans les entrées
   float travelDistance;
   cout << "- distance [km]       : ";
   cin >> travelDistance;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   float travelSpeed;
   cout << "- vitesse [km/h]      : ";
   cin >> travelSpeed;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   // Calcule le temps de trajet
   int travelTime = ceil((travelDistance / travelSpeed) * 60.0);
   float luggagePrice = PER_LUGGAGE_TAX * luggageCount;
   float travelPrice = PER_MINUTE_PRICE * travelTime;
   float totalPrice = BASE_PRICE + luggagePrice + travelPrice;

   // Affiche les résultats
   cout << fixed << setprecision(2) << endl
        << "votre ticket" << endl
        << "=====================" << endl
        << " - prise en charge   : " << BASE_PRICE << endl
        << " - supp bagages      : " << luggagePrice << endl
        << " - prix de la course : " << travelPrice << endl
        << " TOTAL : " << totalPrice << endl;

   // Laisse l'utilisateur appuyer sur ENTREE pour fermer le programme
   cout << "presser ENTREE pour quitter" << endl;
   cin.ignore(numeric_limits<streamsize>::max(), '\n');

   // Fin de programme :tada:
   return EXIT_SUCCESS;
}

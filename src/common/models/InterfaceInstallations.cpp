#include "Installation.h"
#include "Field.h"
#include "Infirmary.h"
#include "Position.h"
#include "TrainingField.h"
#include "Club.h"
#include "Manager.h"
#include "Shop.h"

#include <iostream>
#include <string>

using namespace std;

//Ordre des installations : Infirmerie, Shop
/*
   int main()
   {
    char quit = 'a';
    while (quit != 'q'){
        cout<< "Bienvenue "<<endl;
        Club club = Club();
        Manager manager = Manager("Bruno", "SupayrPoney", "coucou", club);
        cout << "Que voulez-vous ajouter comme installation? [i pour infirmerie, s pour shop, r pour rien]"<<endl;
        char userChoice;
        cin>> userChoice;
        if (userChoice == 'i'){
            Infirmary infirmary = Infirmary();
            club.addInstallation(infirmary,0);
        }
        else if (userChoice == 's'){
            string shopName;
            cout<<"Nom du magasin?"<<endl;
            cin>>shopName;
            Shop shop = Shop(shopName,1);
            club.addInstallation(shop,0);
        }
        else{
            cout<<"Vous n'avez rien ajouté"<<endl;
        }
        cout<<"voulez-vous quitter? [q pour oui]"<<endl;
        cin>>quit;

    }



    return 0;
   }
 */

# Quiddich Manager 2014

Quiddich Manager 2014 is a university project part of the BA2 cursus in Computer Science at [ULB](http://www.ulb.ac.be/) (Course info-f-209)

The goal was to write in groups of 6 (our was 3) a client-server multiplayer Quiddich game in C++ with no external libs (apart for the GUI)

## Team
* Bruno Rocha Pereira
* Romain Fontaine
* Nikita Marchant

# License

    The MIT License (MIT)
    Copyright (c) 2013-2014
    nimarcha@ulb.ac.be rfontain@ulb.ac.be brochape@ulb.ac.be



# How To

##Compilation

Dans le dossier root, exécutez la commande:

    make


##Exécution

###Client
Dans le dossier root, exécutez la commande:

    make client

Si vous désirez changez l'host(adresse du serveur), executer la commande ./build/bin/client hostname
###Serveur
Exécutez la commande:

    make server

##Documentation
###Doxygen
Pour compiler la documentation, exécutez la commande:

    make doc

Pour l'afficher la documentation, ouvrez le fichier suivant `build/doc/html/index.html`

###Srd
Pour compiler le srd, exécutez la commande:

    make srd

Pour l'afficher, ouvrez le fichier suivant `srd/srd.pdf`


Pour nettoyer les fichiers générés par les compilations, exécutez la commande:

    make clean

###Divers
Par défaut, le serveur tourne sur le port 9000. Pour le modifier, appelez le client avec comme premier paramètre le hostname et comme second paramètre le port.
Pour le serveur, modifiez le fichier `serveurconfig.json` .

Pour exécutez les tests, allez dans le dossier à tester et exécutez la commande :

    make test

Pour initialiser le serveur avec des données de test, exécutez la commande :

    make init

Les utilisateurs suivant seront donc dès lors disponnibles :
 * 'player1' avec le mot de passe 'pass1'
 * 'player2' avec le mot de passe 'pass2'

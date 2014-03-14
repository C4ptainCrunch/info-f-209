#Read Me

##Compilation

Dans le dossier root, exécutez la commande:

    make


##Exécution

###Client
Dans le dossier root, exécutez la commande:

    make client

Si vous désirez changez l'host(adresse du serveur), executer la commande /build/bin/client hostname
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
Par défaut, le serveur tourne sur le port 5000. Pour le modifier, appelez le client avec comme premier paramètre le hostname et comme second paramètre le port.
Pour le serveur, modifiez le fichier `serveurconfig.json` .

Pour exécutez les tests, allez dans le dossier à tester et exécutez la commande :

    make test


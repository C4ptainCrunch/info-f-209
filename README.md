# info-f-209 : Quidditch

## Wiki
GitHub comporte un wiki, ça peut être cool de l'utiliser pour regrouper les informations : [liste des pages existantes](https://github.com/C4ptainCrunch/info-f-209/wiki/_pages)

## Compiler le srd
Utiliser latexmk avec la commande suivante (dans le dossier srd):
```bash
latexmk srd
```

Et pour nettoyer le dossier de tous les fichiers de compilation (.aux et autre):
```bash
latexmk -c
```

## Aide Git
Cloner le répertoire git (si c'est votre première fois, regardez comment configurer git ici en bas)
```bash
git clone git@github.com:C4ptainCrunch/info-f-209.git # Si vous utilisez une clé publique
git clone https://github.com/C4ptainCrunch/info-f-209.git # Si vous n'en avez pas
cd info-f-209
```

Lister les changements et puis commiter l'entièreté
```bash
git status
git commit -a
```

Lister les changements (et fichiers non versionnés) et les ajouter puis commiter
```bash
git status
git add le/chemin/vers/le_fichier l/autre/fichier.txt
git commit -a
```

Pousser ses changements vers GitHub
```bash
git push origin master
```

Récupérer les derniers commits depuis le grand nain ternète
```bash
git pull origin master
```

Voir les derniers commits
```bash
git log # Version verbeuse et complète
git log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit -- # Version coleur cool
```

### Configurer git
A ne faire qu'une fois
```bash
git config —global user.name "Nom Prénom"
git config —global user.email "adresse_mail_pas_spécialement@ulb.ac.be" # Celle de votre compte GitHub
```

Tant qu'on y est, une petite intro à Git : http://try.github.io/


## Because Harry Potter is damn cool
![useless image](http://www.canailleblog.com/photos/mon-pere-a-son-premier-match-de-quidditch-james-sirius-potter20110511154039.jpg)

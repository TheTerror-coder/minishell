# Project "Minishell - As beautiful as a shell"

Description : Le projet consiste à créer un shell simple, une sorte de mini-bash, qui permet d'exécuter des commandes via un interpréteur de lignes de commande interactif. À travers ce projet, tu vas apprendre à manipuler les processus, les descripteurs de fichiers, la gestion de l'historique des commandes, les redirections, les pipes et l’expansion des variables d’environnement, tout en respectant les principes de base d’un shell Unix.
Compétences et technologies utilisées :

    Langage : C
    Gestion des processus : Utilisation de fork, wait, execve, et autres fonctions liées à la gestion des processus.
    Descripteurs de fichiers : Manipulation de fichiers avec des fonctions comme open, read, write, et close.
    Gestion des signaux : Prise en charge des signaux ctrl-C, ctrl-D, et ctrl-\.
    Gestion de l'environnement : Expansion des variables d'environnement avec $ et gestion des commandes comme cd, echo, pwd, etc.
    Interaction avec l'utilisateur : Utilisation de readline pour lire les commandes et affichage d’un prompt interactif.
    Systèmes de redirection et de pipes : Mise en œuvre de redirections de flux (<, >, >>, <<) et de pipes pour connecter plusieurs commandes entre elles.

Responsabilités et Réalisations :

    Création d’un shell interactif :
        Développement d’un shell qui affiche un prompt et attend que l'utilisateur entre une commande.
        Le shell prend en charge l'exécution des commandes en recherchant les exécutables appropriés via la variable d'environnement PATH, ou en utilisant des chemins relatifs/absolus.

    Gestion de l’historique des commandes :
        Implémentation d'un système d'historique qui enregistre les commandes précédentes et les affiche lorsque l'utilisateur appuie sur les flèches haut/bas.
        L’historique fonctionne même après l’exécution d’une commande, permettant à l'utilisateur de naviguer facilement entre les commandes passées.

    Traitement des redirections :
        Gestion des redirections simples et doubles (>, <, >>), en redirigeant l'entrée/sortie standard selon les besoins des commandes.
        Implémentation de la redirection ici-doc (<<), où l'utilisateur peut fournir un délimiteur et l'entrée sera lue jusqu’à ce que ce délimiteur apparaisse.

    Gestion des pipes :
        Implémentation de la gestion des pipes (|), permettant de relier la sortie d'une commande à l'entrée de la suivante dans une séquence de commandes.
        La sortie de chaque commande est connectée à l’entrée de la commande suivante à l'aide de descripteurs de fichiers.

    Gestion des variables d'environnement :
        Expansion des variables d’environnement telles que $HOME, $PATH, et $?, permettant leur utilisation dynamique dans les commandes.
        Le système doit également permettre l'expansion de variables personnalisées en utilisant la syntaxe $.

    Implémentation des commandes internes :
        Création des commandes internes classiques telles que echo (avec l’option -n), cd (avec des chemins relatifs ou absolus), pwd, export, unset, env, et exit.
        Ces commandes sont exécutées directement dans le shell sans lancer de nouveaux processus externes.

    Gestion des signaux :
        Gestion des signaux de manière appropriée, notamment :
            ctrl-C : Affiche un nouveau prompt sur une nouvelle ligne.
            ctrl-D : Quitte le shell.
            ctrl-\ : Aucun effet.
        Assurer que le shell réagit de manière correcte aux interruptions de l'utilisateur.

    Optimisation de la gestion mémoire :
        Bien que la fonction readline() puisse entraîner des fuites de mémoire, aucune fuite n'est autorisée dans le code proprement écrit. Une gestion rigoureuse de la mémoire est implémentée avec malloc, free et autres fonctions de gestion dynamique.

    Respect des contraintes :
        Respect des consignes strictes du projet, notamment l'utilisation d'un nombre limité de variables globales et l'absence de structures non demandées (comme des structures de type "norm").
        Garantie que le shell fonctionne conformément aux attentes de bash dans des scénarios courants.

    Tests et validation :
        Création de tests pour valider le bon fonctionnement du shell dans des configurations diverses (gestion des redirections, des pipes, et des commandes internes).
        Vérification que le shell fonctionne correctement dans des environnements interactifs et non-interactifs.

Résultats :

    Shell fonctionnel : Création d'un shell simple mais complet, capable de gérer des commandes, des redirections, des pipes et des variables d’environnement avec une gestion correcte de l’historique.
    Exécution des commandes : Le shell peut exécuter des commandes locales et des programmes externes en respectant le PATH et les permissions.
    Redirections et pipes : Mise en œuvre robuste des redirections et des pipes permettant une exécution correcte des flux de données entre commandes.
    Support de l’historique et des signaux : Fonctionnalités d'historique de commande et gestion des signaux, avec un comportement conforme à ce qui est attendu sous bash.

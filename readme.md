# Pour installer MySQL Connector/C++, suivez ces étapes :

#### Prérequis avoir installer MySQL avant
Si ce n'est pas le cas, vous pouvez l'installer avec le lien suivant :<br>
https://dev.mysql.com/downloads/windows/installer/

#### Etapes : 
1. Rendez-vous sur la page de téléchargement de MySQL Connector/C++ à l'adresse [https://dev.mysql.com/downloads/connector/cpp/](https://dev.mysql.com/downloads/connector/cpp/).

2. Choisissez la version appropriée pour votre système et cliquez sur "Télécharger".<br>
___ Dans notre cas nous avons choisis: Windows (x86, 64-bit), MSI Installer ___

3. Il se peut que l'on vous demande de vous connecter ou de créer un compte Oracle Web. Si vous ne souhaitez pas le faire, cliquez simplement sur "Non merci, lancez simplement le téléchargement".

4. Une fois le téléchargement terminé, ouvrez l'installateur et suivez les instructions pour installer MySQL Connector/C++.

5. Après l'installation, ajoutez le chemin d'accès aux fichiers d'en-tête de MySQL Connector/C++ dans le chemin d'inclusion de votre compilateur.

6. Pour Visual Studio Code, modifier le fichier `c_cpp_properties.json` dans votre espace de travail. <br> Pour trouver ce fichier, cherchez "c_cpp_properties.json" dans la barre de navigation en haut de vscode. Ajoutez le chemin d'accès à l'ensemble des inclusions (`includePath`) dans ce fichier.
<br>
<br>
Le chemin du fichier dépends de votre système d'exploitation :
<br>
- Sur Windows, si vous avez utilisé l'installateur MySQL, il pourrait se trouver à un emplacement tel que : C:\Program Files\MySQL\MySQL Connector C++ 8.0\include.
<br>
- Sur Linux, si vous l'avez installé via un gestionnaire de paquets tel que apt ou yum, il pourrait se trouver à un emplacement comme : /usr/include/mysql-cppconn-8/jdbc.
<br>
- Sur macOS, si vous l'avez installé via Homebrew, il pourrait se trouver à un emplacement comme /usr/local/Cellar/mysql-connector-c++/8.0.21/include/jdbc.
<br>

7. Voici un exemple de ce à quoi pourrait ressembler le fichier `c_cpp_properties.json` après avoir ajouté le chemin d'accès aux fichiers d'en-tête de MySQL Connector/C++ :
```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/chemin/vers/mysql-connector/include"
            ],
            ...
        }
    ],
    ...
}
```

8. Remplacez
```c
"C:/path/to/mysql-connector/include"
``` 
par le chemin réel du répertoire de MySQL Connector/C++.

9. N'oubliez pas de redémarrer votre IDE après avoir apporté ces modifications pour qu'elles puissent prendre effet.
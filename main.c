#include <cstdio>
#include <cstring>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>

#define MAX_STRING_LENGTH 40

struct Person {
    char nom[MAX_STRING_LENGTH];
    char prenom[MAX_STRING_LENGTH];
    char telephone[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
};

sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
sql::Connection *conn;

void Creer_Enregistrement() {
    struct Person personne;
    printf("Nom : ");
    scanf("%s", personne.nom);
    printf("Prénom : ");
    scanf("%s", personne.prenom);
    printf("Téléphone : ");
    scanf("%s", personne.telephone);
    printf("Email : ");
    scanf("%s", personne.email);

    try {
        sql::Statement *stmt = conn->createStatement();
        char query[256];
        snprintf(query, sizeof(query), "INSERT INTO Personne (Nom, Prenom, Telephone, Email) VALUES ('%s', '%s', '%s', '%s')",
                 personne.nom, personne.prenom, personne.telephone, personne.email);
        stmt->execute(query);
        delete stmt;
        printf("Enregistrement ajouté avec succès.\n");
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur MySQL : " << e.what() << std::endl;
    }
}

void Affiche_Repertoire() {
    try {
        sql::Statement *stmt = conn->createStatement();
        sql::ResultSet *result = stmt->executeQuery("SELECT * FROM Personne");

        if (result == NULL) {
            printf("Aucune personnes présentes en base de données");
            return;
        }

        printf("Répertoire des personnes :\n");
        while (result->next()) {
            printf("Nom : %s\n", result->getString("Nom").c_str());
            printf("Prénom : %s\n", result->getString("Prenom").c_str());
            printf("Téléphone : %s\n", result->getString("Telephone").c_str());
            printf("Email : %s\n", result->getString("Email").c_str());
            printf("-----------\n");
        }

        delete result;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur MySQL : " << e.what() << std::endl;
    }
}

void Recherche() {
    char nomRecherche[MAX_STRING_LENGTH];
    printf("Entrez le nom de la personne que vous recherchez : ");
    scanf("%s", nomRecherche);

    try {
        sql::Statement *stmt = conn->createStatement();
        char query[256];
        snprintf(query, sizeof(query), "SELECT * FROM Personne WHERE Nom = '%s'", nomRecherche);

        sql::ResultSet *result = stmt->executeQuery(query);

        if (result == NULL) {
            printf("La personne avec le nom %s n'existe pas dans la base de données", nomRecherche);
            return;
        }

        printf("Personne trouvée :\n");
        while (result->next()) {
            printf("Nom : %s\n", result->getString("Nom").c_str());
            printf("Prénom : %s\n", result->getString("Prenom").c_str());
            printf("Téléphone : %s\n", result->getString("Telephone").c_str());
            printf("Email : %s\n", result->getString("Email").c_str());
            printf("\n");
        }

        delete result;
        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur MySQL : " << e.what() << std::endl;
    }
}

void Supprimer() {
    char nomSupprimer[MAX_STRING_LENGTH];
    printf("Entrez le nom de la personne à supprimer : ");
    scanf("%s", nomSupprimer);

    try {
        sql::Statement *stmt = conn->createStatement();
        char query[256];
        snprintf(query, sizeof(query), "DELETE FROM Personne WHERE Nom = '%s'", nomSupprimer);

        int rowsAffected = stmt->executeUpdate(query);

        if (rowsAffected > 0) {
            printf("Personne supprimée avec succès.\n");
        } else {
            printf("Aucune personne trouvée avec ce nom. Suppression impossible.\n");
        }

        delete stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur MySQL : " << e.what() << std::endl;
    }
}

int main() {
    try {
        conn = driver->connect("tcp://localhost:3306", "Copium", "Copium");
        conn->setSchema("PROJET_C");

        while (true) {
            int fonctionnalite;

            printf("Que voulez-vous faire :\n");
            printf("* Ajouter une personne (1)\n");
            printf("* Afficher le répertoire (2)\n");
            printf("* Réaliser une recherche par nom (3)\n");
            printf("* Supprimer une personne par nom (4)\n");
            printf("* Quitter (5)\n");

            scanf("%d", &fonctionnalite);

            if (fonctionnalite == 1) Creer_Enregistrement();
            if (fonctionnalite == 2) Affiche_Repertoire();
            if (fonctionnalite == 3) Recherche();
            if (fonctionnalite == 4) Supprimer();
            if (fonctionnalite == 5) break;

            printf("\n");
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur MySQL : " << e.what() << std::endl;
    }

    if (conn) {
        conn->close();
        delete conn;
    }

    printf("Terminé...\n");
    return 0;
}

/*
 * CREATE DATABASE IF NOT EXISTS PROJET_C;

USE APTN61_BD;

CREATE USER IF NOT EXISTS 'copium'@'localhost' IDENTIFIED BY 'copium';
GRANT ALL ON *.* TO 'copium'@'localhost';
FLUSH PRIVILEGES;

DROP TABLE IF EXISTS Personne;

CREATE TABLE IF NOT EXISTS Personne
(
    Id          INT PRIMARY KEY AUTO_INCREMENT,
    Nom 		VARCHAR(40),
    Prenom		VARCHAR(40),
    email		VARCHAR(40)
);
 */
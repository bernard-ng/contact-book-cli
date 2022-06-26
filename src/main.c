#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "contact.h"

int menu()
{
    int menu;
    printf(
        "Menu Principal \n"
        "==================== \n\n"

        GREEN 
        "1. Ajouter les contacts \n"
        "2. Afficher les contacts \n"
        "3. Modifier un contact \n"
        "4. Supprimer un contact \n"
        "5. Rechercher un contact \n\n"
        "6. Quitter \n\n"
        RESET
    );

    do {
        printf("Votre choix (1 à 6) ? : ");
        scanf("%d", &menu);
    } while (menu < 1 || menu > 6);

    return menu;
}

Collection initializeCollection()
{
    int n;

    printf(YELLOW "Combien de données l'application doit-elle sauvegardé ? \n" RESET);
    printf("Combien de contact : ");
    scanf("%d", &n);

    return createCollection(n);
}

Collection createCollection(int size)
{
    Collection collection = (Collection) malloc(sizeof(collection));
    if (NULL != collection) {
        collection->contacts = (Contact) malloc(sizeof(contact) * size);
        
        if (NULL != collection->contacts) {
            collection->current = 0;
            collection->size = size;
            return collection;
        }

        exit(EXIT_FAILURE);
    }

    exit(EXIT_FAILURE);
}

int hasContact(Collection collection, char message[])
{
    if (collection->contacts[0].id == 0) {
        printf(RED "Aucun contacts à %s, commencez par les ajouter !" RESET, message);
        return 1;
    }

    return 0;
}

void createContact(Collection collection) 
{
    system("clear");
    printf(YELLOW "Option : Ajouter les contacts \n" RESET);
    printf("Vous allez rajouter les informations de %d contacts \n\n", collection->size);

    for (int i = 0; i < collection->size; i++)
    {
        collection->current = i;
        collection->contacts[i].id = i + 1;

        printf("(%d) Entrez le nom : ", collection->current + 1);
        scanf("%s", collection->contacts[i].name);

        printf("(%d) Entrez le prenom : ", collection->current + 1);
        scanf("%s", collection->contacts[i].surname);

        printf("(%d) Entrez le numéro : ", collection->current + 1);
        scanf("%s", collection->contacts[i].number);

        if (i != collection->size - 1) {
            printf(GREEN "\n =================== \n" RESET);
        }
    }

    collection->current = 0;
}

void readContact(Collection collection)
{
    if (hasContact(collection, "afficher") == 1) {
        return;
    }

    system("clear");
    printf(YELLOW "Option : Afficher les contacts \n" RESET);
    printf("les informations de %d contacts seront affichées \n\n", collection->size);

    for (int i = 0; i < collection->size; i++)
    {
        printf("Id : %d \n", collection->contacts[i].id);
        printf("Nom : %s \n", collection->contacts[i].name);
        printf("Prenom : %s \n", collection->contacts[i].surname);
        printf("Numéro : %s \n", collection->contacts[i].number);

        if (i != collection->size - 1) {
            printf(GREEN "\n===================\n" RESET);
        }
    }

    collection->current = 0;  
}

void updateContact(Collection collection)
{
    if (hasContact(collection, "modifier") == 1) {
        return;
    }
}

void deleteContact(Collection collection)
{
    if (hasContact(collection, "supprimer") == 1) {
        return;
    }
}

void searchContact(Collection collection)
{
    if (hasContact(collection, "rechercher") == 1) {
        return;
    }
}

void quit(Collection collection)
{
    free(collection);
    printf(GREEN "Au revoir ! \n" RESET);
    exit(EXIT_SUCCESS);
}

void main ()
{
    Collection collection = initializeCollection();

    do {
        system("clear");
        switch (menu())
        {
            default:
            case 1:
                createContact(collection);
                break;

            case 2:
                readContact(collection);
                break;

            case 3:
                updateContact(collection);
                break;

            case 4:
                deleteContact(collection);
                break;

            case 5:
                searchContact(collection);
                break;

            case 6:
                quit(collection);
                break;
        }

    } while (recommencer("voulez-vous effectuer une autre opération ?") == 'O');
    quit(collection);
}

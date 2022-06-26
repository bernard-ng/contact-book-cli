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

void displaySingleContact(contact contact)
{
    printf("Id : %d \n", contact.id);
    printf("Nom : %s \n", contact.name);
    printf("Prenom : %s \n", contact.surname);
    printf("Numéro : %s \n", contact.number);
}

void createSingleContact(Collection collection)
{
    printf("(%d) Entrez le nom : ", collection->current + 1);
    scanf("%s", collection->contacts[collection->current].name);

    printf("(%d) Entrez le prenom : ", collection->current + 1);
    scanf("%s", collection->contacts[collection->current].surname);

    printf("(%d) Entrez le numéro : ", collection->current + 1);
    scanf("%s", collection->contacts[collection->current].number);
}

void updateSingleContact(Contact contact)
{
    printf("Entrez le nouveau nom : ");
    scanf("%s", contact->name);

    printf("Entrez le nouveau prenom : ");
    scanf("%s", contact->surname);

    printf("Entrez le nouveau numéro : ");
    scanf("%s", contact->number);
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
        createSingleContact(collection);

        if (i != collection->size - 1) {
            printf(GREEN "\n===================\n" RESET);
        }
    }

    collection->current = 0;
    printf(GREEN "Contacts ajoutés avec succès ! \n" RESET);
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
        if (collection->contacts[i].id != 0) {
            displaySingleContact(collection->contacts[i]);
        }

        if (i != collection->size - 1) {
            printf(GREEN "\n===================\n" RESET);
        }
    }

    collection->current = 0;  
}

void updateContact(Collection collection)
{
    char name[255];
    int found;

    if (hasContact(collection, "modifier") == 1) {
        return;
    }

    do
    {
        system("clear");
        printf(YELLOW "Option : Modifier un contact \n" RESET);
        printf("vous faites une recherche sur %d contacts\n\n", collection->size);

        printf("Nom du contact à modifier : ");
        scanf("%s", name);

        found = 0;

        for (int i = 0; i < collection->size; i++)
        {
            if (strcmp(name, collection->contacts[i].name) == 0) {
                printf(GREEN "Contact trouvé \n" RESET);
                displaySingleContact(collection->contacts[i]);
                printf(GREEN "\n===================\n" RESET);
                updateSingleContact(&collection->contacts[i]);
                printf(GREEN "Contact modifié avec succès ! \n" RESET);
                found++;
            }
        }

        if (found == 0)
        {
            printf(RED "Aucun contact ne correspond à votre recherche (%s)!" RESET, name);
        }
    } while (recommencer("Voulez-vous relancer la modification ?") == 'O');
    
}

void deleteContact(Collection collection)
{
    char name[255];
    int found;

    if (hasContact(collection, "supprimer") == 1) {
        return;
    }

    do
    {
        system("clear");
        printf(YELLOW "Option : Supprimer un contact \n" RESET);
        printf("vous faites une recherche sur %d contacts\n\n", collection->size);

        printf("Nom du contact à supprimer : ");
        scanf("%s", name);

        found = 0;

        for (int i = 0; i < collection->size; i++)
        {
            if (strcmp(name, collection->contacts[i].name) == 0) {
                printf(GREEN "Contact trouvé \n" RESET);
                displaySingleContact(collection->contacts[i]);

                for (int j = i - 1; j < collection->size - 1; j++)
                {  
                    collection->contacts[i] = collection->contacts[i+1]; 
                }

                printf(GREEN "Contact supprimé avec succès ! \n" RESET);
                found++;
            }
        }

        if (found == 0)
        {
            printf(RED "Aucun contact ne correspond à votre recherche (%s)!" RESET, name);
        }
    } while (recommencer("Voulez-vous relancer la suppression ?") == 'O');
}

void searchContact(Collection collection)
{
    char name[255];
    int found;

    if (hasContact(collection, "rechercher") == 1) {
        return;
    }

    do
    {
        system("clear");
        printf(YELLOW "Option : Rechercher un contact \n" RESET);
        printf("vous faites une recherche sur %d contacts\n\n", collection->size);

        printf("Nom du contact recherché : ");
        scanf("%s", name);

        found = 0;

        for (int i = 0; i < collection->size; i++)
        {
            if (strcmp(name, collection->contacts[i].name) == 0) {
                printf(GREEN "Contact trouvé \n" RESET);
                displaySingleContact(collection->contacts[i]);
                found++;
            }
        }

        if (found == 0)
        {
            printf(RED "Aucun contact ne correspond à votre recherche (%s)!" RESET, name);
        }
    } while (recommencer("Voulez-vous relancer la rechercher ?") == 'O');
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

    } while (recommencer("Voulez-vous effectuer une autre opération ?") == 'O');
    quit(collection);
}

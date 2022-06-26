typedef struct contact
{
    unsigned int id;
    char name[255];
    char surname[255];
    char number[10];
} contact;
typedef contact * Contact;


typedef struct collection
{
    Contact contacts;
    int size;
    int current;
} collection;
typedef collection * Collection;

int menu();
Collection initializeCollection();
Collection createCollection(int size);

// operations sur un contact
void displaySingleContact(contact contact);
void createSingleContact(Collection collection);
void updateSingleContact(Contact contact);

// operations sur l'ensemble de contact
int hasContact(Collection collection, char message[]);
void createContact(Collection collection);
void readContact(Collection collection);
void updateContact(Collection collection);
void deleteContact(Collection collection);
void searchContact(Collection collection);
void quit(Collection collection);

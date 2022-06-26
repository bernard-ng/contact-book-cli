#define RESET  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"

char recommencer(char message[]) {
    char recommencer;
    
    do {
        printf(YELLOW "\n\n%s (O/N) : " RESET, message);
        scanf(" %c", &recommencer);
    } while (recommencer != 'O' && recommencer != 'N');

    return recommencer;
}

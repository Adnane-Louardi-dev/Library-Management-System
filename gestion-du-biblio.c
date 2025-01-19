#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

//structure de date de format JJ/MM/AAAA
typedef struct {
    int day;
    int month;
    int year;
} Date;

//structure de l'etudiant
typedef struct
{
    char studentID[10];
    char studentLastName[10];
    char studentFirstName[10];
    char studentStudyField[10];
    int studentYearOfRegistration;
} Student;

//structure de l'ouvrage
typedef struct
{
    char bookID[10];
    char bookTitle[20];
    char bookAuthor[20];
    char bookGenre[10];
    int bookYearOfPublication;
} Book;

//structure de le pret
typedef struct 
{
    char loanID[10];
    char studentID[10];
    char bookID[10];
    Date loanStartDate;
    Date loanReturnDate;
} Loan;

void printLine(char ch, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", ch);
    }
    printf("\n");
}

//les fonctions de recherche
int searchForStudent(char* givenStudentID, Student* students, int NumberOfAllStudents){
    for(int i=0; i < NumberOfAllStudents; i++){
        if(strcmp(students[i].studentID, givenStudentID)==0){
            return i;
        }
    }
    return -1;
}
int searchForBook(char* givenBookID, Book* books,int NumberOfAllBooks){
    for(int i=0; i < NumberOfAllBooks; i++){
        if(strcmp(books[i].bookID, givenBookID)==0){
            return i;
        }
    }
    return -1;
}
int searchForLoanByBookID(char* givenBookID,Loan* loans,int NumberOfAllLoans){
    for(int i=0; i < NumberOfAllLoans; i++){
    if(strcmp(loans[i].bookID, givenBookID)==0){
        return i;
    }
    }
    return -1;
}
int searchForLoanByLoanID(char* givenLoanID,Loan* loans,int NumberOfAllLoans){
    for(int i=0; i < NumberOfAllLoans; i++){
    if(strcmp(loans[i].loanID, givenLoanID)==0){
        return i;
    }
    }
    return -1;
}
int searchForBookByTitle(char* givenBookTitle,Book* books,int NumberOfAllBooks){
        for(int i=0; i < NumberOfAllBooks; i++){
        if(strcmp(books[i].bookTitle, givenBookTitle)==0){
            return i;
        }
    }
    return -1;
}

//Les methodes pour gerer les oeuvres
void addBook(Book* books, int *NumberOfAllBooks){
    char givenBookID[10], givenBookName[20], givenBookGenre[10], givenBookAuthor[20];

    printf("Entrer ID de l'oeuvre (il doit etre unique): ");
    scanf("%s", givenBookID);

    // Pour effacer input buffer
    while (getchar() != '\n');

    int indexOfBook = searchForBook(givenBookID, books, *NumberOfAllBooks);
    if (indexOfBook < 0) {
        //Ajouter le ID
        sprintf(books[*NumberOfAllBooks].bookID, "BK%s", givenBookID);

        // Ajouter le nom
        printf("Entrez le nom de l'oeuvre: ");
        fgets(givenBookName, sizeof(givenBookName), stdin);
        givenBookName[strcspn(givenBookName, "\n")] = '\0';
        sprintf(books[*NumberOfAllBooks].bookTitle, "%s", givenBookName);

        // Ajouter l'auteur
        printf("Entrez le nom de l'auteur: ");
        fgets(givenBookAuthor, sizeof(givenBookAuthor), stdin);
        givenBookAuthor[strcspn(givenBookAuthor, "\n")] = '\0';
        sprintf(books[*NumberOfAllBooks].bookAuthor, "%s", givenBookAuthor);

        // Ajouter le genre
        printf("Entrez le genre de l'oeuvre: ");
        fgets(givenBookGenre, sizeof(givenBookGenre), stdin);
        givenBookGenre[strcspn(givenBookGenre, "\n")] = '\0';
        sprintf(books[*NumberOfAllBooks].bookGenre, "%s", givenBookGenre);

        // Ajouter l'année d’inscription
        printf("Entrez l'annee d'edition de l'oeuvre: ");
        scanf("%d", &books[*NumberOfAllBooks].bookYearOfPublication);
        while (getchar() != '\n');

        printf("\nL'oeuvre a ete ajoute avec succes");
        printf("\n---------------------------------------------------\n");
        printf("ID: %s\n", books[*NumberOfAllBooks].bookID);
        printf("Nom: %s\n", books[*NumberOfAllBooks].bookTitle);
        printf("Autheur: %s\n", books[*NumberOfAllBooks].bookAuthor);
        printf("Genre: %s\n", books[*NumberOfAllBooks].bookGenre);
        printf("Edition: %d\n", books[*NumberOfAllBooks].bookYearOfPublication);
        printf("---------------------------------------------------\n");

        (*NumberOfAllBooks)++;
    } else {
        printf("\nCe compte existe deja");
        printf("\n---------------------------------------------------\n");
    }
    while (getchar() != '\n');
}
void modificateBook(Book* books, int NumberOfAllBooks){
    char givenBookID[10], givenBookName[20], givenBookAuthor[20], givenBookGenre[10], givenBookYearOfPulication[10];
    int UserCommandInputNumber;

    printf("entrer ID de l'oeuvre: ");
    scanf("%s", &givenBookID);

    // pour effacer input buffer
    while (getchar() != '\n');

    int indexOfBook=searchForBook(givenBookID, books, NumberOfAllBooks);
    if (indexOfBook>=0){
        printf("L'oeuvre qui vous pouver modifier est:\n");
        printf("---------------------------------------------------");
        printf("\nID de l'oeuvre: %s\nLe nom de l'oeuvre: %s\nL'auteur de l'oeuvre: %s\nLe genre de l'oeuvre: %s \nL'annee de l'edition de l'oeuvre: %d\n",books[indexOfBook].bookID, books[indexOfBook].bookTitle, books[indexOfBook].bookAuthor, books[indexOfBook].bookGenre, books[indexOfBook].bookYearOfPublication);
        printf("---------------------------------------------------\n");
        //modifier le nom
        printf("Entrez le nouveau nom de l'oeuvre (ou appuyez sur Entree pour conserver): ");
        fgets(givenBookName, sizeof(givenBookName), stdin);
        if (strcmp(givenBookName, "\n") != 0) { // la possibilite de la concervation de la valeur precedente
            givenBookName[strcspn(givenBookName, "\n")] = '\0';
            sprintf(books[indexOfBook].bookTitle,"%s", givenBookName);
        }
        //modifier l'auteur
        printf("Entrez le nouveau nom de l'auteur (ou appuyez sur Entree pour conserver): ");
        fgets(givenBookAuthor, sizeof(givenBookAuthor), stdin);
        if (strcmp(givenBookAuthor, "\n") != 0) {
            givenBookAuthor[strcspn(givenBookAuthor, "\n")] = '\0';
            sprintf(books[indexOfBook].bookAuthor,"%s", givenBookAuthor);
        }
        // modifier le genre
        printf("Entrez le nouveau genre (ou appuyez sur Entree pour conserver): ");
        fgets(givenBookGenre, sizeof(givenBookGenre), stdin);
        if (strcmp(givenBookGenre, "\n") != 0) {
            givenBookGenre[strcspn(givenBookGenre, "\n")] = '\0';
            sprintf(books[indexOfBook].bookGenre,"%s", givenBookGenre);
        }
        // modifier l'année d'edition
        printf("Entrez la nouvelle annee d'edition (ou appuyez sur Entree pour conserver): ");
        fgets(givenBookYearOfPulication, sizeof(givenBookYearOfPulication), stdin);
        if (strcmp(givenBookYearOfPulication, "\n") != 0) {
            books[indexOfBook].bookYearOfPublication = atoi(givenBookYearOfPulication);
        }
        printLine('-', 30);
        printf("l'oeuvre est modifie avec succes:\n");
        printf("ID de l'oeuvre: %s\nLe nom de l'oeuvre: %s\nL'auteur de l'oeuvre: %s\nLe genre de l'oeuvre: %s \nL'annee de l'edition de l'oeuvre: %d\n",books[indexOfBook].bookID, books[indexOfBook].bookTitle, books[indexOfBook].bookAuthor, books[indexOfBook].bookGenre, books[indexOfBook].bookYearOfPublication);
        printLine('-', 30);
    }else{
        printf("ce oeuvre n'existe pas");
    }
    while (getchar() != '\n');
}
void deleteBook(Book* books, int *NumberOfAllBooks){
    char givenBookID[10];
    printf("\nVeuillez-vous saisir le numero de l'oeuvre: ");
    scanf("%s", &givenBookID);
    // effacer input buffer apres scanf
    while (getchar() != '\n');

    int indexOfBook=searchForBook(givenBookID, books, *NumberOfAllBooks);
    if(indexOfBook>=0){
        for (int i = indexOfBook; i < *NumberOfAllBooks - 1; i++) {
            books[i] = books[i + 1]; // Décaler les comptes 
        }
        (*NumberOfAllBooks)--; // Réduit le nombre total de comptes
        printLine('-', 30);
        printf("L'oeuvre est supprime avec succes !\n");
        printLine('-', 30);
    }else{
        printf("\nCe oeuvre n'existe pas !");
    }
    while (getchar() != '\n');
}
void consultBooks(Book* books, int NumberOfAllBooks){
    for(int i=0;i< NumberOfAllBooks;i++){
        printf("---------------------------------------------------");
        printf("\nID de l'oeuvre: %s\nLe nom de l'oeuvre: %s\nL'auteur de l'oeuvre: %s\nLe genre de l'oeuvre: %s \nL'annee de l'edition: %d\n",books[i].bookID, books[i].bookTitle, books[i].bookAuthor, books[i].bookGenre, books[i].bookYearOfPublication);
    }
    printLine('-', 30);
    printf("Notre Bibiliotheque a %d oeuvres.\n", NumberOfAllBooks);
    printLine('-', 30);
    while (getchar() != '\n');
}
void manageBooks(Book* books, int NumberOfAllBooks){
    int UserCommandInputNumber;
    do
    {
        printf("\e[1;1H\e[2J");
        printf("   _____                _     _                         _                                                                            \n");
        printf("  / ____|              | |   (_)                       | |                                                                           \n");
        printf(" | |  __    ___   ___  | |_   _    ___    _ __       __| |   ___   ___      ___    _   _  __   __  _ __    __ _    __ _    ___   ___ \n");
        printf(" | | |_ |  / _ \\ / __| | __| | |  / _ \\  | '_ \\     / _` |  / _ \\ / __|    / _ \\  | | | | \\ \\ / / | '__|  / _` |  / _` |  / _ \\ / __|\n");
        printf(" | |__| | |  __/ \\__ \\ | |_  | | | (_) | | | | |   | (_| | |  __/ \\__ \\   | (_) | | |_| |  \\ V /  | |    | (_| | | (_| | |  __/ \\__ \\\n");
        printf("  \\_____|  \\___| |___/  \\__| |_|  \\___/  |_| |_|    \\__,_|  \\___| |___/    \\___/   \\__,_|   \\_/   |_|     \\__,_|  \\__, |  \\___| |___/\n");
        printf("                                                                                                                   __/ |             \n");
        printf("                                                                                                                  |___/              \n");        
        printLine('-', 30);
        printf("1. Ajouter un ouvrage.\n2. Modifier les donnees d'un ouvrage.\n3. supprimer un ouvrage.\n4. Consulter des ouvrages.\n0. Quitter\n");
        printLine('-', 30);
        printf("Saisir le nombre du commande pour suivre: ");
        scanf("%d",&UserCommandInputNumber);
        while (getchar() != '\n');

        switch (UserCommandInputNumber)
        {
        case 1:
            addBook(books, &NumberOfAllBooks);
            break;
        case 2:
            modificateBook(books, NumberOfAllBooks);
            break;
        case 3:
            deleteBook(books, &NumberOfAllBooks);
            break;
        case 4:
            consultBooks(books, NumberOfAllBooks);
            break;
        case 0:
            printf("Quitter");
            break;
        default:
            printf("Votre choix est invalide!\n");
        };
    } while (UserCommandInputNumber!=0);
};

//Les methodes pour gerer les etudiants
void addStudent(Student* students, int *NumberOfAllStudents) {
    char givenStudentNumber[10], givenStudentLastName[10], givenStudentFirstName[10], givenStudentstudentStudyField[10];

    printf("Entrer ID de l'etudiant (il doit etre unique): ");
    scanf("%s", givenStudentNumber);

    // Pour effacer input buffer
    while (getchar() != '\n');

    int indexOfStudent = searchForStudent(givenStudentNumber, students, *NumberOfAllStudents);
    if (indexOfStudent < 0) {
        sprintf(students[*NumberOfAllStudents].studentID, "ST%s", givenStudentNumber);
        // Ajouter le nom
        printf("Entrez le nom de l'etudiant: ");
        fgets(givenStudentLastName, sizeof(givenStudentLastName), stdin);
        givenStudentLastName[strcspn(givenStudentLastName, "\n")] = '\0';
        sprintf(students[*NumberOfAllStudents].studentLastName, "%s", givenStudentLastName);

        // Ajouter le prenom
        printf("Entrez le prenom de l'etudiant: ");
        fgets(givenStudentFirstName, sizeof(givenStudentFirstName), stdin);
        givenStudentFirstName[strcspn(givenStudentFirstName, "\n")] = '\0';
        sprintf(students[*NumberOfAllStudents].studentFirstName, "%s", givenStudentFirstName);

        // Ajouter la filière
        printf("Entrez la filiere de l'etudiant: ");
        fgets(givenStudentstudentStudyField, sizeof(givenStudentstudentStudyField), stdin);
        givenStudentstudentStudyField[strcspn(givenStudentstudentStudyField, "\n")] = '\0';
        sprintf(students[*NumberOfAllStudents].studentStudyField, "%s", givenStudentstudentStudyField);

        // Ajouter l'année d’inscription
        printf("Entrez l'annee d'inscription de l'etudiant: ");
        scanf("%d", &students[*NumberOfAllStudents].studentYearOfRegistration);
        while (getchar() != '\n');

        printf("\e[1;1H\e[2J");
        printLine('-', 30);
        printf("L'etudiant a ete ajoute avec succes\n");
        printLine('-', 30);

        printf("ID: %s\n", students[*NumberOfAllStudents].studentID);
        printf("Nom: %s\n", students[*NumberOfAllStudents].studentLastName);
        printf("Prenom: %s\n", students[*NumberOfAllStudents].studentFirstName);
        printf("Filiere: %s\n", students[*NumberOfAllStudents].studentStudyField);

        (*NumberOfAllStudents)++;
    } else {
        printLine('-', 30);
        printf("Ce compte existe deja\n");
        printLine('-', 30);
    }
    while (getchar() != '\n');
}
void modificateStudent(Student* students, int NumberOfAllStudents){
    char givenStudentNumber[10], givenStudentLastName[10], givenStudentFirstName[10], givenStudentstudentStudyField[10], givenstudentYearOfRegistration[10];
    int UserCommandInputNumber;

    printf("entrer ID de l'etudient: ");
    scanf("%s", &givenStudentNumber);

    // pour effacer input buffer
    while (getchar() != '\n');

    int indexOfStudent=searchForStudent(givenStudentNumber, students, NumberOfAllStudents);
    if (indexOfStudent>=0){
        printf("l'etudiant qui vous pouver modifier est:\n");
        printf("---------------------------------------------------");
        printf("\nID de l'etudiant: %s\nLe nom complet de l'etudiant: %s %s\nLa filiere de l'etudiant: %s \nL'annee d'inscription de l'etudiant: %d\n",students[indexOfStudent].studentID, students[indexOfStudent].studentFirstName, students[indexOfStudent].studentLastName, students[indexOfStudent].studentStudyField, students[indexOfStudent].studentYearOfRegistration);
        printf("---------------------------------------------------\n");
        //modifier le nom
        printf("Entrez le nouveau nom de l'etudiant (ou appuyez sur Entree pour conserver): ");
        fgets(givenStudentLastName, sizeof(givenStudentLastName), stdin);
        if (strcmp(givenStudentLastName, "\n") != 0) { // la possibilite de la concervation de la valeur precedente
            givenStudentLastName[strcspn(givenStudentLastName, "\n")] = '\0';
            sprintf(students[indexOfStudent].studentLastName,"%s", givenStudentLastName);
        }
        //modifier le prenom
        printf("Entrez le nouveau prenom de l'etudiant (ou appuyez sur Entree pour conserver): ");
        fgets(givenStudentFirstName, sizeof(givenStudentFirstName), stdin);
        if (strcmp(givenStudentFirstName, "\n") != 0) {
            givenStudentFirstName[strcspn(givenStudentFirstName, "\n")] = '\0';
            sprintf(students[indexOfStudent].studentFirstName,"%s", givenStudentFirstName);
        }
        // modifier la filière
        printf("Entrez la nouveau filiere de l'etudiant (ou appuyez sur Entree pour conserver): ");
        fgets(givenStudentstudentStudyField, sizeof(givenStudentstudentStudyField), stdin);
        if (strcmp(givenStudentstudentStudyField, "\n") != 0) {
            givenStudentstudentStudyField[strcspn(givenStudentstudentStudyField, "\n")] = '\0';
            sprintf(students[indexOfStudent].studentStudyField,"%s", givenStudentstudentStudyField);
        }
        // modifier l'année d’inscription
        printf("Entrez la nouvelle annee d'inscription de l'etudiant (ou appuyez sur Entree pour conserver): ");
        fgets(givenstudentYearOfRegistration, sizeof(givenstudentYearOfRegistration), stdin);
        if (strcmp(givenstudentYearOfRegistration, "\n") != 0) {
            students[indexOfStudent].studentYearOfRegistration = atoi(givenstudentYearOfRegistration);
        }
        printLine('-', 30);  
        printf("l'etudiant est modifie avec succes:\n");
        printf("ID de l'etudiant: %s\nLe nom de l'etudiant: %s\nLe prenom de l'etudiant: %s\nLa filiere de l'etudiant: %s \nL'annee d'inscription de l'etudiant: %d\n",students[indexOfStudent].studentID, students[indexOfStudent].studentLastName, students[indexOfStudent].studentFirstName, students[indexOfStudent].studentStudyField, students[indexOfStudent].studentYearOfRegistration);
        printLine('-', 30);  
        while (getchar() != '\n');
    }else{
        printLine('-', 30);        
        printf("ce etudiant n'existe pas\n");
        printLine('-', 30);
    }
    while (getchar() != '\n');
}
void deleteStudent(Student* students, int *NumberOfAllStudents) {
    char givenStudentID[10];
    printf("Veuillez-vous saisir le numero de l'etudiant: ");
    scanf("%s", &givenStudentID);
    // Nkhwiw input buffer after scanf
    while (getchar() != '\n');

    int indexOfStudent=searchForStudent(givenStudentID, students, *NumberOfAllStudents);
    if(indexOfStudent>=0){
        for (int i = indexOfStudent; i < *NumberOfAllStudents - 1; i++) {
            students[i] = students[i + 1]; // Décaler les comptes 
        }
        (*NumberOfAllStudents)--; // Réduit le nombre total de comptes
        printLine('-', 30);  
        printf("L'etudiant est supprime avec succes !\n");
        printLine('-', 30);  
    }else{
        printLine('-', 30); 
        printf("Ce etudiant n'existe pas!\n");
        printLine('-', 30); 
    }
    while (getchar() != '\n');
}
void consultStudents(Student* students, int NumberOfAllStudents){
    for(int i=0;i< NumberOfAllStudents;i++){
        printf("---------------------------------------------------");
        printf("\nID de l'etudiant: %s\nLe nom complet de l'etudiant: %s %s\nLa filiere de l'etudiant: %s \nL'annee d'inscription de l'etudiant: %d\n",students[i].studentID, students[i].studentFirstName, students[i].studentLastName, students[i].studentStudyField, students[i].studentYearOfRegistration);
    }
    printLine('-', 30); 
    printf("Notre Bibiliotheque a %d etudiants.\n", NumberOfAllStudents);
    printLine('-', 30); 
    while (getchar() != '\n');
}
void manageStudents(Student* students, int NumberOfAllStudents){
    int UserCommandInputNumber;
    do
    {
        printf("\e[1;1H\e[2J");
        printf("   _____                _     _                         _                    __   _                 _   _                   _         \n");
        printf("  / ____|              | |   (_)                       | |                  /_/  | |               | | (_)                 | |        \n");
        printf(" | |  __    ___   ___  | |_   _    ___    _ __       __| |   ___   ___      ___  | |_   _   _    __| |  _    __ _   _ __   | |_   ___ \n");
        printf(" | | |_ |  / _ \\ / __| | __| | |  / _ \\  | '_ \\     / _` |  / _ \\ / __|    / _ \\ | __| | | | |  / _` | | |  / _` | | '_ \\  | __| / __|\n");
        printf(" | |__| | |  __/ \\__ \\ | |_  | | | (_) | | | | |   | (_| | |  __/ \\__ \\   |  __/ | |_  | |_| | | (_| | | | | (_| | | | | | | |_  \\__ \\\n");
        printf("  \\_____|  \\___| |___/  \\__| |_|  \\___/  |_| |_|    \\__,_|  \\___| |___/    \\___|  \\__|  \\__,_|  \\__,_| |_|  \\__,_| |_| |_|  \\__| |___/\n");
        printf("                                                                                                                                      \n");
        printf("                                                                                                                                      \n");
        printLine('-', 30);
        printf("1. Ajouter un etudiant.\n2. Modifier les donnees d'un etudiant.\n3. supprimer un etudiant.\n4. Consulter des etudiants.\n0. Quitter\n");
        printLine('-', 30);
        printf("Saisir le nombre du commande pour suivre: ");
        scanf("%d",&UserCommandInputNumber);
        while (getchar() != '\n');

        switch (UserCommandInputNumber)
        {
        case 1:
            addStudent(students, &NumberOfAllStudents);
            break;
        case 2:
            modificateStudent(students, NumberOfAllStudents);
            break;
        case 3:
            deleteStudent(students, &NumberOfAllStudents);
            break;
        case 4:
            consultStudents(students, NumberOfAllStudents);
            break;
        case 0:
            printf("Quitter");
            break;
        default:
            printf("Votre choix est invalide!\n");
        };
    } while (UserCommandInputNumber!=0);
};

//Les methodes pour gerer les prêts
void makeLoan(Loan* loans, Student* students, Book* books, int *NumberOfAllLoans, int NumberOfAllStudents, int NumberOfAllBooks, SYSTEMTIME t){
    char givenStudentID[10], givenBookID[10];

    printf("\nVeuillez-vous saisir ID de l'etudiant: ");
    scanf("%s", &givenStudentID);
    while (getchar() != '\n');
    int indexOfStudent = searchForStudent(givenStudentID, students, NumberOfAllStudents);

    printf("\nVeuillez-vous saisir ID de l'oeuvre: ");
    scanf("%s", &givenBookID);
    while (getchar() != '\n');
    int indexOfBook = searchForBook(givenBookID, books, NumberOfAllBooks);
    int indexOfLoan= searchForLoanByBookID(givenBookID, loans, *NumberOfAllLoans);

    // Si l'etudiant et l'ouvrage existent, et l'ouvrage n'est pas deja emprunte
    if (indexOfBook >= 0 && indexOfStudent >= 0 && !(indexOfLoan >= 0)){

        //la date de retour
        printf("\nVeuillez-vous saisir le jour de retour en format jj: ");
        scanf("%d", &loans[*NumberOfAllLoans].loanReturnDate.day); //format jj
        while (getchar() != '\n');

        printf("\nVeuillez-vous saisir le mois de retour en format mm: ");
        scanf("%d", &loans[*NumberOfAllLoans].loanReturnDate.month); //format mm
        while (getchar() != '\n');

        printf("\nVeuillez-vous saisir l'annee de retour en format aaaa: ");
        scanf("%d", &loans[*NumberOfAllLoans].loanReturnDate.year); //format aaaa
        while (getchar() != '\n');

        // la date de debut du pret
        loans[*NumberOfAllLoans].loanStartDate.day = t.wDay;
        loans[*NumberOfAllLoans].loanStartDate.month = t.wMonth;
        loans[*NumberOfAllLoans].loanStartDate.year = t.wYear;
        
        //ajouter le pret
        sprintf(loans[*NumberOfAllLoans].loanID, "LN%03d", *NumberOfAllLoans + 1);
        sprintf(loans[*NumberOfAllLoans].bookID, "%s", books[indexOfBook].bookID);
        sprintf(loans[*NumberOfAllLoans].studentID, "%s", students[indexOfStudent].studentID);

        //incrementer le nombre des prets
        (*NumberOfAllLoans)++;
        printLine('-', 30); 
        printf("Le pret a ete ajoute avec succes\n");
        printLine('-', 30);
    }else if (indexOfBook < 0 || indexOfStudent < 0){
        if(indexOfStudent < 0){
            printLine('-', 30); 
            printf("Ce etudiant n'inscrie pas dans notre bibliotheque.\n");
            printLine('-', 30); 
        }else{
            printLine('-', 30); 
            printf("L'ouvrage n'existe pas dans notre bibliotheque.\n");
            printLine('-', 30); 
        }
    }else{
        printLine('-', 30); 
        printf("L'ouvrage est deja emprunte.\n");
        printLine('-', 30); 
    }
    while (getchar() != '\n');
}
void returnLoan(Loan* loans, int *NumberOfAllLoans){
    char givenLoanID[10];
    printf("\nVeuillez-vous saisir ID du pret: ");
    scanf("%s", &givenLoanID);
    while (getchar() != '\n');

    int indexOfLoan= searchForLoanByLoanID(givenLoanID, loans, *NumberOfAllLoans);
    if(indexOfLoan>=0){
        for (int i = indexOfLoan; i < *NumberOfAllLoans - 1; i++) {
            loans[i] = loans[i + 1]; // Décaler les prets 
        }
        (*NumberOfAllLoans)--; // Réduit le nombre total des prets
        printLine('-', 30); 
        printf("Le pret a ete marque comme retourne avec succes !\n");
        printLine('-', 30);
        
    }else{
        printLine('-', 30); 
        printf("Ce pret n'existe pas.\n");
        printLine('-', 30); 
    }
    while (getchar() != '\n');
}
void manageLoans(Student* students, Book* books, Loan* loans, int NumberOfAllBooks, int NumberOfAllStudents, int *NumberOfAllLoans, SYSTEMTIME t){
    int UserCommandInputNumber;
    do
    {
        printf("\e[1;1H\e[2J");
        printf("   _____                _     _                         _                                  //\\   _         \n");
        printf("  / ____|              | |   (_)                       | |                                |/ \\| | |        \n");
        printf(" | |  __    ___   ___  | |_   _    ___    _ __       __| |   ___   ___     _ __    _ __    ___  | |_   ___ \n");
        printf(" | | |_ |  / _ \\ / __| | __| | |  / _ \\  | '_ \\     / _` |  / _ \\ / __|   | '_ \\  | '__|  / _ \\ | __| / __|\n");
        printf(" | |__| | |  __/ \\__ \\ | |_  | | | (_) | | | | |   | (_| | |  __/ \\__ \\   | |_) | | |    |  __/ | |_  \\__ \\\n");
        printf("  \\_____|  \\___| |___/  \\__| |_|  \\___/  |_| |_|    \\__,_|  \\___| |___/   | .__/  |_|     \\___|  \\__| |___/\n");
        printf("                                                                          | |                              \n");
        printf("                                                                          |_|                              \n");      
        printLine('-', 30);
        printf("1. Enregistrer un pret\n2. Retourner un ouvrage\n0. Quitter\n");
        printLine('-', 30);
        printf("Saisir le nombre du commande pour suivre: ");
        scanf("%d",&UserCommandInputNumber);
        while (getchar() != '\n');

        switch (UserCommandInputNumber)
        {
        case 1:
            makeLoan(loans, students, books, NumberOfAllLoans, NumberOfAllStudents, NumberOfAllBooks, t);
            break;
        case 2:
            returnLoan(loans, NumberOfAllLoans);
            break;
        case 0:
            printf("Quitter");
            break;
        default:
            printf("Votre choix est invalide!\n");
        };
    } while (UserCommandInputNumber!=0);
}

//Les methodes de recherches
void searchForStudentByID(Student* students, int NumberOfAllStudents){
    char givenStudentID[10];

    printf("\nVeuillez-vous saisir ID de l'etudiant: ");
    scanf("%s", &givenStudentID);
    while (getchar() != '\n');

    int indexOfStudent=searchForStudent(givenStudentID, students, NumberOfAllStudents);
    if(indexOfStudent>=0){
        printf("\n---------------------------------------------------\n");
        printf("ID: %s\n", students[indexOfStudent].studentID);
        printf("Nom: %s\n", students[indexOfStudent].studentLastName);
        printf("Prenom: %s\n", students[indexOfStudent].studentFirstName);
        printf("Filiere: %s\n", students[indexOfStudent].studentStudyField);
        printf("L'annee de registration: %d\n", students[indexOfStudent].studentYearOfRegistration);
        printf("---------------------------------------------------\n");
    }else{
        printLine('-', 30); 
        printf("Ce etudiant n'existe pas\n");
        printLine('-', 30); 
    }
    while (getchar() != '\n');
}
void searchForBookByTitleOrGenre(Book* books, int NumberOfAllBooks){
    char givenBookTitle[20], givenBookGenre[10];
    int UserCommandInputNumber;
    printf("1. Recherche par titre\n2. Recherche par le genre\n0. Quitter\n");
    printf("Saisir le nombre du commande pour suivre: ");
    scanf("%d", &UserCommandInputNumber);
    while (getchar() != '\n');

    switch (UserCommandInputNumber)
        {
            case 1:
                printf("\nVeuillez-vous saisir le titre de l'oeuvre: ");
                fgets(givenBookTitle, sizeof(givenBookTitle), stdin);
                givenBookTitle[strcspn(givenBookTitle, "\n")] = '\0';

                int indexOfBook=searchForBookByTitle(givenBookTitle, books, NumberOfAllBooks);//convertir le titre en minuscule
                if(indexOfBook>=0){
                    printLine('-', 30);
                    printf("ID de l'oeuvre: %s\nLe nom de l'oeuvre: %s\nL'auteur de l'oeuvre: %s\nLe genre de l'oeuvre: %s \nL'annee de l'edition: %d\n",books[indexOfBook].bookID, books[indexOfBook].bookTitle, books[indexOfBook].bookAuthor, books[indexOfBook].bookGenre, books[indexOfBook].bookYearOfPublication);
                    printLine('-', 30); 
                }else{
                    printLine('-', 30); 
                    printf("Ce oeuvre n'existe pas\n");
                    printLine('-', 30); 
                }
                break;
            case 2:
                printf("\nVeuillez-vous saisir le genre de l'oeuvre: ");
                scanf("%s", &givenBookGenre);
                while (getchar() != '\n');
                for(int i=0;i< NumberOfAllBooks;i++){
                    if (strcmp(books[i].bookGenre, givenBookGenre)==0)
                    {
                        printLine('-', 30); 
                        printf("ID de l'oeuvre: %s\nLe nom de l'oeuvre: %s\nL'auteur de l'oeuvre: %s\nLe genre de l'oeuvre: %s \nL'annee de l'edition: %d\n",books[i].bookID, books[i].bookTitle, books[i].bookAuthor, books[i].bookGenre, books[i].bookYearOfPublication);
                        printLine('-', 30); 
                    }
                }
                break;
            case 0:
                break;
            default:
                printLine('-', 30); 
                printf("Votre choix est invalide!\n");
                printLine('-', 30); 
        };
    while (getchar() != '\n');
}
void search(Student* students, Book* books, int NumberOfAllBooks, int NumberOfAllStudents){
    int UserCommandInputNumber;
    do
    {
        printf("\e[1;1H\e[2J");
        printf("  _____                  _                            _                  \n");
        printf(" |  __ \\                | |                          | |                 \n");
        printf(" | |__) |   ___    ___  | |__     ___   _ __    ___  | |__     ___   ___ \n");
        printf(" |  _  /   / _ \\  / __| | '_ \\   / _ \\ | '__|  / __| | '_ \\   / _ \\ / __|\n");
        printf(" | | \\ \\  |  __/ | (__  | | | | |  __/ | |    | (__  | | | | |  __/ \\__ \\\n");
        printf(" |_|  \\_\\  \\___|  \\___| |_| |_|  \\___| |_|     \\___| |_| |_|  \\___| |___/\n");
        printf("                                                                         \n");
        printf("                                                                         \n");        
        printLine('-', 30);
        printf("1. Rechercher un etudiant par numero.\n2. Rechercher un ouvrage par titre ou specialite.\n0. Quitter\n");
        printLine('-', 30);
        printf("Saisir le nombre du commande pour suivre: ");
        scanf("%d",&UserCommandInputNumber);
        while (getchar() != '\n');

        switch (UserCommandInputNumber)
        {
        case 1:
            searchForStudentByID(students, NumberOfAllStudents);
            break;
        case 2:
            searchForBookByTitleOrGenre(books, NumberOfAllBooks);
            break;
        case 0:
            printf("Quitter");
            break;
        default:
            printf("Votre choix est invalide!\n");
        };
    } while (UserCommandInputNumber!=0);
}

//Les methodes de generation d'etats
void showLoans(Loan* loans, Student* students, Book* books, int NumberOfAllLoans, int NumberOfAllStudents, int NumberOfAllBooks){
    for(int i=0;i< NumberOfAllLoans;i++){
        int indexOfStudent=searchForStudent(loans[i].studentID, students, NumberOfAllStudents);
        int indexOfBook=searchForBook(loans[i].bookID, books, NumberOfAllBooks);
        printLine('*', 60);
        printf("ID de le pres: %s\nID de l'etudiant: %s\nID de l'oeuvre: %s\nDate de debut de pret: %02d/%02d/%04d\nDate de retour prevue: %02d/%02d/%04d\n", loans[i].loanID, loans[i].studentID, loans[i].bookID, loans[i].loanStartDate.day, loans[i].loanStartDate.month, loans[i].loanStartDate.year, loans[i].loanReturnDate.day, loans[i].loanReturnDate.month, loans[i].loanReturnDate.year);
        printf("\n>>>>>>>>>>>>>>>>Les informations de l'etudiant");
        printf("\nID de l'etudiant: %s\nLe nom complet de l'etudiant: %s %s\nLa filiere de l'etudiant: %s \nL'annee d'inscription de l'etudiant: %04d\n",students[indexOfStudent].studentID, students[indexOfStudent].studentFirstName, students[indexOfStudent].studentLastName, students[indexOfStudent].studentStudyField, students[indexOfStudent].studentYearOfRegistration);
        printf("\n>>>>>>>>>>>>>>>>Les informations de l'ouvrage");
        printf("\nID de l'oeuvre: %s\nLe nom de l'oeuvre: %s\nL'auteur de l'oeuvre: %s\nLe genre de l'oeuvre: %s \nL'annee de l'edition: %04d\n",books[indexOfBook].bookID, books[indexOfBook].bookTitle, books[indexOfBook].bookAuthor, books[indexOfBook].bookGenre, books[indexOfBook].bookYearOfPublication);
        printLine('*', 60);
    }
    printLine('*', 60);
    printf("Notre Bibiliotheque a %d prets.\n", NumberOfAllLoans);
    printLine('*', 60);
    while (getchar() != '\n');
}
int compareDates (Date currentDate, Date returnDate)
{
    if (currentDate.year < returnDate.year)
       return -1;
    else if (currentDate.year > returnDate.year)
       return 1;
    if (currentDate.year == returnDate.year)
    {
        if (currentDate.month<returnDate.month)
            return -1;
        else if (currentDate.month>returnDate.month)
            return 1;
        else if (currentDate.day<returnDate.day)
            return -1;
        else if(currentDate.day>returnDate.day)
            return 1;
        else
            return 0;
    }
}
void delayedLoans(Loan* loans,int NumberOfAllLoans, SYSTEMTIME t){
    Date currentDate={t.wDay, t.wMonth, t.wYear};
    for(int i=0;i<NumberOfAllLoans;i++){
        if (compareDates(currentDate, loans[i].loanReturnDate) > 0)
        {
            printf("\n---------------------------------------------------\n");
            printf("ID de le pres: %s\nID de l'etudiant: %s\nID de l'oeuvre: %s\nDate de debut de pret: %2d/%2d/%4d\nDate de retour prevue: %2d/%2d/%4d\n", loans[i].loanID, loans[i].studentID, loans[i].bookID, loans[i].loanStartDate.day, loans[i].loanStartDate.month, loans[i].loanStartDate.year, loans[i].loanReturnDate.day, loans[i].loanReturnDate.month, loans[i].loanReturnDate.year);
            printf(">>>>>>>>>>> En ratard !<<<<<<<<<<<\n");
        }
    }
    while (getchar() != '\n');
}
void generateStatus(Loan* loans, Student* students, Book* books, int NumberOfAllLoans, int NumberOfAllStudents, int NumberOfAllBooks, SYSTEMTIME t){
    int UserCommandInputNumber;
    do
    {
        printf("\e[1;1H\e[2J");
        printf("   _____     __             __                  _     _                         _     __   _             _         \n");
        printf("  / ____|   /_/            /_/                 | |   (_)                       | |   /_/  | |           | |        \n");
        printf(" | |  __    ___   _ __     ___   _ __    __ _  | |_   _    ___    _ __       __| |   ___  | |_    __ _  | |_   ___ \n");
        printf(" | | |_ |  / _ \\ | '_ \\   / _ \\ | '__|  / _` | | __| | |  / _ \\  | '_ \\     / _` |  / _ \\ | __|  / _` | | __| / __|\n");
        printf(" | |__| | |  __/ | | | | |  __/ | |    | (_| | | |_  | | | (_) | | | | |   | (_| | |  __/ | |_  | (_| | | |_  \\__ \\\n");
        printf("  \\_____|  \\___| |_| |_|  \\___| |_|     \\__,_|  \\__| |_|  \\___/  |_| |_|    \\__,_|  \\___|  \\__|  \\__,_|  \\__| |___/\n");
        printf("                                                                                                                   \n");
        printf("                                                                                                                   \n");
        printLine('-', 30);
        printf("1. Liste des livres empruntes\n2. Liste des retards\n0. Quitter\n");
        printLine('-', 30);
        printf("Saisir le nombre du commande pour suivre: ");
        scanf("%d",&UserCommandInputNumber);
        while (getchar() != '\n');

        switch (UserCommandInputNumber)
        {
        case 1:
            showLoans(loans, students, books, NumberOfAllLoans, NumberOfAllStudents, NumberOfAllBooks);
            break;
        case 2:
            delayedLoans(loans, NumberOfAllLoans, t);
            break;
        case 0:
            printf("Quitter");
            break;
        default:
            printf("Votre choix est invalide!\n");
        };
    } while (UserCommandInputNumber!=0);
}

int main()
{
        int UserCommandInputNumber;
        srand(time(NULL));
        SYSTEMTIME t; // declarer SYSTEMTIME struct pour le temps local
        GetLocalTime(&t);

        Student students[100]={
            {"ST001", "Smith", "John", "CS", 2020},
            {"ST002", "Doe", "Jane", "Math", 2021},
            {"ST003", "Brown", "James", "Physics", 2022},
            {"ST004", "Taylor", "Emily", "Bio", 2023},
            {"ST005", "Wilson", "Emma", "Chem", 2024}
        };// toutes les etudiants
        Book books[100]= {
            {"BK001", "1984", "Orwell", "Fiction", 1949},
            {"BK002", "Dune", "Herbert", "Sci-Fi", 1965},
            {"BK003", "It", "King", "Horror", 1986},
            {"BK004", "Hamlet", "Shakespeare", "Drama", 1603},
            {"BK005", "Sapiens", "Harari", "History", 2011},
            {"BK006", "Inferno", "Brown", "Mystery", 2013},
            {"BK007", "Dracula", "Stoker", "Horror", 1897},
            {"BK008", "Foundation", "Asimov", "Sci-Fi", 1951},
            {"BK009", "Frankenstein", "Shelley", "Horror", 1818},
            {"BK010", "The Hobbit", "Tolkien", "Fantasy", 1937}
        };// toutes les oeuvres
        Loan loans[100] = {
            {"LN001", "ST006", "BK006", {1, 1, 2025}, {7, 1, 2025}},
            {"LN002", "ST002", "BK002", {2, 1, 2025}, {16, 1, 2025}},
            {"LN003", "ST003", "BK003", {3, 1, 2025}, {17, 1, 2025}},
            {"LN004", "ST004", "BK004", {4, 1, 2025}, {18, 1, 2025}},
            {"LN005", "ST005", "BK005", {5, 1, 2025}, {19, 1, 2025}}
        };// toutes les prets
        int NumberOfAllStudents=5, NumberOfAllBooks=10, NumberOfAllLoans=5;
    do{
        printf("\e[1;1H\e[2J");
        printf("   _____           _   _                   _                      ____  _ _     _ _       _   _      __                   \n");
        printf("  / ____|         | | (_)                 | |                    |  _ \\(_) |   (_) |     | | | |     \\_\\                  \n");
        printf(" | |  __  ___  ___| |_ _  ___  _ __     __| |  _   _ _ __   ___  | |_) |_| |__  _| | ___ | |_| |__   ___  __ _ _   _  ___ \n");
        printf(" | | |_ |/ _ \\/ __| __| |/ _ \\| '_ \\   / _` | | | | | '_ \\ / _ \\ |  _ </ | '_ \\| | |/ _ \\| __| '_ \\ / _ \\/ _` | | | |/ _ \\\n");
        printf(" | |__| |  __/\\__ \\ |_| | (_) | | | | | (_| | | |_| | | | |  __/ | |_) | | |_) | | | (_) | |_| | | |  __/ (_| | |_| |  __/\n");
        printf("  \\_____|\\___||___/\\__|_|\\___/|_| |_|  \\__,_|  \\__,_|_| |_|\\___| |____/|_|_.__/|_|_|\\___/ \\__|_| |_|\\___|\\__, |\\__,_|\\___|\n");
        printf("                                                                                                            | |           \n");
        printf("                                                                                                            |_|           \n");
        printLine('*', 30);
        printf("MENU PRINCIPAL\n");
        printLine('*', 30);
        printLine('-', 30);
        printf("1. Gestion des etudiants.\n2. Gestion des ouvrages.\n3. Gestion des prets.\n4. Recherches.\n5. Generation d'etats.\n0. Quitter\n");
        printLine('-', 30);
        printf("\nSaisir le nombre du commande pour suivre: ");
        scanf("%d",&UserCommandInputNumber);
        while (getchar() != '\n');

        switch(UserCommandInputNumber){
        case 1:
            manageStudents(students, NumberOfAllStudents);
            break;
        case 2:
            manageBooks(books, NumberOfAllBooks);
            break;
        case 3:
            manageLoans(students, books, loans, NumberOfAllBooks, NumberOfAllStudents, &NumberOfAllLoans, t);
            break;
        case 4:
            search(students, books, NumberOfAllBooks, NumberOfAllStudents);
            break;
        case 5:
            generateStatus(loans, students, books, NumberOfAllLoans, NumberOfAllStudents, NumberOfAllBooks, t);
            break;
        case 0:
            printf("Quitter");
            break;
        default:
            printf("Votre choix est invalide!\n");
        };
    } while (UserCommandInputNumber!=0);
    return 0;
}
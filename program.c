#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct node{
    int value;
    struct node* next;
};



void deleteFirstNode(struct node**);
void makeNode(struct node**, int);
void deleteLastNode(struct node**);
void deleteNodeByValue(struct node**, int);
void addElementAfterElementWithValue(struct node**, int, int);
void addElementBeforeElementWithValue(struct node**, int, int);
void printLengthOfList(struct node*);
void printList(struct node*, int);
void numberOfOccurences(struct node*, int);
void deleteList(struct node**);
void printBigONotation();
void printNode(int);
int sanScan();

int main(){

    int svar;
    int tempValue = 0;
    int tempValueNewNode = 0;
    int flag = 0;

    struct node* head = NULL;

    while(1){
        do{
            svar = -1;
            tempValue = tempValueNewNode = 0;
            printf("\n_______________________________\n");
            printf("Hvilket meny-valg vil du gjøre?\n");
            printf("Skriv 0 for hjelp\n\n");
            if(flag){
                printf("0. Print ut disse menyvagene igjen\n");
                printf("1. Slett den første node i listen\n");
                printf("2. Lag en ny node\n");
                printf("3. Slett den siste noden i listen\n");
                printf("4. Slett node med oppgitt verdi\n");
                printf("5. Lag node som blir plassert etter en node med oppgitt verdi\n");
                printf("6. Lag node som blir plassert før en node med oppgitt verdi\n");
                printf("7. Skriv ut lengden av listen\n");
                printf("8. Skriv ut antall forekomster av et oppgitt tall\n");
                printf("9. Skriv ut listen\n");
                printf("10. Slett hele listen\n");
                printf("11. G tidskompleksitet for hver funksjon\n\n");
                flag = 0;
            }
            int c;
            printf("Valg: ");
            scanf(" %d", &svar);
            if(!(svar >= 0 && svar <= 11)){
                    printf("Feil input, prøv igjen\n");
                    sleep(5);
                    tcflush(STDIN_FILENO, TCIFLUSH);
            }
        }while((svar < 1 && svar > 11));

        switch (svar)
        {
            case 0: flag = 1; break;
            case 1: deleteFirstNode(&head); break; //Slette første noden i listen
            case 2: printf("Hva skal verdien til noden være?\n"); scanf(" %d", &tempValue);makeNode(&head, tempValue); break; //Legge til node i slutten av listen
            case 3: deleteLastNode(&head); break; //Slett et element i slutten av lista
            case 4: printf("Hva skal verdien være på noden du skal slette? \n"); scanf(" %d", &tempValue); deleteNodeByValue(&head, tempValue);break; //Slett et element med oppgitt verdi i lista
            case 5: printf("Hvilken verdi skal den nye noden ha?\n"); scanf(" %d", &tempValue); printf("Og hvilken verdi skal noden som den skal ligge etter ha?\n"); scanf(" %d", &tempValueNewNode); addElementAfterElementWithValue(&head, tempValue, tempValueNewNode);break; //Legg til et element etter et element med oppgitt verdi
            case 6: printf("Hvilken verdi skal den nye noden ha?\n"); scanf(" %d", &tempValue); printf("Og hvilken verdi skal noden som den skal ligge foran ha?\n"); scanf(" %d", &tempValueNewNode); addElementBeforeElementWithValue(&head, tempValue, tempValueNewNode); break; //Legg til et element foran et element med oppgitt verdi
            case 7: printLengthOfList(head); break; //Skriv ut lengden på listen
            case 8: printf("Hvilket tall skal letes etter?\n"); scanf(" %d", &tempValue); numberOfOccurences(head, tempValue); break; //Tell opp antall forekomster av element med gitt verdi i lista, dette antallet skrives ut
            case 9: printf("Skriv 1 for visuelt kart og 2 for kompakt liste over nodene\n"); tempValue = sanScan(); printList(head, tempValue); break; //Skriv ut hele listen
            case 10: deleteList(&head); break; //Slett hele listen. Hvor mange elementer som ble slettet, skrives ut
            case 11: printBigONotation(); break; //G tidskompleksitet (Big O) for hver funksjon
            default: break;
        }
    }

    return 0;
}


void deleteFirstNode(struct node** headRef){
    if(*headRef != NULL){ //Sjekker om lista er tom, om head peker på en node i stedet for NULL
        struct node* temp; //lager en temp peker
        temp = *headRef; //temp peker peker på den første noden i lista
        temp = temp->next; //temp peker peker på node nr. 2 i lista, som da skal bli node nr. 1 etter at første node er slettet
        free(*headRef);
        *headRef = temp; //head blir satt til node nr. 2, slik at node nr. 1 ikke har en peker til seg lenger, som essensielt sletter noden
        printf("Den første noden i listen er slettet\n");
    }else{
        printf("Listen er tom og kan ingen noder som kan slettes\n");
    }
}

void makeNode(struct node** headRef, int value){
    struct node* newNode = (struct node*)malloc(sizeof(struct node)); //Den nye noden blir opprettet i minne
    struct node* currPtr = *headRef; //oppretter en peker som peker på samme ting som pekeren head
    if(currPtr != NULL){ //sjekker om det er en node i listen, hvis ikke så peker head på null
        while(currPtr->next != NULL){
            currPtr = currPtr->next; //Itererer gjennom lista for å finne siste node i lista
        }
        newNode->value = value; //Setter verdien på noden
        newNode->next = currPtr->next; //setter nye noden sin next til den siste noden i lista sin next
        currPtr->next = newNode; //setter den siste noden i lista til å peke på den nye noden
        printf("Ny node er lagt til med verdi %d \n", newNode->value);
    }else{ //Dette er hvis listen er null
        newNode->value = value; //Setter verdi på den nye noden
        newNode->next = *headRef; //Setter den nye noden sin next til det head peker på, skal pekes på NULL
        *headRef = newNode; //Setter head til å peke på den nye noden
        printf("Ny node er lagt til som første node i listen med verdi %d \n", newNode->value);
    }
}

void deleteLastNode(struct node** headRef){
    struct node* currPtr = *headRef; //oppretter en peker som peker på samme ting som pekeren head
    struct node* temp;
    int flag = 0;

    if(currPtr != NULL){ //sjekker om det er en node i listen, hvis ikke så peker head på null
        while(currPtr->next != NULL){
            temp = currPtr;
            currPtr = currPtr->next; //Itererer gjennom lista for å finne siste node i lista
            flag = 1;
        }
        if(flag == 0){
            *headRef = currPtr->next;
        }else{
            temp->next = currPtr->next;
        }
        free(currPtr);
        printf("Den siste noden i lista er slettet\n");

    }else{ //Dette er hvis listen er null
        printf("Lista er tom, kan ikke slette en node\n");
    }
}

void deleteNodeByValue(struct node** headRef, int value){
    struct node* currPtr = *headRef;
    struct node* temp;

    if(currPtr != NULL && currPtr->value != value){
        while(currPtr != NULL){
            if(currPtr->value == value){
                temp->next = currPtr->next;
                printf("Element med verdi: %d ble slettet\n", currPtr->value);
                break;
            }
            temp = currPtr;
            currPtr = currPtr->next;
        }
    }else if(currPtr != NULL && currPtr->value == value){
        *headRef = currPtr->next;
        printf("Element med verdi: %d ble slettet\n", currPtr->value);
    }else{
        printf("Listen er tom, kan ikke slette en node\n");
    }
}

void addElementAfterElementWithValue(struct node** headRef, int newNodeValue, int searchValue){
    struct node* currPtr = *headRef;
    int flag = 0;
    if(currPtr != NULL){
        while(currPtr != NULL){
            if(currPtr->value == searchValue){
                struct node* newNode = (struct node*)malloc(sizeof(struct node)); //Den nye noden blir opprettet i minne
                newNode->value = newNodeValue; //Setter verdien på noden
                newNode->next = currPtr->next; //setter nye noden sin next til den siste noden i lista sin next
                currPtr->next = newNode; //setter den siste noden i lista til å peke på den nye noden
                printf("Ny node er lagt til med verdi %d, etter noden med verdi %d \n", newNode->value, currPtr->value);
                flag = 1;
                break;
            }
            currPtr = currPtr->next;
        }
        if(flag == 0){
            printf("Kunne ikke finne noden du valgte\n");
        }
    }else{
        printf("Listen er tom, kan ikke søke gjennom tom liste");
    }
}

void addElementBeforeElementWithValue(struct node** headRef, int newNodeValue, int searchValue){
    struct node* currPtr = *headRef;
    struct node* temp;
    int flag = 0;
    if(currPtr != NULL){
        while(currPtr != NULL){
            if(currPtr->value == searchValue){
                struct node* newNode = (struct node*)malloc(sizeof(struct node)); //Den nye noden blir opprettet i minne
                newNode->value = newNodeValue; //Setter verdien på noden
                newNode->next = currPtr; //setter nye noden sin next til den siste noden i lista sin next
                temp->next = newNode; //setter den siste noden i lista til å peke på den nye noden
                printf("Ny node er lagt til med verdi %d, foran noden med verdi %d \n", newNode->value, currPtr->value);
                flag = 1;
                break;
            }
            temp = currPtr;
            currPtr = currPtr->next;
        }
        if(flag == 0){
            printf("Kunne ikke finne noden du valgte\n");
        }
    }else{
        printf("Listen er tom, kan ikke søke gjennom tom liste");
    }
}

void printLengthOfList(struct node* currPtr){
    int teller = 0;
    if(currPtr != NULL){
        while(currPtr != NULL){
            teller++;
            currPtr = currPtr->next;
        }
        printf("Lista har lengden: %d \n", teller);
    }else{
        printf("Lista er tom, lengden er derfor 0\n");
    }
}

void printList(struct node* currPtr, int valg){
    int teller = 0;
    if(valg == 1){
        if(currPtr == NULL){
            printf("Listen er tom (head == NULL)\n\n");
        }
        printf("     HEAD\n");
        printf("      V\n");
        while(currPtr != NULL){
            teller++;
            printNode(currPtr->value);
            //printf("Node nr. %d har verdien %d \n", teller, currPtr->value);
            currPtr = currPtr->next;
        }
        printf("     NULL\n");
    }else if(valg == 2){
        if(currPtr != NULL){
            while(currPtr != NULL){
                teller++;
                printf("Node nr. %d har verdien %d \n", teller, currPtr->value);
                currPtr = currPtr->next;
            }
        }else{
            printf("Listen er tom\n");
        }
    }else{
        printf("error: Valg utenfor område");
    }
}

void numberOfOccurences(struct node* currPtr, int tall){
    int teller = 0;
    if(currPtr != NULL){
        while(currPtr != NULL){
            if(currPtr->value == tall){
                teller++;
            }
            currPtr = currPtr->next;
        }
        printf("Det finnes %d forekomster av taller %d\n", teller, tall);
    }else{
        printf("Lista er tom\n");
    }
}

void deleteList(struct node** headRef){
    struct node* currPtr = *headRef;
    struct node* temp;
    int teller = 0;

    if(currPtr != NULL){
        while(currPtr != NULL){
            temp = currPtr;
            currPtr = currPtr->next;
            free(temp);
            teller++;
        }
        *headRef = NULL;
        printf("%d elementer ble slettet\n", teller);

    }else{
        printf("Lista er allerede tom\n");
    }
}

void printBigONotation(){
    printf("Tidskompleksitet for hver funskjon:\n");
    printf("Funksjon 1: O(1)\n");
    printf("Funksjon 2: O(n)\n");
    printf("Funksjon 3: O(n)\n");
    printf("Funksjon 4: O(n)\n");
    printf("Funksjon 5: O(n)\n");
    printf("Funksjon 6: O(n)\n");
    printf("Funksjon 7: O(n)\n");
    printf("Funksjon 8: O(n)\n");
    printf("Funksjon 9: O(n)\n");
    printf("Funksjon 10: O(n)\n");
    
}

void printNode(int verdi){
    printf("╭-----------╮\n");
    printf("| %5d     | \n", verdi);
    printf("|-----------|\n");
    printf("|   next    |\n");
    printf("╰-----------╯\n");
    printf("      V     \n");
}

int sanScan(){
    int temp;
    do{
        scanf(" %d", &temp);
        if(!(temp == 1 || temp == 2)){
            printf("Feil valg, prøv igjen\n");
        }
    }while(!(temp == 1 || temp == 2));
    return temp;
}

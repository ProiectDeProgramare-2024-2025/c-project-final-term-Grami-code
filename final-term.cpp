#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char numarCard[20];
    char numePosesor[50];
    char dataExpirare[10];
} Card;

void citesteDinFisier(Card carduri[], int* n) {
    FILE* f = fopen("carduri.txt", "r");
    if (!f) {
        printf("Fisierul nu a putut fi deschis.\n");
        *n = 0;
        return;
    }

    *n = 0;
    while (fscanf(f, "%s %s %s", carduri[*n].numarCard, carduri[*n].numePosesor,
                  carduri[*n].dataExpirare) == 3) {
        (*n)++;
    }
    fclose(f);
}

void salveazaInFisier(Card carduri[], int n) {
    FILE* f = fopen("carduri.txt", "w");
    if (!f) {
        printf("Eroare la scrierea in fisier.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s %s %s\n", carduri[i].numarCard, carduri[i].numePosesor,
                carduri[i].dataExpirare);
    }

    fclose(f);
}

void adaugaCard(Card carduri[], int* n) {
    if (*n >= MAX) {
        printf("Nu se mai pot adauga carduri!\n");
        return;
    }

    printf("Introduceti numarul cardului (ex: 53545676********): ");
    scanf("%s", carduri[*n].numarCard);

    printf("Introduceti numele posesorului (fara spatii): ");
    scanf("%s", carduri[*n].numePosesor);

    printf("Introduceti data expirarii (ex: 12/25): ");
    scanf("%s", carduri[*n].dataExpirare);

    (*n)++;
    salveazaInFisier(carduri, *n);
    printf("Card adaugat cu succes!\n");
}

void afiseazaCarduri(Card carduri[], int n) {
    if (n == 0) {
        printf("Nu exista carduri in portofel.\n");
        return;
    }


    printf("Carduri:\n");
    for (int i = 0; i < n; i++) {
        printf("Numar: \033[1;31m %s \033[0m, Nume: \033[1;36m %s \033[0m, Expirare: %s\n",
               carduri[i].numarCard, carduri[i].numePosesor,
               carduri[i].dataExpirare);
    }
}

void stergeCard(Card carduri[], int* n) {
    char numar[20];
    printf("Introduceti numarul cardului de sters: ");
    scanf("%s", numar);

    int gasit = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(carduri[i].numarCard, numar) == 0) {
            for (int j = i; j < *n - 1; j++) {
                carduri[j] = carduri[j + 1];
            }
            (*n)--;
            salveazaInFisier(carduri, *n);
            printf("Card sters cu succes.\n");
            gasit = 1;
            break;
        }
    }

    if (!gasit)
        printf("Cardul nu a fost gasit.\n");
}

void meniu() {
    Card carduri[MAX];
    int n = 0;
    citesteDinFisier(carduri, &n);

    int optiune;
    do {
        printf("\n=== Meniu Wallet Electronic ===\n");
        printf("1. Adauga card\n");
        printf("2. Vizualizeaza carduri\n");
        printf("3. Sterge card\n");
        printf("4. Iesire\n");
        printf("Alege optiunea: ");
        scanf("%d", &optiune);

        switch (optiune) {
            case 1:
                adaugaCard(carduri, &n);
                break;
            case 2:
                afiseazaCarduri(carduri, n);
                break;
            case 3:
                stergeCard(carduri, &n);
                break;
            case 4:
                printf("Program incheiat.\n");
                break;
            default:
                printf("Optiune invalida.\n");
        }
    } while (optiune != 4);
}

int main() {
    meniu();
    return 0;
}

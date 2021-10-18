#include "navegador.h"

struct strings {
    int total;
    char **arrayStrings;
    int pag;
    int indice;
};

struct pagina {
    int total;
    char **arrayStrings;
    int indice;
};

char *getLine(Pagina d) {
    int i;
    char *line = NULL;
    if (d->indice < d->total) {
        i = d->indice;
        line = strdup(d->arrayStrings[i]);
        d->indice++;
    }
    return line;
}

#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))
#define N_YELLOW(s) COLOR_BOLD_YELLOW s COLOR_ANSI_RESET

#define DISPLAY_NAVEGADOR_HELPER()                                                                                                                                                                                                                             \
    puts(                                                                                                                                                                                                                                                      \
        " ╔════════════════╦═════════════╦═════════════════════╦═════════════"                                           \
        "════════════════╦══════════════════════════╦══════════╗ ");                                                                                                                                                                                           \
    puts(" ║ [" N_YELLOW("1") "] Retroceder ║ [" N_YELLOW("2") "] Avançar ║ [" N_YELLOW("3") "] Escolher página ║ [" N_YELLOW("4") "] Voltar à Página Inicial ║ [" N_YELLOW("5") "] Ir até última página ║ [" N_YELLOW("0") "] Sair ║ "); \
    puts(                                                                                                                                                                                                                                                      \
        " ╚════════════════╩═════════════╩═════════════════════╩═════════════"                                           \
        "════════════════╩══════════════════════════╩══════════╝ ");                                                                                                                                                                                           \
    putchar('\n');

void displayStructureArrayHelper() {
    puts(
        " ╔════════════════╦═════════════╦═════════════════════╦═════════════"
        "════════════════╦══════════════════════════╦══════════╗ ");
    puts(" ║ [" N_YELLOW("1") "] Retroceder ║ [" N_YELLOW("2") "] Avançar ║ [" N_YELLOW("3") "] Escolher página ║ [" N_YELLOW("4") "] Voltar à Página Inicial ║ [" N_YELLOW("5") "] Ir até última página ║ [" N_YELLOW("0") "] Sair ║ ");
    puts(
        " ╚════════════════╩═════════════╩═════════════════════╩═════════════"
        "════════════════╩══════════════════════════╩══════════╝ ");
    puts(
        " ╔════════════════╦════════════════╦════════════════╦═════════════════"
        "════════╗");
    puts(" ║ [" N_YELLOW("6") "] Filial 1   ║  [" N_YELLOW("7") "] Filial 2  ║  [" N_YELLOW("8") "] Filial 3  ║  [" N_YELLOW("9") "] Resultados totais  ║");
    puts(
        " ╚════════════════╩════════════════╩════════════════╩═════════════════"
        "════════╝");
    putchar('\n');
}

ListaStrings createStrings(int total, char **strings) {
    int i;
    ListaStrings new = malloc(sizeof(struct strings));
    if (new == NULL) {
        return NULL;
    } else {
        new->arrayStrings = malloc(total * sizeof(char *));
        for (i = 0; i < total; i++) new->arrayStrings[i] = strdup(strings[i]);
        new->total = total;
    }
    new->pag = 1;
    new->indice = 0;
    return new;
}

Pagina getPage(ListaStrings strs) {
    int i, j, end;
    Pagina pag = malloc(sizeof(struct pagina));
    if (pag == NULL) return NULL;
    i = strs->indice;
    if (i + STRPPAG >= strs->total) {
        pag->arrayStrings = malloc((strs->total - i) * sizeof(char *));
        end = strs->total;
    } else {
        pag->arrayStrings = malloc(STRPPAG * sizeof(char *));
        end = i + STRPPAG;
    }
    // if cenas
    j = 0;
    while (i < end) {
        pag->arrayStrings[j++] = strdup(strs->arrayStrings[i++]);
    }
    pag->indice = 0;
    pag->total = j;
    return pag;
}

int getPageNumber(ListaStrings strs) { return strs->pag; }

int getTotal(ListaStrings strs) { return strs->total; }

int getPagesTotalNumber(ListaStrings strs) {
    int total = strs->total;
    int resto = total % STRPPAG;
    total = (total / STRPPAG) + ((resto != 0) ? 1 : 0);
    return total;
}

void proxPage(ListaStrings strs) {
    int i = strs->indice;
    int total = strs->total;
    if (i + STRPPAG < total) {
        strs->indice += STRPPAG;
        strs->pag++;
    }
}

void prevPage(ListaStrings strs) {
    int i = strs->indice;
    if (i >= STRPPAG) {
        strs->indice -= STRPPAG;
        strs->pag--;
    }
}

void goPage(int page, ListaStrings strs) {
    int dif;
    if (page >= 1 && page <= getPagesTotalNumber(strs)) {
        dif = abs(strs->pag - page);
        if (page < strs->pag) {
            strs->indice -= dif * STRPPAG;
        } else {
            strs->indice += dif * STRPPAG;
        }
        strs->pag = page;
    }
}

void fstPage(ListaStrings strs) {
    strs->pag = 1;
    strs->indice = 0;
}

void lastPage(ListaStrings strs) {
    int last = getPagesTotalNumber(strs);
    goPage(last, strs);
}

void display_pagina(Pagina d, char *cabecalho) {
    char *linha;
    int cmpc = strlen(cabecalho) + 2;

    printf("\n ╔");
    for (int i = 0; i < cmpc; i++) printf("═");
    printf("╗\n");
    printf(" ║ " COLOR_BOLD_BLUE "%s" COLOR_ANSI_RESET " ║\n", cabecalho);

    while ((linha = getLine(d))) {
        int cmpl = strlen(linha);
        printf(" ║");
        for (int i = 0; i < (cmpc - cmpl) / 2; i++) printf(" ");
        printf("%s", linha);
        for (int i = 0; i < (cmpc - cmpl) / 2; i++) printf(" ");
        printf("║");
        free(linha);
        printf("\n");
    }

    printf(" ╚");
    for (int i = 0; i < cmpc; i++) printf("═");
    printf("╝\n");
}

void displayStructure(ArrayList l, char *cabecalho) {
    ListaStrings diccionary = createStrings((int)l->size, (char **)l->body);
    Pagina printer;
    int i = 1000;
    int totalPages = getPagesTotalNumber(diccionary);

    while (i) {
        switch (i) {
            case 0:
                break;
            case 1:
                prevPage(diccionary);
                break;
            case 2:
                proxPage(diccionary);
                break;
            case 3:
                printf("\n");
                printf(
                    COLOR_ANSI_RED
                    "Qual a página que pretende consultar? " COLOR_ANSI_RESET);
                scanf(" %d", &i);
                CLEAN_STDIN();
                goPage(i, diccionary);
                break;
            case 4:
                fstPage(diccionary);
                break;
            case 5:
                lastPage(diccionary);
                break;
        }

        printer = getPage(diccionary);
        system("clear");
        display_pagina(printer, cabecalho);
        printf("\n");
        DISPLAY_NAVEGADOR_HELPER();
        printf("Nº de entradas: %d\n", arraylist_size(l));
        printf("\n");
        printf("Página %d / %d\n", getPageNumber(diccionary), totalPages);
        printf("\n");
        printf(COLOR_ANSI_RED "QUE AÇÃO PRETENDE REALIZAR?  " COLOR_ANSI_RESET);
        scanf(" %d", &i);
        CLEAN_STDIN();
    }
}

void displayStructureArray(ArrayList *l, int size) {
    int current = 0;
    int totalPages[size];
    ListaStrings *diccionary = malloc(sizeof(ListaStrings) * size);
    for (int i = 0; i < size; i++) {
        diccionary[i] = createStrings((int)l[i]->size, (char **)l[i]->body);
        totalPages[i] = getPagesTotalNumber(diccionary[i]);
    }
    Pagina printer;
    int i = 1000;
    while (i) {
        switch (i) {
            case 0:
                break;
            case 1:
                prevPage(diccionary[current]);
                break;
            case 2:
                proxPage(diccionary[current]);
                break;
            case 3:
                printf("\n");
                printf(
                    COLOR_ANSI_RED
                    "Qual a página que pretende consultar? " COLOR_ANSI_RESET);
                scanf("%d", &i);
                goPage(i, diccionary[current]);
                break;
            case 4:
                fstPage(diccionary[current]);
                break;
            case 5:
                lastPage(diccionary[current]);
                break;
            case 6:
                current = 0;
                break;
            case 7:
                current = 1;
                break;
            case 8:
                current = 2;
                break;
            case 9:
                current = 3;
                break;
        }
        printer = getPage(diccionary[current]);
        system("clear");
        display_pagina(printer, "Produtos (Sem Compras)");
        printf("\n");
        displayStructureArrayHelper();
        printf("Nº de entradas: %d\n", arraylist_size(l[current]));
        printf("\n");
        printf("Página %d / %d\n", getPageNumber(diccionary[current]),
               totalPages[current]);
        printf("\n");
        printf(COLOR_ANSI_RED "QUE AÇÃO PRETENDE REALIZAR?  " COLOR_ANSI_RESET);
        scanf(" %d", &i);
        CLEAN_STDIN();
    }
}
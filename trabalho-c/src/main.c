#include "main.h"

int main(int argc, char **argv) {
    Bool FICHEIROS_LIDOS = false;

    clock_t begin, end;
    double cpu_time_used;

    int state;

    SGV sgv = NULL;

    show_logo();

    do {
        state = menuOptions(&sgv, &FICHEIROS_LIDOS);
        if (state == INVALID) {
            PRINT_ERROR("Opção inválida!");
            PRESS_ENTER_TO_CONTINUE();
        }
    } while (state != EXIT);

    begin = clock();
    if (FICHEIROS_LIDOS == true) {
        freeSGV(sgv);
    }
    end = clock();

    cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
    printf("TEMPO FREE: %f\n\n", cpu_time_used);

    return 0;
}

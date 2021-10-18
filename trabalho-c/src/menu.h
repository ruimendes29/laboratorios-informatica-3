#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include "arraylist.h"
#include "boolean.h"
#include "colors.h"
#include "defines.h"
#include "navegador.h"
#include "queries.h"
#include "sgv.h"

#define EXIT 0
#define INVALID 99

#define CLEAN_STDIN() while (getchar() != '\n')

#define PRESS_ENTER_TO_CONTINUE()                                              \
    puts(COLOR_ANSI_BLUE "\nPRESS" COLOR_ANSI_YELLOW " ENTER " COLOR_ANSI_BLUE \
                         "TO CONTINUE\n\n" COLOR_ANSI_RESET);                  \
    if (getchar() != '\n') CLEAN_STDIN();

#define PRINT_ERROR(string)    \
    puts("\n\n" COLOR_BOLD_RED \
         "ERROR: " COLOR_ANSI_RED string COLOR_ANSI_RESET "\n\n")

void show_logo();

int menuOptions(SGV*, Bool*);

SGV querie1(SGV, Bool*);

void querie2();

void querie3();

void querie4();

void querie5(SGV, Bool);

void querie6();

void querie7(SGV sgv, Bool flidos);

void querie8(SGV, Bool);

void querie9(SGV, Bool);

void querie10(SGV, Bool);

void querie11(SGV sgv, Bool flidos);

void querie12(SGV, Bool);

#endif

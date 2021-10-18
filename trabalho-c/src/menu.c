#include "menu.h"

/* NUMERO DE OPÇÕES DE TAREFAS A PEDIR */
#define NTASKS 13

/* TEXTO A IMPRIMIR PARA O UTILIZADOR ESCOLHER UMA OPÇÃO */
static char *tasks[NTASKS] = {
    "Sair",
    "Ler ficheiros e inicializar estruturas",
    "Lista e número de produtos cujo nome começa por uma determinada letra",
    "Número de vendas e faturação de um produto, num determinado mês",
    "Lista ordenada de códigos de produto que ninguém comprou",
    "Lista ordenada de clientes que fizeram compras em todas as filiais",
    "Número de clientes registados que não fizeram compras e número de "
    "produtos que não foram vendidos",
    "Tabela para um cliente do número de produtos comprados por mês por filial",
    "Dado um intervalo de meses determinar o número total de vendas registadas "
    "nesse intervalo e o montante faturado",
    "Dado um código de produto e uma filial, determinar os códigos de cliente "
    "que o compraram distinguindo entre N e P",
    "Dado um código de cliente e um mês, determinar a lista de produtos que "
    "mais comprou por quantidade, por ordem decresecente",
    "Lista com os N produtos mais vendidos do ano, indicando o número total "
    "de clientes e unidades vendidas, filial a filial",
    "Dado um código de cliente determinar quais os códigos dos 3 produtos em "
    "que mais gastou dinheiro durante o ano",
};

Bool isMenuOptionValid(int opt) {
    return (opt >= 0 && opt < NTASKS) ? true : false;
}

void show_info(char *s) {
    printf("\n" COLOR_ANSI_GREEN "%s" COLOR_ANSI_RESET "\n\n", s);
}

void show_logo() {
    char buffer[70];
    FILE *fp;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    fp = fopen(".art/logo.ascii", "r");

    system("clear");

    if (fp != NULL) {
        puts(COLOR_BOLD_CYAN);
        while (fgets(buffer, 70, fp)) {
            for (int i = 0; i < (w.ws_col - 67) / 2; i++) printf(" ");
            printf("%s", buffer);
        }
        puts(COLOR_ANSI_RESET);
        fclose(fp);
    }

    printf("\n\n");
    for (int i = 0; i < (w.ws_col - 23) / 2; i++) printf(" ");
    puts(COLOR_ANSI_BLUE "PRESS" COLOR_ANSI_YELLOW " ENTER " COLOR_ANSI_BLUE
                         "TO CONTINUE\n" COLOR_ANSI_RESET);
    if (getchar() != '\n') CLEAN_STDIN();
}

static void show_list_options() {
    puts("\n");
    puts(COLOR_BOLD_YELLOW
         "PRESSIONE UM DOS NÚMEROS QUE ANTECEDEM AS OPÇÕES PARA "
         "SELECIONAR UMA TAREFA A EXECUTAR:" COLOR_ANSI_RESET);
    puts("\n");

    for (int i = 0; i < NTASKS; i++)
        printf(COLOR_BOLD_RED "%2d" COLOR_BOLD_MAGENTA " 🠪 " COLOR_ANSI_RESET
                              "%s" COLOR_ANSI_RESET "\n",
               i, tasks[i]);
}

static int get_int_option() {
    int opt = INVALID;

    puts("\n");
    printf(COLOR_BOLD_GREEN "Opção: " COLOR_ANSI_RESET);
    scanf(" %d", &opt);
    CLEAN_STDIN();
    puts("\n");

    if (isMenuOptionValid(opt) == true) {
        if (opt == EXIT) {
            show_info("Saindo...");
            return EXIT;
        } else {
            return opt;
        }
    }

    return INVALID;
}

ssize_t readln(int fildes, void *buf, ssize_t nbyte) {
    ssize_t size = 0;
    char c;
    char *buff = (char *)buf;
    while (size < nbyte && read(fildes, &c, 1) == 1) {
        buff[size++] = c;
        if (c == '\n') return size;
    }
    return size;
}

/* GREET USER */
int menuOptions(SGV *sgv, Bool *flidos) {
    int opt;
    system("clear");
    show_list_options();
    opt = get_int_option();

    switch (opt) {
        case 0:
            return EXIT;
            break;
        case 1:
            *sgv = querie1(*sgv, flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 2:
            querie2(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 3:
            querie3(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 4:
            querie4(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 5:
            querie5(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 6:
            querie6(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 7:
            querie7(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 8:
            querie8(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 9:
            querie9(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 10:
            querie10(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 11:
            querie11(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        case 12:
            querie12(*sgv, *flidos);
            PRESS_ENTER_TO_CONTINUE();
            system("clear");
            break;
        default:
            break;
    }

    return opt;
}

SGV querie1(SGV sgv, Bool *flidos) {
    clock_t begin, end;
    double cpu_time_used;
    char ficheiros[3][MAX_BUFFER];
    FILE *fp = NULL;
    char *tmp = malloc(sizeof(char) * MAX_BUFFER);
    Bool fvalido = false;
    strcpy(ficheiros[0], DEFAULT_CLIENTES_PATH);
    strcpy(ficheiros[1], DEFAULT_PRODUTOS_PATH);
    strcpy(ficheiros[2], DEFAUL_VENDAS_PATH);

    if (*flidos == true) {
        show_info("A libertar memória préviamente alocada...");
        begin = clock();
        freeSGV(sgv);
        end = clock();
        show_info("Memória desalocada com sucesso em:");
        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("%f segundos\n\n", cpu_time_used);
    }

    sgv = initSGV();

    for (int i = 0; i < 3; i++) {
        do {
            switch (i) {
                case 0:
                    printf("Ficheiro de Clientes (ENTER para default): ");
                    break;
                case 1:
                    printf("Ficheiro de Produtos (ENTER para default): ");
                    break;
                case 2:
                    printf("Ficheiro de Vendas (ENTER para default): ");
                    break;
            }

            fgets(tmp, MAX_BUFFER, stdin);

            if (tmp[0] == '\n') {
                fvalido = true;
            } else {
                tmp = strtok(tmp, "\n");
                fp = fopen(tmp, "r");
                if (fp != NULL) {
                    fvalido = true;
                    fclose(fp);
                    strcpy(ficheiros[i], tmp);
                }
            }

        } while (fvalido == false);

        fvalido = false;
    }

    show_info("A construir as estruturas...");

    begin = clock();
    sgv = answerQuery1(sgv, ficheiros[0], ficheiros[1], ficheiros[2]);
    end = clock();

    cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
    printf("TEMPO QUERY 1: %f segundos\n\n", cpu_time_used);

    *flidos = true;
    free(tmp);

    return sgv;
}

void querie2(SGV sgv, Bool flidos) {
    ArrayList resultado;
    clock_t begin, end;
    double cpu_time_used;
    char c;
    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        do {
            printf("Letra pela qual começam os código de produto: ");
            scanf("%c", &c);
            CLEAN_STDIN();
        } while (!isalpha(c));

        begin = clock();
        resultado = getListProdutosByChar(getProdutos(sgv), c);
        end = clock();

        displayStructure(resultado, "Produtos");
        arraylist_destroy(resultado);

        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("TEMPO QUERY 2: %f segundos\n\n", cpu_time_used);
    }
}

void showQuery3ByFilial(FacProd *arg) {
    for (int i = 0; i < NUM_FILIAIS; i++) {
        printf("\nFILIAL %d: \n", i + 1);
        printf(COLOR_ANSI_GREEN
               "Número total de registos de venda: " COLOR_ANSI_RESET "%d\n",
               getRegistosVendaN(arg[i]) + getRegistosVendaP(arg[i]));
        printf(COLOR_ANSI_GREEN
               "Número total de registos de venda em modo N: " COLOR_ANSI_RESET
               "%d\n",
               getRegistosVendaN(arg[i]));
        printf(COLOR_ANSI_GREEN
               "Número total de registos de venda em modo P: " COLOR_ANSI_RESET
               "%d\n",
               getRegistosVendaP(arg[i]));
        printf(COLOR_ANSI_GREEN
               "O total faturado em modo N é: " COLOR_ANSI_RESET "%.2f\n",
               (float)getFacturacaoNFromProd(arg[i]));
        printf(COLOR_ANSI_GREEN
               "O total faturado em modo P é: " COLOR_ANSI_RESET "%.2f\n",
               (float)getFacturacaoPFromProd(arg[i]));
        printf(COLOR_ANSI_GREEN "O total faturado é: " COLOR_ANSI_RESET
                                "%.2f\n\n",
               (float)getFacturacaoNFromProd(arg[i]) +
                   getFacturacaoPFromProd(arg[i]));
    }
    printf("\n");
    printf(COLOR_ANSI_BLUE
           "   "
           "╔══════════════════════════════════════════════════════════════════"
           "══════════════╗\n");
    printf(
        "   ║    Prima a tecla '1' se pretender ver os resultados na sua forma "
        "condensada    ║\n");
    printf(
        "   "
        "╚═════════════════════════════════════════════════════════════════════"
        "═══════════╝" COLOR_ANSI_RESET "\n");
    printf(COLOR_ANSI_BLUE
           "   "
           "╔══════════════════════════════════════════════════════════════════"
           "══════════════╗\n");
    printf(
        "   ║                        Prima a tecla '0' para sair               "
        "              ║\n");
    printf(
        "   "
        "╚═════════════════════════════════════════════════════════════════════"
        "═══════════╝" COLOR_ANSI_RESET "\n");
}

void querie3(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    FacProd *resultado;
    Produto checker = NULL;
    int valido;
    Bool existe;
    char *tmp = malloc(sizeof(char) * MAX_BUFFER);
    int mes, scan = 0, totalRegistos, registosVendaN, registosVendaP,
             faturacaoN, faturacaoP, faturacao;
    totalRegistos = registosVendaN = registosVendaP = faturacaoN = faturacaoP =
        faturacao = 0;
    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, for favor!");
        PRESS_ENTER_TO_CONTINUE();
    } else {
        do {
            printf("Código de produto: ");
            fgets(tmp, MAX_BUFFER, stdin);
            if (tmp[0] == '\n') {
                valido = 0;
                existe = false;
                printf(COLOR_ANSI_RED "\nInput inválido!\n\n" COLOR_ANSI_RESET);
            } else {
                tmp = strtok(tmp, "\n");
                valido = isProductCodeValid(tmp);
                if (!valido) {
                    existe = false;
                    printf(COLOR_ANSI_RED
                           "\nPor favor introduza um código de produto "
                           "válido!\n\n" COLOR_ANSI_RESET);
                } else {
                    checker = criaProduto(tmp);
                    existe = existeProduto(getProdutos(sgv), checker);
                    if (existe == false)
                        printf(COLOR_ANSI_RED
                               "\nO produto introduzido não consta do catalogo "
                               "de produtos!\n\n" COLOR_ANSI_RESET);
                }
            }
        } while (!isalpha(tmp[0]) || !valido || existe == false);

        do {
            printf("Mês: ");
            scanf("%d", &mes);
            CLEAN_STDIN();
        } while (mes < 1 || mes > 12);

        begin = clock();
        resultado = answerQuery3(sgv, tmp, mes);
        end = clock();

        do {
            if (!scan)
                showQuery3ByFilial(resultado);
            else {
                for (int i = 0; i < NUM_FILIAIS; i++) {
                    registosVendaN += getRegistosVendaN(resultado[i]);
                    registosVendaP += getRegistosVendaP(resultado[i]);
                    faturacaoN += getFacturacaoNFromProd(resultado[i]);
                    faturacaoP += getFacturacaoPFromProd(resultado[i]);
                }
                totalRegistos = registosVendaN + registosVendaP;
                faturacao = faturacaoN + faturacaoP;
                printf("\nTOTAL (DADOS CONDENSADOS): \n");
                printf(COLOR_ANSI_GREEN
                       "Número total de registos de venda: " COLOR_ANSI_RESET
                       "%d\n",
                       totalRegistos);
                printf(COLOR_ANSI_GREEN
                       "Número total de registos de venda em modo "
                       "N: " COLOR_ANSI_RESET "%d\n",
                       registosVendaN);
                printf(COLOR_ANSI_GREEN
                       "Número total de registos de venda em modo "
                       "P: " COLOR_ANSI_RESET "%d\n",
                       registosVendaP);
                printf(COLOR_ANSI_GREEN
                       "O total faturado em modo N é: " COLOR_ANSI_RESET
                       "%.2f\n",
                       (float)faturacaoN);
                printf(COLOR_ANSI_GREEN
                       "O total faturado em modo P é: " COLOR_ANSI_RESET
                       "%.2f\n",
                       (float)faturacaoP);
                printf(COLOR_ANSI_GREEN "O total faturado é: " COLOR_ANSI_RESET
                                        "%.2f\n\n",
                       (float)faturacao);
            }
            scanf("%d", &scan);
            CLEAN_STDIN();
        } while (scan);

        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTEMPO QUERY 3: %f segundos\n\n", cpu_time_used);

        free(tmp);
        for (int i = 0; i < NUM_FILIAIS; i++) freeFacProd(resultado[i]);
        free(resultado);
    }
}

void querie4(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    ArrayList *resultado = malloc(sizeof(ArrayList) * NUM_FILIAIS + 1);

    if (flidos == false) {
        PRINT_ERROR("Falta ler ficheiros!");
        PRESS_ENTER_TO_CONTINUE();
    } else {
        begin = clock();
        resultado = answerQuery4(sgv);
        end = clock();

        displayStructureArray(resultado, NUM_FILIAIS + 1);

        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTEMPO QUERY 4: %f segundos\n\n", cpu_time_used);
    }

    for (int i = 0; i < NUM_FILIAIS + 1; i++) arraylist_destroy(resultado[i]);
    free(resultado);
}

void querie5(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    ArrayList resultado = NULL;

    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
        PRESS_ENTER_TO_CONTINUE();
    } else {
        begin = clock();
        resultado = getListClientesUsadosTodasFiliais(getClientes(sgv));
        end = clock();

        displayStructure(resultado, "Cliente");

        arraylist_destroy(resultado);

        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTEMPO QUERY 5: %f segundos\n\n", cpu_time_used);
    }
}

void querie6(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        begin = clock();
        int nclientes = getCatClientesNaoUsados(getClientes(sgv));
        int nprodutos = getCatProdsNaoUsados(getProdutos(sgv));
        end = clock();

        printf("Número de Clientes sem compras: %d\n", nclientes);
        printf("Número de Produtos não comprados: %d\n\n", nprodutos);

        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTEMPO QUERY 6: %f segundos\n\n", cpu_time_used);
    }
}

void querie7(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    ArrayList resultado = NULL;
    Cliente c = NULL;
    char *codigo = malloc(sizeof(char) * MAX_BUFFER);

    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        do {
            printf("Código do Cliente: ");
            scanf(" %s", codigo);
            CLEAN_STDIN();
            putchar('\n');
        } while (isClientCodeValid(codigo) == 0);

        c = criaCliente(codigo);

        if (existeCliente(getClientes(sgv), c) == false) {
            PRINT_ERROR("Cliente não existe no Catálogo!");
        } else {
            begin = clock();
            resultado = answerQuery7(getFiliais(sgv), c);
            end = clock();

            displayStructure(resultado, "Mes   Filial 1   Filial 2   Filial 3");

            arraylist_destroy(resultado);

            cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
            printf("\nTEMPO QUERY 7: %f segundos\n\n", cpu_time_used);
        }
    }

    free(codigo);
}

void querie8(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    int quantidade = 0;
    double facturacao = 0.f;

    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        int mesI = 0, mesF = 0;

        do {
            printf("Mês Inicial: ");
            scanf(" %d", &mesI);
            CLEAN_STDIN();
            putchar('\n');
        } while (mesI < 1 || mesI > 12);

        do {
            printf("Mês Final: ");
            scanf(" %d", &mesF);
            CLEAN_STDIN();
            putchar('\n');
        } while (mesF < 1 || mesF > 12);

        begin = clock();
        quantidade = answerQuery8(sgv, &facturacao, mesI, mesF);
        end = clock();

        printf("Número total de registos de venda : %d\n", quantidade);
        printf("\nTotal facturado: %f\n", facturacao);

        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTEMPO QUERY 8: %f segundos\n\n", cpu_time_used);
    }
}

void querie9(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    ArrayList *resultado = NULL;
    Produto p = NULL;
    char *codigo = malloc(sizeof(char) * MAX_BUFFER);
    int filial = 0;
    char op = '\0';
    int i = 0;

    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        do {
            printf("Código do Produto: ");
            scanf(" %s", codigo);
            CLEAN_STDIN();
            putchar('\n');
        } while (isProductCodeValid(codigo) == 0);

        p = criaProduto(codigo);

        if (existeProduto(getProdutos(sgv), p) == false) {
            PRINT_ERROR("Cliente não existe no Catálogo!");
        } else {
            do {
                printf("Filial a consultar: ");
                scanf(" %d", &filial);
                CLEAN_STDIN();
                putchar('\n');
            } while (filial < 1 || filial > NUM_FILIAIS);

            begin = clock();
            resultado = answerQuery9(p, getFiliais(sgv)[filial - 1]);
            end = clock();

            do {
                printf(
                    "Pretende consultar as compras realizadas em modo N ou P? "
                    ": ");
                scanf(" %c", &op);
                CLEAN_STDIN();
                putchar('\n');
            } while (op != 'N' && op != 'P');

            i = (op == 'N') ? 0 : 1;
            displayStructure(resultado[i], "Cliente N");

            arraylist_destroy(resultado[0]);
            arraylist_destroy(resultado[1]);
            free(resultado);

            cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
            printf("\nTEMPO QUERY 9: %f segundos\n\n", cpu_time_used);
        }
    }

    free(codigo);
}

void querie10(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    ArrayList resultado = NULL;
    Cliente c = NULL;
    int mes = 0;
    char *codigo = malloc(sizeof(char) * MAX_BUFFER);

    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        do {
            printf("Código do Cliente: ");
            scanf(" %s", codigo);
            CLEAN_STDIN();
            putchar('\n');
        } while (isClientCodeValid(codigo) == 0);

        c = criaCliente(codigo);

        if (existeCliente(getClientes(sgv), c) == false) {
            PRINT_ERROR("Cliente não existe no Catálogo!");
        } else {
            do {
                printf("Mês a consultar: ");
                scanf(" %d", &mes);
                CLEAN_STDIN();
                putchar('\n');
            } while (mes < 1 || mes > 12);

            begin = clock();
            resultado = answerQuery10(sgv, c, mes);
            end = clock();

            displayStructure(resultado, "Produto   Quantidade");

            arraylist_destroy(resultado);

            cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
            printf("\nTEMPO QUERY 10: %f segundos\n\n", cpu_time_used);
        }
    }

    free(codigo);
}

void querie11(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    ArrayList *resultado = malloc(sizeof(ArrayList) * NUM_FILIAIS);
    int n = 0, nfilial = 1;

    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        do {
            printf("Quantos produtos: ");
            scanf(" %d", &n);
            CLEAN_STDIN();
            putchar('\n');
        } while (n <= 0);

        begin = clock();
        resultado = answerQuery11(sgv, n);
        end = clock();

        while (nfilial != 0) {
            do {
                printf("\nEscolha uma filial (ou escreva zero para sair): ");
                scanf(" %d", &nfilial);
                CLEAN_STDIN();
                putchar('\n');
            } while (nfilial < 0 || nfilial > 3);

            if (nfilial != 0) {
                displayStructure(
                    resultado[nfilial - 1],
                    " Produto    Unidades Vendidas    Clientes Envolvidos");
            }
        }

        for (int j = 0; j < NUM_FILIAIS; j++) arraylist_destroy(resultado[j]);
        free(resultado);

        cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
        printf("\nTEMPO QUERY 11: %f segundos\n\n", cpu_time_used);
    }
}

void querie12(SGV sgv, Bool flidos) {
    clock_t begin, end;
    double cpu_time_used;
    char *codigo = malloc(sizeof(char) * MAX_BUFFER);

    if (flidos == false) {
        PRINT_ERROR("Carregue estruturas, por favor!");
    } else {
        do {
            printf("Código do Cliente: ");
            fgets(codigo, MAX_BUFFER, stdin);
            codigo = strtok(codigo, "\n");
            putchar('\n');
        } while (isClientCodeValid(codigo) == 0);

        Cliente c = criaCliente(codigo);

        if (existeCliente(getClientes(sgv), c) == false) {
            PRINT_ERROR("Cliente não existe no Catálogo!");
        } else {
            begin = clock();
            ArrayList resultado = answerQuery12(sgv, c);
            end = clock();

            displayStructure(resultado, "Produtos    Facturacao");

            arraylist_destroy(resultado);

            cpu_time_used = (float)(end - begin) / CLOCKS_PER_SEC;
            printf("\nTEMPO QUERY 12: %f segundos\n\n", cpu_time_used);
        }
    }

    free(codigo);
}

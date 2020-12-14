#include <ncurses.h>
#define LINE_START 1
#define SCAN_LINE 14
#define SCAN_COL 30

#include "header.h"

WINDOW *logs;
WINDOW *menu;

int option = -1;

void init_menu() {
    initscr();

    logs = newwin(8, 1500, 0, 0);
    menu = newwin(16, 1500, 10, 0);
}

void *display_logs(void *arg) {
    sleep(1);

    while (option != 0) {
        wclear(logs);
        mvwprintw(logs, LINE_START, 0, "------------CLIENTES-------------------");

        struct Client *client = head;
        if (client == NULL)
            mvwprintw(logs, LINE_START + 2, 12, "SEM CLIENTES!!!");

        int col_position = 0;
        while (client != NULL) {
            mvwprintw(logs, LINE_START + 1, col_position, "|-----------------------");
            mvwprintw(logs, LINE_START + 2, col_position, "| %s", client->room, client);
            mvwprintw(logs, LINE_START + 3, col_position, "| %s: %d", client->input, client->input_value);
            mvwprintw(logs, LINE_START + 4, col_position, "| %s: %d", client->output, client->output_value);
            mvwprintw(logs, LINE_START + 5, col_position, "| Temp: %d", client->temperature);
            mvwprintw(logs, LINE_START + 6, col_position, "| Hum: %d", client->humidity);

            col_position += 26;
            client = client->next;
        }
        mvwprintw(logs, LINE_START + 7, 0, "--------------------------------------");
        wrefresh(logs);

        sleep(1);
    }

    return NULL;
}

void *read_menu(void *arg) {
    int value;
    char posfix_code[3];
    char *code = malloc(4);

    while (option != 0) {
        wclear(menu);
        mvwprintw(menu, LINE_START, 0, "-----------------MENU----------------\n");

        if (new_client == NULL) {
            mvwprintw(menu, LINE_START + 1, 0, "Para ligar um dispostivo digite 1 + código do dispositivo.\n");
            mvwprintw(menu, LINE_START + 2, 0, "Para desligar um dispostivo digite 1 + código do dispositivo.\n");
            mvwprintw(menu, LINE_START + 3, 0, "Para sair digite 0.\n");
            mvwprintw(menu, LINE_START + 4, 0, "Ex: Para ligar (3)Comodo-Entrada digite 13.");

            struct Client *client = head;
            int line = LINE_START + 6;
            int i = 0;
            while (client != NULL) {
                mvwprintw(menu, line, 0, "(%d)%s-%s", i, client->room, client->input);
                i++;
                line++;
                client = client->next;
            }

            mvwprintw(menu, line, 0, "-------------------------------------\n");
            mvwprintw(menu, SCAN_LINE, 0, "Escolha a opção: ");
            wrefresh(menu);

            mvwscanw(menu, SCAN_LINE, SCAN_COL, "%d", &option);
            wclear(menu);

            sprintf(code, "%d", option);
            add_to_csv(code);
        } else {
            char room[50], input_name[50], output_name[50];
            mvwprintw(menu, LINE_START + 1, 0, "NOVO DISPOSITIVO AGUARDANDO CONFIGURACAO.\n");
            
            mvwprintw(menu, LINE_START + 2, 0, "Digite o nome do comodo: \n");
            wrefresh(menu);
            mvwscanw(menu, LINE_START + 2, 100, "%s", room);

            mvwprintw(menu, LINE_START + 3, 0, "Digite o nome do dispositivo de entrada: \n");
            wrefresh(menu);
            mvwscanw(menu, LINE_START + 3, 100, "%s", input_name);

            mvwprintw(menu, LINE_START + 4, 0, "Digite o nome do dispositivo de saida: \n");
            wrefresh(menu);
            mvwscanw(menu, LINE_START + 4, 100, "%s", output_name);
            
            config_client(room, input_name, output_name);

            sprintf(code, "Configurou cliente");
            add_to_csv(code);
     
        }

        sleep(1);
    }

    return NULL;
}

void shut_down_menu() {
    endwin();
}
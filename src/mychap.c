/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** mychap
*/

#include "mychap.h"

chap_t  init_chap(char **av)
{
    chap_t chap;
    int i = 1;

    while (i < 7) {
        if (strcmp(av[i], "-t") == 0)
            chap.addr = av[++i];
        else if (strcmp(av[i], "-p") == 0)
            chap.port = atoi(av[++i]);
        else if (strcmp(av[i], "-P") == 0)
            chap.password = av[++i];
        else
            exit(84);
        i++;
    }
    return chap;
}

void    first_step(chap_t chap, client_t client)
{
    send_message("client hello", chap, client);
}

int my_chap(char **av)
{
    chap_t chap = init_chap(av);
    client_t client = create_socket(chap);
    
    first_step(chap, client);
    receive_challenge(chap, client);
    receive_secret(chap, client);
   
    close(client.fd);
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 7) {
        perror("-usage: ./client -t host -p port -P password");
        exit(84);
    } else if (ac == 2 && strcmp(av[1], "-h")) {
        printf("-usage: ./client -t host -p port -P password\n");
        exit(0);
    }
    return my_chap(av);
}
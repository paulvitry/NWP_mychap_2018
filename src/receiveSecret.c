/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** receiveSecret
*/

#include "mychap.h"

void    receive_secret(chap_t chap, client_t client)
{
    struct sockaddr_in dAddr = {0};
    char *msg;

    if ((msg = receive_message(chap, client, &dAddr)) == NULL) {
        perror ("fuck packet not received");
        exit(EXIT_FAILURE);
    }
    if (strcmp("KO", msg) == 0)
        printf("KO\n");
    else
        printf("Secret: '%s'\n", msg);
}
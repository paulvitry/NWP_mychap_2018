/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** createSocket
*/

#include "mychap.h"

void    init_address(struct sockaddr_in *addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(0);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
}

client_t create_socket(chap_t chap)
{
    client_t client;
    int opt = 1;
    unsigned int len = sizeof(client.addr);

    (void)chap;
    if ((client.fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0)
        exit (EXIT_FAILURE);
    if (setsockopt(client.fd, IPPROTO_IP, IP_HDRINCL, &opt,
                                                sizeof(opt)) < 0)
        exit(EXIT_FAILURE);
    init_address(&client.addr);
    if (bind(client.fd, (void *)&client.addr, sizeof(client.addr)) != 0) {
        close(client.fd);
        client.fd = -1;
    }
    getsockname(client.fd, (void *)&client.addr, &len);
    return client;
}

/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** send
*/

#include "mychap.h"

char    *create_buffer(Message_t message)
{
    char *buffer = malloc(4096);

    if (buffer == NULL)
        return NULL;
    memset(buffer, '\0', 4096);
    memcpy(buffer, &message.ipv4, sizeof(struct iphdr));
    buffer += sizeof(struct iphdr);
    memcpy(buffer, &message.udp, sizeof(struct udphdr));
    buffer += sizeof(struct udphdr);
    memcpy(buffer, message.message, strlen(message.message) * sizeof(char));
    buffer -= (sizeof(struct iphdr) + sizeof(struct udphdr));
    return buffer;
}

void set_binding_struct(struct sockaddr_in *binding, char *addr, int port)
{
    if (binding == NULL)
        return;
    memset(binding, 0, sizeof(*binding));
    if (addr == NULL || (strcmp(addr, "localhost") == 0))
        binding->sin_addr.s_addr = htonl(INADDR_ANY);
    else if ((strcmp(addr, "127.0.0.1") == 0))
        binding->sin_addr.s_addr = htonl(INADDR_ANY);
    else
        binding->sin_addr.s_addr = inet_addr(addr);
    binding->sin_port = htons(port);
    binding->sin_family = AF_INET;
}

void    send_message(char *msg, chap_t chap, client_t client)
{
    Message_t message;
    struct sockaddr_in server = {0};
    message = create_message(msg, chap, client);

    set_binding_struct(&server, chap.addr, chap.port);
    if ( inet_aton(chap.addr, (struct in_addr *)&server.sin_addr.s_addr) == 0 )
    {
        printf("No such hostname: '%s'\n", chap.addr);
        exit(EXIT_FAILURE);
    }
    if (sendto(client.fd, create_buffer(message), message.ipv4.tot_len, 0,
        (struct sockaddr *)&server, sizeof(server)) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
    }
}
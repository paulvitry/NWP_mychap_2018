/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** receiveChallenge
*/

#include "mychap.h"


bool check_ip(char *packet, char *addr)
{
    struct iphdr *ip = (void *)packet;

    if (ip == NULL || addr == NULL)
        return (false);
    return (inet_addr(addr) == ip->saddr);
}

bool check_udp_port(char *packet, unsigned int port)
{
    struct udphdr *udp = (void *)(packet + sizeof(struct iphdr));

    if (udp == NULL)
        return (false);
    return (port == ntohs(udp->source));
}

char    *receive_message(chap_t chap, client_t client, struct sockaddr_in *add)
{
    char buffer[4096] = {0};
    unsigned int len  = sizeof(struct sockaddr);
    ssize_t  count;
    ssize_t start = time(NULL);

    while (!check_ip(buffer, chap.addr)
            || !check_udp_port(buffer, chap.port)) {
        if ((time(NULL) - start) > 3)
            return (NULL);
        memset(buffer, 0, 4096);
        count = recvfrom(client.fd, (char *)buffer, 4096,
            MSG_WAITALL, (struct sockaddr *)add,
            &len);
    }
    if (count <= (ssize_t)(HEADERS_SIZE))
        return (NULL);
    buffer[count] = '\0';
    return (strdup(&buffer[HEADERS_SIZE]));
}

int     generate_sha_256(char *msg, unsigned int len, char *buf)
{
    SHA256_CTX sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    if (buf == NULL || msg == NULL) {
        fprintf(stderr, "generate_sha256(): Argument musn't be NULL\n");
        return (1);
    }
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, msg, len);
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(buf + (i * 2), "%02x", hash[i]);
    buf[64] = 0;
    return (0);
}

void    receive_challenge(chap_t chap, client_t client)
{
    struct sockaddr_in dAddr = {0};
    char buffer[SHA256_DIGEST_LENGTH * 2] = {0};
    char *msg;

    if ((msg = receive_message(chap, client, &dAddr)) == NULL) {
        perror ("fuck packet not received");
        exit(EXIT_FAILURE);
    }
    msg = strcat(msg, chap.password);
    if (msg == NULL || generate_sha_256(msg, strlen(msg), buffer))
        return;
    free(msg);
    sleep(1);
    send_message(buffer, chap, client);
}
/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** mychap
*/

#ifndef MYCHAP_H_
#define MYCHAP_H_

#define BUFFER_SIZE 1024

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h> 
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <sys/select.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <dirent.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <openssl/sha.h>
#include "UDP.h"
#include "IPV4.h"
#include <time.h>

#define HEADERS_SIZE sizeof(struct udphdr) + sizeof(struct iphdr)
// typedef struct udphdr UDP_t;
// typedef struct iphdr  IPV4_t;

typedef struct chap_s
{
    char    *addr;
    int     port;
    char    *password;
} chap_t;

typedef struct client_s
{
    int     fd;
    struct  sockaddr_in addr;
    int     port;
    char    ip[16]; 
} client_t;


typedef struct Message_s
{
    struct iphdr        ipv4;
    struct udphdr       udp;
    char        *message;
} Message_t;

client_t        create_socket(chap_t chap);

Message_t       create_message(char *str, chap_t chap, client_t client);

unsigned short  csum(unsigned short *buf, int nwords);

void    get_source(client_t *client);

bool    check_ip(char *packet, char *addr);

bool    check_udp_port(char *packet, unsigned int port);

char    *receive_message(chap_t chap, client_t client, struct sockaddr_in *add);

void    receive_challenge(chap_t chap, client_t client);

void    send_message(char *msg, chap_t chap, client_t client);

void    receive_secret(chap_t chap, client_t client);

char    *create_buffer(Message_t message);

void    set_binding_struct(struct sockaddr_in *binding, char *addr, int port);



#endif /* !MYCHAP_H_ */

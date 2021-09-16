/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** createMessage
*/

#include "mychap.h"

void    get_source(client_t *client)
{
    int len = sizeof(client->addr);
    char *ip = malloc(16);

    if (ip == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
	getsockname(client->fd, (struct sockaddr *) &client->addr,
                                            (socklen_t*)&len);
	inet_ntop(AF_INET, &client->addr.sin_addr, client->ip,
                                        sizeof(client->ip));
	client->port = ntohs(client->addr.sin_port);

}

unsigned short csum(unsigned short *buf, int nwords)
{
  unsigned long sum;

  for (sum=0; nwords>0; nwords--)
    sum += *buf++;
  sum = (sum >> 16) + (sum &0xffff);
  sum += (sum >> 16);
  return (unsigned short)(~sum);
}

struct iphdr      create_ipv4(char *dAddr, char *srcAddr, char *str)
{
    struct iphdr ip;

    ip.ihl = 5;
    ip.version = 4;
    ip.tos = 0;
    ip.tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + strlen(str);
    ip.id = htons(54321);
    ip.frag_off = 0;
    ip.ttl = 255;
    ip.protocol = 17;
    ip.saddr = inet_addr(srcAddr);
    ip.daddr = inet_addr(dAddr);
    ip.check = csum((void*)&ip, ip.tot_len);
    return ip;
}

struct udphdr       create_udp(char *str, int destPort, int srcPort)
{
    struct udphdr udp;

    udp.dest = htons(destPort);
    udp.source = htons(srcPort);
    udp.len =  htons(sizeof(struct udphdr) + strlen(str));
    udp.check = 0;
    return udp;
}

Message_t   create_message(char *str, chap_t chap, client_t client)
{
    Message_t  message;
    char *sAddr = inet_ntoa(client.addr.sin_addr);
    uint16_t fd = ntohs(client.fd);

    message.ipv4 = create_ipv4(chap.addr, sAddr, str);
    message.udp = create_udp(str, chap.port, fd);
    message.message = str;

    return message;
} 
/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** IPV4
*/

#ifndef IPV4_H_
#define IPV4_H_

typedef struct IPV4_s
{
    unsigned char       version;
    unsigned char       IHL;
    unsigned char       tos;
    unsigned short int  tot_len;
    unsigned short int  ident;
    unsigned char       flags;
    unsigned short int  offset;
    unsigned char       ttl;
    unsigned char       protocol;
    unsigned short int  chksum;
    unsigned int        sourceip;
    unsigned int        destip;
} IPV4_t;

#endif /* !IPV4_H_ */

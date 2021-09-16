/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** UDP
*/

#ifndef UDP_H_
#define UDP_H_

//UDP
typedef struct UDP_s
{
    unsigned short sourcePort;
    unsigned short destinationPort;
    unsigned short length;
    unsigned short checksum;
} UDP_t;

#endif /* !UDP_H_ */

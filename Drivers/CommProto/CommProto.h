/*
 * CommProto.h
 *
 *  Created on: 2014 kov. 29
 *      Author: Gra�vidas
 */

#ifndef COMMPROTO_H_
#define COMMPROTO_H_

#include <avr/io.h>

#define PKTLEN 10

void PROTO_RecvData(uint8_t *data, uint8_t len);

#endif /* COMMPROTO_H_ */

/*
 * CommProto.c
 *
 *  Created on: 2014 kov. 29
 *      Author: Gražvidas
 */

#include "CommProto.h"


void PROTO_RecvData(uint8_t *data, uint8_t len)
{
	// length of packet
	uint8_t pktLen = data[0];

	if (pktLen <= 1 || pktLen > PKTLEN)
		return;

	// decode packet
	// check address
	// decode cmd
	// use data
}


/*
 * CC1101.c
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#include "CC1101.h"

CC1101_Interface_t RF = {
		&Spi,
		CC_Init,
		CC_LoadConfig
};

CC1101_Config_t RFCfgDefault = {

};

void CC_Init()
{

}

void CC_LoadConfig(CC1101_Config_t *cfg, uint8_t *ok)
{

}

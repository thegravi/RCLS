/*
 * CC1101.h
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#ifndef CC1101_H_
#define CC1101_H_

#include "../SPI/SPI.h"

enum {
    CC_REG_IOCFG2,      //0x00
    CC_REG_IOCFG1,      //0x01
    CC_REG_IOCFG0,      //0x02
    CC_REG_FIFOTHR,     //0x03
    CC_REG_SYNC1,       //0x04
    CC_REG_SYNC0,       //0x05
    CC_REG_PKTLEN,      //0x06
    CC_REG_PKTCTRL1,    //0x07
    CC_REG_PKTCTRL0,    //0x08
    CC_REG_ADDR,        //0x09
    CC_REG_CHANNR,      //0x0A
    CC_REG_FSCTRL1,     //0x0B
    CC_REG_FSCTRL0,     //0x0C
    CC_REG_FREQ2,       //0x0D
    CC_REG_FREQ1,       //0x0E
    CC_REG_FREQ0,       //0x0F
    CC_REG_MDMCFG4,     //0x10
    CC_REG_MDMCFG3,     //0x11
    CC_REG_MDMCFG2,     //0x12
    CC_REG_MDMCFG1,     //0x13
    CC_REG_MDMCFG0,     //0x14
    CC_REG_DEVIATN,     //0x15
    CC_REG_MCSM2,       //0x16
    CC_REG_MCSM1,       //0x17
    CC_REG_MCSM0,       //0x18
    CC_REG_FOCCFG,      //0x19
    CC_REG_BSCFG,       //0x1A
    CC_REG_AGCRL2,      //0x1B
    CC_REG_AGCRL1,      //0x1C
    CC_REG_AGCRL0,      //0x1D
    CC_REG_WOREVT1,     //0x1E
    CC_REG_WOREVT0,     //0x1F
    CC_REG_WORCTRL,     //0x20
    CC_REG_FREND1,      //0x21
    CC_REG_FREND0,      //0x22
    CC_REG_FSCAL3,      //0x23
    CC_REG_FSCAL2,      //0x24
    CC_REG_FSCAL1,      //0x25
    CC_REG_FSCAL0,      //0x26
    CC_REG_RCCTRL1,     //0x27
    CC_REG_RCCTRL0,     //0x28

    CC_REG_CNT,

    //other commands
    CC_REG_FIFO = 0x3F
};

typedef struct {
	uint16_t data[CC_REG_CNT];

}CC1101_Config_t;
extern CC1101_Config_t RFCfgDefault;

typedef struct {
	SPI_Interface_t *spi;
	void (*init)(void);
	void (*loadConfig)(CC1101_Config_t *cfg, uint8_t *ok);

}CC1101_Interface_t;
extern CC1101_Interface_t RF;

void CC_Init(void);
void CC_LoadConfig(CC1101_Config_t *cfg, uint8_t *ok);

#endif /* CC1101_H_ */

/*
 * CC1101.h
 *
 *  Created on: 2014 vas. 17
 *      Author: Gražvidas
 */

#ifndef CC1101_H_
#define CC1101_H_

#include "../SPI/SPI.h"
#include "../../common.h"
#include <util/delay.h>
#include "../UART/uart.h"

#define CC_LOG	1

#define CC_PIN_SI			PB3
#define CC_PIN_SO			PB4
#define CC_PIN_CS			PB2
#define CC_PIN_SCK			PB5
#define CC_PIN_GDO0
#define CC_PIN_GDO1
#define CC_DDR				DDRB
#define CC_PORT				PORTB

//Define command strobes
#define CC_CMD_RESET        0x30
#define CC_CMD_FSTXON       0x31
#define CC_CMD_SXOFF        0x32
#define CC_CMD_SCAL     	0x33
#define CC_CMD_SRX      	0x34
#define CC_CMD_STX      	0x35
#define CC_CMD_SIDLE        0x36
#define CC_CMD_SWOR     	0x38
#define CC_CMD_SPWD     	0x39
#define CC_CMD_SFRX     	0x3A
#define CC_CMD_SFTX     	0x3B
#define CC_CMD_SWORRST      0x3C
#define CC_CMD_SNOP         0x3D

enum {
    CC_REG_IOCFG2=0,    // GDO2 Output Pin Configuration
    CC_REG_IOCFG1,      // GDO1 Output Pin Configuration
    CC_REG_IOCFG0,      // GDO0 Output Pin Configuration
    CC_REG_FIFOTHR,     // RX FIFO and TX FIFO Thresholds
    CC_REG_SYNC1,       // Sync Word, High Byte
    CC_REG_SYNC0,       // Sync Word, Low Byte
    CC_REG_PKTLEN,      // Packet Length
    CC_REG_PKTCTRL1,    // Packet Automation Control
    CC_REG_PKTCTRL0,    // Packet Automation Control
    CC_REG_ADDR,        // Device Address
    CC_REG_CHANNR,      // Channel Number
    CC_REG_FSCTRL1,     // Frequency Synthesizer Control
    CC_REG_FSCTRL0,     // Frequency Synthesizer Control
    CC_REG_FREQ2,       // Frequency Control Word, High Byte
    CC_REG_FREQ1,       // Frequency Control Word, Middle Byte
    CC_REG_FREQ0,        // Frequency Control Word, Low Byte
    CC_REG_MDMCFG4,     // Modem Configuration
    CC_REG_MDMCFG3,     // Modem Configuration
    CC_REG_MDMCFG2,     // Modem Configuration
    CC_REG_MDMCFG1,     // Modem Configuration
    CC_REG_MDMCFG0,     // Modem Configuration
    CC_REG_DEVIATN,     // Modem Deviation Setting
    CC_REG_MCSM2,       // Main Radio Control State Machine Configuration
    CC_REG_MCSM1,       // Main Radio Control State Machine Configuration
    CC_REG_MCSM0,       // Main Radio Control State Machine Configuration
    CC_REG_FOCCFG,      // Frequency Offset Compensation Configuration
    CC_REG_BSCFG,       // Bit Synchronization Configuration
    CC_REG_AGCRL2,      // AGC Control
    CC_REG_AGCRL1,      // AGC Control
    CC_REG_AGCRL0,      // AGC Control
    CC_REG_WOREVT1,     // High Byte Event0 Timeout
    CC_REG_WOREVT0,     // Low Byte Event0 Timeout
    CC_REG_WORCTRL,     // Wake On Radio Control
    CC_REG_FREND1,      // Front End RX Configuration
    CC_REG_FREND0,      // Front End TX Configuration
    CC_REG_FSCAL3,      // Frequency Synthesizer Calibration
    CC_REG_FSCAL2,      // Frequency Synthesizer Calibration
    CC_REG_FSCAL1,      // Frequency Synthesizer Calibration
    CC_REG_FSCAL0,      // Frequency Synthesizer Calibration
    CC_REG_RCCTRL1,     // RC Oscillator Configuration
    CC_REG_RCCTRL0,     // RC Oscillator Configuration

    CC_REG_CNT,

    //other commands
    CC_REG_FIFO = 0x3F
};

typedef struct {
	uint8_t SPtr;
	uint16_t data[CC_REG_CNT];

}CC1101_Config_t;
extern CC1101_Config_t RFCfgDefault;

typedef struct {
	SPI_Interface_t *spi;
	void (*init)(void);
	void (*sendData)(void *data, uint8_t size, uint8_t *funcOK);

	uint8_t initSucc;

}CC1101_Interface_t;
extern CC1101_Interface_t RF;

void CC_Init(void);
void CC_SendData(void *data, uint8_t size, uint8_t *funcOK);

#endif /* CC1101_H_ */

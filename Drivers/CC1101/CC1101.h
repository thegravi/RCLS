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
#include "../LCD/lcd.h"

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

#define CC_READ_BURST		0xC0
#define CC_READ_SINGLE		0x80
#define CC_WRITE_BURST		0x40

#define CC_READ_STATUS		0xC0
#define CC_READ_CONFIG		0x80

// Status registers
#define CC_PARTNUM           0x30        // Chip ID
#define CC_VERSION           0x31        // Chip ID
#define CC_FREQEST           0x32        // Frequency Offset Estimate from Demodulator
#define CC_LQI               0x33        // Demodulator Estimate for Link Quality
#define CC_RSSI              0x34        // Received Signal Strength Indication
#define CC_MARCSTATE         0x35        // Main Radio Control State Machine State
#define CC_WORTIME1          0x36        // High Byte of WOR Time
#define CC_WORTIME0          0x37        // Low Byte of WOR Time
#define CC_PKTSTATUS         0x38        // Current GDOx Status and Packet Status
#define CC_VCO_VC_DAC        0x39        // Current Setting from PLL Calibration Module
#define CC_TXBYTES           0x3A        // Underflow and Number of Bytes
#define CC_RXBYTES           0x3B        // Overflow and Number of Bytes
#define CC_RCCTRL1_STATUS    0x3C        // Last RC Oscillator Calibration Result
#define CC_RCCTRL0_STATUS    0x3D        // Last RC Oscillator Calibration Result

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
    CC_REG_AGCCTRL2,    // AGC Control
    CC_REG_AGCCTRL1,    // AGC Control
    CC_REG_AGCCTRL0,    // AGC Control
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
	void (*sendData)(uint8_t *data, uint8_t size, uint8_t *funcOK);
	uint8_t (*receivePacket)(uint8_t *buffer, uint8_t *len, uint8_t *ok);

	uint8_t initSucc;

}CC1101_Interface_t;
extern CC1101_Interface_t RF;

void CC_Init(void);
void CC_SendData(uint8_t *data, uint8_t size, uint8_t *funcOK);
uint8_t CC_ReceivePacket(uint8_t *buffer, uint8_t *len, uint8_t *ok);
uint8_t CC_ReadFIFO(uint8_t *data, uint8_t size, uint8_t *ok);

#endif /* CC1101_H_ */

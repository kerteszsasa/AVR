
#define SLA_W 0x9E
#define SLA_R 0x9f

extern void TWI_Init(void);
extern void SPI_MasterTransmit(char cData);
extern void StartCond(void);
extern void StopCond(void);
extern void TWI_DATA_WRITE(unsigned char data);
extern unsigned char TWI_DATA_READ(char ack);

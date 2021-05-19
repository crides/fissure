#ifndef _SPI_H_
#define _SPI_H_

#include <avr/io.h>

#define configure_pin_sck() DDRB |= _BV(DDB1)
#define configure_pin_mosi() DDRB |= _BV(DDB2)
#define configure_pin_miso() DDRB &= ~_BV(DDB3)
#define configure_pin_ss() DDRB |= _BV(DDB6)

#define select_card() PORTB &= ~_BV(PORTB6)
#define unselect_card() PORTB |= _BV(PORTB6)

void spi_init(void);
void spi_send_byte(uint8_t);
void spi_send_word(uint16_t);
void spi_send_addr(uint32_t);
uint8_t spi_recv_byte(void);

#endif

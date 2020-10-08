#pragma once

#ifdef __AVR__
#include <avr/io.h>

#define configure_pin_sck() DDRB |= _BV(DDB1)
#define configure_pin_mosi() DDRB |= _BV(DDB2)
#define configure_pin_miso() DDRB &= ~_BV(DDB3)
#define configure_pin_ss() DDRB |= _BV(DDB6)

#define select_card() PORTB &= ~_BV(PORTB6)
#define unselect_card() PORTB |= _BV(PORTB6)
#else
#include <stdint.h>
#endif

void flash_init(void);
void flash_read(uint32_t addr, uint8_t *buf, uint8_t len);
void flash_write(uint32_t addr, uint8_t *buf, uint8_t len);
void flash_erase_page(uint32_t addr);

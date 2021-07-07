# Simple build guide for Fissure v3.1

This version of the board isn't really designed with easy assembly in mind, and the order of building is really important. If you mess it up, things are harder but not impossible to fix.

## BOM

The number of switches is dependent on how many you want to have. The board is designed around a 36-key keyboard, and the extra 2 key outside of the pinky column is only used for the right side for steno. Thus I only use 38 keys myself, but you can really do anything between 36 and 40. I'll assume 40 below.

Basics:
40 x choc PG1350
40 x 1N4148 diode in SOD-123 package. I used [these](https://www.digikey.com/en/products/detail/diodes-incorporated/1N4148W-13-F/2242774)
 2 x PJ-320D TRRS jack
 2 x promicro (and probably sockets)
 2 x EVQQ2 reset buttons. I used [these](https://www.digikey.com/en/products/detail/panasonic-electronic-components/EVQ-Q2B03W/762922)
 2 x 4.7k 0805 resistors if you are not using an OLED with builtin I2C pullups. Or you can use soft serial.
 
Optional:
 1 x OLED (OLED doesn't work on the right side)
 2 x SK6812MINI Neopixels
 
I also have footprints for a MT25Q SPI NOR flash and a 10k 0805 resistor, but those are for custom embedded steno functionality, and I don't consider them publically available. Let me know if you want to use it, but it'll probably be a hassle to set up.

## Assembly

Parallel assembly can be and should be done on the individual board pieces first before final assembly.

- Alpha piece: Do it like other boards with underside promicros. Sockets first, then diodes, RGB if you have one, and reset buttons, lastly switches
- Thumb piece: Same as the alpha one. Diodes before switches
- Middle piece: OLED and TRRS jack in whatever ordering

### Final assembly

The middle piece can be angled however you want to achieve different heights and thumb-alpha positioning. I used solder balls on the alpha and thumb pieces to sort of hold the middle piece in place, before adjusting the angles. Actual steps:
- For the connector on the bottom side of the alpha piece and the top side of the thumb piece, add a lot of solder to the both pads at both ends of the connector.
- Place the middle piece between the 2, and adjust the angle to suit your hands.
- When the angle feels good, use the solder from the thumb piece to solder together the thumb and middle piece.
- Take away the alpha piece and solder the rest of the pads.
- Put the alpha piece back on top of both the middle and bottom pieces, and solder them together using the solder from the alpha piece.
- Finally flip the whole thing around and solder the rest of the pads.

## Configuration

```c
#define MATRIX_ROW_PINS { E6, B4, B5, D7 }
#define MATRIX_COL_PINS { D3, D2, F4, F5, F6 }
#define RGB_DI_PIN F7
```

#include "neopixel.h"

/***************************************************
This is a library for the Adafruit 1.8" SPI display.
This library works with the Adafruit 1.8" TFT Breakout w/SD card
----> http://www.adafruit.com/products/358
as well as Adafruit raw 1.8" TFT display
----> http://www.adafruit.com/products/618

Check out the links above for our tutorials and wiring diagrams
These displays use SPI to communicate, 4 or 5 pins are required to
interface (RST is optional)
Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
MIT license, all text above must be included in any redistribution
****************************************************/

#ifndef _ADAFRUIT_ST7735H_
#define _ADAFRUIT_ST7735H_

#define ARDUINO 100

#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H

#define SPARK_CORE

#define swap(a, b) { int16_t t = a; a = b; b = t; }

class Adafruit_GFX : public Print {

  public:

Adafruit_GFX(int16_t w, int16_t h); // Constructor

// This MUST be defined by the subclass:
virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

// These MAY be overridden by the subclass to provide device-specific
// optimized code.  Otherwise 'generic' versions are used.
virtual void
drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color),
drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color),
fillScreen(uint16_t color),
invertDisplay(boolean i);

// These exist only with Adafruit_GFX (no subclass overrides)
void
drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
 uint16_t color),
fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
 int16_t delta, uint16_t color),
drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
 int16_t x2, int16_t y2, uint16_t color),
fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
 int16_t x2, int16_t y2, uint16_t color),
drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
  int16_t radius, uint16_t color),
fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
  int16_t radius, uint16_t color),
drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap,
 int16_t w, int16_t h, uint16_t color),
drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
 uint16_t bg, uint8_t size),
setCursor(int16_t x, int16_t y),
setTextColor(uint16_t c),
setTextColor(uint16_t c, uint16_t bg),
setTextSize(uint8_t s),
setTextWrap(boolean w),
setRotation(uint8_t r);

#if ARDUINO >= 100
virtual size_t write(uint8_t);
#else
virtual void   write(uint8_t);
#endif

int16_t
height(void),
width(void);

uint8_t getRotation(void);

protected:
const int16_t
WIDTH, HEIGHT;   // This is the 'raw' display w/h - never changes
int16_t
_width, _height, // Display w/h as modified by current rotation
cursor_x, cursor_y;
uint16_t
textcolor, textbgcolor;
uint8_t
textsize,
rotation;
boolean
wrap; // If set, 'wrap' text at right edge of display
};

#endif // _ADAFRUIT_GFX_H

typedef unsigned char prog_uchar;


#define ST7735_TFTWIDTH  128
#define ST7735_TFTHEIGHT 128

#define ST7735_NOP   0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13

#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define ST7735_PTLAR   0x30
#define ST7735_COLMOD  0x3A
#define ST7735_MADCTL  0x36

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD

#define ST7735_PWCTR6  0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// Color definitions
#define BLACK   0x0000
#define BLUE  0x001F
#define RED   0xF800
#define GREEN   0x07E0
#define CYAN  0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


class Adafruit_ST7735 : public Adafruit_GFX {

  public:

  Adafruit_ST7735(uint8_t CS, uint8_t RS, uint8_t SID, uint8_t SCLK,
    uint8_t RST);
  Adafruit_ST7735(uint8_t CS, uint8_t RS, uint8_t RST);

void   initB(void),               // for ST7735B displays
initR(), // for ST7735R
setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1),
pushColor(uint16_t color),
fillScreen(uint16_t color),
drawPixel(int16_t x, int16_t y, uint16_t color),
drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
 uint16_t color),
setRotation(uint8_t r),
invertDisplay(boolean i);
uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);

/* These are not for current use, 8-bit protocol only!
 uint8_t  readdata(void),
 readcommand8(uint8_t);
 uint16_t readcommand16(uint8_t);
 uint32_t readcommand32(uint8_t);
 void   dummyclock(void);
 */

 private:
 void   spiwrite(uint8_t),
 writecommand(uint8_t c),
 writedata(uint8_t d),
 commandList(const uint8_t *addr),
 commonInit(const uint8_t *cmdList);
//uint8_t  spiread(void);

boolean  hwSPI;

#if defined(__AVR__) || defined(CORE_TEENSY)
volatile uint8_t *dataport, *clkport, *csport, *rsport;
uint8_t  _cs, _rs, _rst, _sid, _sclk,
datapinmask, clkpinmask, cspinmask, rspinmask,
colstart, rowstart; // some displays need this changed
#endif //  #ifdef __AVR__

#if defined(__SAM3X8E__)
Pio *dataport, *clkport, *csport, *rsport;
uint32_t  _cs, _rs, _rst, _sid, _sclk,
datapinmask, clkpinmask, cspinmask, rspinmask,
colstart, rowstart; // some displays need this changed
#endif //  #if defined(__SAM3X8E__)

#if defined(SPARK_CORE)
uint32_t  _cs, _rs, _rst, _sid, _sclk,
datapinmask, clkpinmask, cspinmask, rspinmask,
colstart, rowstart; // some displays need this changed
#endif

};

#endif


#define PROGMEM


// Standard ASCII 5x7 font

static const unsigned char font[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
  0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
  0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
  0x18, 0x3C, 0x7E, 0x3C, 0x18,
  0x1C, 0x57, 0x7D, 0x57, 0x1C,
  0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
  0x00, 0x18, 0x3C, 0x18, 0x00,
  0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
  0x00, 0x18, 0x24, 0x18, 0x00,
  0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
  0x30, 0x48, 0x3A, 0x06, 0x0E,
  0x26, 0x29, 0x79, 0x29, 0x26,
  0x40, 0x7F, 0x05, 0x05, 0x07,
  0x40, 0x7F, 0x05, 0x25, 0x3F,
  0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
  0x7F, 0x3E, 0x1C, 0x1C, 0x08,
  0x08, 0x1C, 0x1C, 0x3E, 0x7F,
  0x14, 0x22, 0x7F, 0x22, 0x14,
  0x5F, 0x5F, 0x00, 0x5F, 0x5F,
  0x06, 0x09, 0x7F, 0x01, 0x7F,
  0x00, 0x66, 0x89, 0x95, 0x6A,
  0x60, 0x60, 0x60, 0x60, 0x60,
  0x94, 0xA2, 0xFF, 0xA2, 0x94,
  0x08, 0x04, 0x7E, 0x04, 0x08,
  0x10, 0x20, 0x7E, 0x20, 0x10,
  0x08, 0x08, 0x2A, 0x1C, 0x08,
  0x08, 0x1C, 0x2A, 0x08, 0x08,
  0x1E, 0x10, 0x10, 0x10, 0x10,
  0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
  0x30, 0x38, 0x3E, 0x38, 0x30,
  0x06, 0x0E, 0x3E, 0x0E, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x5F, 0x00, 0x00,
  0x00, 0x07, 0x00, 0x07, 0x00,
  0x14, 0x7F, 0x14, 0x7F, 0x14,
  0x24, 0x2A, 0x7F, 0x2A, 0x12,
  0x23, 0x13, 0x08, 0x64, 0x62,
  0x36, 0x49, 0x56, 0x20, 0x50,
  0x00, 0x08, 0x07, 0x03, 0x00,
  0x00, 0x1C, 0x22, 0x41, 0x00,
  0x00, 0x41, 0x22, 0x1C, 0x00,
  0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
  0x08, 0x08, 0x3E, 0x08, 0x08,
  0x00, 0x80, 0x70, 0x30, 0x00,
  0x08, 0x08, 0x08, 0x08, 0x08,
  0x00, 0x00, 0x60, 0x60, 0x00,
  0x20, 0x10, 0x08, 0x04, 0x02,
  0x3E, 0x51, 0x49, 0x45, 0x3E,
  0x00, 0x42, 0x7F, 0x40, 0x00,
  0x72, 0x49, 0x49, 0x49, 0x46,
  0x21, 0x41, 0x49, 0x4D, 0x33,
  0x18, 0x14, 0x12, 0x7F, 0x10,
  0x27, 0x45, 0x45, 0x45, 0x39,
  0x3C, 0x4A, 0x49, 0x49, 0x31,
  0x41, 0x21, 0x11, 0x09, 0x07,
  0x36, 0x49, 0x49, 0x49, 0x36,
  0x46, 0x49, 0x49, 0x29, 0x1E,
  0x00, 0x00, 0x14, 0x00, 0x00,
  0x00, 0x40, 0x34, 0x00, 0x00,
  0x00, 0x08, 0x14, 0x22, 0x41,
  0x14, 0x14, 0x14, 0x14, 0x14,
  0x00, 0x41, 0x22, 0x14, 0x08,
  0x02, 0x01, 0x59, 0x09, 0x06,
  0x3E, 0x41, 0x5D, 0x59, 0x4E,
  0x7C, 0x12, 0x11, 0x12, 0x7C,
  0x7F, 0x49, 0x49, 0x49, 0x36,
  0x3E, 0x41, 0x41, 0x41, 0x22,
  0x7F, 0x41, 0x41, 0x41, 0x3E,
  0x7F, 0x49, 0x49, 0x49, 0x41,
  0x7F, 0x09, 0x09, 0x09, 0x01,
  0x3E, 0x41, 0x41, 0x51, 0x73,
  0x7F, 0x08, 0x08, 0x08, 0x7F,
  0x00, 0x41, 0x7F, 0x41, 0x00,
  0x20, 0x40, 0x41, 0x3F, 0x01,
  0x7F, 0x08, 0x14, 0x22, 0x41,
  0x7F, 0x40, 0x40, 0x40, 0x40,
  0x7F, 0x02, 0x1C, 0x02, 0x7F,
  0x7F, 0x04, 0x08, 0x10, 0x7F,
  0x3E, 0x41, 0x41, 0x41, 0x3E,
  0x7F, 0x09, 0x09, 0x09, 0x06,
  0x3E, 0x41, 0x51, 0x21, 0x5E,
  0x7F, 0x09, 0x19, 0x29, 0x46,
  0x26, 0x49, 0x49, 0x49, 0x32,
  0x03, 0x01, 0x7F, 0x01, 0x03,
  0x3F, 0x40, 0x40, 0x40, 0x3F,
  0x1F, 0x20, 0x40, 0x20, 0x1F,
  0x3F, 0x40, 0x38, 0x40, 0x3F,
  0x63, 0x14, 0x08, 0x14, 0x63,
  0x03, 0x04, 0x78, 0x04, 0x03,
  0x61, 0x59, 0x49, 0x4D, 0x43,
  0x00, 0x7F, 0x41, 0x41, 0x41,
  0x02, 0x04, 0x08, 0x10, 0x20,
  0x00, 0x41, 0x41, 0x41, 0x7F,
  0x04, 0x02, 0x01, 0x02, 0x04,
  0x40, 0x40, 0x40, 0x40, 0x40,
  0x00, 0x03, 0x07, 0x08, 0x00,
  0x20, 0x54, 0x54, 0x78, 0x40,
  0x7F, 0x28, 0x44, 0x44, 0x38,
  0x38, 0x44, 0x44, 0x44, 0x28,
  0x38, 0x44, 0x44, 0x28, 0x7F,
  0x38, 0x54, 0x54, 0x54, 0x18,
  0x00, 0x08, 0x7E, 0x09, 0x02,
  0x18, 0xA4, 0xA4, 0x9C, 0x78,
  0x7F, 0x08, 0x04, 0x04, 0x78,
  0x00, 0x44, 0x7D, 0x40, 0x00,
  0x20, 0x40, 0x40, 0x3D, 0x00,
  0x7F, 0x10, 0x28, 0x44, 0x00,
  0x00, 0x41, 0x7F, 0x40, 0x00,
  0x7C, 0x04, 0x78, 0x04, 0x78,
  0x7C, 0x08, 0x04, 0x04, 0x78,
  0x38, 0x44, 0x44, 0x44, 0x38,
  0xFC, 0x18, 0x24, 0x24, 0x18,
  0x18, 0x24, 0x24, 0x18, 0xFC,
  0x7C, 0x08, 0x04, 0x04, 0x08,
  0x48, 0x54, 0x54, 0x54, 0x24,
  0x04, 0x04, 0x3F, 0x44, 0x24,
  0x3C, 0x40, 0x40, 0x20, 0x7C,
  0x1C, 0x20, 0x40, 0x20, 0x1C,
  0x3C, 0x40, 0x30, 0x40, 0x3C,
  0x44, 0x28, 0x10, 0x28, 0x44,
  0x4C, 0x90, 0x90, 0x90, 0x7C,
  0x44, 0x64, 0x54, 0x4C, 0x44,
  0x00, 0x08, 0x36, 0x41, 0x00,
  0x00, 0x00, 0x77, 0x00, 0x00,
  0x00, 0x41, 0x36, 0x08, 0x00,
  0x02, 0x01, 0x02, 0x04, 0x02,
  0x3C, 0x26, 0x23, 0x26, 0x3C,
  0x1E, 0xA1, 0xA1, 0x61, 0x12,
  0x3A, 0x40, 0x40, 0x20, 0x7A,
  0x38, 0x54, 0x54, 0x55, 0x59,
  0x21, 0x55, 0x55, 0x79, 0x41,
  0x21, 0x54, 0x54, 0x78, 0x41,
  0x21, 0x55, 0x54, 0x78, 0x40,
  0x20, 0x54, 0x55, 0x79, 0x40,
  0x0C, 0x1E, 0x52, 0x72, 0x12,
  0x39, 0x55, 0x55, 0x55, 0x59,
  0x39, 0x54, 0x54, 0x54, 0x59,
  0x39, 0x55, 0x54, 0x54, 0x58,
  0x00, 0x00, 0x45, 0x7C, 0x41,
  0x00, 0x02, 0x45, 0x7D, 0x42,
  0x00, 0x01, 0x45, 0x7C, 0x40,
  0xF0, 0x29, 0x24, 0x29, 0xF0,
  0xF0, 0x28, 0x25, 0x28, 0xF0,
  0x7C, 0x54, 0x55, 0x45, 0x00,
  0x20, 0x54, 0x54, 0x7C, 0x54,
  0x7C, 0x0A, 0x09, 0x7F, 0x49,
  0x32, 0x49, 0x49, 0x49, 0x32,
  0x32, 0x48, 0x48, 0x48, 0x32,
  0x32, 0x4A, 0x48, 0x48, 0x30,
  0x3A, 0x41, 0x41, 0x21, 0x7A,
  0x3A, 0x42, 0x40, 0x20, 0x78,
  0x00, 0x9D, 0xA0, 0xA0, 0x7D,
  0x39, 0x44, 0x44, 0x44, 0x39,
  0x3D, 0x40, 0x40, 0x40, 0x3D,
  0x3C, 0x24, 0xFF, 0x24, 0x24,
  0x48, 0x7E, 0x49, 0x43, 0x66,
  0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
  0xFF, 0x09, 0x29, 0xF6, 0x20,
  0xC0, 0x88, 0x7E, 0x09, 0x03,
  0x20, 0x54, 0x54, 0x79, 0x41,
  0x00, 0x00, 0x44, 0x7D, 0x41,
  0x30, 0x48, 0x48, 0x4A, 0x32,
  0x38, 0x40, 0x40, 0x22, 0x7A,
  0x00, 0x7A, 0x0A, 0x0A, 0x72,
  0x7D, 0x0D, 0x19, 0x31, 0x7D,
  0x26, 0x29, 0x29, 0x2F, 0x28,
  0x26, 0x29, 0x29, 0x29, 0x26,
  0x30, 0x48, 0x4D, 0x40, 0x20,
  0x38, 0x08, 0x08, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x08, 0x38,
  0x2F, 0x10, 0xC8, 0xAC, 0xBA,
  0x2F, 0x10, 0x28, 0x34, 0xFA,
  0x00, 0x00, 0x7B, 0x00, 0x00,
  0x08, 0x14, 0x2A, 0x14, 0x22,
  0x22, 0x14, 0x2A, 0x14, 0x08,
  0xAA, 0x00, 0x55, 0x00, 0xAA,
  0xAA, 0x55, 0xAA, 0x55, 0xAA,
  0x00, 0x00, 0x00, 0xFF, 0x00,
  0x10, 0x10, 0x10, 0xFF, 0x00,
  0x14, 0x14, 0x14, 0xFF, 0x00,
  0x10, 0x10, 0xFF, 0x00, 0xFF,
  0x10, 0x10, 0xF0, 0x10, 0xF0,
  0x14, 0x14, 0x14, 0xFC, 0x00,
  0x14, 0x14, 0xF7, 0x00, 0xFF,
  0x00, 0x00, 0xFF, 0x00, 0xFF,
  0x14, 0x14, 0xF4, 0x04, 0xFC,
  0x14, 0x14, 0x17, 0x10, 0x1F,
  0x10, 0x10, 0x1F, 0x10, 0x1F,
  0x14, 0x14, 0x14, 0x1F, 0x00,
  0x10, 0x10, 0x10, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x1F, 0x10,
  0x10, 0x10, 0x10, 0x1F, 0x10,
  0x10, 0x10, 0x10, 0xF0, 0x10,
  0x00, 0x00, 0x00, 0xFF, 0x10,
  0x10, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0xFF, 0x10,
  0x00, 0x00, 0x00, 0xFF, 0x14,
  0x00, 0x00, 0xFF, 0x00, 0xFF,
  0x00, 0x00, 0x1F, 0x10, 0x17,
  0x00, 0x00, 0xFC, 0x04, 0xF4,
  0x14, 0x14, 0x17, 0x10, 0x17,
  0x14, 0x14, 0xF4, 0x04, 0xF4,
  0x00, 0x00, 0xFF, 0x00, 0xF7,
  0x14, 0x14, 0x14, 0x14, 0x14,
  0x14, 0x14, 0xF7, 0x00, 0xF7,
  0x14, 0x14, 0x14, 0x17, 0x14,
  0x10, 0x10, 0x1F, 0x10, 0x1F,
  0x14, 0x14, 0x14, 0xF4, 0x14,
  0x10, 0x10, 0xF0, 0x10, 0xF0,
  0x00, 0x00, 0x1F, 0x10, 0x1F,
  0x00, 0x00, 0x00, 0x1F, 0x14,
  0x00, 0x00, 0x00, 0xFC, 0x14,
  0x00, 0x00, 0xF0, 0x10, 0xF0,
  0x10, 0x10, 0xFF, 0x10, 0xFF,
  0x14, 0x14, 0x14, 0xFF, 0x14,
  0x10, 0x10, 0x10, 0x1F, 0x00,
  0x00, 0x00, 0x00, 0xF0, 0x10,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xFF, 0xFF,
  0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
  0x38, 0x44, 0x44, 0x38, 0x44,
  0x7C, 0x2A, 0x2A, 0x3E, 0x14,
  0x7E, 0x02, 0x02, 0x06, 0x06,
  0x02, 0x7E, 0x02, 0x7E, 0x02,
  0x63, 0x55, 0x49, 0x41, 0x63,
  0x38, 0x44, 0x44, 0x3C, 0x04,
  0x40, 0x7E, 0x20, 0x1E, 0x20,
  0x06, 0x02, 0x7E, 0x02, 0x02,
  0x99, 0xA5, 0xE7, 0xA5, 0x99,
  0x1C, 0x2A, 0x49, 0x2A, 0x1C,
  0x4C, 0x72, 0x01, 0x72, 0x4C,
  0x30, 0x4A, 0x4D, 0x4D, 0x30,
  0x30, 0x48, 0x78, 0x48, 0x30,
  0xBC, 0x62, 0x5A, 0x46, 0x3D,
  0x3E, 0x49, 0x49, 0x49, 0x00,
  0x7E, 0x01, 0x01, 0x01, 0x7E,
  0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
  0x44, 0x44, 0x5F, 0x44, 0x44,
  0x40, 0x51, 0x4A, 0x44, 0x40,
  0x40, 0x44, 0x4A, 0x51, 0x40,
  0x00, 0x00, 0xFF, 0x01, 0x03,
  0xE0, 0x80, 0xFF, 0x00, 0x00,
  0x08, 0x08, 0x6B, 0x6B, 0x08,
  0x36, 0x12, 0x36, 0x24, 0x36,
  0x06, 0x0F, 0x09, 0x0F, 0x06,
  0x00, 0x00, 0x18, 0x18, 0x00,
  0x00, 0x00, 0x10, 0x10, 0x00,
  0x30, 0x40, 0xFF, 0x01, 0x01,
  0x00, 0x1F, 0x01, 0x01, 0x1E,
  0x00, 0x19, 0x1D, 0x17, 0x12,
  0x00, 0x3C, 0x3C, 0x3C, 0x3C,
  0x00, 0x00, 0x00, 0x00, 0x00
};

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

Adafruit_GFX::Adafruit_GFX(int16_t w, int16_t h):
WIDTH(w), HEIGHT(h)
{
  _width  = WIDTH;
  _height   = HEIGHT;
  rotation  = 0;
  cursor_y  = cursor_x  = 0;
  textsize  = 1;
  textcolor = textbgcolor = 0xFFFF;
  wrap    = true;
}

// Draw a circle outline
void Adafruit_GFX::drawCircle(int16_t x0, int16_t y0, int16_t r,
  uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r, color);
  drawPixel(x0  , y0-r, color);
  drawPixel(x0+r, y0  , color);
  drawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y, color);
    drawPixel(x0 - x, y0 + y, color);
    drawPixel(x0 + x, y0 - y, color);
    drawPixel(x0 - x, y0 - y, color);
    drawPixel(x0 + y, y0 + x, color);
    drawPixel(x0 - y, y0 + x, color);
    drawPixel(x0 + y, y0 - x, color);
    drawPixel(x0 - y, y0 - x, color);
  }
}

void Adafruit_GFX::drawCircleHelper( int16_t x0, int16_t y0,
  int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f   = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x   = 0;
  int16_t y   = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f   += ddF_y;
    }
    x++;
    ddF_x += 2;
    f   += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}

void Adafruit_GFX::fillCircle(int16_t x0, int16_t y0, int16_t r,
  uint16_t color) {
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void Adafruit_GFX::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
  uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f   = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x   = 0;
  int16_t y   = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f   += ddF_y;
    }
    x++;
    ddF_x += 2;
    f   += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

// Bresenham's algorithm - thx wikpedia
void Adafruit_GFX::drawLine(int16_t x0, int16_t y0,
  int16_t x1, int16_t y1,
  uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
    } else {
      ystep = -1;
    }

    for (; x0<=x1; x0++) {
      if (steep) {
        drawPixel(y0, x0, color);
        } else {
          drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
          y0 += ystep;
          err += dx;
        }
      }
    }

// Draw a rectangle
void Adafruit_GFX::drawRect(int16_t x, int16_t y,
  int16_t w, int16_t h,
  uint16_t color) {
  drawFastHLine(x, y, w, color);
  drawFastHLine(x, y+h-1, w, color);
  drawFastVLine(x, y, h, color);
  drawFastVLine(x+w-1, y, h, color);
}

void Adafruit_GFX::drawFastVLine(int16_t x, int16_t y,
 int16_t h, uint16_t color) {
// Update in subclasses if desired!
drawLine(x, y, x, y+h-1, color);
}

void Adafruit_GFX::drawFastHLine(int16_t x, int16_t y,
 int16_t w, uint16_t color) {
// Update in subclasses if desired!
drawLine(x, y, x+w-1, y, color);
}

void Adafruit_GFX::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color) {
// Update in subclasses if desired!
for (int16_t i=x; i<x+w; i++) {
  drawFastVLine(i, y, h, color);
}
}

void Adafruit_GFX::fillScreen(uint16_t color) {
  fillRect(0, 0, _width, _height, color);
}

// Draw a rounded rectangle
void Adafruit_GFX::drawRoundRect(int16_t x, int16_t y, int16_t w,
 int16_t h, int16_t r, uint16_t color) {
// smarter version
drawFastHLine(x+r  , y  , w-2*r, color); // Top
drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
drawFastVLine(x  , y+r  , h-2*r, color); // Left
drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
// draw four corners
drawCircleHelper(x+r  , y+r  , r, 1, color);
drawCircleHelper(x+w-r-1, y+r  , r, 2, color);
drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
drawCircleHelper(x+r  , y+h-r-1, r, 8, color);
}

// Fill a rounded rectangle
void Adafruit_GFX::fillRoundRect(int16_t x, int16_t y, int16_t w,
 int16_t h, int16_t r, uint16_t color) {
// smarter version
fillRect(x+r, y, w-2*r, h, color);

// draw four corners
fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
fillCircleHelper(x+r  , y+r, r, 2, h-2*r-1, color);
}

// Draw a triangle
void Adafruit_GFX::drawTriangle(int16_t x0, int16_t y0,
  int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint16_t color) {
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}

// Fill a triangle
void Adafruit_GFX::fillTriangle ( int16_t x0, int16_t y0,
 int16_t x1, int16_t y1,
 int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

// Sort coordinates by Y order (y2 >= y1 >= y0)
if (y0 > y1) {
  swap(y0, y1); swap(x0, x1);
}
if (y1 > y2) {
  swap(y2, y1); swap(x2, x1);
}
if (y0 > y1) {
  swap(y0, y1); swap(x0, x1);
}

if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
  a = b = x0;
  if(x1 < a)    a = x1;
  else if(x1 > b) b = x1;
  if(x2 < a)    a = x2;
  else if(x2 > b) b = x2;
  drawFastHLine(a, y0, b-a+1, color);
  return;
}

int16_t
dx01 = x1 - x0,
dy01 = y1 - y0,
dx02 = x2 - x0,
dy02 = y2 - y0,
dx12 = x2 - x1,
dy12 = y2 - y1,
sa   = 0,
sb   = 0;

// For upper part of triangle, find scanline crossings for segments
// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
// is included here (and second loop will be skipped, avoiding a /0
// error there), otherwise scanline y1 is skipped here and handled
// in the second loop...which also avoids a /0 error here if y0=y1
// (flat-topped triangle).
if(y1 == y2) last = y1;   // Include y1 scanline
else     last = y1-1; // Skip it

for(y=y0; y<=last; y++) {
  a   = x0 + sa / dy01;
  b   = x0 + sb / dy02;
  sa += dx01;
  sb += dx02;
  /* longhand:
   a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
   b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
   */
   if(a > b) swap(a,b);
   drawFastHLine(a, y, b-a+1, color);
 }

// For lower part of triangle, find scanline crossings for segments
// 0-2 and 1-2.  This loop is skipped if y1=y2.
sa = dx12 * (y - y1);
sb = dx02 * (y - y0);
for(; y<=y2; y++) {
  a   = x1 + sa / dy12;
  b   = x0 + sb / dy02;
  sa += dx12;
  sb += dx02;
  /* longhand:
   a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
   b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
   */
   if(a > b) swap(a,b);
   drawFastHLine(a, y, b-a+1, color);
 }
}

void Adafruit_GFX::drawBitmap(int16_t x, int16_t y,
  const uint8_t *bitmap, int16_t w, int16_t h,
  uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
        drawPixel(x+i, y+j, color);
      }
    }
  }
}

#if ARDUINO >= 100
size_t Adafruit_GFX::write(uint8_t c) {
  #else
  void Adafruit_GFX::write(uint8_t c) {
    #endif
    if (c == '\n') {
      cursor_y += textsize*8;
      cursor_x  = 0;
      } else if (c == '\r') {
    // skip em
    } else {
      drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
      cursor_x += textsize*6;
      if (wrap && (cursor_x > (_width - textsize*6))) {
        cursor_y += textsize*8;
        cursor_x = 0;
      }
    }
    #if ARDUINO >= 100
    return 1;
    #endif
  }

// Draw a character
void Adafruit_GFX::drawChar(int16_t x, int16_t y, unsigned char c,
  uint16_t color, uint16_t bg, uint8_t size) {

  if((x >= _width)      || // Clip right
     (y >= _height)       || // Clip bottom
     ((x + 6 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
  return;

  for (int8_t i=0; i<6; i++ ) {
    uint8_t line;
    if (i == 5)
    line = 0x0;
    else
    line = pgm_read_byte(font+(c*5)+i);
    for (int8_t j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
        drawPixel(x+i, y+j, color);
        else {  // big size
          fillRect(x+(i*size), y+(j*size), size, size, color);
        }
        } else if (bg != color) {
        if (size == 1) // default size
        drawPixel(x+i, y+j, bg);
        else {  // big size
          fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}

void Adafruit_GFX::setCursor(int16_t x, int16_t y) {
  cursor_x = x;
  cursor_y = y;
}

void Adafruit_GFX::setTextSize(uint8_t s) {
  textsize = (s > 0) ? s : 1;
}

void Adafruit_GFX::setTextColor(uint16_t c) {
  // For 'transparent' background, we'll set the bg
  // to the same as fg instead of using a flag
  textcolor = textbgcolor = c;
}

void Adafruit_GFX::setTextColor(uint16_t c, uint16_t b) {
  textcolor   = c;
  textbgcolor = b;
}

void Adafruit_GFX::setTextWrap(boolean w) {
  wrap = w;
}

uint8_t Adafruit_GFX::getRotation(void) {
  return rotation;
}

void Adafruit_GFX::setRotation(uint8_t x) {
  rotation = (x & 3);
  switch(rotation) {
    case 0:
    case 2:
    _width  = WIDTH;
    _height = HEIGHT;
    break;
    case 1:
    case 3:
    _width  = HEIGHT;
    _height = WIDTH;
    break;
  }
}

// Return the size of the display (per current rotation)
int16_t Adafruit_GFX::width(void) {
  return _width;
}

int16_t Adafruit_GFX::height(void) {
  return _height;
}

void Adafruit_GFX::invertDisplay(boolean i) {
  // Do nothing, must be subclassed if supported
}


inline uint16_t swapcolor(uint16_t x) {
  return (x << 11) | (x & 0x07E0) | (x >> 11);
}


// Constructor when using software SPI.  All output pins are configurable.
Adafruit_ST7735::Adafruit_ST7735(uint8_t cs, uint8_t rs, uint8_t sid,
 uint8_t sclk, uint8_t rst) : Adafruit_GFX(ST7735_TFTWIDTH, ST7735_TFTHEIGHT)
{
  _cs   = cs;
  _rs   = rs;
  _sid  = sid;
  _sclk = sclk;
  _rst  = rst;
  hwSPI = false;
}


// Constructor when using hardware SPI.  Faster, but must use SPI pins
// specific to each board type (e.g. 11,13 for Uno, 51,52 for Mega, etc.)
Adafruit_ST7735::Adafruit_ST7735(uint8_t cs, uint8_t rs, uint8_t rst) :
Adafruit_GFX(ST7735_TFTWIDTH, ST7735_TFTHEIGHT) {
  _cs   = cs;
  _rs   = rs;
  _rst  = rst;
  hwSPI = true;
  _sid  = _sclk = 0;
}

#if defined(CORE_TEENSY) && !defined(__AVR__)
#define __AVR__
#endif

#ifdef __AVR__
inline void Adafruit_ST7735::spiwrite(uint8_t c) {


  if (hwSPI) {
    SPDR = c;
    while(!(SPSR & _BV(SPIF)));
    } else {
    // Fast SPI bitbang swiped from LPD8806 library
    for(uint8_t bit = 0x80; bit; bit >>= 1) {
      if(c & bit) *dataport |=  datapinmask;
      else    *dataport &= ~datapinmask;
      *clkport |=  clkpinmask;
      *clkport &= ~clkpinmask;
    }
  }
}


void Adafruit_ST7735::writecommand(uint8_t c) {
  *rsport &= ~rspinmask;
  *csport &= ~cspinmask;

  spiwrite(c);

  *csport |= cspinmask;
}


void Adafruit_ST7735::writedata(uint8_t c) {
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;

  spiwrite(c);

  *csport |= cspinmask;
}
#endif //#ifdef __AVR__

#if defined(__SAM3X8E__)
inline void Adafruit_ST7735::spiwrite(uint8_t c) {


  if (hwSPI) {
    SPI.transfer(c);
    } else {
    // Fast SPI bitbang swiped from LPD8806 library
    for(uint8_t bit = 0x80; bit; bit >>= 1) {
      if(c & bit) dataport->PIO_SODR |= datapinmask;
      else    dataport->PIO_CODR |= datapinmask;
      clkport->PIO_SODR |= clkpinmask;
      clkport->PIO_CODR |= clkpinmask;
    }
  }
}


void Adafruit_ST7735::writecommand(uint8_t c) {
  rsport->PIO_CODR |=  rspinmask;
  csport->PIO_CODR  |=  cspinmask;

  spiwrite(c);

  csport->PIO_SODR  |=  cspinmask;
}


void Adafruit_ST7735::writedata(uint8_t c) {
  rsport->PIO_SODR |=  rspinmask;
  csport->PIO_CODR  |=  cspinmask;

  spiwrite(c);

  csport->PIO_SODR  |=  cspinmask;
}
#endif //#if defined(__SAM3X8E__)

#if defined(SPARK_CORE)
inline void Adafruit_ST7735::spiwrite(uint8_t c) {

  if (hwSPI) {
    SPI.transfer(c);
    } else {
    // Fast SPI bitbang swiped from LPD8806 library
    for(uint8_t bit = 0x80; bit; bit >>= 1) {
      if(c & bit) digitalWrite(_sid, HIGH);
      else    digitalWrite(_sid, LOW);
      digitalWrite(_sclk, HIGH);
      digitalWrite(_sclk, LOW);
    }
  }
}

void Adafruit_ST7735::writecommand(uint8_t c) {
  digitalWrite(_rs, LOW);
  digitalWrite(_cs, LOW);
  spiwrite(c);
  digitalWrite(_cs, HIGH);
}


void Adafruit_ST7735::writedata(uint8_t c) {
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);
  spiwrite(c);
  digitalWrite(_cs, HIGH);
}
#endif //#if defined(SPARK_CORE)


// Rather than a bazillion writecommand() and writedata() calls, screen
// initialization commands and arguments are organized in these tables
// stored in PROGMEM.  The table may look bulky, but that's mostly the
// formatting -- storage-wise this is hundreds of bytes more compact
// than the equivalent code.  Companion function follows.
#define DELAY 0x80
static const uint8_t PROGMEM
Bcmd[] = {          // Initialization commands for 7735B screens
  18,             // 18 commands in list:
  ST7735_SWRESET,   DELAY,  //  1: Software reset, no args, w/delay
  50,           //   50 ms delay
  ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, no args, w/delay
  255,          //   255 = 500 ms delay
  ST7735_COLMOD , 1+DELAY,  //  3: Set color mode, 1 arg + delay:
  0x05,           //   16-bit color
  10,           //   10 ms delay
  ST7735_FRMCTR1, 3+DELAY,  //  4: Frame rate control, 3 args + delay:
  0x00,           //   fastest refresh
  0x06,           //   6 lines front porch
  0x03,           //   3 lines back porch
  10,           //   10 ms delay
  ST7735_MADCTL , 1    ,  //  5: Memory access ctrl (directions), 1 arg:
  0x08,           //   Row addr/col addr, bottom to top refresh
  ST7735_DISSET5, 2    ,  //  6: Display settings #5, 2 args, no delay:
  0x15,           //   1 clk cycle nonoverlap, 2 cycle gate
  //   rise, 3 cycle osc equalize
  0x02,           //   Fix on VTL
  ST7735_INVCTR , 1    ,  //  7: Display inversion control, 1 arg:
  0x0,          //   Line inversion
  ST7735_PWCTR1 , 2+DELAY,  //  8: Power control, 2 args + delay:
  0x02,           //   GVDD = 4.7V
  0x70,           //   1.0uA
  10,           //   10 ms delay
  ST7735_PWCTR2 , 1    ,  //  9: Power control, 1 arg, no delay:
  0x05,           //   VGH = 14.7V, VGL = -7.35V
  ST7735_PWCTR3 , 2    ,  // 10: Power control, 2 args, no delay:
  0x01,           //   Opamp current small
  0x02,           //   Boost frequency
  ST7735_VMCTR1 , 2+DELAY,  // 11: Power control, 2 args + delay:
  0x3C,           //   VCOMH = 4V
  0x38,           //   VCOML = -1.1V
  10,           //   10 ms delay
  ST7735_PWCTR6 , 2    ,  // 12: Power control, 2 args, no delay:
  0x11, 0x15,
  ST7735_GMCTRP1,16    ,  // 13: Magical unicorn dust, 16 args, no delay:
  0x09, 0x16, 0x09, 0x20, //   (seriously though, not sure what
  0x21, 0x1B, 0x13, 0x19, //    these config values represent)
0x17, 0x15, 0x1E, 0x2B,
0x04, 0x05, 0x02, 0x0E,
  ST7735_GMCTRN1,16+DELAY,  // 14: Sparkles and rainbows, 16 args + delay:
  0x0B, 0x14, 0x08, 0x1E, //   (ditto)
  0x22, 0x1D, 0x18, 0x1E,
  0x1B, 0x1A, 0x24, 0x2B,
  0x06, 0x06, 0x02, 0x0F,
  10,           //   10 ms delay
  ST7735_CASET  , 4    ,  // 15: Column addr set, 4 args, no delay:
  0x00, 0x02,       //   XSTART = 2
  0x00, 0x81,       //   XEND = 129
  ST7735_RASET  , 4    ,  // 16: Row addr set, 4 args, no delay:
  0x00, 0x02,       //   XSTART = 1
  0x00, 0x81,       //   XEND = 160
  ST7735_NORON  ,   DELAY,  // 17: Normal display on, no args, w/delay
  10,           //   10 ms delay
  ST7735_DISPON ,   DELAY,  // 18: Main screen turn on, no args, w/delay
  255 },          //   255 = 500 ms delay

Rcmd1[] = {         // Init for 7735R, part 1 (red or green tab)
  15,             // 15 commands in list:
  ST7735_SWRESET,   DELAY,  //  1: Software reset, 0 args, w/delay
  150,          //   150 ms delay
  ST7735_SLPOUT ,   DELAY,  //  2: Out of sleep mode, 0 args, w/delay
  255,          //   500 ms delay
  ST7735_FRMCTR1, 3    ,  //  3: Frame rate ctrl - normal mode, 3 args:
  0x01, 0x2C, 0x2D,     //   Rate = fosc/(1x2+40) * (LINE+2C+2D)
  ST7735_FRMCTR2, 3    ,  //  4: Frame rate control - idle mode, 3 args:
  0x01, 0x2C, 0x2D,     //   Rate = fosc/(1x2+40) * (LINE+2C+2D)
  ST7735_FRMCTR3, 6    ,  //  5: Frame rate ctrl - partial mode, 6 args:
  0x01, 0x2C, 0x2D,     //   Dot inversion mode
  0x01, 0x2C, 0x2D,     //   Line inversion mode
  ST7735_INVCTR , 1    ,  //  6: Display inversion ctrl, 1 arg, no delay:
  0x07,           //   No inversion
  ST7735_PWCTR1 , 3    ,  //  7: Power control, 3 args, no delay:
  0xA2,
  0x02,           //   -4.6V
  0x84,           //   AUTO mode
  ST7735_PWCTR2 , 1    ,  //  8: Power control, 1 arg, no delay:
  0xC5,           //   VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
  ST7735_PWCTR3 , 2    ,  //  9: Power control, 2 args, no delay:
  0x0A,           //   Opamp current small
  0x00,           //   Boost frequency
  ST7735_PWCTR4 , 2    ,  // 10: Power control, 2 args, no delay:
  0x8A,           //   BCLK/2, Opamp current small & Medium low
  0x2A,
  ST7735_PWCTR5 , 2    ,  // 11: Power control, 2 args, no delay:
  0x8A, 0xEE,
  ST7735_VMCTR1 , 1    ,  // 12: Power control, 1 arg, no delay:
  0x0E,
  ST7735_INVOFF , 0    ,  // 13: Don't invert display, no args, no delay
  ST7735_MADCTL , 1    ,  // 14: Memory access control (directions), 1 arg:
  0xC8,           //   row addr/col addr, bottom to top refresh
  ST7735_COLMOD , 1    ,  // 15: set color mode, 1 arg, no delay:
  0x05 },         //   16-bit color

Rcmd2green[] = {      // Init for 7735R, part 2 (green tab only)
  2,            //  2 commands in list:
  ST7735_CASET  , 4    ,  //  1: Column addr set, 4 args, no delay:
  0x00, 0x02,       //   XSTART = 0
  0x00, 0x7F+0x02,    //   XEND = 127
  ST7735_RASET  , 4    ,  //  2: Row addr set, 4 args, no delay:
  0x00, 0x01,       //   XSTART = 0
  0x00, 0x7F+0x02 },    //   XEND = 127

Rcmd3[] = {         // Init for 7735R, part 3 (red or green tab)
  4,            //  4 commands in list:
  ST7735_GMCTRP1, 16    , //  1: Magical unicorn dust, 16 args, no delay:
  0x02, 0x1c, 0x07, 0x12,
  0x37, 0x32, 0x29, 0x2d,
  0x29, 0x25, 0x2B, 0x39,
  0x00, 0x01, 0x03, 0x10,
  ST7735_GMCTRN1, 16    , //  2: Sparkles and rainbows, 16 args, no delay:
  0x03, 0x1d, 0x07, 0x06,
  0x2E, 0x2C, 0x29, 0x2D,
  0x2E, 0x2E, 0x37, 0x3F,
  0x00, 0x00, 0x02, 0x10,
  ST7735_NORON  ,  DELAY, //  3: Normal display on, no args, w/delay
  10,           //   10 ms delay
  ST7735_DISPON ,  DELAY, //  4: Main screen turn on, no args w/delay
  100 };          //   100 ms delay


// Companion code to the above tables.  Reads and issues
// a series of LCD commands stored in PROGMEM byte array.
void Adafruit_ST7735::commandList(const uint8_t *addr) {

  uint8_t  numCommands, numArgs;
  uint16_t ms;

  numCommands = pgm_read_byte(addr++);   // Number of commands to follow
  while(numCommands--) {         // For each command...
    writecommand(pgm_read_byte(addr++)); //   Read, issue command
    numArgs  = pgm_read_byte(addr++);  //   Number of args to follow
    ms     = numArgs & DELAY;      //   If hibit set, delay follows args
    numArgs &= ~DELAY;           //   Mask out delay bit
    while(numArgs--) {           //   For each argument...
      writedata(pgm_read_byte(addr++));  //   Read, issue argument
    }

    if(ms) {
      ms = pgm_read_byte(addr++); // Read post-command delay time (ms)
      if(ms == 255) ms = 500;   // If 255, delay for 500 ms
      delay(ms);
    }
  }
}


// Initialization code common to both 'B' and 'R' type displays
void Adafruit_ST7735::commonInit(const uint8_t *cmdList) {
  colstart  = rowstart = 0; // May be overridden in init func

  pinMode(_rs, OUTPUT);
  pinMode(_cs, OUTPUT);
  #ifdef __AVR__
  csport  = portOutputRegister(digitalPinToPort(_cs));
  rsport  = portOutputRegister(digitalPinToPort(_rs));
  #endif
  #if defined(__SAM3X8E__)
  csport  = digitalPinToPort(_cs);
  rsport  = digitalPinToPort(_rs);
  #endif
  #ifndef SPARK_CORE
  cspinmask = digitalPinToBitMask(_cs);
  rspinmask = digitalPinToBitMask(_rs);
  #endif
  if(hwSPI) { // Using hardware SPI
    SPI.begin();
    #ifdef __AVR__
    SPI.setClockDivider(SPI_CLOCK_DIV4); // 4 MHz (half speed)
    //Due defaults to 4mHz (clock divider setting of 21)
    #endif
    #if defined(__SAM3X8E__)
    SPI.setClockDivider(21); // 4 MHz
    //Due defaults to 4mHz (clock divider setting of 21), but we'll set it anyway
    #endif
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    } else {
      pinMode(_sclk, OUTPUT);
      pinMode(_sid , OUTPUT);
      #ifdef __AVR__
      clkport   = portOutputRegister(digitalPinToPort(_sclk));
      dataport  = portOutputRegister(digitalPinToPort(_sid));
      #endif
      #if defined(__SAM3X8E__)
      clkport   = digitalPinToPort(_sclk);
      dataport  = digitalPinToPort(_sid);
      #endif
      #ifndef SPARK_CORE
      clkpinmask  = digitalPinToBitMask(_sclk);
      datapinmask = digitalPinToBitMask(_sid);
      #endif

      #ifdef __AVR__
      *clkport   &= ~clkpinmask;
      *dataport  &= ~datapinmask;
      #endif
      #if defined(__SAM3X8E__)
    clkport ->PIO_CODR  |=  clkpinmask; // Set control bits to LOW (idle)
    dataport->PIO_CODR  |=  datapinmask; // Signals are ACTIVE HIGH
    #endif
    #if defined(SPARK_CORE)
    digitalWrite(_sclk, LOW);
    digitalWrite(_sid, LOW);
    #endif
  }

  // toggle RST low to reset; CS low so it'll listen to us
  #ifdef __AVR__
  *csport &= ~cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  csport ->PIO_CODR  |=  cspinmask; // Set control bits to LOW (idle)
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_cs, LOW);
  #endif
  if (_rst) {
    pinMode(_rst, OUTPUT);
    digitalWrite(_rst, HIGH);
    delay(500);
    digitalWrite(_rst, LOW);
    delay(500);
    digitalWrite(_rst, HIGH);
    delay(500);
  }

  if(cmdList) commandList(cmdList);
}


// Initialization for ST7735B screens
void Adafruit_ST7735::initB(void) {
  commonInit(Bcmd);
}


// Initialization for ST7735R screens (green or red tabs)
void Adafruit_ST7735::initR() {
  commonInit(Rcmd1);
  commandList(Rcmd2green);
  colstart = 2;
  rowstart = 1;
  commandList(Rcmd3);
}


void Adafruit_ST7735::setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1,
  uint8_t y1) {

  writecommand(ST7735_CASET); // Column addr set
  writedata(0x00);
  writedata(x0+colstart);   // XSTART
  writedata(0x00);
  writedata(x1+colstart);   // XEND

  writecommand(ST7735_RASET); // Row addr set
  writedata(0x00);
  writedata(y0+rowstart);   // YSTART
  writedata(0x00);
  writedata(y1+rowstart);   // YEND

  writecommand(ST7735_RAMWR); // write to RAM
}


void Adafruit_ST7735::pushColor(uint16_t color) {
  #ifdef __AVR__
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  rsport->PIO_SODR |=  rspinmask;
  csport->PIO_CODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);
  #endif

  spiwrite(color >> 8);
  spiwrite(color);

  #ifdef __AVR__
  *csport |= cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  csport->PIO_SODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_cs, HIGH);
  #endif
}

void Adafruit_ST7735::drawPixel(int16_t x, int16_t y, uint16_t color) {

  if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;

  setAddrWindow(x,y,x+1,y+1);

  #ifdef __AVR__
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  rsport->PIO_SODR |=  rspinmask;
  csport->PIO_CODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);
  #endif

  spiwrite(color >> 8);
  spiwrite(color);

  #ifdef __AVR__
  *csport |= cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  csport->PIO_SODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_cs, HIGH);
  #endif
}


void Adafruit_ST7735::drawFastVLine(int16_t x, int16_t y, int16_t h,
  uint16_t color) {

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((y+h-1) >= _height) h = _height-y;
  setAddrWindow(x, y, x, y+h-1);

  uint8_t hi = color >> 8, lo = color;
  #ifdef __AVR__
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  rsport->PIO_SODR |=  rspinmask;
  csport->PIO_CODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);
  #endif

  while (h--) {
    spiwrite(hi);
    spiwrite(lo);
  }
  #ifdef __AVR__
  *csport |= cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  csport->PIO_SODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_cs, HIGH);
  #endif
}


void Adafruit_ST7735::drawFastHLine(int16_t x, int16_t y, int16_t w,
  uint16_t color) {

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  setAddrWindow(x, y, x+w-1, y);

  uint8_t hi = color >> 8, lo = color;
  #ifdef __AVR__
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  rsport->PIO_SODR |=  rspinmask;
  csport->PIO_CODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);
  #endif

  while (w--) {
    spiwrite(hi);
    spiwrite(lo);
  }
  #ifdef __AVR__
  *csport |= cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  csport->PIO_SODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_cs, HIGH);
  #endif
}



void Adafruit_ST7735::fillScreen(uint16_t color) {
  fillRect(0, 0,  _width, _height, color);
}



// fill a rectangle
void Adafruit_ST7735::fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
 uint16_t color) {

  // rudimentary clipping (drawChar w/big text requires this)
  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  setAddrWindow(x, y, x+w-1, y+h-1);

  uint8_t hi = color >> 8, lo = color;
  #ifdef __AVR__
  *rsport |=  rspinmask;
  *csport &= ~cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  rsport->PIO_SODR |=  rspinmask;
  csport->PIO_CODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_rs, HIGH);
  digitalWrite(_cs, LOW);
  #endif

  for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
      spiwrite(hi);
      spiwrite(lo);
    }
  }

  #ifdef __AVR__
  *csport |= cspinmask;
  #endif
  #if defined(__SAM3X8E__)
  csport->PIO_SODR  |=  cspinmask;
  #endif
  #if defined(SPARK_CORE)
  digitalWrite(_cs, HIGH);
  #endif
}


// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t Adafruit_ST7735::Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

void Adafruit_ST7735::setRotation(uint8_t m) {

  writecommand(ST7735_MADCTL);
  rotation = m % 4; // can't be higher than 3
  switch (rotation) {
    case 0:
    writedata(MADCTL_MX | MADCTL_MY | MADCTL_BGR);
    _width  = ST7735_TFTWIDTH;
    _height = ST7735_TFTHEIGHT;
    break;
    case 1:
    writedata(MADCTL_MY | MADCTL_MV | MADCTL_BGR);
    _width  = ST7735_TFTHEIGHT;
    _height = ST7735_TFTWIDTH;
    break;
    case 2:
    writedata(MADCTL_BGR);
    _width  = ST7735_TFTWIDTH;
    _height = ST7735_TFTHEIGHT;
    break;
    case 3:
    writedata(MADCTL_MX | MADCTL_MV | MADCTL_BGR);
    _width  = ST7735_TFTHEIGHT;
    _height = ST7735_TFTWIDTH;
    break;
  }
}


void Adafruit_ST7735::invertDisplay(boolean i) {
  writecommand(i ? ST7735_INVON : ST7735_INVOFF);
}

#define cs   4
#define dc   2
#define rst  3  // you can also connect this to the Arduino reset

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

#define LED_INDIGO     0x4B0082
#define LED_GREEN      0x00FF00
#define LED_RED        0xFF0000
#define LED_WHITE      0xFFFFFF
#define LED_WEAK_WHITE 0x222222
#define PIXEL_PIN      D5
#define PIXEL_COUNT    10
#define PIXEL_TYPE     WS2812B

Adafruit_NeoPixel leds = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int currentNum = -1;
int targetNum  = -1;

int currentHours    = -1;
int currentHundreds = -1;
int currentTens     = -1;
int currentOnes     = -1;

int leftEdge  = 0;
int rightEdge = 128;

const int digitHeight = 55;

int minutes   = 50;
int userInput = 4;

long lastUserInput       = millis() - 5000;
long lastFreeBusyRequest = millis() - 5000;
long lastButtonPress     = millis() - 5000;
long lastButtonRelease   = millis() - 5000;

const int buttonPin = D6;
int buttonState     = 0;

const int encoderPin1    = D0;
const int encoderPin2    = D1;
volatile int lastEncoded = 0;

bool waitingForReserver  = false;
bool waitingForFreeBusy  = false;
bool receivedStatus      = false;
bool connectedToInternet = false;

String previousStatus = "";
String currentStatus  = "free";       // "free"       or "busy"
String mode           = "showStatus"; // "showStatus" or "userInput"

String identifier = String(rand());

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup(void)
{
  Serial.begin(9600);

  tft.initR();
  tft.setRotation(2);
  blankOutScreen();

  pinMode(buttonPin, INPUT);

  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);

  leds.begin();
  leds.setBrightness(100);
  setAll(0);

  drawWord("Connecting", 5, 50, 2, BLUE);

  for (int i=0; i<3; i++) {
    if (!Spark.connected()) {
      Spark.connect();

      for (int j=0; j<5; j++) {
        cylon(LED_INDIGO, 60);
      }
    }
  }

  setAll(0);
  blankOutScreen();

  if (Spark.connected()) {
    drawWord("Connected!", 5, 50, 2, WHITE);
    connectedToInternet = true;
  } else {
    drawWord("Offline", 25, 50, 2, WHITE);
  }

  delay(1000);
  blankOutScreen();

  RGB.control(true);
  RGB.color(0, 0, 0);

  attachInterrupt(encoderPin1, handleRotation, CHANGE);
  attachInterrupt(encoderPin2, handleRotation, CHANGE);
}

void loop() {
  if (currentStatus == "busy") checkButtonHold();
  if (currentStatus == "free") checkButtonPress();

  setLights();

  if (mode == "userInput") {
    drawUserInput();
    checkInputTimeout();
  } else if (mode == "showStatus") {
    drawStatus();
  }
}

void handleRotation() {
  if (currentStatus == "busy" || minutes <= 5) return;

  if (mode == "showStatus") {
    blankOutScreen();
    mode = "userInput";
  }

  int MSB = digitalRead(encoderPin1);
  int LSB = digitalRead(encoderPin2);

  int encoded = (MSB << 1) | LSB;
  int sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1011) userInput--;
  if (sum == 0b1000) userInput++;

  if (userInput < 4)       userInput = 4;
  if (userInput > minutes) userInput = minutes;

  lastEncoded = encoded;
  lastUserInput = millis();
}

void checkButtonPress() {
  buttonState = digitalRead(buttonPin);

  if (
    buttonState == HIGH                 &&
    (millis() - lastButtonPress) > 5000 &&
    mode == "userInput"                 &&
    userInput > 4
  ) {
    handleButtonPress();
  }
}

void checkButtonHold() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) lastButtonRelease = millis();
  if (millis() > lastButtonRelease && millis() - lastButtonRelease > 2000) {
    if (connectedToInternet) {
      Spark.publish("graba/buttonPress", "free", 60, PRIVATE);
    }

    currentStatus = "free";
    minutes       = 49;
    userInput     = 4;
    blankOutScreen();
  }
}

void checkInputTimeout() {
  if ((millis() - lastUserInput) > 5000) {
    blankOutScreen();
    userInput = 4;
    mode = "showStatus";
  }
}

void handleButtonPress() {
  if (connectedToInternet) {
    Spark.publish("graba/buttonPress", "booked", 60, PRIVATE);
  }

  lastButtonRelease = millis() + 2000;
  lastButtonPress   = millis();
  mode              = "showStatus";
  currentStatus     = "busy";
  minutes           = userInputInFives();

  blankOutScreen();
}

int userInputInFives() {
  int guess = (userInput / 5) * 5;

  if (((minutes / 5) * 5) == guess) {
    return userInput;
  } else {
    return guess;
  }
}

void sadTimes() {
}

void setLights() {
  if (mode == "userInput") {
    float percent = (1.0 * userInputInFives() / minutes);

    for (int i=0; i<PIXEL_COUNT; i++) {
      if (i < (percent * PIXEL_COUNT)) {
        leds.setPixelColor(i, LED_WHITE);
      } else {
        leds.setPixelColor(i, LED_WEAK_WHITE);
      }
    }
    leds.show();
  } else if (mode == "showStatus") {
    if (currentStatus == "free") {
      setAll(LED_GREEN);
    } else {
      setAll(LED_RED);
    }
  }
}

void drawUserInput() {
  drawSlidingBar();
  drawNumber(userInputInFives(), GREEN);
}

void drawSlidingBar() {
  int barWidth = (1.0 * userInputInFives() / minutes) * 96;

  tft.drawRect(15, 25, 98, 20, WHITE);

  tft.fillRect(16,            26, barWidth,      18, WHITE);
  tft.fillRect(16 + barWidth, 26, 96 - barWidth, 18, BLACK);
}

void drawStatus() {
  drawAvailability();
  drawNumber(minutes, statusColor());
}

void drawAvailability() {
  if (previousStatus == currentStatus) return;

  if (currentStatus == "free") {
    drawWord("Available", 12, 30, 2, statusColor());
  } else {
    drawWord("Busy", 30, 25, 3, statusColor());
  }

  previousStatus = currentStatus;
}

uint16_t statusColor() {
  return (currentStatus == "free") ? GREEN : RED;
}

void drawNumber(int num, uint16_t color) {
  if (currentNum == num) return;

  targetNum = num;
  prepareScreen();

  if (targetNum >= 120) {
    setEdges(13, 121);
    drawHours(color);
  } else if (targetNum >= 100) {
    setEdges(13, 121);
    drawHundreds(color);
  } else if (targetNum >= 10) {
    setEdges(31, 103);
    drawTens(color);
  } else {
    setEdges(49, 85);
    drawOnes(color);
  }

  currentNum = targetNum;
}

void prepareScreen() {
  if (changeAround(10) || changeAround(100) || changeAround(120)) {
    resetScreen();
  }
}

void blankOutScreen() {
  resetScreen();
  tft.fillScreen(BLACK);
}

void resetScreen() {
  // clear out tracking variables
  previousStatus  = "";
  currentNum      = -1;
  currentHours    = -1;
  currentHundreds = -1;
  currentTens     = -1;
  currentOnes     = -1;

  // black out existing writing/numbers
  tft.fillRect(leftEdge, digitHeight, rightEdge - leftEdge, 42, BLACK);
}

bool changeAround(int pivot) {
  return ((currentNum >= pivot && targetNum <  pivot)
    ||    (currentNum <  pivot && targetNum >= pivot));
}

void setEdges(int left, int right) {
  leftEdge  = left;
  rightEdge = right;
}

void drawHours(uint16_t color) {
  int hours = targetNum / 60;

  if (hours != currentHours) {
    currentHours = hours;

    drawDigit(hours, 13, digitHeight, color);
    tft.setCursor(49, digitHeight + 10);
    tft.setTextColor(color);
    tft.setTextSize(4);
    tft.print("hrs");
  }
}

void drawHundreds(uint16_t color) {
  int hundreds = (targetNum / 100) % 10;
  int tens     = (targetNum / 10)  % 10;
  int ones     = (targetNum / 1)   % 10;

  if (hundreds != currentHundreds) {
    currentHundreds = hundreds;
    drawDigit(hundreds, 13, digitHeight, color);
  }

  if (tens != currentTens) {
    currentTens = tens;
    drawDigit(tens, 49, digitHeight, color);
  }

  if (ones != currentOnes) {
    currentOnes = ones;
    drawDigit(ones, 85, digitHeight, color);
  }
}

void drawTens(uint16_t color) {
  int tens = (targetNum / 10) % 10;
  int ones = (targetNum / 1)  % 10;

  if (tens != currentTens) {
    currentTens = tens;
    drawDigit(tens, 31, digitHeight, color);
  }

  if (ones != currentOnes) {
    currentOnes = ones;
    drawDigit(ones, 67, digitHeight, color);
  }
}

void drawOnes(uint16_t color) {
  int ones = targetNum % 10;

  if (ones != currentOnes) {
    currentOnes = ones;
    drawDigit(ones, 49, digitHeight, color);
  }
}

void drawDigit(int digit, int x, int y, uint16_t color) {
  tft.fillRect(x, y, 36, 42, BLACK);

  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(6);
  tft.println(digit);
}

void drawWord(String word, int x, int y, int size, uint16_t color) {
  tft.fillRect(12, 25, 110, 25, BLACK);

  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.println(word);
}

void cylon(unsigned long color, byte wait) {
  const byte weight = 4;

  byte red   = (color & 0xFF0000) >> 16;
  byte green = (color & 0x00FF00) >> 8;
  byte blue  = (color & 0x0000FF);

  // Start at closest LED, and move to the outside
  for (int i=0; i<=PIXEL_COUNT-1; i++)
  {
    setAll(0);
    leds.setPixelColor(i, red, green, blue);  // Set the bright middle eye
    // Now set two eyes to each side to get progressively dimmer
    for (int j=1; j<2; j++)
    {
      if (i-j >= 0)
        leds.setPixelColor(i-j, red/(weight*j), green/(weight*j), blue/(weight*j));
      if (i-j <= PIXEL_COUNT)
        leds.setPixelColor(i+j, red/(weight*j), green/(weight*j), blue/(weight*j));
    }
    leds.show();  // Turn the LEDs on
    delay(wait);  // Delay for visibility
  }
}

void setAll(unsigned long color) {
  for (int i=0; i<PIXEL_COUNT; i++) {
    leds.setPixelColor(i, color);
  }

  leds.show();
}

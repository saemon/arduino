#ifndef AQMON_LCD_H
#define AQMON_LCD_H

#include <inttypes.h>
#include "Print.h"
#include "AqmonCommons.h"
#include "AqmonSipo595.h"


// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#define LCD_COMMANDWORD 0x0000
#define LCD_DATAWORD 0x8000
#define LCD_ENABLEUP 0x4000
#define LCD_4BITMASK 0xFE00
#define LCD_8BITMASK 0xFFE0

class AqmonLCD : public Print {
  public:
    void init(
      byte lcdCols,  // no of columns supported by LCD
      byte lcdRows, // no of rows supported by LCD
      byte lcdMode, //4 ot 8 bit lcd data bus
      byte lcdBusOffset, //bitmask for which 5 bits of sipo bus drive the LCD, must be contiguos and in LCD pin order
      AqmonSipo595 *sipo
    );

    void begin(uint8_t cols, uint8_t rows, uint8_t mode);
    void clear();
    void home();

    void noDisplay();
    void display();
    void noBlink();
    void blink();
    void noCursor();
    void cursor();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void leftToRight();
    void rightToLeft();
    void autoscroll();
    void noAutoscroll();

    void setRowOffsets(int row1, int row2, int row3, int row4);
    void createChar(uint8_t, uint8_t[]);
    void setCursor(uint8_t, uint8_t);
    virtual size_t write(uint8_t);
    void command(uint8_t);
    void command(uint8_t,boolean);

    using Print::write;
  private:
    void send(uint8_t,boolean);
    void send(uint8_t,boolean,boolean);

    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;

    uint8_t _initialized;
    uint8_t _numlines;
    uint8_t _rows;
    uint8_t _cols;
    uint8_t _busOffset;
    uint8_t _mode;
    uint8_t _row_offsets[4];

    AqmonSipo595 *sipo;
};


#endif

#ifndef FIRMWARE_INC_BITMAPS_H_
#define FIRMWARE_INC_BITMAPS_H_

#define BLANK_CHAR  "  "
#define SOLID_CHAR  "B "

#define SMALL_DIGIT_ROWS  7
#define LARGE_DIGIT_ROWS  12

static char large_numbers[][LARGE_DIGIT_ROWS] = {
    {
        // 0
        0b00111100,
        0b01111110,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // 1
        0b00011000,
        0b00111000,
        0b01111000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b11111111,
        0b11111111
    },
    {
        // 2
        0b00111100,
        0b01111110,
        0b11000011,
        0b00000011,
        0b00000111,
        0b00001110,
        0b00011100,
        0b00111000,
        0b01110000,
        0b11100000,
        0b11111111,
        0b11111111
    },
    {
        // 3
        0b00111100,
        0b01111110,
        0b11000011,
        0b00000011,
        0b00000011,
        0b00111110,
        0b00111110,
        0b00000011,
        0b00000011,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // 4
        0b00000110,
        0b00001110,
        0b00011110,
        0b00111110,
        0b01110110,
        0b11100110,
        0b11000110,
        0b11111111,
        0b11111111,
        0b00000110,
        0b00000110,
        0b00000110
    },
    {
        // 5
        0b11111111,
        0b11111111,
        0b11000000,
        0b11000000,
        0b11000000,
        0b11111100,
        0b01111110,
        0b00000011,
        0b00000011,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // 6
        0b00111100,
        0b01111110,
        0b11000011,
        0b11000000,
        0b11000000,
        0b11111110,
        0b11111111,
        0b11000011,
        0b11000011,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // 7
        0b11111111,
        0b11111111,
        0b00000011,
        0b00000011,
        0b00000110,
        0b00000110,
        0b00001100,
        0b00001100,
        0b00011000,
        0b00011000,
        0b00110000,
        0b00110000
    },
    {
        // 8
        0b00111100,
        0b01111110,
        0b11000011,
        0b11000011,
        0b11000011,
        0b01111110,
        0b01111110,
        0b11000011,
        0b11000011,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // 9
        0b00111100,
        0b01111110,
        0b11000011,
        0b11000011,
        0b11000011,
        0b01111111,
        0b01111111,
        0b00000011,
        0b00000011,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // 10
        0b11111111,
        0b11111111,
        0b00000111,
        0b00001110,
        0b00011100,
        0b00111000,
        0b01110000,
        0b11100000,
        0b11000000,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // 11
        0b00111100,
        0b01111110,
        0b11000011,
        0b11000000,
        0b11000000,
        0b01111100,
        0b01111100,
        0b11000000,
        0b11000000,
        0b11000011,
        0b01111110,
        0b00111100
    },
    {
        // .
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b00001100,
        0b00001100
    },
    {
        // :
        0b00000000,
        0b00000000,
        0b00000000,
        0b00001100,
        0b00001100,
        0b00000000,
        0b00000000,
        0b00001100,
        0b00001100,
        0b00000000,
        0b00000000,
        0b00000000
    },
};

// digits need to be stored as 8 col wide so leave the first 2 cols as 0s
static char small_numbers[][SMALL_DIGIT_ROWS] = {
    {
        // 0
        0b0001110,
        0b0010001,
        0b0010001,
        0b0010001,
        0b0010001,
        0b0010001,
        0b0001110
    },
    {
        // 1
        0b0000100,
        0b0001100,
        0b0010100,
        0b0000100,
        0b0000100,
        0b0000100,
        0b0011111
    },
    {
        // 2
        0b0001110,
        0b0010001,
        0b0000001,
        0b0000010,
        0b0000100,
        0b0001000,
        0b0011111
    },
    {
        // 3
        0b0001110,
        0b0010001,
        0b0000001,
        0b0000110,
        0b0000001,
        0b0010001,
        0b0001110
    },
    {
        // 4
        0b0000010,
        0b0000110,
        0b0001010,
        0b0010010,
        0b0011111,
        0b0000010,
        0b0000010
    },
    {
        // 5
        0b0011111,
        0b0010000,
        0b0011110,
        0b0000001,
        0b0000001,
        0b0010001,
        0b0001110
    },
    {
        // 6
        0b0001110,
        0b0010000,
        0b0010000,
        0b0011110,
        0b0010001,
        0b0010001,
        0b0001110
    },
    {
        // 7
        0b0011111,
        0b0000001,
        0b0000001,
        0b0000010,
        0b0000100,
        0b0000100,
        0b0000100
    },
    {
        // 8
        0b0001110,
        0b0010001,
        0b0010001,
        0b0001110,
        0b0010001,
        0b0010001,
        0b0001110
    },
    {
        // 9
        0b0001110,
        0b0010001,
        0b0010001,
        0b0001111,
        0b0000001,
        0b0000001,
        0b0001110
    },
    {
        // 10
        0b0011111,
        0b0000010,
        0b0000100,
        0b0001000,
        0b0010000,
        0b0010001,
        0b0001110
    },
    {
        // 11
        0b0001110,
        0b0010001,
        0b0010000,
        0b0001100,
        0b0010000,
        0b0010001,
        0b0001110
    },
    {
        // .
        0b0000000,
        0b0000000,
        0b0000000,
        0b0000000,
        0b0000000,
        0b0000000,
        0b0000010
    },
    {
        // :
        0b0000000,
        0b0000000,
        0b0000010,
        0b0000000,
        0b0000010,
        0b0000000,
        0b0000000
    },
};

// digits need to be stored as 8 col wide so right align the symbols like with the small numbers
// all digits bottom-right aligned
static char small_symbols[][SMALL_DIGIT_ROWS] = {
    {
        // D
        0b00000000,
        0b00000000,
        0b00000110,
        0b00000101,
        0b00000101,
        0b00000101,
        0b00000110
    },
    {
        // S
        0b00000000,
        0b00000000,
        0b00000011,
        0b00000100,
        0b00000111,
        0b00000001,
        0b00000110
    },
    {
        // sun
        0b00000100,
        0b00010101,
        0b00001110,
        0b00011011,
        0b00001110,
        0b00010101,
        0b00000100
    },
    {
        // moon
        0b00001110,
        0b00010100,
        0b00101000,
        0b00101000,
        0b00100100,
        0b00010011,
        0b00001110
    },
    {
        // A
        0b00000000,
        0b00000000,
        0b00000010,
        0b00000101,
        0b00000111,
        0b00000101,
        0b00000101
    },
    {
        // T
        0b00000000,
        0b00000000,
        0b00000111,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000010
    },
    {
        // AM
        0b00000000,
        0b00000000,
        0b00100101,
        0b01010111,
        0b01110111,
        0b01010101,
        0b01010101
    },
    {
        // PM
        0b00000000,
        0b00000000,
        0b01110101,
        0b01010111,
        0b01110111,
        0b01000101,
        0b01000101
    },
    {
        // !
        0b00000000,
        0b00000000,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000000,
        0b00000010
    },
};

#endif  // FIRMWARE_INC_CLOCK_TYPES_H_

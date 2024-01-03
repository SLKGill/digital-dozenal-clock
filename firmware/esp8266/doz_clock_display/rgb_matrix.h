#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H

#include <Arduino.h>

#define PIXEL_COLS 64
#define PIXEL_ROWS 32

<<<<<<< HEAD
#define TOTAL_BYTES (PIXEL_COLS*PIXEL_ROWS/8)

#define LARGE_REGION_HEIGHT 12
#define LARGE_REGION_SIZE   (PIXEL_COLS*LARGE_REGION_HEIGHT/8)
#define SMALL_REGION_HEIGHT 7
#define SMALL_REGION_SIZE   (PIXEL_COLS*SMALL_REGION_HEIGHT/8)
=======
typedef enum {
  Low,
  Med,
  High
}BrightnessLevel;
>>>>>>> 96ed25f (Display working with ESP8266)

typedef enum {
  Red,
  Green,
  Blue,
  White,
  Yellow,
  Cyan,
  Magenta,
  Black
}PixelColour;

typedef struct {
  uint8_t height;
  uint8_t width;
  uint8_t topleft_x;
  uint8_t topleft_y;
  PixelColour colour;
  uint8_t is_active;
<<<<<<< HEAD
  uint8_t *pixel_buffer;
  uint8_t pixel_buffer_size;
}PixelRegion;

static uint8_t top_region_buffer[SMALL_REGION_SIZE];
static PixelRegion top_region = {
  .height = SMALL_REGION_HEIGHT,
  .width = PIXEL_COLS,
  .topleft_x = 0,
  .topleft_y = 1,
  .colour = Red,
  .is_active = 1,
  .pixel_buffer = top_region_buffer,
  .pixel_buffer_size = SMALL_REGION_SIZE,
};

static uint8_t mid_region_buffer[LARGE_REGION_SIZE];
static PixelRegion mid_region = {
  .height = LARGE_REGION_HEIGHT,
  .width = PIXEL_COLS,
  .topleft_x = 0,
  .topleft_y = 10,
  .colour = Green,
  .is_active = 1,
  .pixel_buffer = mid_region_buffer,
  .pixel_buffer_size = LARGE_REGION_SIZE,
};

static uint8_t bot_region_buffer[SMALL_REGION_SIZE];
static PixelRegion bot_region = {
  .height = SMALL_REGION_HEIGHT,
  .width = PIXEL_COLS,
  .topleft_x = 0,
  .topleft_y = 24,
  .colour = Blue,
  .is_active = 1,
  .pixel_buffer = bot_region_buffer,
  .pixel_buffer_size = SMALL_REGION_SIZE,
=======
}PixelRegion;

static PixelRegion region1 = {
  .height = PIXEL_ROWS,
  .width = PIXEL_COLS,
  .topleft_x = 0,
  .topleft_y = 0,
  .colour = Red,
  .is_active = 1
>>>>>>> 96ed25f (Display working with ESP8266)
};

void RgbMatrix_Init();
void RgbMatrix_Update();

<<<<<<< HEAD
void RgbMatrix_Clear();
void RgbMatrix_SetBrightness(uint8_t level);
=======
void RgbMatrix_DisplayOff(void);
void RgbMatrix_DisplayOn(void);
void RgbMatrix_SetBrightness(BrightnessLevel level);
>>>>>>> 96ed25f (Display working with ESP8266)

void RgbMatrix_RegionOff(PixelRegion *region);
void RgbMatrix_RegionOn(PixelRegion *region);
void RgbMatrix_RegionSetColour(PixelRegion *region, PixelColour colour);
<<<<<<< HEAD
void RgbMatrix_RegionWritePixels(PixelRegion *region);
=======
void RgbMatrix_RegionWritePixels(PixelRegion *region, uint8_t pixels[]);
>>>>>>> 96ed25f (Display working with ESP8266)


#endif /* RGB_MATRIX_H */

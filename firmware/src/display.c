/*
 * display.c
 * Software to operate the clock display
 *
 *  Created on: Jan 08, 2024
 *      Author: Matt L.
 */

#include "display.h"
#include "bitmaps.h"

#define NUM_SHOWTIME_STATES 4

#define DEFAULT_FORMAT      TRAD_24H
#define DEFAULT_BRIGHTNESS  HIGH_BRIGHTNESS

#define LARGE_BITMAP_SIZE 96
#define SMALL_BITMAP_SIZE 56

typedef enum row_number_t
{
    ROW_1 = 1,
    ROW_2 = 2,
    ROW_3 = 3
} RowNumber;

typedef struct bitmap{
    RowNumber   num;
    uint8_t     *p_bitmap;
    uint8_t     bitmap_size;
} Bitmap;

typedef enum state_code_t
{
    STATE_OFF,
    STATE_SHOWTIME123,
    STATE_SHOWTIME23,
    STATE_SHOWTIME12,
    STATE_SHOWTIME2,
    STATE_SETTIME,
    STATE_SETTIMER,
    STATE_SETALARM
} StateCode;

typedef struct state_t
{
    StateCode state_code;

    void (*entry)(Display *ctx);
    void (*update)(Display *ctx);
    void (*exit)(Display *ctx);
} State;

typedef struct state_machine_t {
    State *curr_state;
    Display *ctx;
} DisplayFSM;

/*
    Private function definitions
*/
// State machine functions
static void Default_Entry(Display *ctx);
static void Default_Update(Display *ctx);
static void Default_Exit(Display *ctx);
static void Off_Entry(Display *ctx);
static void Off_Update(Display *ctx);
static void ShowTime123_Entry(Display *ctx);
static void ShowTime23_Entry(Display *ctx);
static void ShowTime12_Entry(Display *ctx);
static void ShowTime2_Entry(Display *ctx);
static void ShowTime_Update(Display *ctx);
static void SetTime_Entry(Display *ctx);
static void SetTime_Update(Display *ctx);
static void SetTimer_Entry(Display *ctx);
static void SetTimer_Update(Display *ctx);
static void SetAlarm_Entry(Display *ctx);
static void SetAlarm_Update(Display *ctx);

static void transition(State *next);

// Bitmap creation functions
static void displayChar(Bitmap *row_bitmap, uint8_t char_index,
        uint8_t digit[]);
static void displayTime(Bitmap *row_bitmap, uint32_t time_ms);
static void blinkDigit(Bitmap *row_bitmap, uint8_t char_index);
/*
    State definitions
*/
State s_off =
{
    .state_code = STATE_OFF,
    .entry = Default_Entry,
    .update = Default_Update,
    .exit = Default_Exit,
};

State s_show_time123 =
{
    .state_code = STATE_SHOWTIME123,
    .entry = ShowTime123_Entry,
    .update = ShowTime_Update,
    .exit = Default_Exit,
};

State s_show_time23 =
{
    .state_code = STATE_SHOWTIME23,
    .entry = ShowTime23_Entry,
    .update = ShowTime_Update,
    .exit = Default_Exit,
};

State s_show_time12 =
{
    .state_code = STATE_SHOWTIME12,
    .entry = ShowTime12_Entry,
    .update = ShowTime_Update,
    .exit = Default_Exit,
};

State s_show_time2 =
{
    .state_code = STATE_SHOWTIME2,
    .entry = ShowTime2_Entry,
    .update = ShowTime_Update,
    .exit = Default_Exit,
};

State s_set_time =
{
    .state_code = STATE_SETTIME,
    .entry = SetTime_Entry,
    .update = SetTime_Update,
    .exit = Default_Exit,
};

State s_set_timer =
{
    .state_code = STATE_SETTIMER,
    .entry = SetTimer_Entry,
    .update = SetTimer_Update,
    .exit = Default_Exit,
};

State s_set_alarm =
{
    .state_code = STATE_SETALARM,
    .entry = SetAlarm_Entry,
    .update = SetAlarm_Update,
    .exit = Default_Exit,
};

/*
    Bitmap definitions
*/
static uint8_t row1_pixels[SMALL_BITMAP_SIZE];
Bitmap row1_bitmap = {
    .num = ROW_1,
    .p_bitmap = row1_pixels,
    .bitmap_size = SMALL_BITMAP_SIZE
};

static uint8_t row2_pixels[LARGE_BITMAP_SIZE];
Bitmap row2_bitmap = {
    .num = ROW_2,
    .p_bitmap = row2_pixels,
    .bitmap_size = LARGE_BITMAP_SIZE
};

static uint8_t row3_pixels[SMALL_BITMAP_SIZE];
Bitmap row3_bitmap = {
    .num = ROW_3,
    .p_bitmap = row3_pixels,
    .bitmap_size = SMALL_BITMAP_SIZE,
};

/*
    Private variables
*/
static DisplayFSM g_fsm = {0};
static State *show_time_states[NUM_SHOWTIME_STATES] =
{
    &s_show_time123,
    &s_show_time23,
    &s_show_time12,
    &s_show_time2
};
static uint8_t show_time_index = 0;
volatile uint8_t blink_state = 0;

/*
    Public functions
*/
ClockStatus Display_Init(Display *self, ExternVars *vars)
{
    // Check for NULL pointers
    if (self->displayOff == NULL ||
            self->displayOn == NULL ||
            self->setBrightness == NULL ||
            self->setBitmap == NULL ||
            self->setColour == NULL ||
            self->show == NULL ||
            self->hide == NULL)
    {
        return CLOCK_FAIL;
    }
    self->clock_vars = vars;
    self->time_format = DEFAULT_FORMAT;
    self->brightness = DEFAULT_BRIGHTNESS;
    g_fsm.ctx = self;
    g_fsm.curr_state = &s_off;
    show_time_index = 0;

    // Set brightness
    g_fsm.ctx->setBrightness(g_fsm.ctx->brightness);

    // Start FSM
    g_fsm.curr_state->entry(g_fsm.ctx);
    return CLOCK_OK;
}

void Display_Update(void)
{
    g_fsm.curr_state->update(g_fsm.ctx);
}

void Display_PeriodicCallback(void)
{
    // Update status of any blinking digits
    blink_state = !blink_state;
}

void Display_Off(void)
{
    // Check if currently in a ShowTime state
    if (g_fsm.curr_state->state_code ==
        show_time_states[show_time_index]->state_code)
    {
        transition(&s_off);
    }
}

void Display_On(void)
{
    // Check if currently in Off state
    if (g_fsm.curr_state->state_code == STATE_OFF)
    {
        transition(show_time_states[show_time_index]);
    }
}

void Display_ToggleMode(void)
{
    // Check if currently in a ShowTime state
    if (g_fsm.curr_state->state_code ==
        show_time_states[show_time_index]->state_code)
    {
        // Transition to the next ShowTime state
        show_time_index = (show_time_index + 1) % NUM_SHOWTIME_STATES;
        transition(show_time_states[show_time_index]);
    }
}

void Display_SetTime(void)
{
    // Check if currently in a ShowTime state
    if (g_fsm.curr_state->state_code ==
        show_time_states[show_time_index]->state_code)
    {
        transition(&s_set_time);
    }
}

void Display_SetTimer(void)
{
    // Check if currently in a ShowTime state
    if (g_fsm.curr_state->state_code ==
        show_time_states[show_time_index]->state_code)
    {
        transition(&s_set_timer);
    }
}

void Display_SetAlarm(void)
{
    // Check if currently in a ShowTime state
    if (g_fsm.curr_state->state_code ==
        show_time_states[show_time_index]->state_code)
    {
        transition(&s_set_alarm);
    }
}

void Display_ShowTime(void)
{
    // Check if currently in a valid Set state
    if (g_fsm.curr_state->state_code == STATE_SETALARM
        || g_fsm.curr_state->state_code == STATE_SETTIMER
        || g_fsm.curr_state->state_code == STATE_SETTIME)
    {
        transition(show_time_states[show_time_index]);
    }
}

void Display_SetFormat(TimeFormats format)
{
    g_fsm.ctx->time_format = format;
}

void Display_SetBrightness(BrightnessLevels brightness)
{
    g_fsm.ctx->brightness = brightness;
    g_fsm.ctx->setBrightness(g_fsm.ctx->brightness);
}

/*
    Private functions
*/
void Default_Entry(Display *ctx)
{
    UNUSED(ctx);
}
void Default_Update(Display *ctx)
{
    UNUSED(ctx);
}
void Default_Exit(Display *ctx)
{
    UNUSED(ctx);
}
static void Off_Entry(Display *ctx)
{
    ctx->displayOff();
}
static void Off_Update(Display *ctx)
{
    UNUSED(ctx);
}
static void ShowTime123_Entry(Display *ctx)
{
    ctx->show(ROW_1);
    ctx->show(ROW_2);
    ctx->show(ROW_3);
}
static void ShowTime23_Entry(Display *ctx)
{
    ctx->hide(ROW_1);
    ctx->show(ROW_2);
    ctx->show(ROW_3);
}
static void ShowTime12_Entry(Display *ctx)
{
    ctx->show(ROW_1);
    ctx->show(ROW_2);
    ctx->hide(ROW_3);
}
static void ShowTime2_Entry(Display *ctx)
{
    ctx->hide(ROW_1);
    ctx->show(ROW_2);
    ctx->hide(ROW_3);
}
static void ShowTime_Update(Display *ctx)
{
    UNUSED(ctx);
}
static void SetTime_Entry(Display *ctx)
{
    ctx->show(ROW_1);
    ctx->show(ROW_2);
    ctx->show(ROW_3);
}
static void SetTime_Update(Display *ctx)
{
    UNUSED(ctx);
}
static void SetTimer_Entry(Display *ctx)
{
    ctx->show(ROW_1);
    ctx->show(ROW_2);
    ctx->show(ROW_3);
}
static void SetTimer_Update(Display *ctx)
{
    UNUSED(ctx);
}
static void SetAlarm_Entry(Display *ctx)
{
    ctx->show(ROW_1);
    ctx->show(ROW_2);
    ctx->show(ROW_3);
}
static void SetAlarm_Update(Display *ctx)
{
    UNUSED(ctx);
}

void transition(State *next)
{
    g_fsm.curr_state->exit(g_fsm.ctx);
    g_fsm.curr_state = next;
    g_fsm.curr_state->entry(g_fsm.ctx);
}

void printDisplay() {
    printf("Printing Rows >>>>>>>>>>>>>>>>>>>\n\n");

    unsigned columnCounter = 0;
    printf("Row 1\n\n");
    for (unsigned i = 0; i < SMALL_BITMAP_SIZE; ++i) {
        for (int b = 7; b >= 0; --b) {
            if ((row1_bitmap.p_bitmap[i] >> b) & 0x1) {
                printf("o");
            } else {
                printf(".");
            }
        }
        ++columnCounter;
        if (columnCounter >= 8) {
            columnCounter = 0;
            printf("\n");
        }
    }
    printf("\n");

    columnCounter = 0;
    printf("Row 2\n\n");
    for (unsigned i = 0; i < LARGE_BITMAP_SIZE; ++i) {
        for (int b = 7; b >= 0; --b) {
            if ((row2_bitmap.p_bitmap[i] >> b) & 0x1) {
                printf("o");
            } else {
                printf(".");
            }
        }
        ++columnCounter;
        if (columnCounter >= 8) {
            columnCounter = 0;
            printf("\n");
        }
    }
    printf("\n");

    columnCounter = 0;
    printf("Row 3\n\n");
    for (unsigned i = 0; i < SMALL_BITMAP_SIZE; ++i) {
        for (int b = 7; b >= 0; --b) {
            if ((row3_bitmap.p_bitmap[i] >> b) & 0x1) {
                printf("o");
            } else {
                printf(".");
            }
        }
        ++columnCounter;
        if (columnCounter >= 8) {
            columnCounter = 0;
            printf("\n");
        }
    }
    printf("\n");
}

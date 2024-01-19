#ifndef FIRMWARE_INC_CLOCK_TYPES_H_
#define FIRMWARE_INC_CLOCK_TYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void) x

// Generic error code return type
typedef enum clockstatus
{
    CLOCK_OK,
    CLOCK_FAIL
} ClockStatus;

#endif  // FIRMWARE_INC_CLOCK_TYPES_H_

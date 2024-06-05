
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"
#include "touchscreen.h"

#define TERMINAL_HEIGHT 40
#define TERMINAL_WIDTH  138

// sizings
#define SIZE_SMALL_Y   8
#define SIZE_SMALL_X  32
#define SIZE_MEDIUM_Y 16
#define SIZE_MEDIUM_X 64
#define SIZE_LARGE_Y  30 // 128 bytes extra for page write, name
#define SIZE_LARGE_X 128

#define BUFF_LEN 14

#define CHAR_DELETE 127
#define CHAR_RETURN 13

// FSM
typedef enum {
    TITLE,
    SIZING,
    CANVAS,
    SAVE,
    BROWSER,
    OPTIONS,
    PREVIEW
} state_t;

void Error_Handler(void);
void SystemClock_Config(void);
void Move_Cursor(status_t status);
void On_Click(state_t *state, status_t status, uint8_t *cursor_allowed);
void On_Press(state_t *state, uint8_t *cursor_allowed);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

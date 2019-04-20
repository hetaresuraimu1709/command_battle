#pragma once

typedef enum KEY_STATE_ENUM
{
    KEY_STATE_OFF = 0,
    KEY_STATE_PUSHDOWN,
    KEY_STATE_PRESSED,
    KEY_STATE_PULLUP
}KEY_STATE_ENUM;

void initKey();
void updateKey();
KEY_STATE_ENUM getKey(unsigned char keyCode);

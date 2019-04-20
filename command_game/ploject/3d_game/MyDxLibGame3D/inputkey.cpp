#include "inputkey.h"
#include <DxLib.h>

KEY_STATE_ENUM key[256];
char           keyState[2][256];

int nowKey, prevKey;

void initKey()
{
    int i, j;

    for(i = 0; i < 2; i++)
    {
        for (j = 0; j < 256; j++)
        {
            keyState[i][j] = 0;
            key[j] = KEY_STATE_OFF;
        }
    }
    nowKey = 0; prevKey = 1;

}

void updateKey()
{
    // 現在のキーと一つ前のフレームのキー状態を入れ替える
    nowKey ^= 1;
    prevKey = nowKey ^ 1;

    // キー状態取得
    GetHitKeyStateAll(keyState[nowKey]);

    //
    for (int i = 0; i < 256; i++)
    {
        char nowInput = keyState[nowKey][i];
        char prevInput = keyState[prevKey][i];

        if (nowInput)
        {
            //現在押されている

            //前のフレームも押されていた？
            if (prevInput)
            {
                key[i] = KEY_STATE_PRESSED; // 押されっぱなし
            }
            else 
			{
                key[i] = KEY_STATE_PUSHDOWN;// 今押された
            }

        }
        else
        {
            // 現在キーは押されていない

            // 前のフレームで押されていた？
            if (prevInput)
            {
                key[i] = KEY_STATE_PULLUP;
            }
            else {
                key[i] = KEY_STATE_OFF;
            }
        }
    }
}



KEY_STATE_ENUM getKey(unsigned char keyCode)
{
    return key[keyCode];
}


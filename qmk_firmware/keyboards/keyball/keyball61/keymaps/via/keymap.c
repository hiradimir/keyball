/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_DEL   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_INT3  ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    MO(1)    , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_RBRC  ,              KC_NUHS, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
    _______  , KC_LCTL  , KC_LALT  , KC_LGUI,LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1),    KC_BSPC,LT(2,KC_ENT),LT(1,KC_LNG2),KC_RGUI, _______ , KC_RALT  , KC_PSCR
  ),

  [1] = LAYOUT_universal(
    S(KC_ESC), S(KC_1)  , KC_LBRC  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                                  KC_EQL   , S(KC_6)  ,S(KC_QUOT), S(KC_8)  , S(KC_9)  ,S(KC_INT1),
    S(KC_DEL), S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                                  S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,S(KC_INT3),
    S(KC_TAB), S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                                  S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L)  , KC_QUOT  , S(KC_2)  ,
    _______  , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,S(KC_RBRC),           S(KC_NUHS), S(KC_N)  , S(KC_M)  ,S(KC_COMM), S(KC_DOT),S(KC_SLSH),S(KC_RSFT),
    _______  ,S(KC_LCTL),S(KC_LALT),S(KC_LGUI), _______  , _______  , _______  ,            _______  , _______  , _______  ,S(KC_RGUI), _______  , S(KC_RALT), _______
  ),

  [2] = LAYOUT_universal(
    SSNP_FRE , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    SSNP_VRT , _______  , KC_7     , KC_8     , KC_9     , _______  ,                                  _______  , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , KC_F12   ,
    SSNP_HOR , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                                  KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,            S(KC_9)  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , KC_0     , KC_DOT   , _______  , _______  , _______  ,             KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EE_CLR   ,            EE_CLR   , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    return state;
}

// 明度の上限を抑える
void set_color(int index, uint8_t hsvred, uint8_t hsvgreen, uint8_t hsvblue) {
    HSV hsv = (HSV){hsvred, hsvgreen, hsvblue};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    if (hsv.s > rgb_matrix_get_sat()) {
        hsv.s = rgb_matrix_get_sat();
    }
    if (hsv.h > rgb_matrix_get_hue()) {
        hsv.h = rgb_matrix_get_hue();
    }
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
      // RGB_MATRIX_SOLID_COLOR(1)のときに、自作LEDロジックが動くようにする
    if (rgb_matrix_get_mode() != 1) {
       return true;
    }
    
    uint8_t current_layer = get_highest_layer(layer_state | default_layer_state);

    // for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
    //     for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
    //         uint8_t index = g_led_config.matrix_co[row][col];

    //         if (index % 2 == 0 && index >= led_min && index < led_max && index != NO_LED &&
    //             keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
    //                 rgb_matrix_set_color(index, RGB_GREEN);
    //         }
    //     }
    // }
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t i = g_led_config.matrix_co[row][col];

            if(i < led_min && i >= led_max && i == NO_LED) {
                continue;
            }

            // if((i >= 27 && i <= 32) || (i >= 0 && i <= 5)) {
            //     set_color(i, HSV_PINK);
            //     continue;
            // }
            uint16_t keycode = keymap_key_to_keycode(current_layer, (keypos_t){col,row});

            if(keycode >= KC_A && keycode <= KC_Z) {
                set_color(i, HSV_AZURE);
            } else if(keycode >= KC_1 && keycode <= KC_0) {
                set_color(i, HSV_BLUE);
            } else if(keycode >= KC_ENTER && keycode <= KC_CAPS_LOCK) {
                set_color(i, HSV_CHARTREUSE);
            } else if(keycode >= KC_F1 && keycode <= KC_F12) {
                set_color(i, HSV_MAGENTA);
            } else if(keycode >= KC_PRINT_SCREEN && keycode <= KC_PAGE_DOWN) {
                set_color(i, HSV_CORAL);
            } else if(keycode >= KC_RIGHT && keycode <= KC_UP) {
                set_color(i, HSV_CYAN);
            } else if(keycode >= QK_KB_0 && keycode <= QK_KB_31) {
                set_color(i, HSV_PINK);
            } else if (keycode == KC_NO ){
                set_color(i, HSV_OFF);
            } else {
                set_color(i, HSV_GOLD);
            }
        }
    }
    return false;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif


#ifdef RGB_MATRIX_ENABLE
#define NL NO_LED
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  /*
  {24, 19, 14,  9,  5,  1,            66,     62,     58,     54, 49, 44}, \
  {25, 20, 15, 10,  6,  2,            67,     63,     59,     55, 50, 45}, \
  {26, 21, 16, 11,  7,  3,            68,     64,     60,     56, 51, 46}, \
  {27, 22, 17, 12,  8,  4,  0,    70, 69,     65,     61,     57, 52, 47}, \
  {28, 23, 18, 13, 34, 35, 36,    37, 38, NO_LED, NO_LED, NO_LED, 53, 48} \ 
  // {29, 30, 31 ,32, 33,                    39, 40, 41, 42, 43}   //underglows 
  */
  {24, 19, 14, NL,  9,  5,  1, NL}, \
  {25, 20, 15, NL, 10,  6,  2, NL}, \
  {26, 21, 16, NL, 11,  7,  3, NL}, \
  {27, 22, 17, NL, 12,  8,  4,  0}, \
  {28, 23, 18, NL, 13, 34, 35, 36}, \
  {44, 49, 54, NL, 58, 62, 66, NL}, \
  {45, 50, 55, NL, 59, 63, 67, NL}, \
  {46, 51, 56, NL, 60, 64, 68, NL}, \
  {47, 52, 57, NL, 61, 65, 69, 70}, \
  {48, 53, NL, NL, NL, NL, 38, 37} \
}, {
  // LED Index to Physical Position
  // {x,y}: x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION , y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
{84,48}	, //0
{70,0}	, //1
{70,16}	, //2
{70,32}	, //3
{70,48}	, //4
{56,0}	, //5
{56,16}	, //6
{56,32}	, //7
{56,48}	, //8
{42,0}	, //9
{42,16}	, //10
{42,32}	, //11
{42,48}	, //12
{42,64}	, //13
{28,0}	, //14
{28,16}	, //15
{28,32}	, //16
{28,48}	, //17
{28,64}	, //18
{14,0}	, //19
{14,16}	, //20
{14,32}	, //21
{14,48}	, //22
{14,64}	, //23
{0,0}	, //24
{0,16}	, //25
{0,32}	, //26
{0,48}	, //27
{0,64}	, //28
{0,0}	, //29
{0,0}	, //30
{0,0}	, //31
{0,0}	, //32
{0,0}	, //33
{56,64}	, //34
{70,64}	, //35
{84,64}	, //36
{126,64}	, //37
{140,64}	, //38
{0,0}	, //39
{0,0}	, //40
{0,0}	, //41
{0,0}	, //42
{0,0}	, //43
{210,0}	, //44
{210,16}	, //45
{210,32}	, //46
{210,48}	, //47
{210,64}	, //48
{196,0}	, //49
{196,16}	, //50
{196,32}	, //51
{196,48}	, //52
{196,64}	, //53
{182,0}	, //54
{182,16}	, //55
{182,32}	, //56
{182,48}	, //57
{168,0}	, //58
{168,16}	, //59
{168,32}	, //60
{168,48}	, //61
{154,0}	, //62
{154,16}	, //63
{154,32}	, //64
{154,48}	, //65
{140,0}	, //66
{140,16}	, //67
{140,32}	, //68
{140,48}	, //69
{126,48}	, //70
{0,0}	, //71
{0,0}	, //72
{0,0}	, //73
}, {
  // LED Index to Flag
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT	,
LED_FLAG_KEYLIGHT ,
LED_FLAG_NONE	,
LED_FLAG_NONE	,
LED_FLAG_NONE		
} };

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgb_matrix_reload_from_eeprom();
}

#undef LD
#endif
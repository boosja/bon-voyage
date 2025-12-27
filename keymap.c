#include QMK_KEYBOARD_H
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
};

enum layers {
  _MAC_BASE = 0,
  _MAC_SYMBOLS = 1,
  _MAC_MISC = 2,
  _LINUX_BASE = 3,
  _LINUX_SYMBOLS = 4,
  _LINUX_MISC = 5,
};

// This is a hack!
// The layers and keycodes are arbitrary, but needs to be unique combinations,
// so that the switch-statement in process_record_user keeps working.
#define DUAL_FUNC_0 LT(5, KC_V)
#define DUAL_FUNC_1 LT(11, KC_F19)
#define DUAL_FUNC_2 LT(3, KC_H)
#define DUAL_FUNC_3 LT(2, KC_0)
#define DUAL_FUNC_4 LT(1, KC_F9)
#define DUAL_FUNC_5 LT(14, KC_A)
#define DUAL_FUNC_6 LT(11, KC_W)
#define DUAL_FUNC_7 LT(12, KC_G)
#define DUAL_FUNC_8 LT(12, KC_8)
#define DUAL_FUNC_9 LT(3, KC_F5)
#define DUAL_FUNC_10 LT(3, KC_F4)

#define LCTL_A MT(MOD_LCTL, KC_A)
#define LCTL_F MT(MOD_LCTL, KC_F)
#define LCTL_PREV MT(MOD_LCTL, KC_MEDIA_PREV_TRACK)
#define LCTL_PLAY MT(MOD_LCTL, KC_MEDIA_PLAY_PAUSE)
#define RCTL_J MT(MOD_RCTL, KC_J)
#define LALT_S MT(MOD_LALT, KC_S)
#define LALT_NEXT MT(MOD_LALT, KC_MEDIA_NEXT_TRACK)
#define RALT_L MT(MOD_RALT, KC_L)
#define LSFT_D MT(MOD_LSFT, KC_D)
#define LSFT_STOP MT(MOD_LSFT, KC_MEDIA_STOP)
#define RSFT_K MT(MOD_RSFT, KC_K)
#define LSUPER_SPACE MT(MOD_LGUI, KC_SPACE)
#define RSUPER_ENTER MT(MOD_RGUI, KC_ENTER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Mac Layers
  [_MAC_BASE] = LAYOUT_voyager(
    NRW_LESS_MAC,   KC_1,          KC_2,     KC_3,     KC_4,     KC_5,                KC_6,   KC_7,     KC_8,       KC_9,      KC_0,          NRW_BSLS_MAC,
    KC_TAB,         KC_Q,          KC_W,     KC_E,     KC_R,     KC_T,                KC_Y,   KC_U,     KC_I,       KC_O,      KC_P,          NRW_SLSH,
    KC_BSPC,        LCTL_A,        LALT_S,   LSFT_D,   LCTL_F,   KC_G,                KC_H,   RCTL_J,   RSFT_K,     RALT_L,    DUAL_FUNC_1,   NRW_AT_MAC,
    KC_ESCAPE,      DUAL_FUNC_0,   KC_X,     KC_C,     KC_V,     KC_B,                KC_N,   KC_M,     NRW_COMM,   NRW_DOT,   NRW_MINS,      KC_HYPR,
                                        LSUPER_SPACE,   TT(_MAC_MISC),                OSL(_MAC_SYMBOLS),   RSUPER_ENTER
  ),
  [_MAC_SYMBOLS] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_F1,         KC_F2,         KC_F3,          KC_F4,          KC_F5,                       KC_F6,      KC_F7,                        KC_F8,         KC_F9,          KC_F10,        KC_F11,
    KC_GRAVE,       NRW_EXLM,      NRW_AT_MAC,    NRW_LBRC,       NRW_RBRC,       NRW_APOS_MAC,                NRW_AE,     NRW_PLUS,                     NRW_MINS,      NRW_EQL,        NRW_ARNG,      KC_F12,
    KC_TRANSPARENT, DUAL_FUNC_2,   DUAL_FUNC_3,   DUAL_FUNC_4,    DUAL_FUNC_5,    NRW_GRV_MAC,                 NRW_QUES,   MT(MOD_RCTL, NRW_LESS_MAC),   DUAL_FUNC_6,   DUAL_FUNC_7,    DUAL_FUNC_8,   KC_TRANSPARENT,
    KC_TRANSPARENT, NRW_PERC,      NRW_CIRC,      NRW_LCBR_MAC,   NRW_RCBR_MAC,   NRW_TILD,                    NRW_AMPR,   NRW_LABK,                     NRW_RABK,      NRW_BSLS_MAC,   NRW_OSTR,      KC_TRANSPARENT,
                                                           TO(_MAC_BASE),   KC_TRANSPARENT,                    TO(_MAC_MISC),   KC_TRANSPARENT
  ),
  [_MAC_MISC] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR, RGB_MODE_FORWARD,  RGB_SLD,         RGB_VAD,        RGB_VAI,                        KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_AUDIO_MUTE,  KC_TRANSPARENT,                 KC_PAGE_UP,     KC_HOME,            KC_UP,          KC_END,         KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LCTL_PREV,          LALT_NEXT,         LSFT_STOP,       LCTL_PLAY,      KC_TRANSPARENT,                 KC_PGDN,        KC_LEFT,            KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,    HSV_0_255_255,   HSV_74_255_255, HSV_169_255_255,                KC_TRANSPARENT, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                             DUAL_FUNC_9,   KC_TRANSPARENT,                 TO(_MAC_SYMBOLS),   KC_TRANSPARENT
  ),
  // Linux layers
  [_LINUX_BASE] = LAYOUT_voyager(
    NRW_LESS_MAC,   KC_1,          KC_2,     KC_3,     KC_4,     KC_5,                KC_6,   KC_7,     KC_8,       KC_9,      KC_0,          NRW_BSLS_MAC,
    KC_TAB,         KC_Q,          KC_W,     KC_E,     KC_R,     KC_T,                KC_Y,   KC_U,     KC_I,       KC_O,      KC_P,          NRW_SLSH,
    KC_BSPC,        LCTL_A,        LALT_S,   LSFT_D,   LCTL_F,   KC_G,                KC_H,   RCTL_J,   RSFT_K,     RALT_L,    DUAL_FUNC_1,   NRW_AT_MAC,
    KC_ESCAPE,      DUAL_FUNC_0,   KC_X,     KC_C,     KC_V,     KC_B,                KC_N,   KC_M,     NRW_COMM,   NRW_DOT,   NRW_MINS,      KC_HYPR,
                                      LSUPER_SPACE,   TT(_LINUX_MISC),                OSL(_LINUX_SYMBOLS),   RSUPER_ENTER
  ),
  [_LINUX_SYMBOLS] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_F1,         KC_F2,         KC_F3,          KC_F4,          KC_F5,                       KC_F6,      KC_F7,                        KC_F8,         KC_F9,          KC_F10,        KC_F11,
    KC_GRAVE,       NRW_EXLM,      NRW_AT_MAC,    NRW_LBRC,       NRW_RBRC,       NRW_APOS_MAC,                NRW_AE,     NRW_PLUS,                     NRW_MINS,      NRW_EQL,        NRW_ARNG,      KC_F12,
    KC_TRANSPARENT, DUAL_FUNC_2,   DUAL_FUNC_3,   DUAL_FUNC_4,    DUAL_FUNC_5,    NRW_GRV_MAC,                 NRW_QUES,   MT(MOD_RCTL, NRW_LESS_MAC),   DUAL_FUNC_6,   DUAL_FUNC_7,    DUAL_FUNC_8,   KC_TRANSPARENT,
    KC_TRANSPARENT, NRW_PERC,      NRW_CIRC,      NRW_LCBR_MAC,   NRW_RCBR_MAC,   NRW_TILD,                    NRW_AMPR,   NRW_LABK,                     NRW_RABK,      NRW_BSLS_MAC,   NRW_OSTR,      KC_TRANSPARENT,
                                                         TO(_LINUX_BASE),   KC_TRANSPARENT,                    TO(_LINUX_MISC),   KC_TRANSPARENT
  ),
  [_LINUX_MISC] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR, RGB_MODE_FORWARD,  RGB_SLD,         RGB_VAD,        RGB_VAI,                        KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_AUDIO_MUTE,  KC_TRANSPARENT,                 KC_PAGE_UP,     KC_HOME,            KC_UP,          KC_END,         KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, LCTL_PREV,          LALT_NEXT,         LSFT_STOP,       LCTL_PLAY,      KC_TRANSPARENT,                 KC_PGDN,        KC_LEFT,            KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,    HSV_0_255_255,   HSV_74_255_255, HSV_169_255_255,                KC_TRANSPARENT, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB),   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                            DUAL_FUNC_10,   KC_TRANSPARENT,                 TO(_LINUX_SYMBOLS),   KC_TRANSPARENT
  ),
};

extern rgb_config_t rgb_matrix_config;

RGB hsv_to_rgb_with_value(HSV hsv) {
  RGB rgb = hsv_to_rgb( hsv );
  float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
  return (RGB){ f * rgb.r, f * rgb.g, f * rgb.b };
}

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [1] = { {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255} },

    [2] = { {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192} },

    [3] = { {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175}, {141,233,175} },

    [4] = { {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255}, {42,255,255} },

    [5] = { {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192}, {0,255,192} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb_with_value(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
    return false;
  }
  if (!keyboard_config.disable_layer_led) {
    switch (biton32(layer_state)) {
      case 0:
        set_layer_color(0);
        break;
      case 1:
        set_layer_color(1);
        break;
      case 2:
        set_layer_color(2);
        break;
      case 3:
        set_layer_color(3);
        break;
      case 4:
        set_layer_color(4);
        break;
      case 5:
        set_layer_color(5);
        break;
      default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
          rgb_matrix_set_color_all(0, 0, 0);
        }
    }
  } else {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
      rgb_matrix_set_color_all(0, 0, 0);
    }
  }

  return true;
}

void my_tap_hold_register_code16(uint16_t kc_tap, uint16_t kc_held, keyrecord_t *record) {
  if (record->tap.count > 0) {
    if (record->event.pressed) {
      register_code16(kc_tap);
    } else {
      unregister_code16(kc_tap);
    }
  } else {
    if (record->event.pressed) {
      register_code16(kc_held);
    } else {
      unregister_code16(kc_held);
    }
  }
}

void my_dual_func_layer_key(uint16_t layer, uint16_t kc_held, keyrecord_t *record) {
  if (record->tap.count > 0) {
    if (record->event.pressed) {
      layer_move(layer);
    } else {
      layer_move(layer);
    }
  } else {
    if (record->event.pressed) {
      register_code16(kc_held);
    } else {
      unregister_code16(kc_held);
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DUAL_FUNC_0:
      my_tap_hold_register_code16(KC_Z, KC_CAPS, record);
      return false;
    case DUAL_FUNC_1:
      my_tap_hold_register_code16(NRW_COLN, KC_RIGHT_GUI, record);
      return false;
    case DUAL_FUNC_2:
      my_tap_hold_register_code16(NRW_HASH, KC_LEFT_CTRL, record);
      return false;
    case DUAL_FUNC_3:
      my_tap_hold_register_code16(NRW_DLR_MAC, KC_LEFT_ALT, record);
      return false;
    case DUAL_FUNC_4:
      my_tap_hold_register_code16(NRW_LPRN, KC_LEFT_SHIFT, record);
      return false;
    case DUAL_FUNC_5:
      my_tap_hold_register_code16(NRW_RPRN, KC_LEFT_CTRL, record);
      return false;
    case DUAL_FUNC_6:
      my_tap_hold_register_code16(NRW_DQUO, KC_RIGHT_SHIFT, record);
      return false;
    case DUAL_FUNC_7:
      my_tap_hold_register_code16(NRW_SLSH, KC_RIGHT_ALT, record);
      return false;
    case DUAL_FUNC_8:
      my_tap_hold_register_code16(NRW_ASTR, KC_RIGHT_GUI, record);
      return false;
    case DUAL_FUNC_9:
      my_dual_func_layer_key(_MAC_BASE, KC_LEFT_GUI, record);
      return false;
    case DUAL_FUNC_10:
      my_dual_func_layer_key(_LINUX_BASE, KC_LEFT_GUI, record);
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_0_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,255,255);
      }
      return false;
    case HSV_74_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(74,255,255);
      }
      return false;
    case HSV_169_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(169,255,255);
      }
      return false;
  }
  return true;
}

// OS detection
static os_variant_t current_os = OS_UNSURE;

bool process_detected_host_os_user(os_variant_t detected_os) {
    current_os = detected_os;

    if (detected_os == OS_MACOS) {
      set_single_persistent_default_layer(_MAC_BASE);
    } else if (detected_os == OS_LINUX) {
      set_single_persistent_default_layer(_LINUX_BASE);
    }
    return true;
}

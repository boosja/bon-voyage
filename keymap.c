#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_norwegian.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum layers {
  _MAC_BASE = 0,
  _MAC_SYMBS = 1,
  _MAC_MISC = 2,
  _LNX_BASE = 3,
  _LNX_SYMBS = 4,
  _LNX_MISC = 5,
};

// OS detection
static os_variant_t current_os = OS_UNSURE;

bool process_detected_host_os_user(os_variant_t detected_os) {
    current_os = detected_os;

    if (detected_os == OS_MACOS) {
      set_single_persistent_default_layer(_MAC_BASE);
    } else if (detected_os == OS_LINUX) {
      set_single_persistent_default_layer(_LNX_BASE);
    }
    return true;
}

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  NO_BTCK_LIVE,
};

// Mac specific keycodes
#define NO_AT_MAC KC_NUHS
#define NO_BSLS_MAC S(ALGR(KC_7))
#define NO_BTCK_MAC ALGR(KC_EQL)
#define NO_CIRC_MAC S(KC_RBRC)
#define NO_DLR_MAC S(KC_4)
#define NO_LCBR_MAC S(ALGR(KC_8))
#define NO_PIPE_MAC KC_NUBS
#define NO_QUOT_MAC KC_GRV
#define NO_RCBR_MAC S(ALGR(KC_9))
#define NO_TILD_MAC ALGR(KC_RBRC)

// This is a hack!
// The layers and keycodes are arbitrary, but needs to be unique combinations,
// so that the switch-statement in process_record_user keeps working,
// AND that the tap-hold-functionality works.
#define LCTL_HASH LT(3, KC_H)
#define LCTL_RPRN LT(14, KC_A)
#define LSFT_LPRN LT(1, KC_F9)
#define LALT_DLR LT(2, KC_0)
#define LALT_DLR_MAC LT(5, KC_V)
#define LGUI_MAC_BASE LT(3, KC_F5)
#define LGUI_LNX_BASE LT(3, KC_F4)
#define RSFT_DQUO LT(11, KC_W)
#define RALT_SLSH LT(12, KC_G)
#define RGUI_ASTR LT(12, KC_8)
#define RGUI_COLN LT(11, KC_F19)

// To shorter names:
#define LCTL_A MT(MOD_LCTL, KC_A)
#define LCTL_F MT(MOD_LCTL, KC_F)
#define LCTL_PREV MT(MOD_LCTL, KC_MEDIA_PREV_TRACK)
#define LCTL_PLAY MT(MOD_LCTL, KC_MEDIA_PLAY_PAUSE)
#define RCTL_J MT(MOD_RCTL, KC_J)
#define RCTL_QUOT MT(MOD_RCTL, NO_QUOT)
#define RCTL_QUOT_MAC MT(MOD_RCTL, NO_QUOT_MAC)
#define LALT_S MT(MOD_LALT, KC_S)
#define LALT_NEXT MT(MOD_LALT, KC_MEDIA_NEXT_TRACK)
#define RALT_L MT(MOD_RALT, KC_L)
#define LSFT_D MT(MOD_LSFT, KC_D)
#define LSFT_STOP MT(MOD_LSFT, KC_MEDIA_STOP)
#define RSFT_K MT(MOD_RSFT, KC_K)
#define LSUPER_SPACE MT(MOD_LGUI, KC_SPACE)
#define RSUPER_ENTER MT(MOD_RGUI, KC_ENTER)
#define TOG_LAYER_CLR TOGGLE_LAYER_COLOR
#define RGB_MODE_FWRD RGB_MODE_FORWARD

#define MY_AA NO_ARNG
#define MY_OE NO_OSTR

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Mac Layers
  [_MAC_BASE] = LAYOUT_voyager(
    NO_QUOT_MAC,   KC_1,          KC_2,          KC_3,          KC_4,          KC_5,                     KC_6,          KC_7,          KC_8,          KC_9,          KC_0,          NO_BSLS_MAC,
    KC_TAB,        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                     KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          NO_SLSH,
    KC_BSPC,       LCTL_A,        LALT_S,        LSFT_D,        LCTL_F,        KC_G,                     KC_H,          RCTL_J,        RSFT_K,        RALT_L,        RGUI_COLN,     NO_AT_MAC,
    KC_ESCAPE,     KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                     KC_N,          KC_M,          NO_COMM,       NO_DOT,        NO_MINS,       KC_HYPR,
                                                                LSUPER_SPACE,  TT(_MAC_MISC),            OSL(_MAC_SYMBS), RSUPER_ENTER
  ),
  [_MAC_SYMBS] = LAYOUT_voyager(
    _______,       KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,                    KC_F6,         KC_F7,         KC_F8,         KC_F9,         KC_F10,        KC_F11,
    KC_GRAVE,      NO_EXLM,       _______,       NO_LBRC,       NO_RBRC,       NO_PIPE_MAC,              NO_AE,         NO_PLUS,       NO_MINS,       NO_EQL,        MY_AA,         KC_F12,
    _______,       LCTL_HASH,     LALT_DLR_MAC,  LSFT_LPRN,     LCTL_RPRN,     NO_BTCK_MAC,              NO_QUES,       RCTL_QUOT_MAC, RSFT_DQUO,     RALT_SLSH,     RGUI_ASTR,     _______,
    _______,       NO_PERC,       NO_CIRC_MAC,   NO_LCBR_MAC,   NO_RCBR_MAC,   NO_TILD_MAC,              NO_AMPR,       NO_LABK,       NO_RABK,       NO_BSLS_MAC,   MY_OE,         _______,
                                                                TO(_MAC_BASE), _______,                  TO(_MAC_MISC), _______
  ),
  [_MAC_MISC] = LAYOUT_voyager(
    RGB_TOG,       TOG_LAYER_CLR, RGB_MODE_FWRD, RGB_SLD,       RGB_VAD,       RGB_VAI,                  _______,       _______,       _______,       _______,       _______,       QK_BOOT,
    _______,       _______,       KC_VOLD,       KC_VOLU,       KC_MUTE,       _______,                  KC_PAGE_UP,    KC_HOME,       KC_UP,         KC_END,        _______,       _______,
    _______,       LCTL_PREV,     LALT_NEXT,     LSFT_STOP,     LCTL_PLAY,     _______,                  KC_PGDN,       KC_LEFT,       KC_DOWN,       KC_RIGHT,      _______,       _______,
    _______,       _______,       _______,       HSV_0_255_255, HSV_74_255_255,HSV_169_255_255,          _______,       _______,       _______,       _______,       _______,       _______,
                                                                LGUI_MAC_BASE, _______,                  TO(_MAC_SYMBS), _______
  ),
  // Linux layers
  [_LNX_BASE] = LAYOUT_voyager(
    KC_LGUI,       KC_1,          KC_2,          KC_3,          KC_4,          KC_5,                     KC_6,          KC_7,          KC_8,          KC_9,          KC_0,          NO_BSLS,
    KC_TAB,        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                     KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          NO_SLSH,
    KC_BSPC,       LCTL_A,        LALT_S,        LSFT_D,        LCTL_F,        KC_G,                     KC_H,          RCTL_J,        RSFT_K,        RALT_L,        RGUI_COLN,     NO_AT,
    KC_ESCAPE,     KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,                     KC_N,          KC_M,          KC_COMM,       KC_DOT,        NO_MINS,       KC_HYPR,
                                                                LSUPER_SPACE,  TT(_LNX_MISC),            OSL(_LNX_SYMBS), RSUPER_ENTER
  ),
  [_LNX_SYMBS] = LAYOUT_voyager(
    _______,       KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,                    KC_F6,         KC_F7,         KC_F8,         KC_F9,         KC_F10,        KC_F11,
    _______,       NO_EXLM,       _______,       NO_LBRC,       NO_RBRC,       NO_PIPE,                  NO_AE,         NO_PLUS,       NO_MINS,       NO_EQL,        MY_AA,         KC_F12,
    _______,       LCTL_HASH,     LALT_DLR,      LSFT_LPRN,     LCTL_RPRN,     NO_BTCK_LIVE,             NO_QUES,       RCTL_QUOT,     RSFT_DQUO,     RALT_SLSH,     RGUI_ASTR,     _______,
    _______,       NO_PERC,       NO_CIRC,       NO_LCBR,       NO_RCBR,       NO_TILD,                  NO_AMPR,       NO_LABK,       NO_RABK,       NO_BSLS,       MY_OE,         _______,
                                                                TO(_LNX_BASE), _______,                  TO(_LNX_MISC), _______
  ),
  [_LNX_MISC] = LAYOUT_voyager(
    RGB_TOG,       TOG_LAYER_CLR, RGB_MODE_FWRD, RGB_SLD,       RGB_VAD,       RGB_VAI,                  _______,       _______,       _______,       _______,       _______,       QK_BOOT,
    _______,       _______,       KC_VOLD,       KC_VOLU,       KC_MUTE,       _______,                  KC_PAGE_UP,    KC_HOME,       KC_UP,         KC_END,        _______,       _______,
    _______,       LCTL_PREV,     LALT_NEXT,     LSFT_STOP,     LCTL_PLAY,     _______,                  KC_PGDN,       KC_LEFT,       KC_DOWN,       KC_RIGHT,      _______,       _______,
    _______,       _______,       _______,       HSV_0_255_255, HSV_74_255_255,HSV_169_255_255,          _______,       _______,       _______,       _______,       _______,       _______,
                                                                LGUI_LNX_BASE, _______,                  TO(_LNX_SYMBS), _______
  ),
};

const key_override_t delete_key_override = ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_BSPC, KC_DEL, ~0, MOD_MASK_CAG);

const key_override_t *key_overrides[] = {
	&delete_key_override
};

void register_modless_code16(keyrecord_t *record, uint16_t kc_key) {
  uint8_t current_mods = get_mods();
  if (record->event.pressed) {
    clear_mods();
    register_code16(kc_key);
    set_mods(current_mods);
  } else {
    clear_mods();
    unregister_code16(kc_key);
    set_mods(current_mods);
  }
}

void handle_dual_func(keyrecord_t *record, uint16_t kc_held, uint16_t kc_tap) {
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

void handle_dual_layer_func(keyrecord_t *record, uint16_t kc_held, uint16_t layer) {
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
    case KC_7:
      if (current_os == OS_LINUX) {
        if (get_mods() == MOD_BIT(KC_LALT)) {
          register_modless_code16(record, NO_PIPE); // Alt + 7 => |
          return false;
        } else if (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT))) {
          register_modless_code16(record, NO_BSLS); // Shift + Alt + 7 => backslash
          return false;
        }
      }
      return true;
    case KC_8:
      if (current_os == OS_LINUX) {
        if (get_mods() == MOD_BIT(KC_LALT)) {
          register_modless_code16(record, NO_LBRC); // Alt + 8 => [
          return false;
        } else if (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT))) {
          register_modless_code16(record, NO_LCBR); // Shift + Alt + 8 => {
          return false;
        }
      }
      return true;
    case KC_9:
      if (current_os == OS_LINUX) {
        if (get_mods() == MOD_BIT(KC_LALT)) {
          register_modless_code16(record, NO_RBRC); // Alt + 9 => ]
          return false;
        } else if (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT))) {
          register_modless_code16(record, NO_RCBR); // Shift + Alt + 9 => }
          return false;
        }
      }
      return true;
    case RGUI_COLN:
      handle_dual_func(record, KC_RIGHT_GUI, NO_COLN);
      return false;
    case LCTL_HASH:
      handle_dual_func(record, KC_LEFT_CTRL, NO_HASH);
      return false;
    case LALT_DLR:
      handle_dual_func(record, KC_LEFT_ALT, NO_DLR);
      return false;
    case LALT_DLR_MAC:
      handle_dual_func(record, KC_LEFT_ALT, NO_DLR_MAC);
      return false;
    case LSFT_LPRN:
      handle_dual_func(record, KC_LEFT_SHIFT, NO_LPRN);
      return false;
    case LCTL_RPRN:
      handle_dual_func(record, KC_LEFT_CTRL, NO_RPRN);
      return false;
    case RSFT_DQUO:
      handle_dual_func(record, KC_RIGHT_SHIFT, NO_DQUO);
      return false;
    case RALT_SLSH:
      handle_dual_func(record, KC_RIGHT_ALT, NO_SLSH);
      return false;
    case RGUI_ASTR:
      handle_dual_func(record, KC_RIGHT_GUI, NO_ASTR);
      return false;
    case LGUI_MAC_BASE:
      handle_dual_layer_func(record, KC_LEFT_GUI, _MAC_BASE);
      return false;
    case LGUI_LNX_BASE:
      handle_dual_layer_func(record, KC_LEFT_GUI, _LNX_BASE);
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
    case NO_BTCK_LIVE:
      if (record->event.pressed) {
        tap_code16(S(KC_EQL));
        tap_code(KC_SPC);
      }
      return false;
  }
  return true;
}

// !!! LIGHTS !!!
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
    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },
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

# Bon Voyage

The QMK keymap for the ZSA Voyager keyboard of Boosja.

Setup to support both Mac and Linux with norwegian layout.

## Setup

- Clone ZSA's [qmk firmware](https://github.com/zsa/qmk_firmware)
- Follow [the guide](https://docs.qmk.fm/newbs_getting_started)
- Clone this repo to `qmk_firmware/keyboards/zsa/voyager/keymaps/bon-voyage`

## Flash

- `qmk flash` will build and flash the keymap onto the keyboard
  - _Make sure the keyboard is in flashing mode_

## The stuff

I wanted to use my Voyager keyboard on both my work Macbook and my home laptop
running linux without having to remember all kinds of differences. For instance,
I very much prefer where Apple has placed `()[]{}` on the 8 and 9 keys. It just
makes sence to me.

And I use a norwegian layout, which also differs between a mac and a linux
system.

### OS detection

So first off I need to detect whether the keyboard is connected to a mac or
linux machine. Fortunately QMK supports this — just add `OS_DETECTION_ENABLE =
yes` to `rules.mk` and implement `process_detected_host_os_user`-function in
`keymap.c` and you're good to go.

Based on your layout you can configure the differences in keycodes in different
ways. I have chosen to create OS-specific layers with the downside of a bit of
code duplication. If there were just a few keychanges between the OSs I could
have handled it logically instead in `process_record_user`.

### The layers

As I said, I have created OS-specific layers.

```c
enum layers {
  _MAC_BASE = 0,
  _MAC_SYMBS = 1,
  _MAC_MISC = 2,
  _LNX_BASE = 3,
  _LNX_SYMBS = 4,
  _LNX_MISC = 5,
};
```

There are three layers per OS, a base layer with all the letters, a layer for
all symbols, and a layer with media controls, arrow-keys and other misc stuff.

### Homerow mods

All layers have homerow mods — if you hold down the `F`-key, for instance, it
functions as `ctrl`.

```c
// Left-hand side
// CTRL           ALT            SHIFT          CTRL
   LCTL_A,        LALT_S,        LSFT_D,        LCTL_F

// Right-hand side
// CTRL           SHIFT          ALT            CMD / WIN
   RCTL_J,        RSFT_K,        RALT_L,        RGUI_COLN
```

Since I use Emacs, `ctrl` is in high demand. That is why I have it double on
my left hand, to make it easier to press certain keycombinations in Emacs.

I also have a `GUI`-key available on both my thumbs to resemble where CMD is
placed on a mac.

On my right pinky I have colon for that peak Clojure-development. But this gets
a little tricky with homerow-mods. The same applies to my symbol-layer. You
would need to, when tapping the key, to virtually hold down shift and then press
the key, that in its shifted state, has the symbol you want. This is, of course,
not a problem when you just want the symbol, but when you add a modifier when
holding the key, the shiftet state doesn't work.

The way ZSA has handled this is with little hack. They define a key using `LT`
with an arbitrary layer and an arbitrary keycode (which must be valid layer and
keycodes) and then overwrites the logic in `process_record_user`:

```c
#define RGUI_COLN LT(11, KC_F19)

// ...

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // cases ...
    case RGUI_COLN:
      // is it tapped?
      if (record->tap.count > 0) {
        // is it pressed down?
        if (record->event.pressed) {
          register_code16(NO_COLN);
        // is it released?
        } else {
          unregister_code16(NO_COLN);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_RIGHT_GUI);
        } else {
          unregister_code16(KC_RIGHT_GUI);
        }
      }
      return false;
    // more cases ...
```

This way we can get homerow-mods even on keys with a shiftet keycode.

### Delete when shifting backspace with key overrides

[Documentation](https://docs.qmk.fm/features/key_overrides) for overriding keys.

Send delete when pressing `shift + backspace` is documented
[here](https://docs.qmk.fm/features/key_overrides#simple-example). This to avoid
using a key specifically for delete.

To have it register delete ONLY on shift (and not when any other mod is also
pressed) you can do it like so:

```c
ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, KC_BSPC, KC_DEL, ~0, MOD_MASK_CAG);
```

### Mac-styled symbols on the 7, 8 and 9 keys

This was harder to get to work than I expected it to be, but I figured it out in
the end. The hard part being using `shift` and `alt` for custom behavior: when
pressing `alt` on `8` send a `[` (a key that is behind a modifier, ALGR on a
norwegian layout).

I first tried [overriding the keys](https://docs.qmk.fm/features/key_overrides),
but the modifiers I held down were added to the "modded" key it should send. It
was modifier inception, and I couldn't figure out how to make it work.

I ended up doing it in `process_record_user` and manually removing and adding
the modifiers before and after sending the symbol-keycode:

```c
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // cases ...
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
    // more cases ...
```

### Caps Word

[Feature documentation](https://docs.qmk.fm/features/caps_word)

Caps Word is a variation of Capslock, where it will capitalize only the next
word.

To make Caps Word function with a norwegian layout, add:

```c
// Caps Word with norwegian layout:
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case NO_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case NO_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}
```

### Give me backtick now immediately, not after I press space!

On mac this is easy, just press `option` instead of `shift` on the backtick-key.

It's another story on linux. I have fixed this by creating a custom keycode, and
then send a backtick followed by a space logically:

```c
enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  NO_BTCK_LIVE, // <- this one
};

// other code

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // cases ...
    case NO_BTCK_LIVE:
      if (record->event.pressed) {
        tap_code16(S(KC_EQL));
        tap_code(KC_SPC);
      }
      return false;
    // more cases ...
```

`NO_BTCK_LIVE` as opposed to a dead key.

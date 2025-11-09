#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum {
    TD_SFT_CAPS,
};

// forward declarations
void sft_caps_finished(tap_dance_state_t *state, void *user_data);
void sft_caps_reset(tap_dance_state_t *state, void *user_data);

// tap dance action table
tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_caps_finished, sft_caps_reset),
};

// state keeper for whether we registered a hold-style shift
static bool sft_was_held = false;

void sft_caps_finished(tap_dance_state_t *state, void *user_data) {
    // single tap (count == 1)
    if (state->count == 1) {
        // if key is still held down at the end of the dance, treat as hold (regular shift)
        if (state->pressed) {
            // start acting like a normal held Shift
            register_code(KC_LSFT);
            sft_was_held = true;
        } else {
            // tapped: set as one-shot modifier (Shift)
            // set_oneshot_mods expects modifier bits, use MOD_BIT(KC_*) helper
            set_oneshot_mods(MOD_BIT(KC_LSFT));
        }
    }
    // double tap: Caps Lock
    else if (state->count == 2) {
        tap_code(KC_CAPS);
    }
    // (optional) more taps could be handled here
}

void sft_caps_reset(tap_dance_state_t *state, void *user_data) {
    // If we registered a hold-style Shift earlier, unregister it now
    if (sft_was_held) {
        unregister_code(KC_LSFT);
        sft_was_held = false;
    }
    // nothing to do for the one-shot: QMK manages oneshot lifecycle (and ONESHOT_TIMEOUT)
}



const uint16_t PROGMEM lesc[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM resc[] = {KC_J, KC_K, COMBO_END};
combo_t key_combos[] = {
    COMBO(lesc, KC_ESC),
    COMBO(resc, KC_ESC),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
// ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
    OSL(3),         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,               KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_DEL,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    OS_LALT,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,               KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        OS_RCTL,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,               KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLSH,        OSL(3),
// ╰───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┴───────────────┴───────────────╯
                                                    OS_LCTL,        LGUI_T(KC_ENT), LT(1, KC_TAB),      LT(2, KC_BSPC), MEH_T(KC_SPC),  TD(TD_SFT_CAPS)
//                                                 ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
    ),
    [1] = LAYOUT_split_3x6_3(
// ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
    KC_TRNS,        KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,            KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_BSPC,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    KC_TRNS,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,               KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRNS,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    KC_TRNS,        KC_TRNS,        KC_TILDE,       KC_GRAVE,       KC_LBRC,        KC_LCBR,            KC_RCBR,        KC_RBRC,        KC_QUOT,        KC_DQT,         KC_RGUI,        KC_TRNS,
// ╰───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┴───────────────┴───────────────╯
                                                    KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_TRNS,        KC_TRNS,        KC_TRNS
//                                                 ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
    ),
    [2] = LAYOUT_split_3x6_3(
// ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
    KC_TRNS,        KC_DEL,         KC_TRNS,        KC_UNDS,        KC_PLUS,        KC_TRNS,            KC_HOME,        KC_PGDN,        KC_PGUP,        KC_END,         KC_PIPE,        KC_TRNS,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_MINUS,       KC_EQUAL,       KC_TRNS,            KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_BSLS,        KC_TRNS,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    KC_TRNS,        KC_LT,          KC_GT,          KC_INSERT,      KC_PAUSE,       KC_SCLN,            KC_MPRV,        KC_MPLY,        KC_MNXT,        KC_VOLD,        KC_VOLU,        KC_TRNS,
// ╰───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┴───────────────┴───────────────╯
                                                    KC_TRNS,        KC_TRNS,        KC_TAB,             KC_TRNS,        KC_TRNS,        KC_TRNS
//                                                 ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
    ),
    [3] = LAYOUT_split_3x6_3(
// ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮   ╭───────────────┬───────────────┬───────────────┬───────────────┬───────────────┬───────────────╮
    KC_TRNS,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,              KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        QK_BOOT,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    KC_TRNS,        KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,             KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_SCRL,        KC_TRNS,
// ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤
    KC_TRNS,        KC_CAPS,        KC_TRNS,        KC_TRNS,        KC_F11,         KC_F12,             KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_PSCR,        KC_TRNS,
// ╰───────────────┴───────────────┴───────────────┼───────────────┼───────────────┼───────────────┤   ├───────────────├───────────────┼───────────────┼───────────────┴───────────────┴───────────────╯
                                                    KC_TRNS,        KC_TRNS,        KC_TAB,             KC_BSPC,        KC_ENT,         KC_TRNS
//                                                 ╰───────────────┴───────────────┴───────────────╯   ╰───────────────┴───────────────┴───────────────╯
    )
};


#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C


//
// Created by camilo on 9/17/23 11:44 <3ThomasBorregaardSorensen!!
//


#include "acme/constant/user_key.h"


///* XFree86 key code to SDL scancode mapping table
//   Sources:
//   - atKeyNames.h from XFree86 source code
//*/
///* *INDENT-OFF* */
//static const ::user::enum_key xfree86_key_table[] = {
//   /*  0 */    ::user::e_key_none,
//   /*  1 */    ::user::e_key_escape,
//   /*  2 */    ::user::e_key_1,
//   /*  3 */    ::user::e_key_2,
//   /*  4 */    ::user::e_key_3,
//   /*  5 */    ::user::e_key_4,
//   /*  6 */    ::user::e_key_5,
//   /*  7 */    ::user::e_key_6,
//   /*  8 */    ::user::e_key_7,
//   /*  9 */    ::user::e_key_8,
//   /*  10 */   ::user::e_key_9,
//   /*  11 */   ::user::e_key_0,
//   /*  12 */   ::user::e_key_minus,
//   /*  13 */   ::user::e_key_equal,
//   /*  14 */   ::user::e_key_back,
//   /*  15 */   ::user::e_key_tab,
//   /*  16 */   ::user::e_key_q,
//   /*  17 */   ::user::e_key_w,
//   /*  18 */   ::user::e_key_e,
//   /*  19 */   ::user::e_key_r,
//   /*  20 */   ::user::e_key_t,
//   /*  21 */   ::user::e_key_y,
//   /*  22 */   ::user::e_key_u,
//   /*  23 */   ::user::e_key_i,
//   /*  24 */   ::user::e_key_o,
//   /*  25 */   ::user::e_key_p,
//   /*  26 */   ::user::e_key_leftbracket,
//   /*  27 */   ::user::e_key_rightbracket,
//   /*  28 */   ::user::e_key_return,
//   /*  29 */   ::user::e_key_left_control,
//   /*  30 */   ::user::e_key_a,
//   /*  31 */   ::user::e_key_s,
//   /*  32 */   ::user::e_key_d,
//   /*  33 */   ::user::e_key_f,
//   /*  34 */   ::user::e_key_g,
//   /*  35 */   ::user::e_key_h,
//   /*  36 */   ::user::e_key_j,
//   /*  37 */   ::user::e_key_k,
//   /*  38 */   ::user::e_key_l,
//   /*  39 */   ::user::e_key_semicolon,
//   /*  40 */   ::user::e_key_apostrophe2,
//   /*  41 */   ::user::e_key_grave,
//   /*  42 */   ::user::e_key_left_shift,
//   /*  43 */   ::user::e_key_backslash2,
//   /*  44 */   ::user::e_key_z,
//   /*  45 */   ::user::e_key_x,
//   /*  46 */   ::user::e_key_c,
//   /*  47 */   ::user::e_key_v,
//   /*  48 */   ::user::e_key_b,
//   /*  49 */   ::user::e_key_n,
//   /*  50 */   ::user::e_key_m,
//   /*  51 */   ::user::e_key_comma,
//   /*  52 */   ::user::e_key_period2,
//   /*  53 */   ::user::e_key_slash,
//   /*  54 */   ::user::e_key_right_shift,
//   /*  55 */   ::user::e_key_numpad_multiply,
//   /*  56 */   ::user::e_key_left_alt,
//   /*  57 */   ::user::e_key_space,
//   /*  58 */   ::user::e_key_capslock,
//   /*  59 */   ::user::e_key_f1,
//   /*  60 */   ::user::e_key_f2,
//   /*  61 */   ::user::e_key_f3,
//   /*  62 */   ::user::e_key_f4,
//   /*  63 */   ::user::e_key_f5,
//   /*  64 */   ::user::e_key_f6,
//   /*  65 */   ::user::e_key_f7,
//   /*  66 */   ::user::e_key_f8,
//   /*  67 */   ::user::e_key_f9,
//   /*  68 */   ::user::e_key_f10,
//   /*  69 */   ::user::e_key_numlockclear,
//   /*  70 */   ::user::e_key_scrolllock,
//   /*  71 */   ::user::e_key_numpad_7,
//   /*  72 */   ::user::e_key_numpad_8,
//   /*  73 */   ::user::e_key_numpad_9,
//   /*  74 */   ::user::e_key_numpad_minus,
//   /*  75 */   ::user::e_key_numpad_4,
//   /*  76 */   ::user::e_key_numpad_5,
//   /*  77 */   ::user::e_key_numpad_6,
//   /*  78 */   ::user::e_key_numpad_plus,
//   /*  79 */   ::user::e_key_numpad_1,
//   /*  80 */   ::user::e_key_numpad_2,
//   /*  81 */   ::user::e_key_numpad_3,
//   /*  82 */   ::user::e_key_numpad_0,
//   /*  83 */   ::user::e_key_numpad_period,
//   /*  84 */   ::user::e_key_sysreq,
//   /*  85 */   ::user::e_key_mode,
//   /*  86 */   ::user::e_key_nonusbackslash,
//   /*  87 */   ::user::e_key_f11,
//   /*  88 */   ::user::e_key_f12,
//   /*  89 */   ::user::e_key_home,
//   /*  90 */   ::user::e_key_up,
//   /*  91 */   ::user::e_key_page_up,
//   /*  92 */   ::user::e_key_left,
//   /*  93 */   ::user::e_key_brightnessdown, /* on powerbook g4 / key_begin */
//   /*  94 */   ::user::e_key_right,
//   /*  95 */   ::user::e_key_end,
//   /*  96 */   ::user::e_key_down,
//   /*  97 */   ::user::e_key_page_down,
//   /*  98 */   ::user::e_key_insert,
//   /*  99 */   ::user::e_key_delete,
//   /*  100 */  ::user::e_key_numpad_enter,
//   /*  101 */  ::user::e_key_right_ctrl,
//   /*  102 */  ::user::e_key_pause,
//   /*  103 */  ::user::e_key_printscreen,
//   /*  104 */  ::user::e_key_numpad_divide,
//   /*  105 */  ::user::e_key_ralt,
//   /*  106 */  ::user::e_key_none, /* break */
//   /*  107 */  ::user::e_key_lgui,
//   /*  108 */  ::user::e_key_rgui,
//   /*  109 */  ::user::e_key_application,
//   /*  110 */  ::user::e_key_f13,
//   /*  111 */  ::user::e_key_f14,
//   /*  112 */  ::user::e_key_f15,
//   /*  113 */  ::user::e_key_f16,
//   /*  114 */  ::user::e_key_f17,
//   /*  115 */  ::user::e_key_international1, /* \_ */
//   /*  116 */  ::user::e_key_none, /* is translated to xk_iso_level3_shift by my x server, but i have no keyboard that generates this code, so i don't know what the correct sdl_scancode_* for it is */
//   /*  117 */  ::user::e_key_none,
//   /*  118 */  ::user::e_key_numpad_equals,
//   /*  119 */  ::user::e_key_none,
//   /*  120 */  ::user::e_key_none,
//   /*  121 */  ::user::e_key_international4, /* henkan_mode */
//   /*  122 */  ::user::e_key_none,
//   /*  123 */  ::user::e_key_international5, /* muhenkan */
//   /*  124 */  ::user::e_key_none,
//   /*  125 */  ::user::e_key_international3, /* yen */
//   /*  126 */  ::user::e_key_none,
//   /*  127 */  ::user::e_key_none,
//   /*  128 */  ::user::e_key_none,
//   /*  129 */  ::user::e_key_none,
//   /*  130 */  ::user::e_key_none,
//   /*  131 */  ::user::e_key_none,
//   /*  132 */  ::user::e_key_power,
//   /*  133 */  ::user::e_key_mute,
//   /*  134 */  ::user::e_key_volumedown,
//   /*  135 */  ::user::e_key_volumeup,
//   /*  136 */  ::user::e_key_help,
//   /*  137 */  ::user::e_key_stop,
//   /*  138 */  ::user::e_key_again,
//   /*  139 */  ::user::e_key_none, /* props */
//   /*  140 */  ::user::e_key_undo,
//   /*  141 */  ::user::e_key_none, /* front */
//   /*  142 */  ::user::e_key_copy,
//   /*  143 */  ::user::e_key_none, /* open */
//   /*  144 */  ::user::e_key_paste,
//   /*  145 */  ::user::e_key_find,
//   /*  146 */  ::user::e_key_cut,
//};

/* for wireless usb keyboard (manufacturer trust) without numpad. */
static const ::user::enum_key xfree86_key_table2[] = {
   /*  0 */    ::user::e_key_none,
   /*  1 */    ::user::e_key_escape,
   /*  2 */    ::user::e_key_1,
   /*  3 */    ::user::e_key_2,
   /*  4 */    ::user::e_key_3,
   /*  5 */    ::user::e_key_4,
   /*  6 */    ::user::e_key_5,
   /*  7 */    ::user::e_key_6,
   /*  8 */    ::user::e_key_7,
   /*  9 */    ::user::e_key_8,
   /*  10 */   ::user::e_key_9,
   /*  11 */   ::user::e_key_0,
   /*  12 */   ::user::e_key_minus,
   /*  13 */   ::user::e_key_equal,
   /*  14 */   ::user::e_key_back,
   /*  15 */   ::user::e_key_tab,
   /*  16 */   ::user::e_key_q,
   /*  17 */   ::user::e_key_w,
   /*  18 */   ::user::e_key_e,
   /*  19 */   ::user::e_key_r,
   /*  20 */   ::user::e_key_t,
   /*  21 */   ::user::e_key_y,
   /*  22 */   ::user::e_key_u,
   /*  23 */   ::user::e_key_i,
   /*  24 */   ::user::e_key_o,
   /*  25 */   ::user::e_key_p,
   /*  26 */   ::user::e_key_left_bracket,
   /*  27 */   ::user::e_key_right_bracket,
   /*  28 */   ::user::e_key_return,
   /*  29 */   ::user::e_key_left_control,
   /*  30 */   ::user::e_key_a,
   /*  31 */   ::user::e_key_s,
   /*  32 */   ::user::e_key_d,
   /*  33 */   ::user::e_key_f,
   /*  34 */   ::user::e_key_g,
   /*  35 */   ::user::e_key_h,
   /*  36 */   ::user::e_key_j,
   /*  37 */   ::user::e_key_k,
   /*  38 */   ::user::e_key_l,
   /*  39 */   ::user::e_key_semicolon,
   /*  40 */   ::user::e_key_apostrophe,
   /*  41 */   ::user::e_key_grave,
   /*  42 */   ::user::e_key_left_shift,
   /*  43 */   ::user::e_key_backslash,
   /*  44 */   ::user::e_key_z,
   /*  45 */   ::user::e_key_x,
   /*  46 */   ::user::e_key_c,
   /*  47 */   ::user::e_key_v,
   /*  48 */   ::user::e_key_b,
   /*  49 */   ::user::e_key_n,
   /*  50 */   ::user::e_key_m,
   /*  51 */   ::user::e_key_comma,
   /*  52 */   ::user::e_key_period,
   /*  53 */   ::user::e_key_slash,
   /*  54 */   ::user::e_key_right_shift,
   /*  55 */   ::user::e_key_numpad_multiply,
   /*  56 */   ::user::e_key_left_alt,
   /*  57 */   ::user::e_key_space,
   /*  58 */   ::user::e_key_capslock,
   /*  59 */   ::user::e_key_f1,
   /*  60 */   ::user::e_key_f2,
   /*  61 */   ::user::e_key_f3,
   /*  62 */   ::user::e_key_f4,
   /*  63 */   ::user::e_key_f5,
   /*  64 */   ::user::e_key_f6,
   /*  65 */   ::user::e_key_f7,
   /*  66 */   ::user::e_key_f8,
   /*  67 */   ::user::e_key_f9,
   /*  68 */   ::user::e_key_f10,
   /*  69 */   ::user::e_key_numlock_clear,
   /*  70 */   ::user::e_key_scroll_lock,
   /*  71 */   ::user::e_key_numpad_7,
   /*  72 */   ::user::e_key_numpad_8,
   /*  73 */   ::user::e_key_numpad_9,
   /*  74 */   ::user::e_key_numpad_minus,
   /*  75 */   ::user::e_key_numpad_4,
   /*  76 */   ::user::e_key_numpad_5,
   /*  77 */   ::user::e_key_numpad_6,
   /*  78 */   ::user::e_key_numpad_plus,
   /*  79 */   ::user::e_key_numpad_1,
   /*  80 */   ::user::e_key_numpad_2,
   /*  81 */   ::user::e_key_numpad_3,
   /*  82 */   ::user::e_key_numpad_0,
   /*  83 */   ::user::e_key_numpad_period,
   /*  84 */   ::user::e_key_sysreq,    /* ???? */
   /*  85 */   ::user::e_key_mode,      /* ???? */
   /*  86 */   ::user::e_key_non_us_back_slash,
   /*  87 */   ::user::e_key_f11,
   /*  88 */   ::user::e_key_f12,
   /*  89 */   ::user::e_key_international1, /* \_ */
   /*  90 */   ::user::e_key_none,   /* katakana */
   /*  91 */   ::user::e_key_none,   /* hiragana */
   /*  92 */   ::user::e_key_international4, /* henkan_mode */
   /*  93 */   ::user::e_key_international2, /* hiragana_katakana */
   /*  94 */   ::user::e_key_international5, /* muhenkan */
   /*  95 */   ::user::e_key_none,
   /*  96 */   ::user::e_key_numpad_enter,
   /*  97 */   ::user::e_key_right_control,
   /*  98 */   ::user::e_key_numpad_divide,
   /*  99 */   ::user::e_key_print_screen,
   /* 100 */   ::user::e_key_right_alt,      /* iso_level3_shift, altgr, ralt */
   /* 101 */   ::user::e_key_none,   /* linefeed */
   /* 102 */   ::user::e_key_home,
   /* 103 */   ::user::e_key_up,
   /* 104 */   ::user::e_key_page_up,
   /* 105 */   ::user::e_key_left,
   /* 106 */   ::user::e_key_right,
   /* 107 */   ::user::e_key_end,
   /* 108 */   ::user::e_key_down,
   /* 109 */   ::user::e_key_page_down,
   /* 110 */   ::user::e_key_insert,
   /* 111 */   ::user::e_key_delete,
   /* 112 */   ::user::e_key_none,
   /* 113 */   ::user::e_key_mute,
   /* 114 */   ::user::e_key_volume_down,
   /* 115 */   ::user::e_key_volume_up,
   /* 116 */   ::user::e_key_power,
   /* 117 */   ::user::e_key_numpad_equal,
   /* 118 */   ::user::e_key_none,   /* plusminus */
   /* 119 */   ::user::e_key_pause,
   /* 120 */   ::user::e_key_none,   /* xf86launcha */
   /* 121 */   ::user::e_key_none,   /* kp_decimal */
   /* 122 */   ::user::e_key_none,   /* hangul */
   /* 123 */   ::user::e_key_none,   /* hangul_hanja */
   /* 124 */   ::user::e_key_international3, /* yen */
   /* 125 */   ::user::e_key_left_gui,
   /* 126 */   ::user::e_key_right_gui,
   /* 127 */   ::user::e_key_application,
   /* 128 */   ::user::e_key_cancel,
   /* 129 */   ::user::e_key_again,
   /* 130 */   ::user::e_key_none,   /* sunprops */
   /* 131 */   ::user::e_key_undo,
   /* 132 */   ::user::e_key_none,   /* sunfront */
   /* 133 */   ::user::e_key_copy,
   /* 134 */   ::user::e_key_none,   /* sunopen */
   /* 135 */   ::user::e_key_paste,
   /* 136 */   ::user::e_key_find,
   /* 137 */   ::user::e_key_cut,
   /* 138 */   ::user::e_key_help,
   /* 139 */   ::user::e_key_none,   /* xf86menukb */
   /* 140 */   ::user::e_key_calculator,
   /* 141 */   ::user::e_key_none,
   /* 142 */   ::user::e_key_sleep,
   /* 143 */   ::user::e_key_none,   /* xf86wakeup */
   /* 144 */   ::user::e_key_none,   /* xf86explorer */
   /* 145 */   ::user::e_key_none,   /* xf86send */
   /* 146 */   ::user::e_key_none,
   /* 147 */   ::user::e_key_none,   /* xf86xfer */
   /* 148 */   ::user::e_key_app1,      /* xf86launch1 */
   /* 149 */   ::user::e_key_app2,      /* xf86launch2 */
   /* 150 */   ::user::e_key_www,
   /* 151 */   ::user::e_key_none,   /* xf86dos */
   /* 152 */   ::user::e_key_none,   /* xf86screensaver */
   /* 153 */   ::user::e_key_none,
   /* 154 */   ::user::e_key_none,   /* xf86rotatewindows */
   /* 155 */   ::user::e_key_mail,
   /* 156 */   ::user::e_key_ac_bookmarks,   /* xf86favorites */
   /* 157 */   ::user::e_key_computer,
   /* 158 */   ::user::e_key_ac_back,
   /* 159 */   ::user::e_key_ac_forward,
   /* 160 */   ::user::e_key_none,
   /* 161 */   ::user::e_key_eject,
   /* 162 */   ::user::e_key_eject,
   /* 163 */   ::user::e_key_audionext,
   /* 164 */   ::user::e_key_audioplay,
   /* 165 */   ::user::e_key_audioprev,
   /* 166 */   ::user::e_key_audiostop,
   /* 167 */   ::user::e_key_none,   /* xf86audiorecord */
   /* 168 */   ::user::e_key_audiorewind,   /* xf86audiorewind */
   /* 169 */   ::user::e_key_none,   /* xf86phone */
   /* 170 */   ::user::e_key_none,
   /* 171 */   ::user::e_key_f13,       /* xf86tools */
   /* 172 */   ::user::e_key_ac_home,
   /* 173 */   ::user::e_key_ac_refresh,
   /* 174 */   ::user::e_key_none,   /* xf86close */
   /* 175 */   ::user::e_key_none,
   /* 176 */   ::user::e_key_none,
   /* 177 */   ::user::e_key_none,   /* xf86scrollup */
   /* 178 */   ::user::e_key_none,   /* xf86scrolldown */
   /* 179 */   ::user::e_key_none,   /* parenleft */
   /* 180 */   ::user::e_key_none,   /* parenright */
   /* 181 */   ::user::e_key_none,   /* xf86new */
   /* 182 */   ::user::e_key_again,
   /* 183 */   ::user::e_key_f13,       /* xf86tools */
   /* 184 */   ::user::e_key_f14,       /* xf86launch5 */
   /* 185 */   ::user::e_key_f15,       /* xf86launch6 */
   /* 186 */   ::user::e_key_f16,       /* xf86launch7 */
   /* 187 */   ::user::e_key_f17,       /* xf86launch8 */
   /* 188 */   ::user::e_key_f18,       /* xf86launch9 */
   /* 189 */   ::user::e_key_f19,       /* null keysym */
   /* 190 */   ::user::e_key_none,
   /* 191 */   ::user::e_key_none,
   /* 192 */   ::user::e_key_none,   /* xf86touchpadtoggle */
   /* 193 */   ::user::e_key_none,
   /* 194 */   ::user::e_key_none,
   /* 195 */   ::user::e_key_mode,
   /* 196 */   ::user::e_key_none,
   /* 197 */   ::user::e_key_none,
   /* 198 */   ::user::e_key_none,
   /* 199 */   ::user::e_key_none,
   /* 200 */   ::user::e_key_audioplay,
   /* 201 */   ::user::e_key_none,   /* xf86audiopause */
   /* 202 */   ::user::e_key_none,   /* xf86launch3 */
   /* 203 */   ::user::e_key_none,   /* xf86launch4 */
   /* 204 */   ::user::e_key_none,   /* xf86launchb */
   /* 205 */   ::user::e_key_none,   /* xf86suspend */
   /* 206 */   ::user::e_key_none,   /* xf86close */
   /* 207 */   ::user::e_key_audioplay,
   /* 208 */   ::user::e_key_audionext,
   /* 209 */   ::user::e_key_none,
   /* 210 */   ::user::e_key_print_screen,
   /* 211 */   ::user::e_key_none,
   /* 212 */   ::user::e_key_none,   /* xf86webcam */
   /* 213 */   ::user::e_key_none,
   /* 214 */   ::user::e_key_none,
   /* 215 */   ::user::e_key_mail,
   /* 216 */   ::user::e_key_none,
   /* 217 */   ::user::e_key_ac_search,
   /* 218 */   ::user::e_key_none,
   /* 219 */   ::user::e_key_none,   /* xf86finance */
   /* 220 */   ::user::e_key_none,
   /* 221 */   ::user::e_key_none,   /* xf86shop */
   /* 222 */   ::user::e_key_none,
   /* 223 */   ::user::e_key_stop,
   /* 224 */   ::user::e_key_brightness_down,
   /* 225 */   ::user::e_key_brightness_up,
   /* 226 */   ::user::e_key_media_select,
   /* 227 */   ::user::e_key_display_switch,
   /* 228 */   ::user::e_key_kbdillumtoggle,
   /* 229 */   ::user::e_key_kbdillumdown,
   /* 230 */   ::user::e_key_kbdillumup,
   /* 231 */   ::user::e_key_none,   /* xf86send */
   /* 232 */   ::user::e_key_none,   /* xf86reply */
   /* 233 */   ::user::e_key_none,   /* xf86mailforward */
   /* 234 */   ::user::e_key_none,   /* xf86save */
   /* 235 */   ::user::e_key_none,   /* xf86documents */
   /* 236 */   ::user::e_key_none,   /* xf86battery */
   /* 237 */   ::user::e_key_none,   /* xf86bluetooth */
   /* 238 */   ::user::e_key_none,   /* xf86wlan */
};

///* xvnc / xtightvnc scancodes from xmodmap -pk */
//static const sdl_scancode xvnc_scancode_table[] = {
//   /*  0 */    sdl_scancode_lctrl,
//   /*  1 */    sdl_scancode_rctrl,
//   /*  2 */    sdl_scancode_lshift,
//   /*  3 */    sdl_scancode_rshift,
//   /*  4 */    sdl_scancode_unknown, /* meta_l */
//   /*  5 */    sdl_scancode_unknown, /* meta_r */
//   /*  6 */    sdl_scancode_lalt,
//   /*  7 */    sdl_scancode_ralt,
//   /*  8 */    sdl_scancode_space,
//   /*  9 */    sdl_scancode_0,
//   /*  10 */   sdl_scancode_1,
//   /*  11 */   sdl_scancode_2,
//   /*  12 */   sdl_scancode_3,
//   /*  13 */   sdl_scancode_4,
//   /*  14 */   sdl_scancode_5,
//   /*  15 */   sdl_scancode_6,
//   /*  16 */   sdl_scancode_7,
//   /*  17 */   sdl_scancode_8,
//   /*  18 */   sdl_scancode_9,
//   /*  19 */   sdl_scancode_minus,
//   /*  20 */   sdl_scancode_equals,
//   /*  21 */   sdl_scancode_leftbracket,
//   /*  22 */   sdl_scancode_rightbracket,
//   /*  23 */   sdl_scancode_semicolon,
//   /*  24 */   sdl_scancode_apostrophe,
//   /*  25 */   sdl_scancode_grave,
//   /*  26 */   sdl_scancode_comma,
//   /*  27 */   sdl_scancode_period,
//   /*  28 */   sdl_scancode_slash,
//   /*  29 */   sdl_scancode_backslash,
//   /*  30 */   sdl_scancode_a,
//   /*  31 */   sdl_scancode_b,
//   /*  32 */   sdl_scancode_c,
//   /*  33 */   sdl_scancode_d,
//   /*  34 */   sdl_scancode_e,
//   /*  35 */   sdl_scancode_f,
//   /*  36 */   sdl_scancode_g,
//   /*  37 */   sdl_scancode_h,
//   /*  38 */   sdl_scancode_i,
//   /*  39 */   sdl_scancode_j,
//   /*  40 */   sdl_scancode_k,
//   /*  41 */   sdl_scancode_l,
//   /*  42 */   sdl_scancode_m,
//   /*  43 */   sdl_scancode_n,
//   /*  44 */   sdl_scancode_o,
//   /*  45 */   sdl_scancode_p,
//   /*  46 */   sdl_scancode_q,
//   /*  47 */   sdl_scancode_r,
//   /*  48 */   sdl_scancode_s,
//   /*  49 */   sdl_scancode_t,
//   /*  50 */   sdl_scancode_u,
//   /*  51 */   sdl_scancode_v,
//   /*  52 */   sdl_scancode_w,
//   /*  53 */   sdl_scancode_x,
//   /*  54 */   sdl_scancode_y,
//   /*  55 */   sdl_scancode_z,
//   /*  56 */   sdl_scancode_backspace,
//   /*  57 */   sdl_scancode_return,
//   /*  58 */   sdl_scancode_tab,
//   /*  59 */   sdl_scancode_escape,
//   /*  60 */   sdl_scancode_delete,
//   /*  61 */   sdl_scancode_home,
//   /*  62 */   sdl_scancode_end,
//   /*  63 */   sdl_scancode_pageup,
//   /*  64 */   sdl_scancode_pagedown,
//   /*  65 */   sdl_scancode_up,
//   /*  66 */   sdl_scancode_down,
//   /*  67 */   sdl_scancode_left,
//   /*  68 */   sdl_scancode_right,
//   /*  69 */   sdl_scancode_f1,
//   /*  70 */   sdl_scancode_f2,
//   /*  71 */   sdl_scancode_f3,
//   /*  72 */   sdl_scancode_f4,
//   /*  73 */   sdl_scancode_f5,
//   /*  74 */   sdl_scancode_f6,
//   /*  75 */   sdl_scancode_f7,
//   /*  76 */   sdl_scancode_f8,
//   /*  77 */   sdl_scancode_f9,
//   /*  78 */   sdl_scancode_f10,
//   /*  79 */   sdl_scancode_f11,
//   /*  80 */   sdl_scancode_f12,
//};

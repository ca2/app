//
//  keyboard.cpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 18/05/20.
//

#include "framework.h"
#include "keyboard.h"


bool apple_is_action_key(int i)
{
   
   if(i==kVK_Return) return true;
  if(i==kVK_Tab          ) return true;
  //if(i==kVK_Space        ) return true;
  if(i==kVK_Delete       ) return true;
  if(i==kVK_Escape       ) return true;
  if(i==kVK_Command      ) return true;
  if(i==kVK_Shift        ) return true;
  if(i==kVK_CapsLock     ) return true;
  if(i==kVK_Option       ) return true;
  if(i==kVK_Control      ) return true;
  if(i==kVK_RightShift   ) return true;
  if(i==kVK_RightOption  ) return true;
  if(i==kVK_RightControl ) return true;
  if(i==kVK_Function     ) return true;
  if(i==kVK_F17          ) return true;
  if(i==kVK_VolumeUp     ) return true;
  if(i==kVK_VolumeDown   ) return true;
  if(i==kVK_Mute         ) return true;
  if(i==kVK_F18          ) return true;
  if(i==kVK_F19          ) return true;
  if(i==kVK_F20          ) return true;
  if(i==kVK_F5           ) return true;
  if(i==kVK_F6           ) return true;
  if(i==kVK_F7           ) return true;
  if(i==kVK_F3           ) return true;
  if(i==kVK_F8           ) return true;
  if(i==kVK_F9           ) return true;
  if(i==kVK_F11          ) return true;
  if(i==kVK_F13          ) return true;
  if(i==kVK_F16          ) return true;
  if(i==kVK_F14          ) return true;
  if(i==kVK_F10          ) return true;
  if(i==kVK_F12          ) return true;
  if(i==kVK_F15          ) return true;
  if(i==kVK_Help         ) return true;
  if(i==kVK_Home         ) return true;
  if(i==kVK_PageUp       ) return true;
  if(i==kVK_ForwardDelete) return true;
  if(i==kVK_F4           ) return true;
  if(i==kVK_End          ) return true;
  if(i==kVK_F2           ) return true;
  if(i==kVK_PageDown     ) return true;
  if(i==kVK_F1           ) return true;
  if(i==kVK_LeftArrow    ) return true;
  if(i==kVK_RightArrow   ) return true;
  if(i==kVK_DownArrow    ) return true;
  if(i==kVK_UpArrow      ) return true;

   return false;
}


///**
// * Key Flags
// */
//
//#define KBDEXT      (WINUSHORT) 0x0100
//#define KBDMULTIVK   (WINUSHORT) 0x0200
//#define KBDSPECIAL   (WINUSHORT) 0x0400
//#define KBDNUMPAD   (WINUSHORT) 0x0800
//#define KBDUNICODE   (WINUSHORT) 0x1000
//#define KBDINJECTEDVK   (WINUSHORT) 0x2000
//#define KBDMAPPEDVK   (WINUSHORT) 0x4000
//#define KBDBREAK   (WINUSHORT) 0x8000

/**
 * X11 Keycodes
 */

/**
 * Mac OS X
 */

#define APPLE_VK_ANSI_A         0x00
#define APPLE_VK_ANSI_S         0x01
#define APPLE_VK_ANSI_D         0x02
#define APPLE_VK_ANSI_F         0x03
#define APPLE_VK_ANSI_H         0x04
#define APPLE_VK_ANSI_G         0x05
#define APPLE_VK_ANSI_Z         0x06
#define APPLE_VK_ANSI_X         0x07
#define APPLE_VK_ANSI_C         0x08
#define APPLE_VK_ANSI_V         0x09
#define APPLE_VK_ISO_Section      0x0A
#define APPLE_VK_ANSI_B         0x0B
#define APPLE_VK_ANSI_Q         0x0C
#define APPLE_VK_ANSI_W         0x0D
#define APPLE_VK_ANSI_E         0x0E
#define APPLE_VK_ANSI_R         0x0F
#define APPLE_VK_ANSI_Y         0x10
#define APPLE_VK_ANSI_T         0x11
#define APPLE_VK_ANSI_1         0x12
#define APPLE_VK_ANSI_2         0x13
#define APPLE_VK_ANSI_3         0x14
#define APPLE_VK_ANSI_4         0x15
#define APPLE_VK_ANSI_6         0x16
#define APPLE_VK_ANSI_5         0x17
#define APPLE_VK_ANSI_Equal      0x18
#define APPLE_VK_ANSI_9         0x19
#define APPLE_VK_ANSI_7         0x1A
#define APPLE_VK_ANSI_Minus      0x1B
#define APPLE_VK_ANSI_8         0x1C
#define APPLE_VK_ANSI_0         0x1D
#define APPLE_VK_ANSI_RightBracket   0x1E
#define APPLE_VK_ANSI_O         0x1F
#define APPLE_VK_ANSI_U         0x20
#define APPLE_VK_ANSI_LeftBracket   0x21
#define APPLE_VK_ANSI_I         0x22
#define APPLE_VK_ANSI_P         0x23
#define APPLE_VK_Return         0x24
#define APPLE_VK_ANSI_L         0x25
#define APPLE_VK_ANSI_J         0x26
#define APPLE_VK_ANSI_Quote      0x27
#define APPLE_VK_ANSI_K         0x28
#define APPLE_VK_ANSI_Semicolon      0x29
#define APPLE_VK_ANSI_Backslash      0x2A
#define APPLE_VK_ANSI_Comma      0x2B
#define APPLE_VK_ANSI_Slash      0x2C
#define APPLE_VK_ANSI_N         0x2D
#define APPLE_VK_ANSI_M         0x2E
#define APPLE_VK_ANSI_Period      0x2F
#define APPLE_VK_Tab         0x30
#define APPLE_VK_Space         0x31
#define APPLE_VK_ANSI_Grave      0x32
#define APPLE_VK_Delete         0x33
#define APPLE_VK_0x34         0x34
#define APPLE_VK_Escape         0x35
#define APPLE_VK_0x36         0x36
#define APPLE_VK_Command      0x37
#define APPLE_VK_Shift         0x38
#define APPLE_VK_CapsLock      0x39
#define APPLE_VK_Option         0x3A
#define APPLE_VK_Control      0x3B
#define APPLE_VK_RightShift      0x3C
#define APPLE_VK_RightOption      0x3D
#define APPLE_VK_RightControl      0x3E
#define APPLE_VK_Function      0x3F
#define APPLE_VK_F17         0x40
#define APPLE_VK_ANSI_KeypadDecimal   0x41
#define APPLE_VK_0x42         0x42
#define APPLE_VK_ANSI_KeypadMultiply   0x43
#define APPLE_VK_0x44         0x44
#define APPLE_VK_ANSI_KeypadPlus   0x45
#define APPLE_VK_0x46         0x46
#define APPLE_VK_ANSI_KeypadClear   0x47
#define APPLE_VK_VolumeUp      0x48
#define APPLE_VK_VolumeDown      0x49
#define APPLE_VK_Mute         0x4A
#define APPLE_VK_ANSI_KeypadDivide   0x4B
#define APPLE_VK_ANSI_KeypadEnter   0x4C
#define APPLE_VK_0x4D         0x4D
#define APPLE_VK_ANSI_KeypadMinus   0x4E
#define APPLE_VK_F18         0x4F
#define APPLE_VK_F19         0x50
#define APPLE_VK_ANSI_KeypadEquals   0x51
#define APPLE_VK_ANSI_Keypad0      0x52
#define APPLE_VK_ANSI_Keypad1      0x53
#define APPLE_VK_ANSI_Keypad2      0x54
#define APPLE_VK_ANSI_Keypad3      0x55
#define APPLE_VK_ANSI_Keypad4      0x56
#define APPLE_VK_ANSI_Keypad5      0x57
#define APPLE_VK_ANSI_Keypad6      0x58
#define APPLE_VK_ANSI_Keypad7      0x59
#define APPLE_VK_F20         0x5A
#define APPLE_VK_ANSI_Keypad8      0x5B
#define APPLE_VK_ANSI_Keypad9      0x5C
#define APPLE_VK_JIS_Yen      0x5D
#define APPLE_VK_JIS_Underscore      0x5E
#define APPLE_VK_JIS_KeypadComma   0x5F
#define APPLE_VK_F5         0x60
#define APPLE_VK_F6         0x61
#define APPLE_VK_F7         0x62
#define APPLE_VK_F3         0x63
#define APPLE_VK_F8         0x64
#define APPLE_VK_F9         0x65
#define APPLE_VK_JIS_Eisu      0x66
#define APPLE_VK_F11         0x67
#define APPLE_VK_JIS_Kana      0x68
#define APPLE_VK_F13         0x69
#define APPLE_VK_F16         0x6A
#define APPLE_VK_F14         0x6B
#define APPLE_VK_F10         0x6D
#define APPLE_VK_0x6C         0x6C
#define APPLE_VK_0x6E         0x6E
#define APPLE_VK_F12         0x6F
#define APPLE_VK_0x70         0x70
#define APPLE_VK_F15         0x71
#define APPLE_VK_Help         0x72
#define APPLE_VK_Home         0x73
#define APPLE_VK_PageUp         0x74
#define APPLE_VK_ForwardDelete      0x75
#define APPLE_VK_F4         0x76
#define APPLE_VK_End         0x77
#define APPLE_VK_F2         0x78
#define APPLE_VK_PageDown      0x79
#define APPLE_VK_F1         0x7A
#define APPLE_VK_LeftArrow      0x7B
#define APPLE_VK_RightArrow      0x7C
#define APPLE_VK_DownArrow      0x7D
#define APPLE_VK_UpArrow      0x7E
#define KEYCODE_TYPE_APPLE      0x00000001
#define KEYCODE_TYPE_EVDEV      0x00000002

#ifdef __cplusplus
extern "C" {
#endif
   
   /**
    * Functions
    */
   
   char* GetVirtualKeyName(::u32 vkcode);
   ::u32 GetVirtualKeyCodeFromName(const char* vkname);
   ::u32 GetVirtualKeyCodeFromXkbKeyName(const char* xkbname);
   
   ::u32 GetVirtualKeyCodeFromVirtualScanCode(::u32 scancode, ::u32 dwKeyboardType);
   ::u32 GetVirtualScanCodeFromVirtualKeyCode(::u32 vkcode, ::u32 dwKeyboardType);
   
#define KEYCODE_TYPE_APPLE      0x00000001
#define KEYCODE_TYPE_EVDEV      0x00000002
   
   ::u32 GetVirtualKeyCodeFromKeycode(::u32 keycode, ::u32 dwFlags);
   ::u32 GetKeycodeFromVirtualKeyCode(::u32 keycode, ::u32 dwFlags);
   
#ifdef __cplusplus
}
#endif

::u32 fixKeyCode(::u32 keyCode, unichar keyChar, enum APPLE_KEYBOARD_TYPE type)
{
   /**
    * In 99% of cases, the given key code is truly keyboard independent.
    * This function handles the remaining 1% of edge cases.
    *
    * Hungarian Keyboard: This is 'QWERTZ' and not 'QWERTY'.
    * The '0' key is on the left of the '1' key, where '~' is on a US keyboard.
    * A special 'i' letter key with acute is found on the right of the left shift key.
    * On the hungarian keyboard, the 'i' key is at the left of the 'Y' key
    * Some international keyboards have a corresponding key which would be at
    * the left of the 'Z' key when using a QWERTY layout.
    *
    * The Apple Hungarian keyboard sends inverted key codes for the '0' and 'i' keys.
    * When using the US keyboard layout, key codes are left as-is (inverted).
    * When using the Hungarian keyboard layout, key codes are swapped (non-inverted).
    * This means that when using the Hungarian keyboard layout with a US keyboard,
    * the keys corresponding to '0' and 'i' will effectively be inverted.
    *
    * To fix the '0' and 'i' key inversion, we use the corresponding output character
    * provided by OS X and check for a character to key code mismatch: for instance,
    * when the output character is '0' for the key code corresponding to the 'i' key.
    */
   
#if 0
   switch (keyChar)
   {
      case '0':
      case 0x00A7: /* section sign */
         if (keyCode == APPLE_VK_ISO_Section)
            keyCode = APPLE_VK_ANSI_Grave;
         break;
         
      case 0x00ED: /* latin small letter i with acute */
      case 0x00CD: /* latin capital letter i with acute */
         if (keyCode == APPLE_VK_ANSI_Grave)
            keyCode = APPLE_VK_ISO_Section;
         break;
   }
   
#endif
   
   /* Perform keycode correction for all ISO keyboards */
   
   if (type == APPLE_KEYBOARD_TYPE_ISO)
   {
      if (keyCode == APPLE_VK_ANSI_Grave)
         keyCode = APPLE_VK_ISO_Section;
      else if (keyCode == APPLE_VK_ISO_Section)
         keyCode = APPLE_VK_ANSI_Grave;
   }
   
   return keyCode;
   
}

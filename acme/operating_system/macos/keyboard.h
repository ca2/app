//
//  Keyboard.h
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 8/19/15.
//
//
/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * MacFreeRDP
 *
 * Copyright 2014 Marc-Andre Moreau <marcandre.moreau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

enum APPLE_KEYBOARD_TYPE
{
   APPLE_KEYBOARD_TYPE_ANSI,
   APPLE_KEYBOARD_TYPE_ISO,
   APPLE_KEYBOARD_TYPE_JIS
};

enum APPLE_KEYBOARD_TYPE mac_detect_keyboard_type();

extern "C"
{

   ::u32 GetVirtualKeyCodeFromKeycode(::u32 keycode, ::u32 dwFlags);
   ::u32 GetVirtualScanCodeFromVirtualKeyCode(::u32 vkcode, ::u32 dwKeyboardType);

} // extern "C"

bool apple_is_action_key(int i);





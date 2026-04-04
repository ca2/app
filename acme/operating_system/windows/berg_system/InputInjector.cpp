// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "acme/_operating_system.h"
#include "InputInjector.h"
#include "Keyboard.h"
//#include "remoting/remoting_common/win_system/Environment.h"
//#include <vector>

#include <crtdbg.h>

InputInjector::InputInjector(bool ctrlAltDelEnabled, LogWriter *log)
: m_controlIsPressed(false),
  m_menuIsPressed(false),
  m_deleteIsPressed(false),
  m_shiftIsPressed(false),
  m_winIsPressed(false),
  m_ctrlAltDelEnabled(ctrlAltDelEnabled),
  m_log(log)
{
  // FIXME: Better to call this function from an owner (Now, its
  // possible only from trunk code because in the stable hive the owner is
  // the deprecated KeyEvent class)
  try {
    resetModifiers();
  }
  catch (::exception &e) {
    m_log->error("InputInjector: error occurred while reseting modifiers: {}",
      e.get_message());
  }
}

InputInjector::~InputInjector()
{
  try {
    resetModifiers();
  } catch (...) {
  }
}

void InputInjector::injectKeyPress(BYTE vkCode)
{
  injectKeyEvent(vkCode, false);
}

void InputInjector::injectKeyRelease(BYTE vkCode)
{
  injectKeyEvent(vkCode, true);
}

void InputInjector::injectKeyEvent(BYTE vkCode, bool release, bool extended)
{
  m_log->debug("Prepare to inject the key event:"
             " vkCode = {}, release = {}, extended = {}",
             (int)vkCode,
             (int)release,
             (int)extended);
  m_log->debug("The modifier states before:"
             " m_controlIsPressed = {};"
             " m_menuIsPressed = {};"
             " m_deleteIsPressed = {};"
             " m_shiftIsPressed = {};"
             " m_winIsPressed = {};",
             (int)m_controlIsPressed,
             (int)m_menuIsPressed,
             (int)m_deleteIsPressed,
             (int)m_shiftIsPressed,
             (int)m_winIsPressed);

  if (vkCode == VK_CONTROL || vkCode == VK_RCONTROL || vkCode == VK_LCONTROL) {
    m_controlIsPressed = !release;
  }
  if (vkCode == VK_MENU || vkCode == VK_RMENU || vkCode == VK_LMENU) {
    m_menuIsPressed = !release;
  }
  if (vkCode == VK_DELETE) {
    m_deleteIsPressed = !release;
  }
  if (vkCode == VK_SHIFT || vkCode == VK_RSHIFT || vkCode == VK_LSHIFT) {
    m_shiftIsPressed = !release;
  }
  if (vkCode == VK_LWIN || vkCode == VK_RWIN) {
    m_winIsPressed = !release;
  }
  m_log->debug("The modifier states after:"
             " m_controlIsPressed = {};"
             " m_menuIsPressed = {};"
             " m_deleteIsPressed = {};"
             " m_shiftIsPressed = {};"
             " m_winIsPressed = {};",
             (int)m_controlIsPressed,
             (int)m_menuIsPressed,
             (int)m_deleteIsPressed,
             (int)m_shiftIsPressed,
             (int)m_winIsPressed);

  if (m_controlIsPressed && m_menuIsPressed && m_deleteIsPressed &&
      !m_winIsPressed && !m_shiftIsPressed) {
    if (m_ctrlAltDelEnabled) {
      m_log->debug("Try simulate the Ctrl+Alt+Del combination");
       throw todo;
      // if (node()->_windows_isVistaOrLater()) {
      //   Environment::simulateCtrlAltDelUnderVista(m_log);
      // }
      // else {
      //   Environment::simulateCtrlAltDel(m_log);
      // }
    } else {
      m_log->debug("The Ctrl+Alt+Del combination is disabled. Ignore the Del key pressing");
    }
  } else {
    INPUT keyEvent = {0};

    keyEvent.type = INPUT_KEYBOARD;
    keyEvent.ki.wVk = vkCode;
    keyEvent.ki.wScan = MapVirtualKey(vkCode, 0);

    if (release) {
      keyEvent.ki.dwFlags = KEYEVENTF_KEYUP;
    }

    if (extended) {
      keyEvent.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }

    if (SendInput(1, &keyEvent, sizeof(keyEvent)) == 0) {
      DWORD errCode = GetLastError();
      if (errCode != ERROR_SUCCESS) {
        throw SystemException("SendInput() function failed:", errCode);
      } else {
        // Under Vista or later the SendInput() function doesn't return error
        // code if inputs blocked by UIPI.
        throw ::remoting::Exception("SendInput() function failed");
      }
    }
  }
}

void InputInjector::injectCharEvent(WCHAR ch, bool release)
{
  m_log->debug("Try insert a char event: char = {}, release = {}",
             (int)ch, (int)release);

  bool ctrlOrAltPressed = m_controlIsPressed || m_menuIsPressed;
  SHORT vkKeyScanResult = 0;
  HKL hklCurrent = (HKL)0x04090409;
  try {
    hklCurrent = getCurrentKbdLayout();
    m_log->debug("Current keyboard layout = {:#08x}", (int)hklCurrent);
    vkKeyScanResult = searchVirtKey(ch, hklCurrent);
    m_log->debug("The virtual code scan result = {}", (int)vkKeyScanResult);
  } catch (...) {
    m_log->debug("Can't insert the char by simulating a key press event,"
              " therefore try insert it as an unicode symbol");
    if (ctrlOrAltPressed) {
      m_log->warning("Can't insert the char by an unicode symbol because"
                   " a modifier is pressed");
      throw;
    }
    INPUT keyEvent = {0};

    keyEvent.type = INPUT_KEYBOARD;
    keyEvent.ki.wVk = 0;
    keyEvent.ki.wScan = ch;
    keyEvent.ki.dwFlags = KEYEVENTF_UNICODE;

    if (release) {
      keyEvent.ki.dwFlags |= KEYEVENTF_KEYUP;
    }

    if (SendInput(1, &keyEvent, sizeof(keyEvent)) == 0) {
      throw SystemException();
    }
    return;
  }
  bool controlSym;
  if (ch >= L'A' && ch <= L'Z' || ch >= L'a' && ch <= L'z') {
    controlSym = m_controlIsPressed && !m_menuIsPressed && !m_shiftIsPressed;
  } else {
    controlSym = false;
  }
  // Not all keys must be typed with the SHIFT to get the lower case when the
  // CAPS pressed, e.g. the numerical keys.
  bool resistantToCaps = isResistantToCaps((BYTE)vkKeyScanResult, hklCurrent);
  bool invariantToShift = isInvariantToShift((BYTE)vkKeyScanResult, hklCurrent);

  // If code belonged with high registr we must generate shift up and shift
  // down also.
  bool shiftedKey = (vkKeyScanResult >> 8 & 1) != 0;
  shiftedKey = shiftedKey && !capsToggled() ||
               shiftedKey && capsToggled() && resistantToCaps ||
               !shiftedKey && capsToggled() && !resistantToCaps;
  bool shiftPressNeeded = shiftedKey && !m_shiftIsPressed && !release &&
                          !controlSym;
  bool shiftUpNeeded = !shiftedKey && m_shiftIsPressed && !release &&
                       !controlSym && !invariantToShift;
  bool ctrlPressNeeded = (vkKeyScanResult >> 9 & 1) && !m_controlIsPressed &&
                         !release;
  bool altPressNeeded = (vkKeyScanResult >> 10 & 1) && !m_menuIsPressed &&
                        !release;
  if ((ctrlPressNeeded || altPressNeeded) &&
      (m_controlIsPressed || m_menuIsPressed)) {
    m_log->error("Received a control combination that we doesn't know how it can be made");
    return;
  }

  m_log->debug("Variable states before generate key events to get the char:"
             " controlSym = {};"
             " resistantToCaps = {};"
             " invariantToShift = {};"
             " shiftedKey = {};"
             " shiftPressNeeded = {};"
             " shiftUpNeeded = {};"
             " ctrlPressNeeded = {};"
             " altPressNeeded = {};",
             (int)controlSym,
             (int)resistantToCaps,
             (int)invariantToShift,
             (int)shiftedKey,
             (int)shiftPressNeeded,
             (int)shiftUpNeeded,
             (int)ctrlPressNeeded,
             (int)altPressNeeded);

  if (ctrlPressNeeded) {
    injectKeyEvent(VK_CONTROL, false);
  }
  if (altPressNeeded) {
    injectKeyEvent(VK_MENU, false);
  }
  if (shiftPressNeeded) {
    injectKeyEvent(VK_SHIFT, false);
  } else if (shiftUpNeeded) {
    injectKeyEvent(VK_SHIFT, true);
  }
  injectKeyEvent(vkKeyScanResult & 255, release);
  if (shiftPressNeeded) {
    injectKeyEvent(VK_SHIFT, true);
  } else if (shiftUpNeeded) {
    injectKeyEvent(VK_SHIFT, false);
  }
  if (altPressNeeded) {
    injectKeyEvent(VK_MENU, true);
  }
  if (ctrlPressNeeded) {
    injectKeyEvent(VK_CONTROL, true);
  }
}

bool InputInjector::isAscii(WCHAR ch)
{
  if (ch >= 0 && ch < 128) {
    return true;
  }
  return false;
}

SHORT InputInjector::searchVirtKey(WCHAR ch, HKL hklCurrent)
{
  // Test for special case
  bool modifiersPressed = m_controlIsPressed || m_menuIsPressed ||
                          m_shiftIsPressed;
  bool onlyCtrlPressed = m_controlIsPressed && !m_menuIsPressed &&
                         !m_shiftIsPressed;
  // Try get virtual code in the current keyboard layout
  SHORT vkKeyScanResult = VkKeyScanExW(ch, hklCurrent);
  if (vkKeyScanResult == -1) {
    if (onlyCtrlPressed) {
      if (ch >= L'A' && ch <= L'Z') {
        return (SHORT)ch;
      } else if (ch >= L'a' && ch <= L'z') {
        return (SHORT)(ch - L'a' + L'A');
      }
    }
    ::string errMess;
    errMess.formatf("Can't translate the {} character to the scan code",
                   (unsigned int)ch);
    throw ::remoting::Exception(errMess);
  }
  if (isDeadKey(vkKeyScanResult, hklCurrent)) {
    throw ::remoting::Exception("Special dead symbol must be inserted"
                    " only as unicode character");
  }
  if (!isOneKeyEventChar(ch, vkKeyScanResult, hklCurrent)) {
    ::string errMess;
    errMess.formatf("Can't get the {} character by one keyboard event",
                   (unsigned int)ch);
    throw ::remoting::Exception(errMess);
  }
  // Special trick to get round a problem when printing the ^6 characters
  // instead of estimated 6.
  if (!modifiersPressed) {
    unsigned short layout = ((unsigned int)hklCurrent & 0xffff0000) >> 16;
    const unsigned short TURKISH = MAKELANGID(LANG_TURKISH, SUBLANG_DEFAULT);
    const unsigned short NORWEGIAN = MAKELANGID(LANG_NORWEGIAN, SUBLANG_DEFAULT);
    const unsigned short BRAZILIAN = MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN);
    const unsigned short GREEK = MAKELANGID(LANG_GREEK, SUBLANG_DEFAULT);
    const unsigned short POLISH1 = MAKELANGID(LANG_POLISH, SUBLANG_DEFAULT);
    const unsigned short POLISH2 = MAKELANGID(LANG_POLISH, SUBLANG_POLISH_POLAND);

    if ((layout == POLISH1 || layout == POLISH2) && ch == _T('`')) {
      throw ::remoting::Exception("Special case for the '`' character on the POLISH"
        " keyboard, it will be inserted as"
        " an unicode");
    }

    if (layout == 0xf001 && ch == _T('6')) {
      throw ::remoting::Exception("Special case for the '6' character on the USA"
                      " international keyboard, it will be inserted as"
                      " an unicode");
    }
    if (layout == BRAZILIAN && ch == _T('6')) {
      throw ::remoting::Exception("Special case for the '6' character on the brazilian"
        " keyboard, it will be inserted as"
        " an unicode");
    }
    if (layout == NORWEGIAN && ch == _T('\\')) {
      throw ::remoting::Exception("Special case for the '\\' character on the norwegian"
                      " keyboard, it will be inserted as"
                      " an unicode");
    }
    if (layout == TURKISH && ch == _T('3')) {
      throw ::remoting::Exception("Special case for the '3' character on the turkish-Q"
        " keyboard, it will be inserted as"
        " an unicode");
    }
    if (layout == GREEK && ch == 0x03c2) {
      throw ::remoting::Exception("Special case for the 'w' character on the greek"
        " keyboard, it will be inserted as"
        " an unicode");
    }
  }
  return vkKeyScanResult;
}

bool InputInjector::capsToggled()
{
  return (GetKeyState(VK_CAPITAL) & 1) != 0;
}

bool InputInjector::isDeadKey(SHORT scanResult, HKL keyboardLayout)
{
  unsigned char kbdState[256];
  memset(kbdState, 0, sizeof(kbdState));
  WCHAR outBuff[20];
  bool withShift = (scanResult >> 8 & 1) != 0;
  bool withCtrl  = (scanResult >> 9 & 1) != 0;
  bool withAlt   = (scanResult >> 10 & 1) != 0;

  kbdState[VK_SHIFT]   = withShift ? 128 : 0;
  kbdState[VK_CONTROL] = withCtrl  ? 128 : 0;
  kbdState[VK_MENU]    = withAlt   ? 128 : 0;

  unsigned char virtKey = scanResult & 255;

  int count = ToUnicodeEx(virtKey, 0, kbdState, outBuff,
                          sizeof(outBuff) / sizeof(WCHAR),
                          0, keyboardLayout);
  bool result = count == -1;
  count = ToUnicodeEx(virtKey, 0, kbdState, outBuff,
                      sizeof(outBuff) / sizeof(WCHAR),
                      0, keyboardLayout);
  result = result || count == -1;
  return result;
}

bool InputInjector::isOneKeyEventChar(WCHAR ch, SHORT scanResult,
                                      HKL keyboardLayout)
{
  unsigned char kbdState[256];
  memset(kbdState, 0, sizeof(kbdState));
  WCHAR outBuff[20];
  bool withShift = (scanResult >> 8 & 1) != 0;
  bool withCtrl  = (scanResult >> 9 & 1) != 0;
  bool withAlt   = (scanResult >> 10 & 1) != 0;

  kbdState[VK_SHIFT]   = withShift ? 128 : 0;
  kbdState[VK_CONTROL] = withCtrl  ? 128 : 0;
  kbdState[VK_MENU]    = withAlt   ? 128 : 0;

  unsigned char virtKey = scanResult & 255;

  int count = ToUnicodeEx(virtKey, 0, kbdState, outBuff,
                          sizeof(outBuff) / sizeof(WCHAR),
                          0, keyboardLayout);
  if (count == 1) {
    return outBuff[0] == ch;
  } else {
    return false;
  }
}

HKL InputInjector::getCurrentKbdLayout()
{
  // Determine current owning thread.
  HWND hwnd = GetForegroundWindow();
  if (hwnd == 0) {
    throw ::remoting::Exception("Can't insert key event because"
                    " a window is losing activation");
  }
  DWORD threadId = GetWindowThreadProcessId(hwnd, 0);
  return GetKeyboardLayout(threadId);
}

bool InputInjector::isDifferentWith(BYTE modifier, BYTE modStateValueOfOn,
                                    BYTE virtKey, HKL keyboardLayout)
{
  unsigned char kbdState[256];
  memset(kbdState, 0, sizeof(kbdState));
  WCHAR outBuff1[20], outBuff2[20];

  // Get symbol(s) without the modifier.
  int count1 = ToUnicodeEx(virtKey, 0, kbdState, outBuff1,
                           sizeof(outBuff1) / sizeof(WCHAR),
                           0, keyboardLayout);

  // Get symbol(s) with modifier.
  kbdState[modifier & 255] = modStateValueOfOn;
  int count2 = ToUnicodeEx(virtKey, 0, kbdState, outBuff2,
                          sizeof(outBuff2) / sizeof(WCHAR),
                          0, keyboardLayout);
  if (count1 != count2) return false; // It isn't invariant
  if (memcmp(outBuff1, outBuff2, count1 * sizeof(WCHAR)) != 0) {
    return false;
  } else {
    return true;
  }
}

bool InputInjector::isInvariantToShift(BYTE virtKey, HKL keyboardLayout)
{
  return isDifferentWith(VK_SHIFT, 128, virtKey, keyboardLayout);
}

bool InputInjector::isResistantToCaps(BYTE virtKey, HKL keyboardLayout)
{
  return isDifferentWith(VK_CAPITAL, 1, virtKey, keyboardLayout);
}

void InputInjector::resetModifiers()
{
  // The Alt key.
  injectKeyEvent(VK_MENU, true);
  injectKeyEvent(VK_LMENU, true);
  injectKeyEvent(VK_RMENU, true);
  // The Shift key.
  injectKeyEvent(VK_SHIFT, true);
  injectKeyEvent(VK_LSHIFT, true);
  injectKeyEvent(VK_RSHIFT, true);
  // The Ctrl key.
  injectKeyEvent(VK_CONTROL, true);
  injectKeyEvent(VK_LCONTROL, true);
  injectKeyEvent(VK_RCONTROL, true);
  // The Win key.
  injectKeyEvent(VK_LWIN, true);
  injectKeyEvent(VK_RWIN, true);
  // The Delete key.
  injectKeyEvent(VK_DELETE, true);
}

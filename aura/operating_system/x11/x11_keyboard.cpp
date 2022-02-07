// xkeyboard.cpp
// Implementation of a class to get keyboard on_layout information and machine layouts
// Copyright (C) 2008 by Jay Bromley <jbromley@gmail.com>
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// $Id: XKeyboard.cpp 53 2008-07-18 08:38:47Z jay $
#include "framework.h"
#include "x11_keyboard.h"
#include "x11_exception.h"
//!!!#include <X11/XKBlib.h>
//!!!#include <X11/keysym.h>

// XKeyboard -----------------------------------------------------------

XKeyboard::XKeyboard()
    : _display(0), _groupCount(0), _currentGroupNum(0),
      _deviceId(XkbUseCoreKbd)
{

    XkbIgnoreExtension(False);

    char* displayName = strdup("");
    int eventCode;
    int errorReturn;
    int major = XkbMajorVersion;
    int minor = XkbMinorVersion;;
    int reasonReturn;
    _display = XkbOpenDisplay(displayName, &eventCode, &errorReturn, &major,
                              &minor, &reasonReturn);
    switch (reasonReturn) {
    case XkbOD_BadLibraryVersion:
        throw X11Exception("Bad XKB library version.");
        break;
    case XkbOD_ConnectionRefused:
        throw X11Exception("Connection to X server refused.");
        break;
    case XkbOD_BadServerVersion:
        throw X11Exception("Bad X11 server version.");
        break;
    case XkbOD_NonXkbServer:
        throw X11Exception("XKB not present.");
        break;
    case XkbOD_Success:
        break;
    }

    if (initializeXkb() != True) {
        throw X11Exception("XKB not initialized.");
    }

    XkbSelectEventDetails(_display, XkbUseCoreKbd, XkbStateNotify,
                          XkbAllStateComponentsMask, XkbGroupStateMask);

    XkbStateRec xkbState;
    XkbGetState(_display, _deviceId, &xkbState);
    _currentGroupNum = (_currentGroupNum != xkbState.group) ? xkbState.group : _currentGroupNum;
    accomodateGroupXkb();
}

Bool XKeyboard::initializeXkb()
{
    // Initialize the XKB extension.
    int major = XkbMajorVersion;
    int minor = XkbMinorVersion;
    int opCode;
    Bool status = XkbQueryExtension(_display, &opCode, &_baseEventCode, &_baseErrorCode,  &major, &minor);

    XkbDescRec* kbdDescPtr = XkbAllocKeyboard();
    if (kbdDescPtr == NULL) {
        //std::cerr << "Failed to get keyboard description." << std::endl;
        return False;
    }

    kbdDescPtr->dpy = _display;
    if (_deviceId != XkbUseCoreKbd) {
        kbdDescPtr->device_spec = _deviceId;
    }

    XkbGetControls(_display, XkbAllControlsMask, kbdDescPtr);
    XkbGetNames(_display, XkbSymbolsNameMask, kbdDescPtr);
    XkbGetNames(_display, XkbGroupNamesMask, kbdDescPtr);

    if (kbdDescPtr->names == NULL) {
//        std::cerr << "Failed to get keyboard description." << std::endl;
        return False;
    }

    // Count the number of configured groups.
    const Atom* groupSource = kbdDescPtr->names->groups;
    if (kbdDescPtr->ctrls != NULL) {
        _groupCount = kbdDescPtr->ctrls->num_groups;
    } else {
        _groupCount = 0;
        while (_groupCount < XkbNumKbdGroups &&
               groupSource[_groupCount] != None) {
            _groupCount++;
        }
    }

    // There is always at least one group.
    if (_groupCount == 0) {
        _groupCount = 1;
    }

    // Get the group names.
    const Atom* tmpGroupSource = kbdDescPtr->names->groups;
    Atom curGroupAtom;
    string groupName;
    for (int i = 0; i < _groupCount; i++) {
        if ((curGroupAtom = tmpGroupSource[i]) != None) {
            char* groupNameC = XGetAtomName(_display, curGroupAtom);
            if (groupNameC == NULL) {
                _groupNames.push_back("");
            } else {
                groupName = groupNameC;
                string::size_type pos = groupName.find('(', 0);
                if (pos>= 0) {
                    groupName = groupName.substr(0, pos + 1);
                }
                _groupNames.push_back(groupName);
            }
            XFree(groupNameC);
        }
    }

    // Get the symbol name and parse it for on_layout symbols.
    Atom symNameAtom = kbdDescPtr->names->symbols;
    string symName;
    if (symNameAtom != None) {
        char* symNameC = XGetAtomName(_display, symNameAtom);
        symName = symNameC;
        XFree(symNameC);
        if (symName.empty()) {
            return False;
        }
    } else {
        return False;
    }

    XkbSymbolParser symParser;
    symParser.parse(symName, _symbolNames);
    int count = _symbolNames.size();
    if (count == 1 && _groupNames[0].empty()  && _symbolNames[0] == "jp") {
        _groupCount = 2;
        _symbolNames[1] = _symbolNames[0];
        _symbolNames[0] = "us";
        _groupNames[0] = "US/ASCII";
        _groupNames[1] = "Japanese";
    } else {
        if (count < _groupCount) {
            int j = count;
            int k = _groupCount;
            while (--j >= 0) _symbolNames.set_at_grow(--k, _symbolNames[j]);
            while (--k >= 0) _symbolNames.set_at_grow(k, "en_US");
        }
    }

    count = _groupNames.size();
    for (int i = 0; i < count; i++) {
        if (_groupNames[i].empty()) {
            string name = getSymbolNameByResNum(i);
            if (name.empty()) {
                name = "U/A";
            }
//            std::cerr << "Group Name " << i + 1 << " is undefined, set to '"
  //                    << name << "'!\n";
            _groupNames[i] = name;
        }
    }

    XkbStateRec xkbState;
    XkbGetState(_display, _deviceId, &xkbState);
    _currentGroupNum = xkbState.group;

    return True;
}

string XKeyboard::getSymbolNameByResNum(int groupResNum)
{
    return _symbolNames[groupNumResToXkb(groupResNum)];
}

string XKeyboard::getGroupNameByResNum(int groupResNum)
{
    return _groupNames[groupNumResToXkb(groupResNum)];
}

int XKeyboard::groupNumResToXkb(int groupResNum)
{
    return groupLookup(groupResNum, _groupNames, _symbolNames, _groupCount);
}

int XKeyboard::groupLookup(int srcValue, StringVector fromText, StringVector toText, int count)
{
    const string srcText = fromText[srcValue];

    if (!srcText.empty()) {
        string targetText;

        for (int i = 0; i < count; i++) {
            targetText = toText[i];
            if (compareNoCase(srcText, targetText) == 0) {
                srcValue = i;
                break;
            }
        }
    }

    return srcValue;
}

void XKeyboard::accomodateGroupXkb()
{
    XkbStateRec state;
    XkbGetState(_display, _deviceId, &state);
    _currentGroupNum = state.group;
}


XKeyboard::~XKeyboard()
{
    XCloseDisplay(_display);
    _display = NULL;
}

int XKeyboard::groupCount() const
{
    return _groupCount;
}

StringVector XKeyboard::groupNames() const
{
    return _groupNames;
}

StringVector XKeyboard::groupSymbols() const
{
    return _symbolNames;
}

int XKeyboard::currentGroupNum() const
{
    XkbStateRec xkbState;
    XkbGetState(_display, _deviceId, &xkbState);
    return static_cast<int>(xkbState.group);
}

string XKeyboard::currentGroupName() const
{
    return _groupNames[currentGroupNum()];
}

string XKeyboard::currentGroupSymbol() const
{
    return _symbolNames[currentGroupNum()];
}

bool XKeyboard::setGroupByNum(int groupNum)
{
    if (_groupCount <= 1) {
        return false;
    }

    Bool result = XkbLockGroup(_display, _deviceId, groupNum);
    if (result == False) {
        return false;
    }
    accomodateGroupXkb();
    return true;
}

bool XKeyboard::changeGroup(int increment)
{
    Bool result = XkbLockGroup(_display, _deviceId,
                               (_currentGroupNum + increment) % _groupCount);
    if (result == False) {
        return false;
    }
    accomodateGroupXkb();
    return true;
}


// XkbSymbolParser -----------------------------------------------------

XkbSymbolParser::XkbSymbolParser()
{
    _nonSymbols.push_back("group");
    _nonSymbols.push_back("inet");
    _nonSymbols.push_back("pc");
}

XkbSymbolParser::~XkbSymbolParser()
{
    _nonSymbols.clear();
}

void XkbSymbolParser::parse(const string& symbols, StringVector& symbolList)
{
    bool inSymbol = false;
    string curSymbol;

    for (int i = 0; i < symbols.size(); i++) {
        char ch = symbols[i];
        if (ch == '+') {
            if (inSymbol) {
                if (isXkbLayoutSymbol(curSymbol)) {
                    symbolList.push_back(curSymbol);
                }
                curSymbol.clear();
            } else {
                inSymbol = true;
            }
        } else if (inSymbol && (isalpha(static_cast<int>(ch)) || ch == '_')) {
            curSymbol.append(1, ch);
        } else {
            if (inSymbol) {
                if (isXkbLayoutSymbol(curSymbol)) {
                    symbolList.push_back(curSymbol);
                }
                curSymbol.clear();
                inSymbol = false;
            }
        }
    }

    if (inSymbol && !curSymbol.empty() && isXkbLayoutSymbol(curSymbol)) {
        symbolList.push_back(curSymbol);
    }
}

bool XkbSymbolParser::isXkbLayoutSymbol(const string& symbol) {
    index result = _nonSymbols.find_first(symbol);
    return result < 0;
}

// Helper functions ----------------------------------------------------

int compareNoCase(const string& s1, const string& s2)
{
    index it1 = 0;
    index it2 = 0;

    //Has the end of at least one of the strings been reached?
    while (it1 < s1.length() && it2 < s2.length()) {
        // Do the letters differ?
        if (::toupper(s1[it1]) != ::toupper(s2[it2])) {
            // return -1 to indicate 'smaller than', 1 otherwise
            return (::toupper(s1[it1]) < ::toupper(s2[it2])) ? -1 : 1;
        }

        // Proceed to the next character in each string.
        ++it1;
        ++it2;
    }

    size_t size1 = s1.size();
    size_t size2 = s2.size();

    // Return -1, 0 or 1 according to strings' lengths.
    if (size1 == size2)  {
        return 0;
    }
    return (size1 < size2) ? -1 : 1;
}

// std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb)
// {
//     os << "xkb {\n\t" << xkb.groupCount() << " groups {" << xkb.groupNames()
//        << "},\n\tsymbols {" << xkb.groupSymbols() << "}\n\tcurrent group: "
//        << xkb.currentGroupSymbol() << " - " << xkb.currentGroupName()
//        << " (" << xkb.currentGroupNum() << ")\n}";
//     return os;
// }

// std::ostream& operator<<(std::ostream& os, const StringVector& sv)
// {
//     for (int i = 0; i < sv.size(); i++) {
//      os << (i == 0 ? "" : ", ") << sv[i];
//     }
//     return os;
// }

// Main entry point_i32 (test) ---------------------------------------------

// int main(int argc, char** argv)
// {
//     XKeyboard xkb;
//     std::cout << xkb << std::endl;
//     xkb.changeGroup(1);
//     std::cout << xkb << std::endl;
//     xkb.changeGroup(1);
//     std::cout << xkb << std::endl;
//     xkb.changeGroup(1);
//     std::cout << xkb << std::endl;
//     return EXIT_SUCCESS;
// }

void x11_keyboard_get_current_group_info(string & strGroupName, string & strGroupSymbol)
{

   XKeyboard xkb;

   strGroupName = xkb.currentGroupName(); //return somethings like "USA"

   strGroupSymbol = xkb.currentGroupSymbol(); //return somethings like "us"

}


string x11_keyboard_get_current_group_name()
{

   XKeyboard xkb;

   return xkb.currentGroupName(); //return somethings like "USA"

}



string x11_keyboard_get_current_group_symbol()
{

   XKeyboard xkb;

   return xkb.currentGroupSymbol(); //return somethings like "us"

}


namespace user
{

   CLASS_DECL_AURA ::user::enum_key keysym_to_userkey(const lparam & lparam)
   {

      KeySym keysym = (KeySym) (iptr)lparam.m_lparam;

      switch(keysym)
      {
      case XK_BackSpace:
         return key_back;
      case XK_Shift_L:
         return key_lshift;
      case XK_Shift_R:
         return key_rshift;
      case XK_Control_L:
         return key_lcontrol;
      case XK_Control_R:
         return key_rcontrol;
      case XK_Alt_L:
         return key_lalt;
      case XK_Alt_R:
         return key_ralt;
      case XK_Delete:
         return key_delete;
      case XK_Return:
         return key_return;
      case XK_Tab:
         return key_tab;
      case XK_Left:
         return key_left;
      case XK_Right:
         return key_right;
      case XK_Up:
         return key_up;
      case XK_Down:
         return key_down;
      case XK_Page_Up:
         return key_prior;
      case XK_Page_Down:
         return key_next;
      case XK_Home:
         return key_home;
      case XK_End:
         return key_end;


      }

      if(keysym >= 'a' && keysym <= 'z')
      {

         return (::user::enum_key) ((int)(::user::e_key_a) + keysym - 'a');

      }
      else if(keysym >= 'A' && keysym <= 'Z')
      {

         return (::user::enum_key) ((int)(::user::e_key_a) + keysym - 'A');

      }

      return key_none;

   }


} // namespace user

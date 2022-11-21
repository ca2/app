// xkeyboard.h
// Interface for a class to get keyboard on_layout information and machine layouts
// Copyright (C) 2008 by Jay Bromley <jbromley@gmail.com>
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// $Id: XKeyboard.h 29 2008-04-09 21:37:44Z jay $
#pragma once

//!!!#include <X11/Xlib.h>


void x11_keyboard_get_current_group_info(string & strGroupName, string & strGroupSymbol);
string x11_keyboard_get_current_group_name();
string x11_keyboard_get_current_group_symbol();
//#include "acme/primitive/collection/string_array.h"

typedef string_array StringVector;


// XKeyboard -----------------------------------------------------------

class XKeyboard
{
public:
    XKeyboard();
    ~XKeyboard();
    int groupCount() const;
    StringVector groupNames() const;
    StringVector groupSymbols() const;
    int currentGroupNum() const;
    string currentGroupName() const;
    string currentGroupSymbol() const;
    bool setGroupByNum(int groupNum);
    bool changeGroup(int increment);

    //friend std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb);

private:
    bool initializeXkb();
    string getSymbolNameByResNum(int groupResNum);
    int groupNumResToXkb(int groupNumRes);
    string getGroupNameByResNum(int groupResNum);
    int groupLookup(int srcValue, StringVector fromText, StringVector toText, int count);
    void accomodateGroupXkb();

    //Display* _display;
    int _groupCount;
    StringVector _groupNames;
    StringVector _symbolNames;
    int _currentGroupNum;

    int _deviceId;
    int _baseEventCode;
    int _baseErrorCode;
};


// XkbSymbolParser -----------------------------------------------------

class XkbSymbolParser
{
public:

    XkbSymbolParser();
    ~XkbSymbolParser();
    void parse(const string& symbols, string_array& symbolList);

private:
    bool isXkbLayoutSymbol(const string& symbol);

    StringVector _nonSymbols;
};


// Helper functions ----------------------------------------------------

int compareNoCase(const string& s1, const string& s2);
// std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb);
// std::ostream& operator<<(std::ostream& os, const StringVector& v);


// Local Variables:
// mode: c++
// End:

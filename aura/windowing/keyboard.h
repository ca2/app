// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20

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


#include "aura/user/user/keyboard.h"
//#include "acme/prototype/collection/string_array.h"


namespace windowing
{


   class CLASS_DECL_AURA keyboard :
      virtual public ::user::keyboard
   {
   public:


      keyboard();
      ~keyboard() override;
      
      
      ::user::enum_key wparam_to_userkey(wparam wparam) override;


      ::i32 groupCount() const;

      string_array_base groupNames() const;

      string_array_base groupSymbols() const;

      ::i32 currentGroupNum() const;

      string currentGroupName() const;

      string currentGroupSymbol() const;

      bool setGroupByNum(::i32 groupNum);

      bool changeGroup(::i32 increment);


      //friend std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb);

   private:


      bool initializeXkb();

      string getSymbolNameByResNum(::i32 groupResNum);

      ::i32 groupNumResToXkb(::i32 groupNumRes);

      string getGroupNameByResNum(::i32 groupResNum);

      ::i32 groupLookup(::i32 srcValue, string_array_base fromText, string_array_base toText, ::i32 count);

      void accomodateGroupXkb();

      ::i32 _groupCount;
      string_array_base _groupNames;
      string_array_base _symbolNames;
      //::i32 _currentGroupNum;

      //::i32 _deviceId;
      //::i32 _baseEventCode;
      //::i32 _baseErrorCode;

   };


// XkbSymbolParser -----------------------------------------------------

   class symbol_parser
   {
   public:

      symbol_parser();

      ~symbol_parser();

      void parse(const string &symbols, string_array_base &symbolList);

   private:

      bool isXkbLayoutSymbol(const string &symbol);

      string_array_base   m_nonSymbols;


   };


// Helper functions ----------------------------------------------------

   //::i32 compareNoCase(const string &s1, const string &s2);
// std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb);
// std::ostream& operator<<(std::ostream& os, const StringVector& v);

//#endif // XKEYBOARD_H_1C79861A_49B3_4A95_88D6_455C22FEB222

// Local Variables:
// mode: c++
// End:


} // namespace windowing

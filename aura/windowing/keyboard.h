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

#include "aura/user/user/keyboard.h"

namespace windowing
{


   class CLASS_DECL_AURA keyboard :
      virtual public ::user::keyboard
   {
   public:


      keyboard();
      ~keyboard() override;
      
      
      ::user::enum_key wparam_to_userkey(wparam wparam) override;


      int groupCount() const;

      string_array groupNames() const;

      string_array groupSymbols() const;

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

      int groupLookup(int srcValue, string_array fromText, string_array toText, int count);

      void accomodateGroupXkb();

      int _groupCount;
      string_array _groupNames;
      string_array _symbolNames;
      int _currentGroupNum;

      int _deviceId;
      int _baseEventCode;
      int _baseErrorCode;

   };


// XkbSymbolParser -----------------------------------------------------

   class symbol_parser
   {
   public:

      symbol_parser();

      ~symbol_parser();

      void parse(const string &symbols, string_array &symbolList);

   private:

      bool isXkbLayoutSymbol(const string &symbol);

      string_array   m_nonSymbols;


   };


// Helper functions ----------------------------------------------------

   //int compareNoCase(const string &s1, const string &s2);
// std::ostream& operator<<(std::ostream& os, const XKeyboard& xkb);
// std::ostream& operator<<(std::ostream& os, const StringVector& v);

//#endif // XKEYBOARD_H_1C79861A_49B3_4A95_88D6_455C22FEB222

// Local Variables:
// mode: c++
// End:


} // namespace windowing

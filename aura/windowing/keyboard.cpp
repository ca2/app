// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
// xkeyboard.cpp
// of a class to get keyboard on_layout information and machine layouts
// Copyright (C) 2008 by Jay Bromley <jbromley@gmail.com>
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.
//
// $Id: keyboard.cpp 53 2008-07-18 08:38:47Z jay $
#include "framework.h"
//#include "_windowing.h"
//#include "x11_keyboard.h"
//#include "x11_exception.h"
//!!!#include <X11/XKBlib.h>
//!!!#include <X11/keysym.h>
//#include "acme/user/user/_constant.h"
#include "acme/constant/user_key.h"
#include "aura/windowing/keyboard.h"
// <3 ThomasBS - 400th follower

// keyboard -----------------------------------------------------------

namespace windowing
{

   keyboard::keyboard()
      :  _groupCount(0) // , 
      //_currentGroupNum(0),
        //_deviceId(0)
   {

   }


   ::user::enum_key keyboard::wparam_to_userkey(wparam wparam)
   {
   
      return ::user::e_key_none;
   
   }


   bool keyboard::initializeXkb()
   {

      return false;
   }




   string keyboard::getSymbolNameByResNum(int groupResNum)
   {
      return _symbolNames[groupNumResToXkb(groupResNum)];
   }

   string keyboard::getGroupNameByResNum(int groupResNum)
   {
      return _groupNames[groupNumResToXkb(groupResNum)];
   }

   int keyboard::groupNumResToXkb(int groupResNum)
   {
      return groupLookup(groupResNum, _groupNames, _symbolNames, _groupCount);
   }


   int keyboard::groupLookup(int srcValue, string_array fromText, string_array toText, int count)
   {

      const string srcText = fromText[srcValue];

      if (srcText.has_character())
      {

         string targetText;

         for (int i = 0; i < count; i++)
         {
            targetText = toText[i];

            if (srcText.case_insensitive_order(targetText) == 0)
            {

               srcValue = i;

               break;

            }

         }

      }

      return srcValue;

   }


   void keyboard::accomodateGroupXkb()
   {
   }


   keyboard::~keyboard()
   {
   }

   int keyboard::groupCount() const
   {
      return _groupCount;
   }


   string_array keyboard::groupNames() const
   {

      return _groupNames;

   }


   string_array keyboard::groupSymbols() const
   {

      return _symbolNames;

   }


   int keyboard::currentGroupNum() const
   {

       return -1;

   }


   string keyboard::currentGroupName() const
   {
      return _groupNames[currentGroupNum()];
   }

   string keyboard::currentGroupSymbol() const
   {
      return _symbolNames[currentGroupNum()];
   }

   bool keyboard::setGroupByNum(int groupNum)
   {
      if (_groupCount <= 1)
      {
         return false;
      }

      return true;
   }

   bool keyboard::changeGroup(int increment)
   {
      return true;
   }


//// XkbSymbolParser -----------------------------------------------------
//
//   XkbSymbolParser::XkbSymbolParser()
//   {
//      _nonSymbols.add("group");
//      _nonSymbols.add("inet");
//      _nonSymbols.add("pc");
//   }
//
//   XkbSymbolParser::~XkbSymbolParser()
//   {
//      _nonSymbols.clear();
//   }
//
//   void XkbSymbolParser::parse(const string &symbols, StringVector &symbolList)
//   {
//      bool inSymbol = false;
//      string curSymbol;
//
//      for (int i = 0; i < symbols.size(); i++)
//      {
//         char ch = symbols[i];
//         if (ch == '+')
//         {
//            if (inSymbol)
//            {
//               if (isXkbLayoutSymbol(curSymbol))
//               {
//                  symbolList.add(curSymbol);
//               }
//               curSymbol.clear();
//            }
//            else
//            {
//               inSymbol = true;
//            }
//         }
//         else if (inSymbol && (isalpha(static_cast<int>(ch)) || ch == '_'))
//         {
//            curSymbol.append(1, ch);
//         }
//         else
//         {
//            if (inSymbol)
//            {
//               if (isXkbLayoutSymbol(curSymbol))
//               {
//                  symbolList.add(curSymbol);
//               }
//               curSymbol.clear();
//               inSymbol = false;
//            }
//         }
//      }
//
//      if (inSymbol && !curSymbol.empty() && isXkbLayoutSymbol(curSymbol))
//      {
//         symbolList.add(curSymbol);
//      }
//   }
//
//   bool XkbSymbolParser::isXkbLayoutSymbol(const string &symbol)
//   {
//      index result = _nonSymbols.find_first(symbol);
//      return result < 0;
//   }
//
//// Helper functions ----------------------------------------------------

//   int compareNoCase(const string &s1, const string &s2)
//   {
//      index it1 = 0;
//      index it2 = 0;
//
//      //Has the end of at least one of the strings been reached?
//      while (it1 < s1.length() && it2 < s2.length())
//      {
//         // Do the letters differ?
//         if (::toupper(s1[it1]) != ::toupper(s2[it2]))
//         {
//            // return -1 to indicate 'smaller than', 1 otherwise
//            return (::toupper(s1[it1]) < ::toupper(s2[it2])) ? -1 : 1;
//         }
//
//         // Proceed to the next character in each string.
//         ++it1;
//         ++it2;
//      }
//
//      size_t size1 = s1.size();
//      size_t size2 = s2.size();
//
//      // Return -1, 0 or 1 according to strings' lengths.
//      if (size1 == size2)
//      {
//         return 0;
//      }
//      return (size1 < size2) ? -1 : 1;
//   }

// std::ostream& operator<<(std::ostream& os, const keyboard& xkb)
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

// Main entry int_point (test) ---------------------------------------------

// int main(int argc, char** argv)
// {
//     keyboard xkb;
//     std::cout << xkb << std::endl;
//     xkb.changeGroup(1);
//     std::cout << xkb << std::endl;
//     xkb.changeGroup(1);
//     std::cout << xkb << std::endl;
//     xkb.changeGroup(1);
//     std::cout << xkb << std::endl;
//     return EXIT_SUCCESS;
// }


   void x11_keyboard_get_current_group_info(string &strGroupName, string &strGroupSymbol)
   {

      keyboard xkb;

      strGroupName = xkb.currentGroupName(); //return somethings like "USA"

      strGroupSymbol = xkb.currentGroupSymbol(); //return somethings like "us"

   }


   string x11_keyboard_get_current_group_name()
   {

      keyboard xkb;

      return xkb.currentGroupName(); //return somethings like "USA"

   }


   string x11_keyboard_get_current_group_symbol()
   {

      keyboard xkb;

      return xkb.currentGroupSymbol(); //return somethings like "us"

   }





} // namespace windowing



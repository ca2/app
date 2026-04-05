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
#pragma once


#pragma warning(disable:4290)


namespace subsystem
{

   // #include "::string.h"

   /**
    * Common ::remoting::Exception class.
    */
   class CLASS_DECL_ACME Exception : virtual public ::exception

   {
   public:
      /**
       * Creates exception with empty description.
       */
      Exception();
      /**
       * Creates exception with specified description.
       * @param format description string in printf-like notation.
       */
      Exception(const_char_pointer pszFormat, ...);
      /**
       * Destructor.
       */
      ~Exception() override;

      /**
       * Returns description of exception.
       */
      //::string get_message() const;

      // protected:
      //::string m_message;
   };


} // namespace subsystem 




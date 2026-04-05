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
#include "Exception.h"


namespace subsystem
{


   Exception::Exception() :
      ::exception(error_remoting)
   {

      // m_message= "";

   }


   Exception::Exception(const_char_pointer pszFormat, ...) :
      ::exception(error_remoting)
   {
      
      va_list vl;

      va_start(vl, pszFormat);

      m_strMessage.formatf_arguments(pszFormat, vl);

      va_end(vl);

   }

   Exception::~Exception()
   {

   }

   ///::string ::remoting::Exception::get_message() const { return m_message; }


} // namespace subsystem
 



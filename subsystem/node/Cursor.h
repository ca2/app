// Copyright (C) 2012 GlavSoft LLC.
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


//#include "remoting/remoting_common/region/::int_point.h"
#include "subsystem/_common_header.h"

namespace subsystem
{

class CursorInterface :
   virtual public ::subsystem::particle_interface<CursorInterface>
{
public:
 //Cursor();
   //virtual ~CursorInterface() = 0;

  virtual ::int_point getCursorPos() const = 0;


};


   class CLASS_DECL_ACME Cursor :
   virtual public ::subsystem::composite<CursorInterface>
   {
   public:
      Cursor();
      ~Cursor() override;

      ::int_point getCursorPos() const override;


   };

//// __WINCURSOR_H__
///
} // namespace subsystem

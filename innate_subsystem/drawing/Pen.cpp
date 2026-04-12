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
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "Pen.h"

//#include <crtdbg.h>

namespace innate_subsystem
{

//Pen::Pen(int type, int width, const ::color::color & color)
   Pen::Pen()
//: m_pen(NULL)
{
  // m_pen = CreatePen(type, width, color);
  //
  // _ASSERT(m_pen != NULL);
}

Pen::~Pen()
{
  //DeleteObject(m_pen);
}

   // void * Pen::_HGDIOBJ()
   // {
   //    return m_pparticleThis->_HGDIOBJ();
   // }


   void Pen::initialize_pen(enum_pen epen, int width, const ::color::color & color)
   ///: m_pen(NULL)
{

   m_pparticleThis->initialize_pen(epen, width, color);
}
   // m_pen = CreatePen(type, width, color);
   //
   // _ASSERT(m_pen != NULL);

}

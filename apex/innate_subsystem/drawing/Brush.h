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

#pragma once
#include "acme/subsystem/particle.h"
#include "GraphicsObject.h"

namespace innate_subsystem
{

   class CLASS_DECL_APEX BrushInterface :
   virtual public ::subsystem::particle_interface<BrushInterface>,
   virtual public GraphicsObject
   {
   public:
      //Brush();
      virtual ~BrushInterface() = 0;

   //protected:
      //virtual void on_release() = 0;


      //virtual void destroyObject() = 0;

   // protected:
   //    HBRUSH m_brush;
   //
   //    friend class Graphics;
   };


   class CLASS_DECL_APEX Brush :
      virtual public ::subsystem::composite<BrushInterface >
   {
   public:
      Brush();
      ~Brush() override;

      //void * _HGDIOBJ() override;

      //protected:
      //void on_release() override;


      void destroyGraphicsObject() override;
      // protected:
      //    HBRUSH m_brush;
      //
      //    friend class Graphics;
   };

} // namespace innate_subsystem

// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
#include "subsystem/platform/Particle.h"
#include "GraphicsObject.h"


//#include "util/CommonHeader.h"

namespace innate_subsystem
{


      class PenInterface :
         virtual public GraphicsObject
      {
      public:

      //public:
         //Pen(::i32 type, ::i32 width, const ::color::color & color);
         //Pen();
          //virtual ~PenInterface() = 0;


         virtual void initialize_pen(::nano::graphics::enum_pen epen, ::f64 fWidth, const ::color::color & color) = 0;


         virtual void setStartCap(::nano::graphics::enum_line_cap elinecap) = 0;
         virtual void setEndCap(::nano::graphics::enum_line_cap elinecap) = 0;


         //virtual void destroyGObject() = 0;
      // protected:
      //    HPEN m_pen;
      //
      //    friend class Graphics;
      };


   class CLASS_DECL_INNATE_SUBSYSTEM PenComposite :
virtual public Composite<PenInterface>
   {
   public:


      ImplementCompositeø(Pen, pen)

      //public:
      //Pen(::i32 type, ::i32 width, const ::color::color & color);
      //Pen();
      //~Pen() override;


      //void * _HGDIOBJ() override;

         void initialize_pen(::nano::graphics::enum_pen epen, ::f64 fWidth, const ::color::color& color) override
      {

         m_ppen->initialize_pen(epen, fWidth, color);
      }

      void setStartCap(::nano::graphics::enum_line_cap elinecap) override { m_ppen->setStartCap(elinecap); }
      void setEndCap(::nano::graphics::enum_line_cap elinecap) override { m_ppen->setEndCap(elinecap); }

      void destroyGraphicsObject() override
      {

         m_ppen->destroyGraphicsObject();
      }

      // protected:
      //    HPEN m_pen;
      //
      //    friend class Graphics;
   };



    class CLASS_DECL_INNATE_SUBSYSTEM PenAggregate :
    virtual public Aggregate< PenComposite >
    {
    public:

        ImplementBaseø(Pen);

    };

   class CLASS_DECL_INNATE_SUBSYSTEM Pen :
   virtual public Object< PenAggregate >
   {
   public:

      ImplementObjectø(Pen)

   };


} // namespace innate_subsystem


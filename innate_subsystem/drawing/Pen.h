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
#include "subsystem/particle.h"
#include "GraphicsObject.h"

//#include "util/CommonHeader.h"

namespace innate_subsystem
{

   enum enum_pen
   {
      e_pen_solid = 0, //PS_SOLID;
      e_pen_dashed = 1, //PS_DASH;
      e_pen_null =5, // PS_NULL;
   };

      class PenInterface :
         virtual public GraphicsObject
      {
      public:

      //public:
         //Pen(int type, int width, const ::color::color & color);
         //Pen();
          //virtual ~PenInterface() = 0;


         virtual void initialize_pen(enum_pen epen, int width, const ::color::color & color) = 0;

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
      //Pen(int type, int width, const ::color::color & color);
      //Pen();
      //~Pen() override;


      //void * _HGDIOBJ() override;

         void initialize_pen(enum_pen epen, int width, const ::color::color& color) override
      {

         m_ppen->initialize_pen(epen, width, color);
      }

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


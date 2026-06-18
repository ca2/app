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
//#define _PROGRESS_BAR_H_

#include "innate_subsystem/gui/Control.h"

namespace innate_subsystem
{
    class ProgressBarInterface :
   virtual public ::Particle
    {
    public:
        //ProgressBar();
        //virtual ~ProgressBarInterface() = 0;

        virtual void setRange(::u16 min, ::u16 max) = 0;
        virtual void setPos(::u16 pos) = 0;
    };

   //using ProgressBarInterface = particle_interface<ProgressBarInterface, ControlInterface>;

    class CLASS_DECL_INNATE_SUBSYSTEM ProgressBarComposite :
   virtual public Composite < ProgressBarInterface >
    {
    public:

       ImplementCompositeø(ProgressBar, progressbar)


        //ProgressBar();
        //~ProgressBar();

        void setRange(::u16 min, ::u16 max) override {m_pprogressbar->setRange(min, max);}
        void setPos(::u16 pos) override{m_pprogressbar->setPos(pos);}
    };

   class CLASS_DECL_INNATE_SUBSYSTEM ProgressBarAggregate :
      virtual public Aggregate< ProgressBarComposite, ControlAggregate >

   {
   public:

      ImplementAggregateø(ProgressBar, Control)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM ProgressBar :
virtual public Object<ProgressBarAggregate>
   {
   public:

       ImplementObjectø(ProgressBar)

   };


} // namespace innate_subsystem

//#endif

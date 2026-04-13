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
//#define _PROGRESS_BAR_H_

#include "innate_subsystem/gui/Control.h"

namespace innate_subsystem
{
    class ProgressBarInterface :
   virtual public ::subsystem::particle_interface<ProgressBarInterface>,
   public Control
    {
    public:
        //ProgressBar();
        //virtual ~ProgressBarInterface() = 0;

        virtual void setRange(unsigned short min, unsigned short max) = 0;
        virtual void setPos(unsigned short pos) = 0;
    };
    class CLASS_DECL_INNATE_SUBSYSTEM ProgressBar :
   virtual public ::subsystem::composite < ProgressBarInterface >
    {
    public:
        ProgressBar();
        ~ProgressBar() override;

        void setRange(unsigned short min, unsigned short max) override;
        void setPos(unsigned short pos) override;
    };
} // namespace innate_subsystem

//#endif

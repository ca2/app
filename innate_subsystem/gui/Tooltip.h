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
//#define _TOOLTIP_H_

//#include "util/CommonHeader.h"
#include "innate_subsystem/gui/Control.h"

//
// Abstract tooltip class
//

namespace innate_subsystem
{


    class TooltipSlice :
    virtual public ::particle_base
    {
    public:
        //Tooltip();
  //      virtual ~TooltipInterface() = 0;
//
        virtual void showTooltip(ControlInterface *control)= 0;

        virtual void setText(const char *text)= 0;
        virtual void setTitle(const char *caption)= 0;

        virtual ::string getText() const= 0;
        virtual ::string getTitle() const= 0;

        virtual void setIconType(int iconType)= 0;
        virtual int getIconType() const = 0;
    };

    //#endif
   using TooltipInterface = particle_interface<TooltipSlice, WindowInterface>;
   
   class CLASS_DECL_INNATE_SUBSYSTEM Tooltip :
   virtual public composite<TooltipSlice, WindowInterface>
   {
   public:
      Tooltip();
      ~Tooltip() override;

      void showTooltip(ControlInterface *control) override;

      void setText(const char *text) override;
      void setTitle(const char *caption) override;

      ::string getText() const override;
      ::string getTitle() const override;

      void setIconType(int iconType) override;
      int getIconType() const override;
   };


}// namespace innate_subsystem




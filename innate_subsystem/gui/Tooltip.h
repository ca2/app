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


   enum enum_tooltip_icon
   {

      e_tooltip_icon_none,
      e_tooltip_icon_warning,

   };


    class TooltipInterface :
    virtual public ::Particle
    {
    public:
        //Tooltip();
  //      virtual ~TooltipInterface() = 0;
//
        virtual void showTooltip(ControlInterface *control)= 0;

        //virtual void setText(const char *text)= 0;
        virtual void setTitle(const char *caption)= 0;

        //virtual ::string getText() const= 0;
        virtual ::string getTitle() const= 0;

        virtual void setIconType(enum_tooltip_icon etooltipicon)= 0;
        virtual enum_tooltip_icon getIconType() const = 0;
    };

    //#endif
   //using TooltipInterface = particle_interface<TooltipInterface, WindowInterface>;
   
   class CLASS_DECL_INNATE_SUBSYSTEM TooltipComposite :
   virtual public Composite<TooltipInterface>
   {
   public:

      ImplementCompositeø(Tooltip, tooltip)

      //Tooltip();
      //~Tooltip() override;

         void showTooltip(ControlInterface* control) override
      {
         m_ptooltip->showTooltip(control);
      }

      //void setText(const char* text) override { m_ptooltip->setText(text);
      //}
      void setTitle(const char *caption) override { m_ptooltip->setTitle(caption); }

      //::string getText() const override { return m_ptooltip->getText();
      //}
      ::string getTitle() const override
      { return m_ptooltip->getTitle();
      }

      void setIconType(enum_tooltip_icon etooltipicon) override { m_ptooltip->setIconType(etooltipicon);
      }
      enum_tooltip_icon getIconType() const override { return m_ptooltip->getIconType();
      }
   };


   class CLASS_DECL_INNATE_SUBSYSTEM TooltipAggregate :
   virtual public Aggregate <TooltipComposite, ControlAggregate>
   {
   public:

      ImplementAggregateø(Tooltip, Control)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM Tooltip :
virtual public Object<TooltipAggregate>
   {
   public:

      ImplementObjectø(Tooltip)

   };


}// namespace innate_subsystem




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


#include "innate_subsystem/gui/Control.h"


namespace innate_subsystem
{


   class CheckBoxInterface :
      virtual public ::particle_base
   {
   public:


      //virtual ~CheckBoxInterface() = 0;

      virtual bool isChecked() = 0;
      virtual void setChecked(bool checked) = 0;

   };

   //using CheckBoxInterface = ::particle_interface<CheckBoxInterface, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM CheckBoxComposite :
      virtual public composite<CheckBoxInterface>
   {
   public:

      implement_compositeø(CheckBox, checkbox)

      //CheckBoxComposite();
      //~CheckBoxComposite();

      bool isChecked() { return m_pcheckbox->isChecked(); }
      void setChecked(bool checked) { m_pcheckbox->setChecked(checked); }

   };

   class CLASS_DECL_INNATE_SUBSYSTEM CheckBox : 
      virtual public aggregate< CheckBoxComposite, Control>

   {
   public:

      implement_aggregateø(CheckBox, Control)

      //CheckBox();
      //~CheckBox();

      //bool isChecked();
      //void setChecked(bool checked);
   };

   
} // namespace innate_subsystem


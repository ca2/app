// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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
//#define __TEXTBOX_H_

#include "subsystem/particle.h"
#include "innate_subsystem/gui/Control.h"
#include "innate_subsystem/gui/Tooltip.h"


namespace innate_subsystem
{


   class TextBoxSlice :
   virtual public ::particle_base
   {
   public:


      //TextBoxInterface();
      //virtual ~TextBoxInterface() = 0;


   ///public:

      //
      // Text limit
      //

      virtual character_count getTextLengthLimit() = 0;
      virtual void setTextLengthLimit(character_count limit) = 0;

      //
      // Methods for multiline textboxes
      //

      virtual int getCurrentLineIndex() = 0;
      virtual int getLineCount() = 0;

      //
      // Get / set caret position
      //

      virtual int getCaretPos() = 0;
      virtual void setCaretPos(int h, int v) = 0;

      //
      // Text selection
      //

      virtual void selectText(character_count startPos, character_count endPos) = 0;

      //
      // Tooltip methods
      //

      virtual void showBalloonTip(TooltipInterface *ptooltip) = 0;
   };

   using TextBoxInterface = particle_interface<TextBoxSlice, ControlInterface>;

   class CLASS_DECL_INNATE_SUBSYSTEM TextBoxComposite :
      virtual public composite<TextBoxSlice, Control>
    {
    public:

      implement_compositeø(TextBox, Control, textbox)
      
       //TextBox();
        //~TextBox();
    //public:

        //
        // Text limit
        //

        virtual character_count getTextLengthLimit() { return m_ptextbox->getTextLengthLimit(); }
        virtual void setTextLengthLimit(character_count limit) { m_ptextbox->setTextLengthLimit(limit); }

        //
        // Methods for multiline textboxes
        //

        virtual int getCurrentLineIndex() { return m_ptextbox->getCurrentLineIndex(); }
        virtual int getLineCount() { return m_ptextbox->getLineCount(); }

        //
        // Get / set caret position
        //

        virtual int getCaretPos() { return m_ptextbox->getCaretPos(); }
        virtual void setCaretPos(int h, int v) { m_ptextbox->setCaretPos(h, v); }

        //
        // Text selection
        //

        virtual void selectText(character_count startPos, character_count endPos) { m_ptextbox->selectText(startPos, endPos); }

        //
        // Tooltip methods
        //

        virtual void showBalloonTip(TooltipInterface *ptooltip) { m_ptextbox->showBalloonTip(ptooltip); }
    };

   class CLASS_DECL_INNATE_SUBSYSTEM TextBox :
   virtual public TextBoxComposite,
   virtual public Control
   {
   public:


   };


} // namespace innate_subsystem




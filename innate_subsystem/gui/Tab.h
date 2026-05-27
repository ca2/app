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


#include "innate_subsystem/gui/Dialog.h"
#include "innate_subsystem/_common_header.h"
//#include "util/::string.h"

namespace innate_subsystem
{
    class TabInterface :
   virtual public ::Particle
    {
    public:
        //Tab();

       //virtual ~TabInterface() =0;
        //Tab(BaseDialog *dialog, const_char_pointer caption);

        //
        // Access methods to protected members
        //

       virtual void initialize_tab(WindowInterface *dialog, const_char_pointer caption) = 0;

        //void setCaption(const_char_pointer caption) = 0; { m_caption->setString(caption); }

       virtual void setCaption(const_char_pointer caption) = 0;

        // const_char_pointer getCaption() {
        //     return m_caption.getString();
        // }

       virtual const_char_pointer getCaption() = 0;

        //void setDialog(BaseDialog *dialog) { m_dialog = dialog; }
        //BaseDialog *getDialog() { return m_dialog; }
       virtual void setWindow(WindowInterface *dialog) = 0;
       virtual WindowInterface *getWindow() = 0;

        //
        // Method return true if tab has dialog
        //

        // virtual bool isOk() { return m_dialog != NULL; }
       virtual bool isOk() = 0;

        //
        // Changes visible state of dialog donates by this tab
        //

        virtual void setVisible(bool visible) = 0;

    // protected:
    //
    //     BaseDialog *m_dialog;
    //     ::string m_caption;
    };
   
   
   
   class CLASS_DECL_INNATE_SUBSYSTEM TabComposite :
      virtual public Composite <TabInterface>
   {
   public:


      ImplementCompositeø(Tab, tab);

      //Tab();

      //~Tab() override;
      //Tab(BaseDialog *dialog, const_char_pointer caption);

      //
      // Access methods to protected members
      //

      void initialize_tab(WindowInterface * pwindow, const_char_pointer caption) override
      {

         m_ptab->initialize_tab(pwindow, caption);
      }

      //void setCaption(const_char_pointer caption) override; { m_caption->setString(caption); }

      void setCaption(const_char_pointer caption) override { m_ptab->setCaption(caption);
      }

      // const_char_pointer getCaption() {
      //     return m_caption.getString();
      // }

      const_char_pointer getCaption() override { return m_ptab->getCaption();
      }

      //void setDialog(BaseDialog *dialog) { m_dialog = dialog; }
      //BaseDialog *getDialog() { return m_dialog; }
      void setWindow(WindowInterface* dialog) override { m_ptab->setWindow(dialog);
      }
      WindowInterface* getWindow() override { return m_ptab->getWindow();
      }

      //
      // Method return true if tab has dialog
      //

      // bool isOk() { return m_dialog != NULL; }
      bool isOk() override
      { return m_ptab->isOk();
      }

      //
      // Changes visible state of dialog donates by this tab
      //

      void setVisible(bool visible) override { m_ptab->setVisible(visible);
      }

      // protected:
      //
      //     BaseDialog *m_dialog;
      //     ::string m_caption;
   };


   class CLASS_DECL_INNATE_SUBSYSTEM TabAggregate :
   virtual public Aggregate <TabComposite, Control>
   {
   public:

      ImplementAggregateø(Tab, Control)

   };


   class CLASS_DECL_INNATE_SUBSYSTEM Tab :
virtual public Object<TabAggregate>
   {
   public:

      ImplementObjectø(Tab)

   };


} // namespace innate_subsystem



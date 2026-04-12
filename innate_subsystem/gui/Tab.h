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


//#include "innate_subsystem/Dialog.h"
#include "innate_subsystem/_common_header.h"
//#include "util/::string.h"

namespace subsystem_apex
{
    class TabInterface :
   virtual public ::subsystem::particle_interface<TabInterface>
    {
    public:
        //Tab();

       //virtual ~TabInterface() =0;
        //Tab(BaseDialog *dialog, const char *caption);

        //
        // Access methods to protected members
        //

       virtual void initialize_tab(DialogInterface *dialog, const char *caption) = 0;

        //void setCaption(const char *caption) = 0; { m_caption->setString(caption); }

       virtual void setCaption(const char *caption) = 0;

        // const char *getCaption() {
        //     return m_caption.getString();
        // }

       virtual const char *getCaption() = 0;

        //void setDialog(BaseDialog *dialog) { m_dialog = dialog; }
        //BaseDialog *getDialog() { return m_dialog; }
       virtual void setDialog(DialogInterface *dialog) = 0;
       virtual DialogInterface *getDialog() = 0;

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
   
   
   
   class CLASS_DECL_APEX Tab :
      virtual public ::subsystem::composite <TabInterface>
   {
   public:


      Tab();

      ~Tab() override;
      //Tab(BaseDialog *dialog, const char *caption);

      //
      // Access methods to protected members
      //

      void initialize_tab(DialogInterface *dialog, const char *caption) override;

      //void setCaption(const char *caption) override; { m_caption->setString(caption); }

      void setCaption(const char *caption) override;

      // const char *getCaption() {
      //     return m_caption.getString();
      // }

      const char *getCaption() override;

      //void setDialog(BaseDialog *dialog) { m_dialog = dialog; }
      //BaseDialog *getDialog() { return m_dialog; }
      void setDialog(DialogInterface *dialog) override;
      DialogInterface *getDialog() override;

      //
      // Method return true if tab has dialog
      //

      // bool isOk() { return m_dialog != NULL; }
      bool isOk() override;

      //
      // Changes visible state of dialog donates by this tab
      //

      void setVisible(bool visible) override;

      // protected:
      //
      //     BaseDialog *m_dialog;
      //     ::string m_caption;
   };


    //#endif
} // namespace subsystem_apex



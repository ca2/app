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

//#include "winhdr.h"

//#include "Singleton.h"
namespace subsystem
{
   /**
    * Loader of resources from resource files linked with application.
    *
    * Singleton without support of "lazy" initialization.
    */
   //class ResourceLoader : public Singleton<ResourceLoader>
   class CLASS_DECL_ACME resource_loader :
      virtual public ::particle
   {
   public:
      /**
       * Initializes resource loader singleton.
       * @param appInst windwos application instance.
       */
      //resource_loader(HINSTANCE appInst);
      resource_loader();
      /**
       * Frees resource loader singleton.
       */
      ~resource_loader() override;

      /**
       * Loads standart icon from resources.
       * @param iconName icon name.
       * @return icon handle of 0 if cannot load icon.
       */
      //HICON loadStandartIcon(const TCHAR *iconName);

      /**
       * Loads icon from resources.
       * @param iconName icon name.
       * @return icon handle of 0 if cannot load icon.
       */
      //virtual ::pointer < innate_ui::icon > loadIconByIntResource(int iId);

      /**
       * Loads string from resources.
       * @param [in] id identifier of string in resource file.
       * @param [out] string storage for string from resources.
       * @return true if string is loaded, false otherwise.
       */
      virtual bool loadString(unsigned int id, ::string & str);
      virtual ::string loadString(unsigned int id);

      /**
       * Loads accelerator from resources.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of accelerator if it's loaded.
       */
      //HACCEL loadAccelerator(UINT id);

      /**
       * Loads standart cursor.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of cursor if it's loaded.
       */
      //HCURSOR loadStandardCursor(const TCHAR *id);
      /**
       * Loads cursor from resources.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of cursor if it's loaded.
       */
      //HCURSOR loadCursor(UINT id);
      //virtual ::pointer < innate_ui::icon > loadCursor(unsigned int id);

   //protected:
      /**
       * Application instance.
       */
     // HINSTANCE m_appInstance;
   };

   //#endif
} // namespace subsystem




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


#include "acme/subsystem/resource_loader.h"
#include "drawing/Icon.h"

//#include "winhdr.h"

//#include "Singleton.h"
namespace innate_subsystem
{
   /**
    * Loader of resources from resource files linked with application.
    *
    * Singleton without support of "lazy" initialization.
    */
   //class ResourceLoader : public Singleton<ResourceLoader>
   class CLASS_DECL_APEX resource_loader :
      virtual public ::subsystem::resource_loader
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
      ::pointer < IconInterface >  loadStandartIcon(const char *iconName);

      /**
       * Loads icon from resources.
       * @param iconName icon name.
       * @return icon handle of 0 if cannot load icon.
       */
      virtual ::pointer < IconInterface > loadIconByIntResource(int iId);

      ::pointer < IconInterface > loadIcon(const char* iconName);

      // /**
      //  * Loads string from resources.
      //  * @param [in] id identifier of string in resource file.
      //  * @param [out] string storage for string from resources.
      //  * @return true if string is loaded, false otherwise.
      //  */
      // virtual bool loadString(unsigned int id, ::string & str);
      // virtual ::string loadString(unsigned int id);

      /**
       * Loads accelerator from resources.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of accelerator if it's loaded.
       */
      //HACCEL loadAccelerator(unsigned int id);

      /**
       * Loads standart cursor.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of cursor if it's loaded.
       */
      //HCURSOR loadStandardCursor(const char *id);
      /**
       * Loads cursor from resources.
       * @param [in] id identifier of accelerator in resource file.
       * @return handle of cursor if it's loaded.
       */
      //HCURSOR loadCursor(unsigned int id);
      virtual ::pointer < IconInterface > loadCursor(unsigned int id);

   //protected:
      /**
       * Application instance.
       */
     // HINSTANCE m_appInstance;
   };

   //#endif
} // namespace innate_subsystem




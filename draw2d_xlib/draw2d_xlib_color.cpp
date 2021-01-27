 /**
 *
 * \file CColor.cpp
 * \brief This file contains the CColor class implementation.
 * \author Vladimir Klubkov (aka marked)
 *
 * Last changes date:
 * \date 15.03.2011
 *
 * Copyright 2011 Vladimir Klubkov <marked-one@yandex.ru>
 *
 * This file is part of OOXlib.
 *
 * OOXLib is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * OOXlib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OOXlib; if not, you can try to find  it here:
 * http://www.gnu.org/licenses/gpl.txt
 * or write to the Free Software Foundation, Inc., 59 Temple Place,
 * Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include "framework.h"


namespace draw2d_xlib
{


  /**
    * Constructor. Creates the default color.
    * \param pXServerConnection A pointer to the CXServerConnection object.
    * \param pScreen A pointer to the CScreen object.
    */
   color::color()
   {

      m_pdisplay = nullptr;
      m_colormap = None;
      __zero(m_color);

   }


   color::~color()
   {

      destroy();

   }

   /**
    * Constructor. Creates the color.
    * \param pXServerConnection A pointer to the CXServerConnection object.
    * \param pScreen A pointer to the CScreen object.
    * \param iRed Input parameter, red color, 0 to 255.
    * \param iGreen Input parameter, green color, 0 to 255.
    * \param iBlue Input parameter, blue color, 0 to 255.
    */
   bool color::create(Display * pdisplay, int iScreen, byte bRed, byte bGreen, byte bBlue, byte bAlpha)
   {

      destroy();

      if(pdisplay == nullptr)
      {

         return false;

      }

      m_pdisplay = pdisplay;

      // Create the colormap.
      m_colormap = ::XDefaultColormap(m_pdisplay, iScreen);

      // Create the color.
      // Magic constant - 257 - is 65535/255. We convert here every value from 256 to 65536 colors.
      m_color.red     = static_cast<short>(bRed)   * 257;
      m_color.green   = static_cast<short>(bGreen) * 257;
      m_color.blue    = static_cast<short>(bBlue)  * 257;
      m_color.flags   = DoRed | DoGreen | DoBlue;

      // Allocate color.
      // XAllocColor can generate a BadColor error.
      if(0 == ::XAllocColor(m_pdisplay, m_colormap, &m_color))
      {

         m_pdisplay == nullptr;

         return false;

      }

      return true;

   }

   /**
    * Destructor. Frees the allocated color.
    */
   bool color::destroy()
   {

      if(m_pdisplay == nullptr)
         return true;

      // We need at least one pixel.
      int pixelCount = 1;

      unsigned long planes = 0;

      // Create array of pixels.
      unsigned long pixels[pixelCount + 1];

      // Become the color pixel into the array.
      pixels[0] = m_color.pixel;

      // And yes! Now we are able to free the color.
      // XFreeColors can generate BadAccess , BadColor , and BadValue errors.
      ::XFreeColors(m_pdisplay, m_colormap, pixels, pixelCount, planes);

      m_pdisplay = nullptr;

      m_colormap = None;

      __zero(m_color);

      return true;

   }


} // namespace draw2d_xlib







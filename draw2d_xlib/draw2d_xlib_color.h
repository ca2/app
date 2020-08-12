/**
 *
 * \file CColor.h
 * \brief This file contains the CColor class declaration.
 * \author Vladimir Klubkov (aka marked)
 *
 * Last changes date:
 * \date 06.03.2011
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

namespace draw2d_xlib
{


   class CLASS_DECL_BASE color
   {
   public:


      Display *   m_pdisplay;
      ::Colormap  m_colormap;
      ::XColor    m_color;


      color();
      ~color();


      bool create(Display * pdisplay, int iScreen, byte bRed, byte bGreen, byte bBlue, byte bAlpha);
      bool destroy();


   };


} // namespace draw2d_xlib

﻿/*
  TurboC, a library for porting Borland Turbo C to GNU gcc.
  Copyright 2002 Ronald S. Burkey
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  
  Contact Ron Burkey at info@sandroid.org.

  Filename:	ellipse.c
  Purpose:	A Borland Turbo C graphics.h function replacement,
  		for porting to *nix.
  Mod history:	05/27/02 RSB	Split off from arc.c.

*/

#ifdef WITH_X

//#include "graphics.h"

//----------------------------------------------------------------------------

void
ellipse (int x, int y, int stangle, int endangle, int xradius, int yradius)
{
  //struct linesettingstype Settings;
  //getlinesettings (&Settings);
  //if (Settings.linestyle != SOLID_LINE || Settings.thickness != NORM_WIDTH)
  //  setlinestyle (SOLID_LINE, 0, TcLinestyle.thickness);
  //// Convert to viewport coordinates.
  //x += TcViewLeft - xradius;
  //y += TcViewTop - yradius;
  //xradius *= 2;
  //yradius *= 2;
  //// Now do the actual drawing.
  //XLockDisplay (TcDisplay);
  //XDrawArc (TcDisplay, TcPixmaps[TcActivePage], TcGc, x, y, xradius, yradius,
	 //   stangle * 64, (endangle - stangle) * 64);

   tc().ag().Arc(x,y,xradius * 2,yradius * 2,stangle,endangle);
   tc().defer_synch();

  //if (TcActivePage == TcVisualPage)
  //  {
  //    XDrawArc (TcDisplay, TcWindow, TcGc, x, y, xradius, yradius,
		//stangle * 64, (endangle - stangle) * 64);
  //    XSync (TcDisplay, False);
  //  }
  //XUnlockDisplay (TcDisplay);
  //if (Settings.linestyle != SOLID_LINE || Settings.thickness != NORM_WIDTH)
  //  setlinestyle (Settings.linestyle, Settings.upattern, Settings.thickness);
}

#endif // WITH_X

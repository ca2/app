/*
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

  Filename:	setXXXXpage.c
  Purpose:	A Borland Turbo C graphics.h function replacement,
  		for porting to *nix.
  Mod history:	05/08/02 RSB	Created.
*/

#ifdef WITH_X

#include "graphics.h"

//----------------------------------------------------------------------------

void
setvisualpage (int page)
{
  int OldWritemode;
  int Left, Top, Right, Bottom, Clip;
  if (page == TcVisualPage)
    return;
  OldWritemode = TcWritemode;
  if (OldWritemode != COPY_PUT)
    setwritemode (COPY_PUT);
  Left = TcViewLeft;
  Top = TcViewTop;
  Right = TcViewRight;
  Bottom = TcViewBottom;
  Clip = TcViewClip;
  setviewport (0, 0, TcXresolution - 1, TcYresolution - 1, 0);
  TcVisualPage = page;
  // Now do the actual drawing.
  XLockDisplay (TcDisplay);
  XCopyArea (TcDisplay, TcPixmaps[TcVisualPage], TcWindow,
	     TcGc, 0, 0, TcXresolution, TcYresolution, 0, 0);
  XSync (TcDisplay, False);
  XUnlockDisplay (TcDisplay);
  setviewport (Left, Top, Right, Bottom, Clip);
  if (OldWritemode != TcWritemode)
    setwritemode (OldWritemode);
}

//----------------------------------------------------------------------------

void
setactivepage (int page)
{
  TcActivePage = page;
}

#endif // WITH_X

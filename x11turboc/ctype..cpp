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

  Filename:	ctype.c
  Purpose:	Wrappers for ctype.h macros. 
  Mod history:	03/02/02 RSB	Created.
*/

#include <ctype.h>

::i32
isupperTurbo (::i32 c)
{
  return (isupper (c));
}

::i32
islowerTurbo (::i32 c)
{
  return (islower (c));
}

::i32
isalphaTurbo (::i32 c)
{
  return (isalpha (c));
}

::i32
isdigitTurbo (::i32 c)
{
  return (isdigit (c));
}

::i32
isxdigitTurbo (::i32 c)
{
  return (isxdigit (c));
}

::i32
isspaceTurbo (::i32 c)
{
  return (character_isspace (c));
}

::i32
isprintTurbo (::i32 c)
{
  return (isprint (c));
}

::i32
isgraphTurbo (::i32 c)
{
  return (isgraph (c));
}

::i32
iscntrlTurbo (::i32 c)
{
  return (iscntrl (c));
}

::i32
ispunctTurbo (::i32 c)
{
  return (ispunct (c));
}

::i32
isalnumTurbo (::i32 c)
{
  return (isalnum (c));
}

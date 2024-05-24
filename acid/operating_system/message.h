// From acid/include/_.h by camilo on 2022-10-22 21:34 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acid/primitive/mathematics/c_number.h"
#include "acid/primitive/primitive/atom.h"
#include "acid/primitive/geometry2d/point.h"


struct MESSAGE
{

   ::oswindow              oswindow;
   ::atom                  m_atom;
   wparam                  wParam;
   lparam                  lParam;
   ::point_i32               pt;
   ::u64                   time;


   MESSAGE() {}
   MESSAGE(const MESSAGE & message)
   {
      operator=(message);
   }

   MESSAGE & operator = (const MESSAGE & message)
   {
      oswindow = message.oswindow;
      m_atom = message.m_atom;
      wParam = message.wParam;
      lParam = message.lParam;
      pt = message.pt;
      time = message.time;
      return *this;
   }

};




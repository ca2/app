// From acme/include/_.h by camilo on 2022-10-22 21:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/atom.h"


struct MESSAGE
{

   ::oswindow              oswindow;
   ::atom                  m_atom;
   wparam                  wParam;
   lparam                  lParam;
   POINT_I32               pt;
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




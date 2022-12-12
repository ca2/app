﻿#include "framework.h"
#include "message.h"


namespace message
{


   //message::message(const ::atom & atom) :
   //{

   //   //common_construct();

   //}


   //message::message(enum_message emessage)
   //{

   //   common_construct(emessage);

   //}


   message::~message()
   {

   }



   //bool message::route_message()
   //{

   //   return m_bRet;

   //}

   bool message::route_message()
   { 
      
      m_pdispatchera->data()[m_iRouteIndex].m_functionHandler(this); 
      
      return m_bRet; 
   
   }


   bool message::all_previous()
   {

      while (m_iRouteIndex >= 0)
      {

         bool bRet = previous();

         if (bRet)
         {

            break;

         }

      }

      return true;

   }


   bool message::previous() 
   { 

      if (--m_iRouteIndex < 0)
      {

         return false;

      }

      if (m_pdispatchera->data())
      {

         m_pdispatchera->data()[m_iRouteIndex].m_functionHandler(this);

      }

      return m_bRet; 
   
   }


   void message::set_lresult(lresult lresult)
   {

      m_lresult = lresult;

   }


   //void message::set(oswindow oswindow, ::windowing::window * playeredUserPrimitive, const ::atom & atom, wparam wparam, ::lparam lparam, const ::point_i32 & point)
   void message::set(oswindow oswindow, ::windowing::window* playeredUserPrimitive, const ::atom& atom, wparam wparam, ::lparam lparam)
   {
      
      //initialize(playeredUserPrimitive);

      m_oswindow = oswindow;

      m_atom = atom;

      m_wparam = wparam;

      m_lparam = lparam;

   }


   ::u32 translate_to_os_message(const ::atom& atom)
   {

      return atom.u32();

   }


} // namespace message




#include "framework.h"
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


   message::message(const ::atom & atom)
   { 
      
      m_atom = atom;
      
      m_union.m_p = nullptr;
      m_pdispatchera = nullptr;
      m_pchannel = nullptr;
      m_wparam = {};
      m_iRouteIndex = -1;
      m_iParam = 0;
      m_bRet = false;
      m_uiMessageFlags = 0;
      m_estatus = ::success;
      m_lresult = 0;

   }


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
   //void message::set(oswindow oswindow, ::windowing::window* playeredUserPrimitive, const ::atom& atom, wparam wparam, ::lparam lparam)
   //{
   //   
   //   //initialize(playeredUserPrimitive);

   //   m_oswindow = oswindow;

   //   m_atom = atom;

   //   m_wparam = wparam;

   //   m_lparam = lparam;

   //}


   ::u32 translate_to_os_message(const ::atom& atom)
   {

      return atom.as_u32();

   }


   message & message::operator = (const message & message)
   {

      if (this != &message)
      {
         
         m_pdispatchera = message.m_pdispatchera;
         m_pchannel = message.m_pchannel;
         m_oswindow = message.m_oswindow;
         m_eflagMessage = message.m_eflagMessage;
         //m_iRouteIndex = message.m_iRouteIndex;
         m_iParam = message.m_iRouteIndex;
         //m_bRet = message.m_iRouteIndex;
         m_uiMessageFlags = message.m_uiMessageFlags;
         //m_estatus = message.m_estatus;
         //m_actioncontext = message.m_estatus;
         m_pointMessage = message.m_pointMessage;
         //m_bProbing = message.m_bProbing;
         //m_bCommand = message.m_bCommand;

      }


      return *this;

   }


} // namespace message




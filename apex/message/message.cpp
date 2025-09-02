#include "framework.h"
#include "message.h"


namespace message
{


   // message::message(const ::atom & atom) :
   //{

   //   //common_construct();

   //}


   // message::message(enum_message emessage)
   //{

   //   common_construct(emessage);

   //}


   message::message(::user::enum_message eusermessage)
   {

      m_eusermessage = eusermessage;

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


   message::~message() {}


   // bool message::route_message()
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


   void message::set_lresult(lresult lresult) { m_lresult = lresult; }


   // void message::set(oswindow oswindow, ::windowing::window * playeredUserPrimitive, ::user::enum_message
   // eusermessage, ::wparam wparam, ::lparam lparam, const ::int_point & point) void message::set(oswindow oswindow,
   // ::windowing::window* playeredUserPrimitive, ::user::enum_message eusermessage, ::wparam wparam, ::lparam
   // lparam)
   //{
   //
   //    //initialize(playeredUserPrimitive);

   //   m_oswindow = oswindow;

   //   id() = atom;

   //   m_wparam = wparam;

   //   m_lparam = lparam;

   //}


   unsigned int translate_to_os_message(const ::atom &atom) { return atom.as_unsigned_int(); }


   message &message::operator=(const message &message)
   {

      if (this != &message)
      {

         m_pdispatchera = message.m_pdispatchera;
         m_pchannel = message.m_pchannel;
         m_oswindow = message.m_oswindow;
         m_eflagMessage = message.m_eflagMessage;
         // m_iRouteIndex = message.m_iRouteIndex;
         m_iParam = message.m_iRouteIndex;
         // m_bRet = message.m_iRouteIndex;
         m_uiMessageFlags = message.m_uiMessageFlags;
         // m_estatus = message.m_estatus;
         // m_actioncontext = message.m_estatus;
         m_pointMessage = message.m_pointMessage;
         // m_bProbing = message.m_bProbing;
         // m_bCommand = message.m_bCommand;
      }


      return *this;
   }


   ::user::activation_token *message::user_activation_token() { return m_actioncontext.user_activation_token(); }


} // namespace message




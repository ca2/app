#include "framework.h"


namespace message
{


   message::message()
   {

      common_construct();

   }


   message::message(::message::e_type etype)
   {

      common_construct(etype);

   }


   message::~message()
   {

   }


   void message::common_construct(::message::e_type etype)
   {

      m_id = etype;
      m_pchannel = nullptr;
      m_wparam = 0;
      m_iRouteIndex = -1;
      m_iParam = 0;
      m_bRet = false;
      m_uiMessageFlags = 0;
      m_estatus = ::success;
      m_lresult = 0;

   }



   //bool message::route_message()
   //{

   //   return m_bRet;

   //}


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


   bool message::previous() { if (--m_iRouteIndex < 0) return false; m_proutea.m_p->m_pData[m_iRouteIndex].m_p->m_pmessageable.m_p->on_message(this); return m_bRet; }


   void message::set_lresult(LRESULT lresult)
   {

      m_lresult = lresult;

   }


   void message::set(::layered * playeredUserPrimitive, UINT uiMessage, WPARAM wparam, ::lparam lparam)

   {
      
      set_context_object(playeredUserPrimitive);

      m_id = ::message::id(::id((iptr) uiMessage), ::message::type_message);

      m_wparam = wparam;

      m_lparam = lparam;

   }


} // namespace message




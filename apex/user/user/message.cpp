// From aura/user/user/message by camilo on 2023-05-07 23:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "windowing/window.h"
#include "message.h"
//#include "interaction_impl.h"
//#include "interaction.h"


namespace user
{


   message::message()
   {

      //m_union.m_p = nullptr;
      m_uiMessageFlags = 0;
      m_lresult = 0;
      m_bDestroyed = false;
      m_bDoSystemDefault = true;

   }





   //user::user(oswindow oswindow, ::layered * playeredUserPrimitive, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   m_uiMessageFlags = 0;
   //   m_lresult = 0;
   //   m_bDestroyed = false;
   //   m_bDoSystemDefault = true;
   //   set(oswindow, playeredUserPrimitive, atom, wparam, lparam);


   //   //papp->tellme_destroyed(puserinteraction, &m_bDestroyed);

   //}


   //user::user(const user & user)
   //{

   //   m_uiMessageFlags = base.m_uiMessageFlags;
   //   m_pwindow = base.m_pwindow;
   //   m_atom = base.m_atom;
   //   m_wparam = base.m_wparam;
   //   m_lparam = base.m_lparam;
   //   m_bConditional = base.m_bConditional;
   //   m_bReflect = base.m_bReflect;
   //   m_bDoSystemDefault = base.m_bDoSystemDefault;
   //   m_bDestroyed = false;

   //   //papp->tellme_destroyed(m_puserinteraction, &m_bDestroyed);

   //}

   message::~message()
   {

      //if(m_puserinteraction != nullptr)
      //{

      //   synchronous_lock synchronouslock(get_ui_destroyed_mutex());

      //   if(m_bDestroyed)
      //   {

      //      debug_print("Window Already Destroyed");

      //   }
      //   else
      //   {

      //      papp->tellme_destroyed(m_puserinteraction, &m_bDestroyed, false);

      //   }

      //}

   }


   //void message::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   //{

   //   m_pwindow = pwindow;

   //   ::message::message::set(oswindow, pwindow, atom, wparam, lparam);

   //}


   //base & base::operator = (const base & base)
   //{

   //   if (this != &base)
   //   {

   //      copy_this(base);

   //   }

   //   return *this;

   //}


   //void base::copy_this(const base & base)
   //{

   //   m_puserinteraction = base.m_puserinteraction;
   //   m_bConditional = base.m_bConditional;
   //   m_bReflect = base.m_bReflect;
   //   m_bDestroyed = base.m_bDestroyed;
   //   m_bDoSystemDefault = base.m_bDoSystemDefault;
   //   m_plresult = base.m_plresult;
   //   m_lresult = base.m_lresult;

   //}

   //void timer::set(::user::interaction_base * puserinteraction,const ::atom & atom,wparam wparam,::lparam lparam)
   //{

   //   base::set(puserinteraction,atom,wparam,lparam);

   //   m_uEvent = static_cast<::u32>(wparam);

   //}



#ifdef WINDOWS_DESKTOP

   //LPNMHDR notify::get_lpnmhdr()
   //{

   //   return (LPNMHDR)m_lparam.m_lparam;

   //}

#endif


   //::user::interaction_impl * message::userinteractionimpl()
   //{

   //   auto pwindow = window();

   //   return pwindow ? pwindow->m_puserinteractionimpl : nullptr;

   //}


   //::user::interaction * message::userinteraction()
   //{

   //   auto pimpl = userinteractionimpl();

   //   return pimpl ? pimpl->m_puserinteraction : nullptr;

   //}


   message & message::operator = (const message & message)
   {

      if (this != &message)
      {

         ::message::message::operator = (message);

         m_pchannel = message.m_pchannel;
         m_pwindow = message.m_pwindow;
         //m_bConditional = m_bConditional;
         //m_bReflect = m_bReflect;
         //m_bDestroyed = m_bDestroyed;
         //m_bDoSystemDefault = m_bDoSystemDefault;

      }

      return *this;

   }



} // namespace user





//
//  macos_window.cpp
//  base
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2013-09-17.
//
//

#include "framework.h"
#include "window_impl.h"
#include "oswindow_data.h"
#include "acme/platform/message_queue.h"


UIWindow * __uiwindow(oswindow oswindow)
{
   
   return (UIWindow *) oswindow->window();
   
}

//oswindow_dataptra * g_poswindowdataptra = nullptr;


//int oswindow_find(nswindow window)
//{
//
//   for(int i = 0; i < g_poswindowdataptra->get_count(); i++)
//   {
//      if(g_poswindowdataptra->element_at(i)->m_nswindow == window)
//      {
//         return i;
//      }
//   }
//
//   return -1;
//
//}

//oswindow_data * oswindow_get(nswindow window)
//{
//
//   auto pFind = oswindow_find(window);
//
//   if(::is_set(pFind))
//      return g_poswindowdataptra->element_at(iFind);
//
//   ::oswindow_data * pdata = aaa_primitive_new ::oswindow_data;
//
//   pdata->m_nswindow    = window;
//
//   g_poswindowdataptra->add(pdata);
//
//   return pdata;
//
//}


oswindow_data::oswindow_data()
{

   m_nswindow  = nullptr;
   m_pimpl     = nullptr;

}


oswindow_data::oswindow_data(nswindow window)
{

   m_nswindow  = window;
   m_pimpl     = nullptr;

}


oswindow_data::oswindow_data(const oswindow_data & oswindow)
{

   m_nswindow  = oswindow.m_nswindow;
   m_pimpl     = oswindow.m_pimpl;

}


oswindow_data::~oswindow_data()
{

}


oswindow_data & oswindow_data::operator = (const oswindow_data & oswindow)
{

   if(&oswindow != this)
   {

      m_nswindow  = oswindow.m_nswindow;
      m_pimpl     = oswindow.m_pimpl;

   }

   return *this;

}


//bool oswindow_erase(nswindow window)
//{
//
//   auto pFind = oswindow_find(window);
//
//   if(::is_null(pFind))
//      return false;
//
//   g_poswindowdataptra->erase_at(iFind);
//
//   return true;
//
//}


void oswindow_data::set_user_interaction_impl(::windowing::window * pimpl)
{

   if(is_null())
      throw ::exception(::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));

   m_pimpl = pimpl;

}


::windowing::window * oswindow_data::get_user_interaction_impl()
{

   if(is_null())
      return nullptr;

   return m_pimpl;

}

::windowing::window * oswindow_data::get_user_interaction_impl() const
{

   if(is_null())
      return nullptr;

   return m_pimpl;

}

::user::interaction * oswindow_data::get_user_interaction()
{

   if(is_null())
      return nullptr;

   if(m_pimpl == nullptr)
      return nullptr;

   return m_pimpl->m_puserinteraction;

}

::user::interaction * oswindow_data::get_user_interaction() const
{

   if(is_null())
      return nullptr;

   if(m_pimpl == nullptr)
      return nullptr;

   return m_pimpl->m_puserinteraction;

}


oswindow oswindow_data::get_parent()
{

   if(is_null())
      return nullptr;

   return m_pimpl->m_puserinteraction->GetParentHandle();

}


oswindow oswindow_data::set_parent(oswindow oswindow)
{

   if(is_null())
      return nullptr;

   ::oswindow oswindowOldParent = get_parent();

   if(oswindow == nullptr || oswindow->m_pimpl == nullptr || oswindow->m_pimpl->m_puserinteraction == nullptr)
   {

      m_pimpl->m_puserinteraction->SetParent(nullptr);

   }
   else
   {

      m_pimpl->m_puserinteraction->SetParent(oswindow->m_pimpl->m_puserinteraction);

   }

   return oswindowOldParent;

}

bool oswindow_data::is_child(::oswindow oswindow)
{

   if (oswindow == nullptr || oswindow->m_pimpl == nullptr || oswindow->m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   if (m_pimpl == nullptr || m_pimpl->m_puserinteraction == nullptr)
   {

      return false;

   }

   return m_pimpl->m_puserinteraction->is_child(oswindow->m_pimpl->m_puserinteraction);

}

iptr oswindow_data::get_window_long_ptr(iptr iIndex)
{

   if(is_null())
      return 0;

   return m_pimpl->m_puserinteraction->get_window_long_ptr((int)iIndex);

}


iptr oswindow_data::set_window_long_ptr(iptr iIndex, iptr iNewLong)
{

   if(is_null())
      return 0;

   return m_pimpl->m_puserinteraction->set_window_long_ptr((int)iIndex, iNewLong);

}


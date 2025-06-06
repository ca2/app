#pragma once


//#include "android_vsnord_native_app_glue.h"


namespace boot
{


   class thread_base;
   class interaction_impl;


} // namespace boot


struct oswindow_data;

typedef address_array < oswindow_data * > oswindow_dataptra;

namespace boot
{


   class thread_axis;
   class interaction_impl;


} // namespace boot


namespace user
{


   class interaction_axis;
   class interaction;


} // namespace user


typedef address_array < oswindow_data * > oswindow_dataptra;

/*
* Copyright (C) 2010 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

struct CLASS_DECL_ACME oswindow_data
{

//#ifdef __ANDROID__
//
//   engine                        m_engine;
//
//#endif

   bool                          m_bMessageOnlyWindow;
   ::windowing::window *    m_pimpl;
   htask                       m_htask;
   color32_t *                    m_pcolorref;
   //RECT32                          m_rect;
   bool                          m_bDestroying;
   bool                          m_bIconic;
   message_queue *                          m_pmq;
//xx

   static oswindow_dataptra * s_pdataptra;
   static ::pointer< ::mutex > s_pmutex;


   oswindow_data();
   oswindow_data(::user::interaction_axis * puiaxisMessageOnlyWindow);
   oswindow_data(const void * p);
   oswindow_data(const LPARAM & lparam);
   oswindow_data(const WPARAM & wparam);


   ~oswindow_data();



   operator void * ()
   {
      return this;
   }

   operator void * () const
   {
      return (void *) this;
   }

   oswindow_data & operator = (const oswindow_data & interaction_impl);

   bool operator == (const void * p) const
   {
      return this == p;
   }

   bool operator != (const void * p) const
   {
      return this != p;
   }


   int store_name(const ::scoped_string & scopedstr);
   int select_input(int iInput);
   int select_all_input();
   int map_window();

   void set_impl(::windowing::window * pimpl);
   ::windowing::window * get_impl();
   ::windowing::window * get_impl() const;
   ::user::interaction * get_user_interaction();
   ::user::interaction * get_user_interaction() const;


   void post_nc_destroy();


   bool is_child(oswindow oswindowCandidateChildOrDescendant); // or descendant
   oswindow get_parent();
   oswindow set_parent(oswindow oswindowNewParent);
   long get_state();
   bool is_iconic();
   bool is_window_visible();
   bool show_window(::e_display edisplay);
   LONG_PTR get_window_long_ptr(int nIndex);
   LONG_PTR set_window_long_ptr(int nIndex, LONG_PTR l);
   bool client_to_screen(POINT32 * lppoint);
   bool screen_to_client(POINT32 * lppoint);



   bool is_null() const
   {
      return ::is_null(this);
   }


   bool is_destroying();


};













// define portable types for 32-bit / 64-bit OS
//typedef int int_bool;
typedef unsigned char uch;
//typedef unsigned short ush;
typedef unsigned int unsigned int;
//typedef int int;


#undef
#undef


#ifndef const
#define const               const
#endif


namespace ca2
{


   class thread_base;


} // namespace ca2



class happening;


class mutex;













CLASS_DECL_ACME oswindow_data * oswindow_get(::windowing::window * pinteraction);

// Created by camilo on 2024-09-13 01:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/nano/nano.h"
#include "acme/windowing/windowing.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"


namespace innate_ui
{


   innate_ui::innate_ui()
   {


   }


   innate_ui::~innate_ui()
   {

   }


   void innate_ui::on_initialize_particle()
   {

      ::acme::department::on_initialize_particle();

      defer_create_synchronization();

   }


   void innate_ui::add_top_level_window(window * pwindow)
   {

      _synchronous_lock synchronous_lock(this->synchronization());

      m_windowa.add(pwindow);

   }


   void innate_ui::_main_post(const ::procedure & procedure)
   {

      auto psystem = system();

      auto pacmewindowing = psystem->acme_windowing();

      pacmewindowing->_main_post(procedure);      //auto pparticle = (::subparticle *)procedure.m_pbase;

      //pparticle->increment_reference_count();

      //PostThreadMessage(m_dwThread, WM_APP + 123, 0, (LPARAM)pparticle);

   }


   void innate_ui::_main_send(const ::procedure & procedure)
   {

      auto psystem = system();

      auto pacmewindowing = psystem->acme_windowing();

      pacmewindowing->_main_send(procedure);      //auto pparticle = (::subparticle *)procedure.m_pbase;

      //pparticle->increment_reference_count();

      //PostThreadMessage(m_dwThread, WM_APP + 123, 0, (LPARAM)pparticle);

   }


   ::pointer < ::innate_ui::icon > innate_ui::innate_ui_icon(const ::payload & payloadFile, const ::int_size & size)
   {

      auto picon = __øcreate < ::innate_ui::icon >();

      picon->create(payloadFile, size);

      return picon;

   }


} // namespace innate_ui


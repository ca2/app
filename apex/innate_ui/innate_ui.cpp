// Created by camilo on 2024-09-13 01:53 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/parallelization/synchronous_lock.h"


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


   void innate_ui::post(const ::procedure & procedure)
   {



   }


   void innate_ui::sync(const ::procedure & procedure)
   {

      manual_reset_event event;

      event.ResetEvent();

      post([procedure, &event]
         {

               procedure();

               event.SetEvent();

         });

      event._wait();

   }
} // namespace innate_ui


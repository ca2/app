//
// Created by camilo on 12/04-April/2022. 22:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
//#include "acme/parallelization/asynchronous.h"
//#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/platform/system.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/windowing/windowing.h"


namespace acme
{


   namespace windowing
   {


      display::display() :
         m_pointCursor2(I32_MINIMUM)

      {

         defer_create_synchronization();

         m_edisplaytype = e_display_type_none;


      }


      display::~display()
      {


      }


      void display::open_display()
      {


      }


      void display::destroy()
      {

         ::object::destroy();

      }


      void display::kick_idle()
      {



      }


      void display::display_post(const ::procedure & procedure)
      {

         //      synchronous_lock synchronouslock(this->synchronization());

         //      m_procedureaPost.add(procedure);

         //      kick_idle();

         system()->acme_windowing()->main_post(procedure);

      }


      void display::display_send(const ::procedure & procedure)
      {

         //auto bIsCurrentBranch = is_branch_current();

         //__matter_send_procedure(this, this, &display::display_post, procedure);

         system()->acme_windowing()->main_send(procedure);

      }


      // bool display::display_posted_routine_step()
      // {
      //
      //    _synchronous_lock synchronouslock(this->synchronization());
      //
      //    if (m_procedureaPost.has_element())
      //    {
      //
      //       auto function = m_procedureaPost.pick_first();
      //
      //       if (function)
      //       {
      //
      //          synchronouslock.unlock();
      //
      //          function();
      //
      //          return true;
      //
      //       }
      //
      //    }
      //
      //    return false;
      //
      // }


      ::int_size display::get_main_screen_size()
      {

         return { 800, 600 };

      }


      enum_display_type display::get_display_type()
      {

         return m_edisplaytype;

      }


      void display::initialize_display_type(enum_display_type edisplaytype)
      {

         m_edisplaytype = edisplaytype;

      }




      enum_display_type g_edisplaytype = e_display_type_none;


      enum_display_type get_display_type()
      {

         return g_edisplaytype;

      }


      void initialize_display_type(enum_display_type edisplaytype)
      {

         g_edisplaytype = edisplaytype;

      }


   } // namespace windowing


} // namespace acme




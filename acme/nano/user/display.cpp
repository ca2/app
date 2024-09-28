//
// Created by camilo on 12/04-April/2022. 22:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
//#include "acme/parallelization/asynchronous.h"
//#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/platform/system.h"
#include "acme/windowing_system/windowing_system.h"


namespace nano
{


namespace user
{


   display::display():
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


   void display::kick_idle()
   {



   }


   void display::display_post(const ::procedure & procedure)
   {

//      synchronous_lock synchronouslock(this->synchronization());

//      m_procedureaPost.add(procedure);

//      kick_idle();

      system()->windowing_system()->main_post(procedure);

   }


   void display::display_send(const ::procedure & procedure)
   {

      //auto bIsCurrentBranch = is_branch_current();

      //__matter_send_procedure(this, this, &display::display_post, procedure);

      system()->windowing_system()->main_send(procedure);

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


   ::size_i32 display::get_main_screen_size()
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




} // namespace user


} // namespace nano




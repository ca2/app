// From impact.h by camilo on 2021-01-15 18:13 <3ThomasBorregaardSorensen!!
#pragma once


#include "impact.h"
#include "aura/user/user/button.h"


namespace user
{


   template < class VIEW, typename BASE_VIEW >
   class show :
      virtual public BASE_VIEW,
      virtual public VIEW
   {
   public:







      show()
      {

      }




      virtual ~show()
      {

      }


      // ::base::application* get_app() { return ::user::impact::get_app(); }
      // ::base::session* get_session() { return ::user::impact::get_session(); }
      // ::base::system* get_system() { return ::user::impact::get_system(); }
      // ::base::user* user() override { return ::user::impact::user(); }


      virtual void initialize(::particle * pparticle) override
      {

         //auto estatus = 

         ::user::impact::initialize(pparticle);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 

         VIEW::initialize(pparticle);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }

      
      void destroy() override
      {

         ::user::impact::destroy();

         VIEW::destroy();

      }


//      virtual void assert_ok() const override
//      {
//         impact::assert_ok();
//         VIEW::assert_ok();
//
//      }
//      virtual void dump(dump_context& dumpcontext) const override
//      {
//         impact::dump(dumpcontext);
//         VIEW::dump(dumpcontext);
//      }


      virtual void install_message_routing(::channel* pchannel) override
      {

         VIEW::install_message_routing(pchannel);
         ::user::impact::install_message_routing(pchannel);

      }


      virtual void route_command(::message::command* pcommand, bool bRouteToKeyDescendant) override
      {

         ::user::impact::route_command(pcommand);

      }


      virtual void on_command(::message::command* pcommand) override
      {

         VIEW::on_command(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

         ::user::impact::on_command(pcommand);

      }


      //using ::user::impact::update;
      void handle(::topic * ptopic, ::handler_context * pcontext) override
      {

         ::user::impact::handle(ptopic, phandlercontext);

         VIEW::handle(ptopic, phandlercontext);

         ////VIEW::handle(ptopic, phandlercontext);

         //if (ptopic->m_bRet)
         //{

         //   return;

         //}

         //if (m_puserinteractionImpactNotify)
         //{

         //   m_puserinteractionImpactNotify->handle(phappening);

         //}

         //::user::interaction * puiParent = get_parent();

         //if (puiParent != nullptr)
         //{

         //   puiParent->handle(phappening);

         //   if (ptopic->m_bRet)
         //   {

         //      return;

         //   }

         //}

      }


      virtual bool pre_create_window(::user::system* pusersystem) override
      {

         if (!::user::impact::pre_create_window(pusersystem))
         {

            return false;

         }

         if (!VIEW::pre_create_window(pusersystem))
         {

            return false;

         }

         return true;

      }


      virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override
      {

         VIEW::_001OnDraw(pgraphics);

      }



      void _001CallOnDraw(::draw2d::graphics_pointer & pgraphics) override
      {

         VIEW::_001CallOnDraw(pgraphics);

      }


      ::data::data * _get_data(const ::atom & atom) override
      {

         return ::user::impact::_get_data(atom);

      }


      //virtual void handle(::topic * ptopic, ::handler_context * pcontext) override
      //{

      //   VIEW::handle(ptopic, phandlercontext);

      //   if(ptopic->m_bRet)
      //   {

      //      return;

      //   }

      //   if(m_puserinteractionImpactNotify)
      //   {

      //      m_puserinteractionImpactNotify->handle(ptopic, phandlercontext);

      //   }

      //   ::user::interaction * puiParent = get_parent();

      //   if (puiParent != nullptr)
      //   {

      //      puiParent->handle(ptopic, phandlercontext);

      //      if (ptopic->m_bRet)
      //      {

      //         return;

      //      }

      //   }



      //}

   };


} // namespace user




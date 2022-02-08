// From impact.h by camilo on 2021-01-15 18:13 <3ThomasBorregaardSørensen!!
#pragma once


namespace user
{


   template < class VIEW >
   class show :
      virtual public impact,
      virtual public VIEW
   {
   public:







      show()
      {

      }




      virtual ~show()
      {

      }


      inline ::base::application* get_application() const { return m_pcontext ? m_pcontext->m_pbaseapplication : nullptr; }
      inline ::base::session* get_session() const { return m_pcontext ? m_pcontext->m_pbasesession : nullptr; }
      inline ::base::system* get_system() const { return m_psystem ? m_psystem->m_pbasesystem : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      virtual void initialize(::object* pobject) override
      {

         //auto estatus = 

         ::user::impact::initialize(pobject);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //estatus = 

         VIEW::initialize(pobject);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      virtual void assert_ok() const override
      {
         impact::assert_ok();
         VIEW::assert_ok();

      }
      virtual void dump(dump_context& dumpcontext) const override
      {
         impact::dump(dumpcontext);
         VIEW::dump(dumpcontext);
      }


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
      void handle(::topic* ptopic, ::context* pcontext) override
      {

         ::user::impact::handle(ptopic, pcontext);

         VIEW::handle(ptopic, pcontext);

         ////VIEW::handle(ptopic, pcontext);

         //if (ptopic->get_extended_topic()->m_bRet)
         //{

         //   return;

         //}

         //if (m_puserinteractionImpactNotify)
         //{

         //   m_puserinteractionImpactNotify->handle(pevent);

         //}

         //::user::interaction * puiParent = get_parent();

         //if (puiParent != nullptr)
         //{

         //   puiParent->handle(pevent);

         //   if (ptopic->get_extended_topic()->m_bRet)
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




      //virtual void handle(::topic * ptopic, ::context * pcontext) override
      //{

      //   VIEW::handle(ptopic, pcontext);

      //   if(ptopic->get_extended_topic()->m_bRet)
      //   {

      //      return;

      //   }

      //   if(m_puserinteractionImpactNotify)
      //   {

      //      m_puserinteractionImpactNotify->handle(ptopic, pcontext);

      //   }

      //   ::user::interaction * puiParent = get_parent();

      //   if (puiParent != nullptr)
      //   {

      //      puiParent->handle(ptopic, pcontext);

      //      if (ptopic->get_extended_topic()->m_bRet)
      //      {

      //         return;

      //      }

      //   }



      //}

   };


} // namespace user




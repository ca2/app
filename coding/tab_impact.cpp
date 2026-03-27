#include "framework.h"
#include "tab_impact.h"
#include "application.h"
#include "document.h"
#include "impact.h"
#include "log_impact.h"
#include "integration.h"
#include "summary.h"
#include "acme/constant/impact.h"
#include "acme/handler/request.h"
#include "aura/user/user/system.h"
#include "berg/user/user/single_document_template.h"


namespace coding
{


   tab_impact::tab_impact()
   {

   }


   tab_impact::~tab_impact()
   {

   }


   void tab_impact::install_message_routing(::channel * pchannel)
   {

      ::user::tab_impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &tab_impact::on_message_create);

   }


   void tab_impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      get_app()->m_ptabimpact = this;

      //set_tab("Options", APP_OPTIONS_IMPACT);
      //set_tab("Integration", MAIN_IMPACT);

      //set_current_tab_by_id(MAIN_IMPACT);

   }


   void tab_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::tab_impact::_001OnNcDraw(pgraphics);

   }


   void tab_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::tab_impact::_001OnDraw(pgraphics);

   }


   void tab_impact::on_change_cur_sel()
   {

      ::user::tab_impact::on_change_cur_sel();

   }

   document* tab_impact::get_document()
   {

      return m_pdocument.cast < document >();

   }
   
   
   void tab_impact::on_create_impact(::user::impact_data * pimpactdata)
   {
      pimpactdata->m_eflag.set(::user::e_flag_hide_all_others_on_show);


      if (pimpactdata->id() == "summary")
      {

         create_impact < ::coding::summary >(pimpactdata);

         pimpactdata->m_bOk = true;

         return;

      }

      if (pimpactdata->id().m_etype == ::atom::e_type_impact
         && (pimpactdata->id().as_long_long() & e_impact_multitasking))
      {

         auto plogimpact = create_impact < ::coding::log_impact >(pimpactdata);

         auto pintegration = get_document()->m_pintegration;

         auto etaskOrdinal = (enum_task)(pimpactdata->id().as_long_long() & 7);

         plogimpact->m_etaskOrdinal = etaskOrdinal;

      }
      else
      {

         switch (pimpactdata->id().as_long_long())
         {
         case MAIN_IMPACT:
         {

            create_impact < ::coding::impact >(pimpactdata);

            pimpactdata->m_bOk = true;

            return;

         }
         break;
         }
    
      }

//      if(pimpactdata->m_atom == "options_impact")
//      {
//
//         create_impact < options_impact >(pimpactdata);
//
//      }

      ::user::tab_impact::on_create_impact(pimpactdata);

   }


   void tab_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::tab_impact::handle(ptopic, phandlercontext);

   }



} // namespace coding




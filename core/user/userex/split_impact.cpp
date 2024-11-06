#include "framework.h"
#include "base/user/user/split_pane.h"
#include "split_impact.h"


namespace userex
{


   split_impact::split_impact()
   {

   }


   split_impact::~split_impact()
   {

   }


   void split_impact::install_message_routing(::channel * pchannel)
   {

      ::user::split_impact::install_message_routing(pchannel);
      ::user::impact_host::install_message_routing(pchannel);

   }


   bool split_impact::on_new_impact_creator_data(::user::impact_data * pimpactdata)
   {

      auto iPane = pimpactdata->m_atom.as_iptr();

      if (::not_found(iPane))
      {

         return false;

      }

      auto ppane = m_panea[iPane].get();

      if (!pimpactdata->m_pplaceholder)
      {

         pimpactdata->m_pplaceholder = get_new_place_holder(ppane->m_rectangleHosting);

         ppane->m_pplaceholder = pimpactdata->m_pplaceholder;

      }

      if (ppane->m_pplaceholder == nullptr)
      {

         return false;

      }

      pimpactdata->m_pimpactdata = (void *) ppane;

      return true;

   }


   void split_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::split_impact::handle(ptopic, pcontext);
      ::user::impact_host::handle(ptopic, pcontext);

   }


   bool split_impact::on_prepare_impact_data(::user::impact_data* pimpactdata)
   {

      pimpactdata->m_pplaceholder = get_pane_holder((::collection::index) pimpactdata->m_iId);

      return true;

   }


   bool split_impact::create_pane(int iPane, bool bFixedSize, ::atom atom)
   {

      ASSERT(iPane >= 0);

      ASSERT(iPane < get_pane_count());

      auto ppane = m_panea[iPane].get();

      ppane->m_bFixedSize = bFixedSize;

      ppane->m_atom = atom;

      ::rectangle_i32 rectangle;

      rectangle = ppane->m_pplaceholder->rectangle();

      ::user::impact_data * pdata = create_impact_by_id(atom);

      if (pdata == nullptr)
      {

         return false;

      }

      return true;

   }


   void split_impact::on_command_probe(::message::command * pcommand)
   {

   }


   void split_impact::on_command(::message::command * pcommand)
   {

   }


} // namespace userex

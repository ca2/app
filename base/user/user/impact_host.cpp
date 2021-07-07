#include "framework.h"
#include "base/user/user/_user.h"



namespace user
{


   ::user::document * get_document(::user::interaction* pinteraction)
   {

      __pointer(::user::frame_window) pframewindow = pinteraction;

      if (pframewindow)
      {

         return pframewindow->get_active_document();

      }
      else
      {

         __pointer(::user::impact) pimpact = pinteraction;

         return pimpact->get_document();

      }

      return nullptr;

   }

   impact_host::impact_host()
   {

   }


   impact_host::~impact_host()
   {

   }


   ::count impact_host::get_view_count()
   {

      return m_impactdatamap.get_count();

   }


   void impact_host::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &impact_host::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact_host::_001OnDestroy);

   }


   void impact_host::on_message_create(::message::message * pmessage)
   {

   }


   void impact_host::_001OnDestroy(::message::message * pmessage)
   {

      m_impactdatamap.erase_all();

   }


   __pointer(::user::impact) impact_host::get_view()
   {

      return nullptr;

   }


   id impact_host::get_view_id()
   {

      return id(::e_type_empty);

   }


   ::user::document * impact_host::get_view_document()
   {

      return ::user::get_document(get_view());

   }


   bool impact_host::on_prepare_impact_data(impact_data * pimpactdata)
   {

      UNREFERENCED_PARAMETER(pimpactdata);

      return false;

   }


   bool impact_host::on_after_create_impact_data(impact_data * pimpactdata)
   {

      UNREFERENCED_PARAMETER(pimpactdata);

      return false;

   }


   impact_data * impact_host::new_impact_data(const id & id, const ::id & idTitle)
   {

      auto pimpactdata  = __new(::user::impact_data(id, idTitle));

      m_impactdatamap[id] = pimpactdata;

      return pimpactdata;

   }


   impact_data * impact_host::allocate_impact_data(const id & id, const ::id & idTitle)
   {

      impact_data * pimpactdata = new_impact_data(id, idTitle);

      try
      {

         on_prepare_impact_data(pimpactdata);

      }
      catch (const ::exception::exception & exception)
      {

         auto ptask = ::get_task();

         if (ptask)
         {

            ptask->handle_exception(exception);

         }

         return nullptr;

      }
      catch (...)
      {

      }

      try
      {

         on_after_create_impact_data(pimpactdata);

      }
      catch (const ::exception::exception & exception)
      {

         handle_exception(exception);

      }
      catch (...)
      {

      }

      return pimpactdata;

   }


   impact_data * impact_host::create_impact(const ::id & id, const ::string & strTitle,  impact_creator * pcreator)
   {

      impact_data * pimpactdata = allocate_impact_data(id, strTitle);

      try
      {

         create_impact(pimpactdata);

      }
      catch (const exception& exception)
      {

         if (exception.m_id == id)
         {

            //::acme::del(pimpactdata);
            // todo
            //erase_impact_data(pimpactdata);

            return nullptr;

         }

         throw ::move(exception);


      }
      catch (const ::exception::exception & exception)
      {

         handle_exception(exception);

         return nullptr;

      }
      catch(...)
      {

         return nullptr;

      }

      if (!pimpactdata->m_bOk)
      {

         //::acme::del(pimpactdata);
         // todo
         //erase_impact_data(pimpactdata);

         return nullptr;

      }

      return pimpactdata;

   }


   void impact_host::create_impact(impact_data * pimpactdata, impact_creator * pcreator)
   {

      auto puserinteractionpointeraChild = pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild;
      if (puserinteractionpointeraChild && puserinteractionpointeraChild->interaction_count() > 0)
      {

         return;

      }

      if(!_create_impact(pcreator, pimpactdata))
      {

         auto papplication = get_application();

         if (!_create_impact(papplication->cast< ::user::impact_creator>(), pimpactdata))
         {

            if (!_create_impact(this, pimpactdata))
            {

               return;

            }

         }

      }

      on_after_host_impact(pimpactdata);

   }


   bool impact_host::_create_impact(impact_creator * pcreator, impact_data * pimpactdata)
   {

      if(!::is_set(pcreator))
      {

         return false;

      }

      try
      {

         if(!pcreator->create_impact(pimpactdata))
         {

            return false;

         }
      }
      catch (const exception& exception)
      {
         if (exception.m_id == pimpactdata->m_id)
         {

            //::acme::del(pimpactdata);

            return false;

         }

         throw ::move(exception);

      }
      catch (const ::exception::exception & exception)
      {

         m_impactdatamap.erase_key(pimpactdata->m_id);

         handle_exception(exception);

         return false;

      }
      catch (...)
      {

         return false;

      }

      return false;

   }


/*
   ::user::impact_data * impact_host::get_impact_data(const id& id, bool bCallOnCreateView)
   {

      if(!bCallOnCreateView)
      {

         synchronous_lock synchronouslock(mutex());

         return m_impactdatamap[id];

      }

      auto rectangleClient = get_child_rect();

      return get_impact_data(id, rectangleClient, bCallOnCreateView);

   }*/


   ::user::impact_data * impact_host::get_impact_data(const id& id,bool bCallOnCreateView)
   {

      auto & pimpactdata = m_impactdatamap[id];

      if (pimpactdata != nullptr)
      {

         return pimpactdata;

      }

      if (!bCallOnCreateView)
      {

         pimpactdata = allocate_impact_data(id, "");

         return pimpactdata;

      }

      pimpactdata = create_impact(id, "");

      if (pimpactdata == nullptr)
      {

         return nullptr;

      }

      return pimpactdata;

   }


   void impact_host::on_erase_child(::user::interaction* pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //   && pupdown->m_eupdown != updown_normal_frame
      //   && pupdown->m_eupdown != updown_none)
      //{

      //   string strView = pupdown->m_id;

      //   auto& app = papplication;

      //   auto pdataclient = app.cast < ::database::client >();

      //   if (pdataclient)
      //   {

      //      bool bShow = false;

      //      ::str::begins_eat_ci(strView, "frame::");

      //      pdataclient->data_set("frame::" + strView + ".visible", bShow);

      //   }

      //}

   }


   void impact_host::on_erase_place_holder_child(::user::interaction* pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //   && pupdown->m_eupdown != updown_normal_frame
      //   && pupdown->m_eupdown != updown_none)
      //{

      //   string strView = pupdown->m_id;

      //   auto pdataclient = papplication->cast < ::database::client > ();

      //   if (pdataclient)
      //   {

      //      bool bShow = false;

      //      ::str::begins_eat_ci(strView, "frame::");

      //      pdataclient->data_set("frame::" + strView + ".visible", bShow);

      //   }

      //}

   }


   void impact_host::on_hide_child(::user::interaction* pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //   && pupdown->m_eupdown != updown_normal_frame
      //   && pupdown->m_eupdown != updown_none)
      //{

      //   string strView = pupdown->m_id;

      //   auto pdataclient = papplication->cast < ::database::client >();

      //   if (pdataclient)
      //   {

      //      bool bShow = false;

      //      ::str::begins_eat_ci(strView, "frame::");

      //      pdataclient->data_set("frame::" + strView + ".visible", bShow);
      //
      //   }

      //}

   }


   void impact_host::on_hide_place_holder_child(::user::interaction* pinteraction)
   {

      /*__pointer(::user::interaction) pupdown = pinteraction;

      if (pupdown.is_set()
         && pupdown->m_eupdown != updown_normal_frame
         && pupdown->m_eupdown != updown_none)
      {

         string strView = pupdown->m_id;

         auto pdataclient = papplication->cast < ::database::client >();

         if (pdataclient)
         {

            bool bShow = false;

            ::str::begins_eat_ci(strView, "frame::");

            pdataclient->data_set("frame::" + strView + ".visible", bShow);

         }

      }*/

   }

   ::user::impact_data * impact_host::impact_host_get_impact_data(const id& id, const ::id& idTitle, ::user::interaction* pinteraction, ::user::document* pdocument)
   {

      auto pimpactdata = m_impactdatamap[id];

      if (pimpactdata)
      {

         return pimpactdata;

      }

      pimpactdata = allocate_impact_data(id, idTitle);

      if (!pimpactdata)
      {

         return nullptr;

      }

      pimpactdata->m_puserinteraction = pinteraction;

      pimpactdata->m_pdocument = pdocument;

      pimpactdata->m_bOk = true;

      return pimpactdata;

   }


   ::user::place_holder * impact_host::updown_target_get_place_holder(::user::interaction* pinteraction, ::user::document* pdocument)
   {

      auto pimpactdata = impact_host_get_impact_data(pinteraction->m_id, pinteraction->get_window_text(), pinteraction, pdocument);

      if (::is_null(pimpactdata))
      {

         return nullptr;

      }

      return pimpactdata->m_pplaceholder;

   }


   impact_data * impact_host::host_impact(const id & id, const ::id & idTitle, ::user::interaction * pinteraction, ::user::document * pdocument)
   {


      INFO("-------------------------------------------------------------------");
      INFO("");
      INFO("");
      INFO("impact_host::host_impact (1)");
      INFO("");
      INFO("");


      auto pimpactdata = impact_host_get_impact_data(id, idTitle, pinteraction, pdocument);

      if (::is_null(pimpactdata))
      {


         INFO("-------------------------------------------------------------------");
         INFO("");
         INFO("");
         INFO("impact_host::host_impact (1.1)");
         INFO("");
         INFO("");


         return nullptr;

      }

      if (pinteraction->m_ewindowflag & e_window_flag_window_created)
      {





         pinteraction->set_parent(pimpactdata->m_pplaceholder);

         on_after_host_impact(pimpactdata);

      }

      return pimpactdata;

   }


   void impact_host::on_after_host_impact(::user::impact_data * pimpactdata)
   {

      if (::is_set(pimpactdata->m_puserinteraction))
      {

         pimpactdata->m_puserinteraction->m_bEnableSaveWindowRect2 = true;

      }

   }


   bool impact_host::is_hosting(::user::interaction * pinteraction)
   {

      if(::is_set(pinteraction))
      {

         return false;

      }

      for(auto & pair : m_impactdatamap)
      {

         if(pinteraction->is_descendant_of(pair.element2()->m_puserinteraction, true))
         {

            return true;

         }

      }

      return false;

   }


   void impact_host::on_change_cur_sel()
   {

   }


   void impact_host::hide_all_except(const id_array & ida)
   {

      auto ppair = m_impactdatamap.get_start();

      while(ppair != nullptr)
      {

         if(!ida.contains(ppair->element1()))
         {

            try
            {

               if(ppair->element2()->m_pplaceholder != nullptr)
               {

                  ppair->element2()->m_pplaceholder->display(e_display_none);

               }
               else if(ppair->element2()->m_puserinteraction != nullptr)
               {

                  ppair->element2()->m_puserinteraction->display(e_display_none);

               }

            }
            catch(...)
            {

            }

         }

         ppair = m_impactdatamap.get_next(ppair);

      }

   }


   void impact_host::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

   }


} // namespace user




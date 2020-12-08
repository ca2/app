#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif



namespace user
{


   ::user::document * get_document(::user::interaction* pinteraction)
   {

      __pointer(::user::frame_window) pframewindow = pinteraction;

      if (pframewindow)
      {

         return pframewindow->GetActiveDocument();

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

      MESSAGE_LINK(e_message_create, pchannel, this, &impact_host::_001OnCreate);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact_host::_001OnDestroy);

   }


   void impact_host::_001OnCreate(::message::message * pmessage)
   {

   }


   void impact_host::_001OnDestroy(::message::message * pmessage)
   {

      m_impactdatamap.remove_all();

   }


   __pointer(::user::impact) impact_host::get_view()
   {

      return nullptr;

   }


   id impact_host::get_view_id()
   {

      return id(::type_empty);

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
      catch (exception_pointer pe)
      {

         auto pthread = ::get_thread();

         if (pthread)
         {

            pthread->handle_exception(pe);

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
      catch (exception_pointer pe)
      {

         handle_exception(pe);

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
      catch (exception_pointer pe)
      {

         __pointer(exception) phostexception = pe;

         if (phostexception.is_set())
         {

            if(phostexception->m_id == id)
            {

               //::acme::del(pimpactdata);
               // todo
               //remove_impact_data(pimpactdata);

               return nullptr;

            }

            throw ::move(pe);

         }

         handle_exception(pe);

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
         //remove_impact_data(pimpactdata);

         return nullptr;

      }

      return pimpactdata;

   }


   void impact_host::create_impact(impact_data * pimpactdata, impact_creator * pcreator)
   {

      auto puiptraChild = pimpactdata->m_pplaceholder->m_puiptraChild;
      if (puiptraChild && puiptraChild->interaction_count() > 0)
      {

         return;

      }

      if(!_create_impact(pcreator, pimpactdata))
      {

         if (!_create_impact(Application.cast< ::user::impact_creator>(), pimpactdata))
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
      catch (exception_pointer pe)
      {

         m_impactdatamap.remove_key(pimpactdata->m_id);

         __pointer(exception) phostexception = pe;

         if (phostexception.is_set())
         {

            if (phostexception->m_id == pimpactdata->m_id)
            {

               //::acme::del(pimpactdata);

               return false;

            }

            throw ::move(pe);

         }

         handle_exception(pe);

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

         sync_lock sl(mutex());

         return m_impactdatamap[id];

      }

      auto rectClient = get_child_rect();

      return get_impact_data(id, rectClient, bCallOnCreateView);

   }*/


   ::user::impact_data * impact_host::get_impact_data(const id& id,bool bCallOnCreateView)
   {

      ::user::impact_data * pdata = m_impactdatamap[id];

      if (pdata != nullptr)
      {

         return pdata;

      }

      if (!bCallOnCreateView)
      {

         pdata = allocate_impact_data(id, "");

         return pdata;

      }

      pdata = create_impact(id, "");

      if (pdata == nullptr)
      {

         return nullptr;

      }

      return pdata;

   }


   void impact_host::on_remove_child(::user::interaction* pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //   && pupdown->m_eupdown != updown_normal_frame
      //   && pupdown->m_eupdown != updown_none)
      //{

      //   string strView = pupdown->m_id;

      //   auto& app = Application;

      //   auto pdataclient = app.cast < ::database::client >();

      //   if (pdataclient)
      //   {

      //      bool bShow = false;

      //      ::str::begins_eat_ci(strView, "frame::");

      //      pdataclient->data_set("frame::" + strView + ".visible", bShow);

      //   }

      //}

   }


   void impact_host::on_remove_place_holder_child(::user::interaction* pinteraction)
   {

      //__pointer(::user::interaction) pupdown = pinteraction;

      //if (pupdown.is_set()
      //   && pupdown->m_eupdown != updown_normal_frame
      //   && pupdown->m_eupdown != updown_none)
      //{

      //   string strView = pupdown->m_id;

      //   auto pdataclient = Application.cast < ::database::client > ();

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

      //   auto pdataclient = Application.cast < ::database::client >();

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

         auto pdataclient = Application.cast < ::database::client >();

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

      if (pinteraction->m_ewindowflag & window_flag_window_created)
      {





         pinteraction->SetParent(pimpactdata->m_pplaceholder);

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


   void impact_host::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

   }


} // namespace user




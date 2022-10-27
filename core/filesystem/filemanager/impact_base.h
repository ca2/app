#pragma once


#include "base/user/user/impact.h"
#include "base/user/user/split_impact.h"
#include "aura/user/user/plain_edit.h"


class CLASS_DECL_CORE filemanager_impact_base :
   virtual public ::user::impact
{
public:


   bool                          m_bEditConnectInit;
   ::fs::data *                  m_pfsdata;
   ::filemanager::document *     m_pfilemanagerdocument;


   filemanager_impact_base();
   ~filemanager_impact_base() override;


   void initialize_impact(::user::document * pdocument) override;


   void install_message_routing(::channel * pchannel) override;


   ::file::item * filemanager_item();
   ::file::path filemanager_path();

   
   virtual ::filemanager::document * filemanager_document() { return m_pfilemanagerdocument; }
   virtual ::filemanager::data *                   filemanager_data();
   inline ::fs::data * fs_data() { return m_pfsdata; }
   inline ::filemanager::document * get_document() { return m_pfilemanagerdocument; }


   void handle(::topic * ptopic, ::context * pcontext) override;


   virtual void browse_sync(const ::action_context & action_context);
   virtual void knowledge(const ::file::path & pathUser, const ::action_context & action_context);

   //string calc_parent_data_key();

   virtual void _001Refresh();

   DECLARE_MESSAGE_HANDLER(_001OnEditPaste);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateEditPaste);
   DECLARE_MESSAGE_HANDLER(_001OnOperationDocMessage);


};

   
template < typename IMPACT >
class filemanager_show :
   virtual public IMPACT,
   virtual public ::filemanager_impact_base
{
public:


   using FILEMANAGER_SHOW_IMPACT = ::filemanager_show < IMPACT >;


   using IMPACT::IMPACT;


   void initialize_impact(::user::document * pdocument) override
   {

      IMPACT::initialize_impact(pdocument);

      ::filemanager_impact_base::initialize_impact(pdocument);

   }


   inline ::core::application* get_app() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
   inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
   inline ::core::system* get_system() const { return acmesystem() ? acmesystem()->m_pcoresystem : nullptr; }

   inline ::filemanager::document * get_document() { return ::filemanager_impact_base::get_document(); }

   virtual void install_message_routing(::channel* pchannel) override
   {

      IMPACT::install_message_routing(pchannel);
      ::filemanager_impact_base::install_message_routing(pchannel);

   }


   virtual void handle(::topic * ptopic, ::context * pcontext) override
   {

      IMPACT::handle(ptopic, pcontext);
      ::filemanager_impact_base::handle(ptopic, pcontext);

   }

   inline ::fs::data * fs_data() { return ::filemanager_impact_base::fs_data(); }


};




#pragma once


class CLASS_DECL_CORE filemanager_impact_base :
   virtual public ::user::impact
{
public:


   bool                          m_bEditConnectInit;


   filemanager_impact_base();
   virtual ~filemanager_impact_base();


   void install_message_routing(::channel * pchannel) override;


   ::file::item * filemanager_item();
   ::file::path filemanager_path();

   
   virtual ::filemanager::document *               filemanager_document();
   virtual ::filemanager::data *                   filemanager_data();
   virtual __pointer(::fs::data)                   fs_data();


   void handle(::topic * psubject, ::context * pcontext) override;


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


   inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
   inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
   inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }


   virtual void install_message_routing(::channel* pchannel) override
   {

      IMPACT::install_message_routing(pchannel);
      ::filemanager_impact_base::install_message_routing(pchannel);

   }


   virtual void handle(::topic * psubject, ::context * pcontext) override
   {

      IMPACT::handle(psubject, pcontext);
      ::filemanager_impact_base::handle(psubject, pcontext);

   }


};




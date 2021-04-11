#pragma once


class CLASS_DECL_CORE filemanager_impact :
   virtual public ::user::impact
{
public:


   bool                          m_bEditConnectInit;


   filemanager_impact();
   virtual ~filemanager_impact();


   virtual void install_message_routing(::channel * pchannel);


   ::file::item * filemanager_item();
   ::file::path filemanager_path();

   
   virtual ::filemanager::document *               filemanager_document();
   virtual ::filemanager::data *                   filemanager_data();
   virtual __pointer(::fs::data)                   fs_data();


   void on_subject(::subject::subject * psubject, ::subject::context * pcontext);


   virtual void browse_sync(const ::action_context & action_context);
   virtual void knowledge(const string & pathUser, const ::action_context & action_context);

   //string calc_parent_data_key();

   virtual void _001Refresh();

   DECLARE_MESSAGE_HANDLER(_001OnEditPaste);
   DECLARE_MESSAGE_HANDLER(_001OnUpdateEditPaste);
   DECLARE_MESSAGE_HANDLER(_001OnOperationDocMessage);


};

   
template < typename IMPACT >
class filemanager_show :
   virtual public IMPACT,
   virtual public ::filemanager_impact
{
public:


   using FILEMANAGER_SHOW_IMPACT = ::filemanager_show < IMPACT >;


   using IMPACT::IMPACT;


   inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
   inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
   inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }
   inline ::core::user* user() const { return get_session() ? get_session()->user() : nullptr; }


   virtual void install_message_routing(::channel* pchannel) override
   {

      IMPACT::install_message_routing(pchannel);
      ::filemanager_impact::install_message_routing(pchannel);

   }


   virtual void on_subject(::subject::subject* psubject, ::subject::context* pcontext) override
   {

      IMPACT::on_subject(psubject, pcontext);
      ::filemanager_impact::on_subject(psubject, pcontext);

   }


};




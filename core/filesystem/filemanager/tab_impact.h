#pragma once


#include "core/user/userex/pane_tab_impact.h"


namespace filemanager
{


   class CLASS_DECL_CORE tab_impact :
      virtual public ::userex::pane_tab_impact
   {
   public:


      tab_impact();
      ~tab_impact() override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual void on_create_impact(::user::impact_data * pimpactdata) override;
      void install_message_routing(::channel * pchannel) override;
      void FileManagerBrowse(const ::string & pcwstr, const ::action_context & action_context);



      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      __pointer(document) get_document();

   };


} // namespace filemanager





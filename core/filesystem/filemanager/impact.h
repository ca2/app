#pragma once


#include "impact_base.h"


namespace filemanager
{


   class CLASS_DECL_CORE impact :
      virtual public ::filemanager_show < ::user::split_impact >
   {
   public:


      impact();
      ~impact() override;


      void install_message_routing(::channel * pchannel) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void on_create_split_impact() override;

      void FileManagerBrowse(const ::string & pcwstr, const ::action_context & action_context);


      virtual void handle(::topic * ptopic, ::context * pcontext) override;


   };



} // namespace filemanager





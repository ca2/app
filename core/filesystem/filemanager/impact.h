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

      void FileManagerBrowse(const ::scoped_string & scopedstrcwstr, const ::action_context & action_context);


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


   };



} // namespace filemanager





#pragma once


#include "impact.h"


namespace filemanager
{


   class CLASS_DECL_CORE left_impact :
      virtual public ::filemanager_show < ::user::split_impact >
   {
   public:


      ::pointer < ::user::tree >                m_pusertree;
      ::pointer < ::filemanager::tree_data >    m_ptreedata;


      left_impact();
      ~left_impact() override;


      void install_message_routing(::channel * pchannel) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      void on_create_split_impact() override;

      void FileManagerBrowse(const ::scoped_string & scopedstrcwstr, const ::action_context & action_context);


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

   };



} // namespace filemanager




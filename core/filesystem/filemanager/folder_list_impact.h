#pragma once


#include "impact_base.h"
#include "core/user/simple/list_impact.h"


namespace filemanager
{


   class  CLASS_DECL_CORE folder_list_impact:
      virtual public ::filemanager_show < simple_list_impact >
   {
   public:


      bool                             m_bRecursive;
      bool                             m_bRecursiveColumn;
      ::pointer<folder_list_data>     m_pfolderlistdata;


      folder_list_impact();
      virtual ~folder_list_impact();


      void install_message_routing(::channel * pchannel) override;


      virtual void initialize(string strDataKeyModifier,bool bRecursive);


      virtual void _001InsertColumns() override;


      bool add_unique(const string_array & stra);
      bool add_unique(const string_array & stra, int_array & baRecursive);
      bool erase(const string_array & stra);


      void on_check_save(::user::interaction* puserinteraction) override;
      void on_check_load(::user::interaction* puserinteraction) override;

      virtual void GetSel(string_array & stra);

      virtual void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace filemanager














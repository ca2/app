// Refactor and Tidy core filemanager component a bit Fix ca2/app#61 by
// camilo on 2023 - 11 - 16 03:54 < 3ThomasBorregaardSorensen!!
#pragma once


#include "core/filesystem/filemanager/impact_base.h"
#include "core/user/simple/list_impact.h"


namespace filemanager
{


   namespace folder
   {

      class document;

      class  CLASS_DECL_CORE list_impact :
         virtual public ::filemanager_show < simple_list_impact >
      {
      public:


         bool                             m_bRecursive;
         bool                             m_bRecursiveColumn;
         ::pointer<folder::list_data>     m_pfolderlistdata;


         list_impact();
         ~list_impact() override;


         void install_message_routing(::channel * pchannel) override;


         document * get_document();


         virtual void initialize_folder_list_impact(string strDataKeyModifier, bool bRecursive);


         virtual void on_insert_columns() override;


         bool add_unique(const string_array & stra);
         bool add_unique(const string_array & stra, ::int_array & baRecursive);
         bool erase(const string_array & stra);


         void on_check_save(::user::interaction * puserinteraction) override;
         void on_check_load(::user::interaction * puserinteraction) override;

         virtual void GetSel(string_array & stra);

         void handle(::topic * ptopic, ::handler_context * pcontext) override;


      };


   } // namespace folder


} // namespace filemanager




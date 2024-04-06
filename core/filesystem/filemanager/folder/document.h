// Created by camilo on 2023-11-16 03:42 <3ThomasBorregaardSorensen!!
// Refactor and Tidy core filemanager component a bit Fix ca2/app#61
#pragma once


#include "base/user/user/document.h"


namespace filemanager
{


   namespace folder
   {


      class CLASS_DECL_CORE document :
         virtual public ::user::document
      {
      public:

         ::atom      m_atomFolderSelectionList;
         bool m_bEnableRecursiveFolderSelectionList;

         document();
         ~document() override;


         bool on_new_document() override;
         virtual bool on_open_document(const ::payload & payloadFile) override;


      };


   } // namespace folder

} // namespace filemanager





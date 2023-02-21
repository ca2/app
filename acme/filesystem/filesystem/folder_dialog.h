// Created by camilo on 2023-02-21 04:01 BRT <3ThomasBorregaardSorensen!!
#pragma once


namespace file
{


   class CLASS_DECL_ACME folder_dialog :
           virtual public particle
   {
   public:


      ::pointer < ::user::element >                      m_puserelement;
      void *                                             m_posdata;
      ::function < void(::pointer<folder_dialog>) >      m_function;
      ::file::path                                       m_path;
      bool                                               m_bCanCreateFolders;

      
      folder_dialog();
      ~folder_dialog() override;
      
      
//      virtual void pick_single_folder(
//                                      ::user::element * pelement,
//                            const ::function < void(::pointer < folder_dialog >) > & function);
   
   
   };


} // namespace file




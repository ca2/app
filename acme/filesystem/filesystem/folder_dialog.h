// Created by camilo on 2023-02-21 04:01 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/filesystem/dialog_base.h"

namespace file
{


   class CLASS_DECL_ACME folder_dialog :
           virtual public ::file::dialog_base
   {
   public:


      // ::pointer < ::user::element >                      m_puserelement;
      // void *                                             m_posdata;
      // ::function < void(::pointer<folder_dialog>) >      m_function;
      // ::file::path                                       m_path;
      // ::particle_array                                   m_particleaHold;


      bool                                               m_bCanCreateFolders;
      ::function < void(::pointer<folder_dialog>) >      m_procedureResponse;

      
      folder_dialog();
      ~folder_dialog() override;


      bool is_folder_dialog() const override;
      
//      virtual void pick_single_folder(
//                                      ::user::element * pelement,
//                            const ::function < void(::pointer < folder_dialog >) > & function);

      void on_dialog_response() override;

   
   };


} // namespace file




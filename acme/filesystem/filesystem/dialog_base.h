//
// Created by camilo on 2026-01-26 11:08 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace file
{


   class CLASS_DECL_ACME dialog_base :
      virtual public ::particle
   {
   public:


      void *                                             m_posdata;
      ::pointer < ::user::element>                       m_puserelement;
      ::file::path                                       m_pathStartFolder;
      ::particle_array                                   m_particleaHold;
      ::file::path_array_base                            m_patha;


      dialog_base();
      ~dialog_base() override;


      virtual bool is_folder_dialog() const;


      virtual void on_chooser_response(const_char_pointer pszPath);
      virtual void on_dialog_response();

   };

} // file


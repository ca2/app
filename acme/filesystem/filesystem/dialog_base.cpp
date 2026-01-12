//
// Created by camilo on 11/01/2026.
//
#include "framework.h"
#include "dialog_base.h"


namespace file
{


   dialog_base::dialog_base()
   {


   }


   dialog_base::~dialog_base()
   {


   }


   bool dialog_base::is_folder_dialog() const
   {

      return false;

   }


   void dialog_base::on_chooser_response(const_char_pointer pszPath)
   {

      m_patha.add(pszPath);

      on_dialog_response();

   }


   void dialog_base::on_dialog_response()
   {

      throw ::interface_only();

   }


} // file
//
//  plain_text_tree.cpp
//  aura
//
//  From plain_text_data.cpp by Camilo Sasuke Thomas Borregaard Soerensen on 30/09/22 14:28.
//
#include "framework.h"
#include "plain_text_tree.h"
#include "acme/primitive/data/listener.h"
#include "apex/filesystem/file/edit_file.h"


namespace user
{


   plain_text_tree::plain_text_tree()
   {

      //m_pgroupcommand      = nullptr;
      m_pfile              = nullptr;
      m_iBranch            = 0;
      m_iSelBeg            = -1;
      m_iSelEnd            = -1;

      __construct_new(m_peditfile);

   }


   plain_text_tree::~plain_text_tree()
   {

   }


   void plain_text_tree::SetFile(file_pointer  pfile)
   {

      m_peditfile->SetFile(pfile);

   }


   bool plain_text_tree::is_tree_modified() const
   {
   
      return m_peditfile->is_edit_file_modified();
   
   }


} // namespace user




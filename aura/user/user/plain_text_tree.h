// From plain_tree_data.h by camilo on 2022-09-03 20:40 <3ThomasBorregaardSorensen!! (ThomasMonth?!!) (ThomasLikesNumber5)
#pragma once


#include "acme/primitive/data/tree.h"
#include "plain_text_data.h"


namespace user
{


   class CLASS_DECL_AURA plain_text_tree:
      public ::data::tree
   {
   public:


      __pointer(plain_text_group_command)       m_pgroupcommand;
      index                                     m_iBranch;
      file_pointer                              m_pfile;
      __pointer(::file::edit_file)              m_peditfile;


      strsize                                   m_iSelBeg;
      strsize                                   m_iSelEnd;


      plain_text_tree();
      ~plain_text_tree() override;


      void SetFile(file_pointer  pfile);


   };



} // namespace user









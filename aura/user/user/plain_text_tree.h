// From plain_tree_data.h by camilo on 2022-09-03 20:40 <3ThomasBorregaardSorensen!! (ThomasMonth?!!) (ThomasLikesNumber5)
#pragma once


#include "acme/prototype/data/tree.h"
#include "plain_text_data.h"

namespace file
{
   class edit_item_base;
}
namespace user
{


   class CLASS_DECL_AURA plain_text_tree:
      public ::data::tree < plain_text_command >
   {
   public:


      ::pointer<plain_text_group_command>      m_pgroupcommand;
      ::collection::index                                     m_iBranch;
      file_pointer                              m_pfile;
      ::pointer<::file::edit_file>             m_peditfile;


      character_count                                   m_iSelBeg;
      character_count                                   m_iSelEnd;


      plain_text_tree();
      ~plain_text_tree() override;


      void destroy() override;


      void SetFile(file_pointer  pfile);
      
      
      virtual bool is_tree_modified() const;

      virtual void _on_undo_edit_item(::file::edit_item_base * pedititem);
      virtual void _on_redo_edit_item(::file::edit_item_base * pedititem);

   };



} // namespace user










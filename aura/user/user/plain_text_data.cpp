#include "framework.h"
#include "plain_text_data.h"
#include "plain_text_tree.h"
#include "acme/constant/user.h"
#include "acme/primitive/data/listener.h"
#include "apex/filesystem/file/edit_file.h"


namespace user
{


   e_plain_text_command plain_text_command::get_command()
   {
      return plain_text_command_none;
   }

   void plain_text_command::Undo(plain_text_tree * pedit)
   {
      __UNREFERENCED_PARAMETER(pedit);
   }

   void plain_text_command::Redo(plain_text_tree * pedit)
   {
      __UNREFERENCED_PARAMETER(pedit);
   }



   void plain_text_set_sel_command::Undo(plain_text_tree * pplaintexttree)
   {

      __UNREFERENCED_PARAMETER(pplaintexttree);

      pplaintexttree->m_iSelBeg = m_iPreviousSelBeg;

      pplaintexttree->m_iSelEnd = m_iPreviousSelEnd;

   }

   void plain_text_set_sel_command::Redo(plain_text_tree * pplaintexttree)
   {
      __UNREFERENCED_PARAMETER(pplaintexttree);
      pplaintexttree->m_iSelBeg = m_iSelBeg;
      pplaintexttree->m_iSelEnd = m_iSelEnd;
   }

   void plain_text_file_command::Undo(plain_text_tree * pplaintexttree)
   {
      pplaintexttree->m_peditfile->Undo();
   }

   void plain_text_file_command::Redo(plain_text_tree * pplaintexttree)
   {
      pplaintexttree->m_peditfile->Redo();
   }




   plain_text_group_command::plain_text_group_command()
   {

      m_pparent = nullptr;

   }

   plain_text_group_command::~plain_text_group_command()
   {


   }

   void plain_text_group_command::Undo(plain_text_tree * pplaintexttree)
   {

      for(index i = m_commanda.get_upper_bound(); i >= 0; i--)
      {

         m_commanda.element_at(i)->Undo(pplaintexttree);

      }

   }


   void plain_text_group_command::Redo(plain_text_tree * pplaintexttree)
   {

      for(index i = 0; i < m_commanda.get_size(); i++)
      {

         m_commanda.element_at(i)->Redo(pplaintexttree);

      }

   }


} // namespace user




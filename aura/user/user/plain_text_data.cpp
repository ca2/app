#include "framework.h"
//#include "aura/user/_user.h"
#include "_data.h"
//#include "_tree.h"


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



   void plain_text_set_sel_command::Undo(plain_text_tree * pdocument)
   {

      __UNREFERENCED_PARAMETER(pdocument);

      pdocument->m_iSelBeg = m_iPreviousSelBeg;

      pdocument->m_iSelEnd = m_iPreviousSelEnd;

   }

   void plain_text_set_sel_command::Redo(plain_text_tree * pdocument)
   {
      __UNREFERENCED_PARAMETER(pdocument);
      pdocument->m_iSelBeg = m_iSelBeg;
      pdocument->m_iSelEnd = m_iSelEnd;
   }

   void plain_text_file_command::Undo(plain_text_tree * pdocument)
   {
      pdocument->m_peditfile->Undo();
   }

   void plain_text_file_command::Redo(plain_text_tree * pdocument)
   {
      pdocument->m_peditfile->Redo();
   }




   plain_text_group_command::plain_text_group_command()
   {

      m_pparent = nullptr;

   }

   plain_text_group_command::~plain_text_group_command()
   {


   }

   void plain_text_group_command::Undo(plain_text_tree * pdocument)
   {

      for(index i = m_commanda.get_upper_bound(); i >= 0; i--)
      {

         m_commanda.element_at(i)->Undo(pdocument);

      }

   }


   void plain_text_group_command::Redo(plain_text_tree * pdocument)
   {

      for(index i = 0; i < m_commanda.get_size(); i++)
      {

         m_commanda.element_at(i)->Redo(pdocument);

      }

   }


} // namespace user




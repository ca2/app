#pragma once


#include "acme/prototype/data/item.h"


namespace user
{


   class plain_text_tree;

   enum e_plain_text_command
   {
      plain_text_command_none,
      plain_text_command_set_sel,
      plain_text_command_file,
      plain_text_command_group,
   };


   class CLASS_DECL_AURA plain_text_command : public ::data::item
   {
   public:
      virtual e_plain_text_command get_command();
      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);


   };


   class CLASS_DECL_AURA plain_text_set_sel_command : public plain_text_command
   {
   public:


      character_count   m_iSelBeg;
      character_count   m_iSelEnd;
      character_count   m_iPreviousSelBeg;
      character_count   m_iPreviousSelEnd;


      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);
      virtual e_plain_text_command get_command() { return plain_text_command_set_sel; };

   };

   class CLASS_DECL_AURA plain_text_file_command : public plain_text_command
   {
   public:
      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);
      virtual e_plain_text_command get_command() { return plain_text_command_file; };
   };


   class CLASS_DECL_AURA plain_text_group_command : 
      public plain_text_command
   {
   public:

      plain_text_command *                m_pparent;
      pointer_array < plain_text_command >      m_commanda;

      plain_text_group_command();
      virtual ~plain_text_group_command();
      virtual e_plain_text_command get_command() { return plain_text_command_group; };
      virtual void Undo(plain_text_tree * pedit);
      virtual void Redo(plain_text_tree * pedit);

   };


} // namespace user




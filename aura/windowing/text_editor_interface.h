// Created by camilo on 2022-05-04 01:13 AM <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/prototype/prototype/object.h"


namespace windowing
{


   class CLASS_DECL_AURA text_editor_interface :
      virtual public object
   {
   public:


      text_editor_interface();
      ~text_editor_interface() override;


      virtual void set_input_method_manager_selection(character_count iSelBeg, character_count iSelEnd, character_count iCandidateBeg, character_count iCandidateEnd);
      virtual void synchronize_input_method_manager_with_selection_end();


      virtual void set_editor_selection(character_count iStart, character_count iEnd);
      virtual void set_editor_text(const ::scoped_string & scopedstrText);
      virtual void set_editor_text_and_selection(const ::scoped_string & scopedstrText, character_count iStart, character_count iEnd);
      virtual void show_software_keyboard();
      virtual void hide_software_keyboard();


   };


} // namespace windowing




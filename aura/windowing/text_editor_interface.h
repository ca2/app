// Created by camilo on 2022-05-04 01:13 AM <3ThomasBorregaardSorensen!!
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA text_editor_interface :
      virtual public object
   {
   public:


      text_editor_interface();
      ~text_editor_interface() override;


      virtual void set_input_method_manager_selection(strsize iSelBeg, strsize iSelEnd, strsize iCandidateBeg, strsize iCandidateEnd);
      virtual void synchronize_input_method_manager_with_selection_end();


      virtual void set_editor_selection(strsize iStart, strsize iEnd);
      virtual void set_editor_text(const ::string & strText);
      virtual void show_software_keyboard();
      virtual void hide_software_keyboard();


   };


} // namespace windowing




#pragma once


namespace userex
{


   class CLASS_DECL_CORE keyboard_layout :
      virtual public ::user::split_view,
      virtual public ::user::form_callback,
      virtual public ::user::list_data
   {
   public:


      __pointer(::user::document)               m_pdocument;
      __pointer(::user::form_view)              m_pview;
      __pointer(simple_list_view)               m_plistview;
      ::user::keyboard_layout_ida               m_layoutida;


      keyboard_layout();
      virtual ~keyboard_layout();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      bool CreateViews();

      void on_show();

      void on_control_event(::user::control_event * pevent) override;

      virtual void _001GetItemText(::user::mesh_item * pitem) override;

      virtual ::count _001GetItemCount() override;

      virtual void update(::update * pupdate) override;
      

   };


} // namespace aura




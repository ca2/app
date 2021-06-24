#pragma once


#include "image_list.h"


namespace userex
{


   class CLASS_DECL_CORE group_image_list_view :
      virtual public ::user::impact
   {
   public:


      class group :
         virtual public ::object
      {
      public:

         ::index                 m_iIndex;
         ::id                    m_idGroup;
         string                  m_strIcon;
         string                  m_strTitle;
         __pointer(image_list_view)     m_plist;

      };


      size_f64                         m_size;
      ::image_pointer                         m_pimage;
      string_array                       m_straClass;
      ::user::button                m_buttonMenu;
      __pointer_array(group)                    m_groupa;
      __pointer(::user::menu)              m_pmenu;
      ::id                          m_idGroup;


      group_image_list_view();
      virtual ~group_image_list_view();


      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;


      virtual ::userex::image_list_view * get_group_list(::id idGroup);

      virtual ::file::path get_link_path(string strLink);

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual string get_group_title(group * pgroup);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_command(::message::command * pcommand) override;

      virtual ::userex::image_list_view * add_group(::id idGroup, string strIcon, string strTitle, ::file::path pathFolder = "");

      ::e_status set_current_item(const ::user::item & item, const ::action_context & action_context) override;

      virtual bool show_group(::id idGroup, ::file::path pathFolder = "");

      virtual void show_menu();

      virtual string get_menu_xml();

      ::userex::image_list_view * get_current_list();

      virtual group * get_group(::id idGroup);

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace tranquillum






#pragma once


#include "image_list.h"


namespace userex
{


   class CLASS_DECL_CORE group_image_list_impact :
      virtual public ::user::impact
   {
   public:


      class group :
         virtual public ::object
      {
      public:

         ::index                 m_iIndex;
         ::atom                    m_atomGroup;
         string                  m_strIcon;
         string                  m_strTitle;
         ::pointer<image_list_impact>    m_plist;

      };


      size_f64                        m_size;
      ::image_pointer                 m_pimage;
      string_array                    m_straClass;
      ::pointer<::user::button>      m_pbuttonMenu;
      pointer_array < group >          m_groupa;
      ::pointer<::user::menu>        m_pmenu;
      ::atom                          m_atomGroup;


      group_image_list_impact();
      virtual ~group_image_list_impact();


      void assert_ok() const override;

      void dump(dump_context & dumpcontext) const override;


      virtual ::userex::image_list_impact * get_group_list(::atom idGroup);

      virtual ::file::path get_link_path(string strLink);

      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual string get_group_title(group * pgroup);

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_command(::message::command * pcommand) override;

      virtual ::userex::image_list_impact * add_group(::atom idGroup, string strIcon, string strTitle, ::file::path pathFolder = "");

      void set_current_item(::item * pitem, const ::action_context & action_context) override;

      virtual bool show_group(::atom idGroup, ::file::path pathFolder = "");

      virtual void show_menu();

      virtual string get_menu_xml();

      ::userex::image_list_impact * get_current_list();

      virtual group * get_group(::atom idGroup);

      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace tranquillum






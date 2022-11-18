#pragma once


#include "impact_base.h"


namespace filemanager
{


   class CLASS_DECL_CORE main_impact:
      virtual public ::filemanager_show < ::user::split_impact >
   {
   public:


      
      file_list *                               m_pfilelist;
      thumbnail *                               m_pthumbnail;
      ::pointer<file_properties_form>        m_ppropform;
      ::pointer<::file::item_array>            m_pitema;


      main_impact();
      ~main_impact() override;


      void install_message_routing(::channel * pchannel) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_create_split_impact() override;

      void FileManagerBrowse(const ::string & pcwstr, const ::action_context & action_context);


      virtual void on_command(::message::command * pcommand) override;

      virtual void OpenSelectionProperties();

      void handle(::topic * ptopic, ::context * pcontext) override;


   };


} // namespace filemanager





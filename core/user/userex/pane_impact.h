#pragma once


#include "base/user/user/impact.h"
#include "base/user/user/impact_creator.h"


namespace userex
{


   class CLASS_DECL_CORE pane_impact :
      virtual public ::user::impact,
      virtual public ::user::impact_creator
   {
   public:


      class menu :
         virtual public ::particle
      {
      public:
         

         string      m_strMatter;
         
         atom        m_atomMenu;


      };


      pointer_array < menu > m_menua;


      pane_impact();
      ~pane_impact() override;


      void on_create_impact(::user::impact_data * pimpactdata) override;


      void set_new_pane_info(atom atom, const ::scoped_string & scopedstrMatter);
      void set_menu_info(atom atom, const ::scoped_string & scopedstrMatter, ::atom idCommand);
   

      virtual void on_command_probe(::message::command * pcommand) override;
      virtual void on_command(::message::command * pcommand) override;

      
   };


} // namespace userex



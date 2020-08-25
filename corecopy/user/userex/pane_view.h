#pragma once


namespace userex
{


   class CLASS_DECL_CORE pane_view :
      virtual public ::user::impact,
      virtual public ::user::impact_creator
   {
   public:

      class menu :
         virtual public object
      {
      public:
         
         string   m_strMatter;
         
         id       m_id;

      };


      pointer_array < menu > m_menua;


      pane_view();
      virtual ~pane_view();


      void on_create_impact(::user::impact_data * pimpactdata) override;


      void set_new_pane_info(id id, const char * pszMatter);
      void set_menu_info(id id, const char * pszMatter, ::id idCommand);
   

      virtual void on_command_probe(::user::command * pcommand) override;
      virtual void on_command(::user::command * pcommand) override;

      
   };


} // namespace userex



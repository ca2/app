#pragma once


namespace browser
{


   enum e_impact
   {

      impact_none,
      impact_menu,
      impact_gcom,
      impact_browser,
      impact_browser_switcher

   };


   class CLASS_DECL_APP_BROWSER ::update :
      public object
   {
   public:


      enum e_type
      {

         type_none,
         type_get_view,
         type_set_view,
         type_on_show_view,

      };


      e_impact    m_eview;
      e_type         m_etype;


      ::update();
      virtual ~::update();


      void set_type(e_type e_type);

      bool is_type_of(e_type e_type);


   };


} // namespace browser
















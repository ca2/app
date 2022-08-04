#pragma once


namespace browser
{


   enum enum_impact
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


      enum enum_type
      {

         type_none,
         type_get_impact,
         type_set_impact,
         type_on_show_impact,

      };


      enum_impact    m_eview;
      enum_type         m_etype;


      ::update();
      virtual ~::update();


      void set_type(enum_type enum_type);

      bool is_type_of(enum_type enum_type);


   };


} // namespace browser
















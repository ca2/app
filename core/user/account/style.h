#pragma once


namespace account
{


   class CLASS_DECL_BERG style :
      virtual public ::user::style
   {
   public:

      string                        m_strLocale;
      string                        m_strSchema;
      string                        m_strRuri;


      style(::particle * pparticle);

      virtual ~style();

      virtual string defer_get_plugin();

      virtual string defer_get(const ::scoped_string & scopedstrUrl);

      virtual string calc_locale();
      virtual string calc_schema();


   };


} // namespace simple_ui





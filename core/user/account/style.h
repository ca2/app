#pragma once


namespace account
{


   class CLASS_DECL_BASE style :
      virtual public ::user::style
   {
   public:

      string                        m_strLocale;
      string                        m_strSchema;
      string                        m_strRuri;


      style(::object * pobject);

      virtual ~style();

      virtual string defer_get_plugin();

      virtual string defer_get(const ::string & pszUrl);

      virtual string calc_locale();
      virtual string calc_schema();


   };


} // namespace simple_ui





#pragma once


namespace str
{


   namespace international
   {


      class CLASS_DECL_ACME locale_schema :
         virtual public ::matter
      {
      public:

         // most simple use:
         // 1. allocate locale_schema.
         // 2. add locale variants in order of importance, most acceptable first
         // 3. finalize locale_schema
         // m_straLocale and m_straStyle will have the locale/styles

         bool                       m_bSchemaOnly;
         bool                       m_bAddAlternateStyle;

         id                         m_idLocale;
         id                         m_idSchema;

         comparable_array < id >    m_idaLocale;
         comparable_array < id >    m_idaSchema;


         locale_schema();
         locale_schema(const locale_schema & ls);
         virtual ~locale_schema();


         ::id localeid(const char * pszLocale, strsize iLen);


         virtual bool add_locale_variant(id idLocale, id Style);
         virtual bool end_prepare(bool bRtlLayout);
         //virtual void end_prepare();

         bool defer_add_locale(id idLocale, id idStyle);
         bool defer_add_locale(const char * psz, strsize iLen, id idStyle);
         bool _add_locale_variant(id pszLocale, id idStyle);
         bool _add_locale_variant(const char * psz, strsize iLen, id idStyle);
         bool process_final_locale_schema(bool bRTLLayout);
         //bool process_final_locale_schema();


         locale_schema & operator = (const locale_schema & ls);

         virtual i64 add_ref(OBJECT_REF_DEBUG_PARAMS);
         virtual i64 release(OBJECT_REF_DEBUG_PARAMS);


      };


      inline bool locale_schema::_add_locale_variant(id idLocale, id idStyle)
      {

         return _add_locale_variant(idLocale.m_psz, strlen(idLocale.m_psz), idStyle);

      }


      inline bool locale_schema::defer_add_locale(const char * pszLocale, strsize iLen, id idSchema)
      {

         return defer_add_locale(localeid(pszLocale, iLen), idSchema);

      }


      CLASS_DECL_ACME void create_rtl_map();


   }  // namespace international


} // namespace acme




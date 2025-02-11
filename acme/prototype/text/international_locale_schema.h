#pragma once


#include "acme/prototype/prototype/atom.h"

#include "acme/prototype/collection/atom_array.h"


namespace text
{


   namespace international
   {


      class CLASS_DECL_ACME locale_schema :
         virtual public ::particle
      {
      public:

         // most simple use:
         // 1. allocate locale_schema.
         // 2. add locale variants in order of importance, most acceptable first
         // 3. destroy locale_schema
         // m_straLocale and m_straStyle will have the locale/styles

         bool                       m_bSchemaOnly;
         bool                       m_bAddAlternateStyle;

         ::string                   m_strLocale;
         ::string                   m_strSchema;

         ::string_array             m_straLocale;
         ::string_array             m_straSchema;


         locale_schema();
         locale_schema(const locale_schema& ls);
         ~locale_schema() override;


         //::atom localeid(const scoped_string & strLocale, character_count iLen);


         virtual bool add_locale_variant(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
         virtual bool end_prepare(bool bRtlLayout);
         //virtual void end_prepare();

         bool defer_add_locale(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
         //bool defer_add_locale(const scoped_string & str, character_count iLen, const ::atom & idStyle);
         bool _add_locale_variant(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
         //bool _add_locale_variant(const scoped_string & str, character_count iLen, atom idStyle);
         bool process_final_locale_schema(bool bRTLLayout);
         //bool process_final_locale_schema();


         locale_schema& operator = (const locale_schema& ls);

#ifdef _DEBUG

         virtual long long increment_reference_count() override;
         virtual long long release() override;

#endif


      };



      CLASS_DECL_ACME void create_rtl_map();


   }  // namespace international


} // namespace text




#pragma once


#include "acme/primitive/primitive/atom.h"

#include "acme/primitive/collection/atom_array.h"


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

         atom                       m_atomLocale;
         atom                       m_atomSchema;

         atom_array                 m_idaLocale;
         atom_array                 m_idaSchema;


         locale_schema();
         locale_schema(const locale_schema& ls);
         ~locale_schema() override;


         //::atom localeid(const scoped_string & strLocale, strsize iLen);


         virtual bool add_locale_variant(const ::atom & idLocale, const ::atom & Style);
         virtual bool end_prepare(bool bRtlLayout);
         //virtual void end_prepare();

         bool defer_add_locale(const ::atom & idLocale, const ::atom & idStyle);
         //bool defer_add_locale(const scoped_string & str, strsize iLen, const ::atom & idStyle);
         bool _add_locale_variant(const ::atom & pszLocale, const ::atom & idStyle);
         //bool _add_locale_variant(const scoped_string & str, strsize iLen, atom idStyle);
         bool process_final_locale_schema(bool bRTLLayout);
         //bool process_final_locale_schema();


         locale_schema& operator = (const locale_schema& ls);

#ifdef _DEBUG

         virtual i64 increment_reference_count() override;
         virtual i64 release() override;

#endif


      };



      CLASS_DECL_ACME void create_rtl_map();


   }  // namespace international


} // namespace text




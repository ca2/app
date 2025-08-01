#pragma once


#define BEGIN_PRIVATE_LANGUAGE_MAP


////#include "acme/prototype/prototype/object.h"
#include "acme/prototype/collection/string_map.h"


namespace user
{


   class CLASS_DECL_APEX language :
      virtual public ::object
   {
   public:


      string               m_strLanguageCode;


      int                  m_iPo;


      string_to_string     m_stringmap;
      string_to_string     m_stringmapHeader;
      bool                 m_bLoadedDefaultResource;
      bool                 m_bLoadedDefaultResourceHeader;
      bool                 m_bLoadedDefaultResourceRet;


      language();
      ~language() override;


      virtual void initialize(::particle * pparticle) override;


      virtual bool defer_load_resource_pofile(bool bOnlyHeader = false);

      virtual string load_podata(bool bOnlyHeader = false);

      virtual bool parse_podata(const ::scoped_string & scopedstrPoData, bool bOnlyHeader = false);

      virtual string get_text(const ::scoped_string & scopedstrText);


   };




} // namespace user




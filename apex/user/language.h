#pragma once


#define BEGIN_PRIVATE_LANGUAGE_MAP


namespace user
{


   class language :
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
      virtual ~language();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual bool defer_load_resource_pofile(bool bOnlyHeader = false);

      virtual string load_podata(bool bOnlyHeader = false);

      virtual bool parse_podata(string strPoData, bool bOnlyHeader = false);

      virtual string get_text(string strText);


   };




} // namespace user




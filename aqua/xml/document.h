#pragma once


namespace xml
{


   class edit;


   class CLASS_DECL_AQUA document :
      virtual public node,
      virtual public ::object
   {
   public:


      __pointer(string_to_string)   m_pentitiesHash;
      __pointer(string_to_string)   m_pentitiesExtHash;
      __pointer(parse_info)         m_pparseinfo;
      ::file::path                  m_pathLocation;
      string                        m_strData1;
      __pointer(::xml::edit)        m_pedit;
      memory                        m_memoryData;
      __pointer(node)               m_pnodeRoot;


      document(parse_info * pparseinfo = nullptr, string_to_string * pentitiesHash = nullptr);
      ~document() override;


      void initialize(::object * pobject) override;
      

      inline void ensure_root()
      {

         if (!m_pnodeRoot)
         {

            create_root();

         }

      }

      void create_root();
      void create_root(const ::string & strName);

      string consume_entity_ref(const char * & pszXml, string & strName, bool useExtEnt, bool & bExt);
      char * patch_entity_ref(const char * & pszXml, int bUseExtEnt);

      node* root() { return m_pnodeRoot; }
      const node * root() const { return m_pnodeRoot; }

      bool load_location(const char * psz);
      bool parse_xml_text(stream & s);
      bool parse_xml_text(const char * pszXmlText);

      inline operator bool() const { return ::is_set(this) && m_pnodeRoot.is_set(); }
      inline bool operator !() const { return !operator bool(); }

      void set_name(const ::string & strName) override;

      document & operator = (const document & document);

      ::stream & write(::stream & stream) const override;
      ::stream & read(::stream & stream) override;


   };


} // namespace xml








#pragma once


#include "node.h"
#include "acme/primitive/primitive/memory.h"


namespace xml
{


   class edit;


   class CLASS_DECL_AQUA document :
      virtual public node //,
      //virtual public ::object
   {
   public:


      ::pointer<string_to_string>  m_pentitiesHash;
      ::pointer<string_to_string>  m_pentitiesExtHash;
      ::pointer<parse_info>        m_pparseinfo;
      ::file::path                  m_pathLocation;
      string                        m_strData1;
      ::pointer<::xml::edit>       m_pedit;
      memory                        m_memoryData;
      //::pointer<node>              m_pnodeRoot;


      document(parse_info * pparseinfo = nullptr, string_to_string * pentitiesHash = nullptr);
      ~document() override;


      void initialize(::particle * pparticle) override;
      

      virtual void ensure_root();
      void create_root();
      void create_root(const ::string & strName);

   
      string consume_entity_ref(const char * & pszXml, string & strName, bool useExtEnt, bool & bExt, ::acme::context * pacmecontext);
      char * patch_entity_ref(const char * & pszXml, int bUseExtEnt, ::acme::context * pacmecontext);

      node* root() { return first_xml_node(); }
      const node * root() const { return first_xml_node(); }

      //void load_location(const char * psz);
      //void parse_xml_text(stream & s);
      //void parse_xml_text(const char * pszXmlText);

      inline operator bool() const { return ::is_set(this) && root(); }
      inline bool operator !() const { return !operator bool(); }

      void set_name(const ::string & strName) override;

      document & operator = (const document & document);

      //::stream & write(::stream & stream) const override;
      //::stream & read(::stream & stream) override;


   };


} // namespace xml








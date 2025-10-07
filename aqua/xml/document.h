#pragma once


#include "node.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/collection/string_map.h"


namespace xml
{


   class edit;


   class CLASS_DECL_AQUA document :
      virtual public node
      //, public ::allocator::accessor < ::xml::document >
   {
   public:


      ::pointer<::map_particle < string_to_string_base >>   m_pentitiesHash;
      ::pointer<::map_particle < string_to_string_base >>   m_pentitiesExtHash;
      ::pointer<parse_info>                                 m_pparseinfo;
      ::file::path                                          m_pathLocation;
      string                                                m_strData1;
      ::pointer<::xml::edit>                                m_pedit;
      memory                                                m_memoryData;
      //::pointer<node>              m_pnodeRoot;


      document(parse_info * pparseinfo = nullptr, string_to_string_base * pentitiesHash = nullptr);
      ~document() override;


      void initialize(::particle * pparticle) override;
      

      virtual void ensure_root();
      void create_root();
      void create_root(const ::scoped_string & scopedstrName);

   
      string consume_entity_ref(::ansi_range & rangeXml, string & strName, bool useExtEnt, bool & bExt, ::platform::context * pacmecontext);
      char * patch_entity_ref(::ansi_range & rangeXml, int bUseExtEnt, ::platform::context * pacmecontext);

      node* root() { return first_xml_node(); }
      const node * root() const { return first_xml_node(); }

      //void load_location(const ::scoped_string & scopedstr);
      //void parse_xml_text(stream & s);
      //void parse_xml_text(const ::scoped_string & scopedstrXmlText);

      inline operator bool() const { return ::is_set(this) && root(); }
      inline bool operator !() const { return !operator bool(); }

      void set_name(const ::scoped_string & scopedstrName) override;

      document & operator = (const document & document);

      //::stream & write(::stream & stream) const override;
      //::stream & read(::stream & stream) override;


   };


} // namespace xml








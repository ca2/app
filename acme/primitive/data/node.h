#pragma once


//#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/string/string.h"
//#include "acme/primitive/primitive/payload.h"
//#include "acme/primitive/collection/pointer_array.h"


namespace data
{


   enum enum_node
   {

      e_node_none,
      e_node_xml_element,     // general node '<matter>...</matter>' or <matter/>
      e_node_xml_pi,          // <?xml version="1.0" ?>
      e_node_xml_comment,     // <!-- comment -->
      e_node_xml_cdata,       // <![CDATA[ cdata ]]>
      e_node_xml_document,    // internal virtual root
      e_node_xml_text        // special node_element - final node matter

   };


   class CLASS_DECL_ACME node :
      virtual public ::particle
   {

   public:


      typedef pointer_array < node > array;

      ::xml::node *              m_pxmlnode;
      node *                     m_pnodeParent;
      enum_node                  m_enode;
      string                     m_strName;
      string                     m_strValue;
      property_set               m_set;
      node::array                m_nodea;

      node();
      ~node() override;


      string name() const { return m_strName; }
      void set_name(const ::scoped_string & scopedstrName) { m_strName = scopedstrName; }
      
      
      string value() const { return m_strValue; }
      void set_value(const ::scoped_string & scopedstrValue) { m_strValue = scopedstrValue; }


      inline enum_node get_type() const { return m_enode; }
      inline void set_type(enum_node enode) { m_enode = enode; }

      inline ::xml::node* get_xml_node() const { return m_pxmlnode; }

      virtual ::xml::document* get_xml_document() const;

      property& attribute(const ::atom & atomAttributeName) { return m_set[atomAttributeName]; }
      const property& attribute(const ::atom & atomAttributeName) const { return m_set[atomAttributeName]; }


      node* node_at(::index i) { return m_nodea[i]; }
      ::count get_node_count() const { return m_nodea.get_count(); }





   };


   inline ::xml::node* __xml(::data::node* pnode) { return pnode == nullptr ? nullptr : pnode->get_xml_node(); }

} // namespace acme




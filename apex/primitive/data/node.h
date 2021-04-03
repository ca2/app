#pragma once


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


   class CLASS_DECL_APEX node :
      virtual public ::object
   {
   protected:


      ::xml::node* m_pxmlnode;

   public:


      typedef __pointer_array(node) array;


      node *                     m_pnodeParent;
      enum_node                  m_enode;
      string                     m_strName;
      string                     m_strValue;
      property_set               m_set;
      node::array                m_nodea;

      

      node();
      virtual ~node();


      string name() const { return m_strName; }
      void set_name(const char * pszName) { m_strName = pszName; }
      
      
      string value() const { return m_strValue; }
      void set_value(const char * pszValue) { m_strValue = pszValue; }


      inline enum_node get_type() const { return m_enode; }
      inline void set_type(enum_node enode) { m_enode = enode; }

      inline ::xml::node* get_xml_node() const { return m_pxmlnode; }

      virtual ::xml::document* get_xml_document() const;

      property& attribute(const char* pszAttributeName) { return m_set[pszAttributeName]; }
      const property& attribute(const char* pszAttributeName) const { return m_set[pszAttributeName]; }


      node* node_at(::index i) { return m_nodea[i]; }
      ::count get_node_count() const { return m_nodea.get_count(); }





   };


   inline ::xml::node* __xml(::data::node* pnode) { return pnode == nullptr ? nullptr : pnode->get_xml_node(); }

} // namespace acme




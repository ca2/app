#pragma once


#include "acme/primitive/data/node.h"


namespace xml
{


   class document;


   class CLASS_DECL_AQUA node :
      virtual public ::data::node,
      public ::allocator::accessor < ::xml::node >
   {
   protected:


      friend class ::allocator::accessor < ::xml::document >;
      friend class ::allocator::accessor < ::xml::node >;


      // name and value
      //string                   m_strName;
      //string                   m_strValue;

      //node *                   m_pnodeParent;      // parent node
      //node::array              m_nodea;            // children pointer node array
      //e_node                   m_etype;            // node type
      ::xml::document *          m_pdocument;             // document
      //property_set             m_set;
      ::index                    m_iFirstXmlNode;


      node();
      node(::xml::node * pnodeParent);


   public:

      
      ~node() override;


      inline ::pointer<::xml::document>get_document() { return m_pdocument; }
      inline const ::pointer<::xml::document>get_document() const { return m_pdocument; }


      virtual void set_name(const ::string & strName);
      virtual void set_value(const ::string & strValue);

      virtual void get_name(string & strName) const { strName = m_strName; }
      virtual void get_value(string & strValue) const { strValue = m_strValue; }

      inline string get_name() const { return m_strName; }
      inline string get_value() const { return m_strValue; }

   
      ::xml::document* get_xml_document() const override;


      index get_index() const;


      node * first_child();
      const node * first_child() const { return ((node *)this)->first_child(); }

      node * first_xml_node() { return m_iFirstXmlNode >= 0 ? m_nodea[m_iFirstXmlNode]->m_pxmlnode : nullptr; }
      const node * first_xml_node() const { return m_iFirstXmlNode >= 0 ? m_nodea[m_iFirstXmlNode]->m_pxmlnode : nullptr; }

      virtual index find(node * pnode);
      virtual index find(const ::scoped_string & scopedstrName, index iStart = 0);

      virtual index find(const ::scoped_string & scopedstrName, const property_set & set, index iStart = 0);

      //virtual bool contains(const property_set & set) const;
      virtual node * get_next_sibling();


      // Load/Save XML
      virtual void load(const ::string & strXml, parse_info * pi = nullptr);


   protected:


      virtual void _load(::ansi_range & rangeXml,parse_info * pi = nullptr);


   public:


      string get_xml(disp_option * opt = nullptr) const;
      string get_text(disp_option * opt = nullptr) const;

      //bool consume(::const_ansi_range & rangeXml, const ::ansi_character * psz);
      //bool consume_whitespaces(::const_ansi_range & rangeXml, i32 iMinimumCount = 1);

      void LoadOtherNodes(bool* pbRet,::ansi_range & rangeXml, parse_info * pparseinfo = nullptr);

      // internal load functions
      //void LoadAttributes(::const_ansi_range & rangeXml, parse_info * pi = nullptr);
      void LoadAttributes(::ansi_range & rangeXml, parse_info * pi = nullptr);
      void LoadProcessingInstruction(::ansi_range & rangeXml, parse_info * pi = nullptr);
      void LoadDocType(::ansi_range & rangeXml, parse_info * pi = nullptr);
      void LoadComment(::ansi_range & rangeXml, parse_info * pi = nullptr);
      void LoadCDATA(::ansi_range & rangeXml, parse_info * pi = nullptr);

      
      node *                  get_child( const char * name);
      node *                  get_child_with_attribute(const ::scoped_string & scopedstrName, const ::atom & idAttribute, const ::payload & varAttribute, index iStart = 0);

      string                  get_simple_path() const;
      index_array             get_indexed_path() const;
      void                    get_indexed_path(index_array & iaPath) const;
      node *                  get_node_from_simple_path(const ::file::path & path);
      node *                  get_node_from_indexed_path(const index_array & ia);
      node *                  get_node_from_attr_path(const ::file::path & path, const scoped_string & scopedstrName, const ::scoped_string & scopedstrAttr);
      index_array             get_child_indexed_path(const node * pnode) const;
      void                    get_child_indexed_path(index_array & iaPath, const node * pnode) const;
      string                  get_child_simple_path(const node * pnode) const;
      string                  get_child_simple_attr_path(node * pnode, const ::scoped_string & scopedstrAttr);
      node *                  get_child(const char * name, index & iStartPosition);
      string                  get_child_value(const char * name);
      string                  get_child_text(const char * name, disp_option * opt = nullptr);

      node::array             children(const char * name);
      node::array &           children();

      ::property *            GetChildAttr(const char * name, const char * attrname);
      string                  GetChildAttrValue(const char * name, const char * attrname);
      node *                  GetChildByAttr(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAttrName, const ::scoped_string & scopedstrAttrValue);
      node *                  GetChildByAnyAttr(const ::scoped_string & scopedstrName, string_array & straName, string_array & straAttrValue);
      node *                  GetChildByAllAttr(const ::scoped_string & scopedstrName, string_array & straName, string_array & straAttrValue);

      node * get_child_at( index iIndex);
      node * get_child_at(const ::scoped_string & scopedstrName, index iIndex, index iDepth = 0);
      node * get_child_at_grow(const ::scoped_string & scopedstrName, index iIndex);
      ::count get_child_attr_value(string_array & stra, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAttrName, index iDepth = 1);
      ::count erase_child_with_attr(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrAttrName, index iIndex, ::count iCount = 1, index iDepth = 1);

      // search node
      node *                  rear_find( const char * name, i32 iDepth = -1);
      node *                  rear_find(const ::scoped_string & scopedstrName, const property_set & set, index iDepth = -1);
      
      index find_child_with_name_and_value(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrValue);
      node * child_with_name_and_value(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrValue);

      string plist_get(const ::scoped_string & scopedstrKey);

      // modify DOM
      ::count get_children_count();
      ::count get_children_count(const ::scoped_string & scopedstrName);
      ::count get_children_count(const ::scoped_string & scopedstrName, index iDepth);
      node *                  child_at(index i);
      //node *                create_node( const char * name = nullptr, const char * value = nullptr );
      node *                  add_child(const ::string & strName = nullptr, const ::scoped_string & scopedstrValue = nullptr);
      node *                  add_child(const ::string & strName, const property_set & set, const ::scoped_string & scopedstrValue = nullptr);
      node *                  add_child( node * node );
      bool                    erase_child( node * node );
      node *                  detach_child( node * node );

      // node/branch copy
      void                    CopyNode( node * node );
      void                    CopyBranch( node * branch );
      void                    _CopyBranch( node * node );
      node *                  AppendChildBranch( node * node );

      bool contains(const ::property_set & set) const { return m_set.contains(set); }
      
      ::property *            find_attribute(const ::scoped_string & scopedstr) { return m_set.find(scopedstr); }

      //template < typename TYPE >
      //bool find_attribute(const ::atom & atom, TYPE & t) { return m_set.find(atom, t); }

      ::property              attribute(const ::atom & atom) { return m_set[atom]; }
      ::property *            attribute_at(index i) { return m_set.property_at(i); }
      ::property *            set_attribute(const property & property) { return set_attribute(property.m_atom, property); }
      ::property *            set_attribute(const ::atom & atom, const ::payload & payload = ::e_type_new);
      bool                    erase_attribute(::property * pproperty) { return erase_attribute(pproperty->m_atom); }
      bool                    erase_attribute(const ::atom & atom) { return m_set.erase_by_name(atom) > 0; }


      bool from_row_column_v2(const string_array_array & straa);
      bool to_row_column_v2(string_array_array & straa);

      // operator overloads
      node * operator [] ( i32 i ) { return child_at(i); }


      void close();


      //::stream & write(::stream & stream) const override;
      //::stream & read(::stream & stream) override;

      
   private:

      node & operator = (const node & node);
      node(const node & node);

   };

} // namespace xml

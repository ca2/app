#pragma once


namespace data
{


   class CLASS_DECL_AURA node :
      virtual public ::generic_object
   {
   public:


      string                     m_strName;
      string                     m_strValue;
      property_set               m_set;
      __pointer_array(node)      m_nodea;


      string name() const { return m_strName; }
      void set_name(const char * pszName) { m_strName = pszName; }
      
      
      string value() const { return m_strValue; }
      void set_value(const char * pszValue) { m_strValue = pszValue; }


      property& attribute(const char* pszAttributeName) { return m_set[pszAttributeName]; }
      const property& attribute(const char* pszAttributeName) const { return m_set[pszAttributeName]; }


      node* node_at(::index i) { return m_nodea[i]; }
      ::count get_node_count() const { return m_nodea.get_count(); }





   };


} // namespace aura




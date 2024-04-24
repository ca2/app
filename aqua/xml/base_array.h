#pragma once


namespace xml
{


   template < i32 m_iNodeNameIndex, class TYPE, class ARG_TYPE = const TYPE &, class ARRAY = ::pointer_array < TYPE > >
   class array :
      public ARRAY,
      public exportable,
      public importable
   {
   public:


      array();
      array(const array & xmla);


      virtual void xml_export(output_tree & xmlof);
      virtual void xml_import(input_tree & xmlif);


   };


   template < i32 m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
   array()
   {
   }

   template < i32 m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
   array(const array & xmla) :
      ARRAY (xmla)
   {
   }



   template < i32 m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   void
   array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
   xml_export(output_tree & xmlof)
   {
      xmlof.set_attribute("count", this->get_size());
      for(i32 i = 0; i < this->get_size(); i++)
      {
         node * pnode = xmlof.export_node(xmlof.get_node_name(m_iNodeNameIndex), this->element_at(i));
         pnode->set_attribute("array_index", i);
      }
   }


   template < i32 m_iNodeNameIndex, class TYPE, class ARG_TYPE, class ARRAY >
   void
   array<m_iNodeNameIndex, TYPE, ARG_TYPE, ARRAY>::
   xml_import(input_tree & xmlif)
   {
      i32 iSize;
      iSize = xmlif.attribute("count");
      ARRAY::set_size(iSize);
      for(i32 i = 0; i < this->get_size(); i++)
      {
         property_set set;
         set.set_at("array_index", i);
         xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex), set, *this->element_at(i));
      }
   }



} // namespace xml





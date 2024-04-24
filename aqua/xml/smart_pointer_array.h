#pragma once


//
//namespace xml
//{
//
//
//   template < i32 m_iNodeNameIndex, class TYPE >
//   class pointer_array :
//      public ::pointer_array < TYPE >,
//      public exportable,
//      public importable
//   {
//   public:
//
//
//      pointer_array();
//      pointer_array(const pointer_array & xmla);
//
//
//      virtual void xml_export(output_tree & xmlof);
//      virtual void xml_import(input_tree & xmlif);
//
//
//   };
//
//
//   template < i32 m_iNodeNameIndex, class TYPE >
//   pointer_array<m_iNodeNameIndex, TYPE>::
//      pointer_array()
//   {
//   }
//
//   template < i32 m_iNodeNameIndex, class TYPE >
//   pointer_array<m_iNodeNameIndex, TYPE>::
//      pointer_array(const pointer_array & xmla)
//   {
//
//      copy(xmla);
//
//   }
//
//
//
//
//} // namespace xml
//


namespace xml
{


   class output_tree;
   class input_tree;


   template < i32 m_iNodeNameIndex, class TYPE >
   class pointer_array :
      public ::pointer_array < TYPE >,
      public exportable,
      public importable
   {
   public:


      pointer_array();
      pointer_array(const pointer_array & xmla);

      using ::pointer_array<TYPE>::operator();
      using matter::operator();

      virtual void xml_export(output_tree & xmlof);
      virtual void xml_import(input_tree & xmlif);


   };


   template < i32 m_iNodeNameIndex,class TYPE >
   pointer_array<m_iNodeNameIndex,TYPE>::
      pointer_array()
   {
      }

   template < i32 m_iNodeNameIndex,class TYPE >
   pointer_array<m_iNodeNameIndex,TYPE>::
      pointer_array(const pointer_array & xmla)
   {

      copy(xmla);

   }




} // namespace xml


//
//
//
//namespace xml
//{
//
//
//   template < i32 m_iNodeNameIndex,class TYPE >
//   class pointer_array:
//      public ::pointer_array < TYPE >,
//      public exportable,
//      public importable
//   {
//   public:
//
//
//      pointer_array();
//      pointer_array(const pointer_array & xmla);
//
//
//      virtual void xml_export(output_tree & xmlof);
//      virtual void xml_import(input_tree & xmlif);
//
//
//   };
//
//
//   template < i32 m_iNodeNameIndex,class TYPE >
//   pointer_array<m_iNodeNameIndex,TYPE>::
//      pointer_array()
//   {
//   }
//
//   template < i32 m_iNodeNameIndex,class TYPE >
//   pointer_array<m_iNodeNameIndex,TYPE>::
//      pointer_array(const pointer_array & xmla)
//   {
//
//      copy(xmla);
//
//   }
//
//
//
//} // namespace xml




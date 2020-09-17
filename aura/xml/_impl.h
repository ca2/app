#pragma once



//
//namespace file
//{
//
//
//   template < class T >
//   bool system::output(::object * pobject,const char * pszOutput,T * p,bool (T::*lpfnOuput)(stream &,const char *),const char * lpszSource)
//   {
//
//      Context.dir().mk(Context.dir().name(pszOutput),papp);
//
//      file_pointer fileOut = papp->get_context_session()->file_get_file(pszOutput,::file::mode_create | ::file::type_binary | ::file::mode_write);
//
//      if(fileOut.is_null())
//         return false;
//
//      stream ostream(fileOut);
//
//      return (p->*lpfnOuput)(ostream,lpszSource);
//
//   }
//
//
//   template < class T >
//   bool system::output(::object * pobject,const char * pszOutput,T * p,bool (T::*lpfnOuput)(stream &,stream &),const char * lpszInput)
//   {
//
//      Context.dir().mk(Context.dir().name(pszOutput),papp);
//
//      file_pointer fileOut = papp->get_context_session()->file_get_file(pszOutput,::file::mode_create | ::file::type_binary | ::file::mode_write);
//
//      if(fileOut.is_null())
//         return false;
//
//      file_pointer fileIn = papp->get_context_session()->file_get_file(lpszInput,::file::type_binary | ::file::mode_read);
//
//      if(fileIn.is_null())
//         return false;
//
//      stream ostream(fileOut);
//
//      stream istream(fileIn);
//
//      return (p->*lpfnOuput)(ostream,istream);
//
//   }
//
//
//   template < class T >
//   bool system::output(::object * pobject,const char * pszOutput,T * p,bool (T::*lpfnOuput)(stream &,stream &),stream & istream)
//   {
//
//      stream ostream(get(pszOutput,papp));
//
//      return (p->*lpfnOuput)(ostream,istream);
//
//   }
//
//
//} // namespace file
//
//






namespace xml
{


//   template < i32 m_iNodeNameIndex,class TYPE >
//   void
//   pointer_array<m_iNodeNameIndex,TYPE>::
//   xml_export(output_tree & xmlof)
//   {
//      xmlof.set_attr("count",this->get_size());
//      for(i32 i = 0; i < this->get_size(); i++)
//      {
//         node * pnode = xmlof.export_node(xmlof.get_node_name(m_iNodeNameIndex),this->operator()(i));
//         pnode->add_attr("array_index",i);
//      }
//   }
//
//
//   template < i32 m_iNodeNameIndex,class TYPE >
//   void
//   pointer_array<m_iNodeNameIndex,TYPE>::
//   xml_import(input_tree & xmlif)
//   {
//      i32 iSize;
//      xmlif.get_attr("count",iSize);
//      this->set_size_create(this, iSize);
//      for(i32 i = 0; i < this->get_size(); i++)
//      {
//         attr_array attra(this->get_context_application());
//         attra.set_at("array_index",i);
//         xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex),attra,this->operator()(i));
//      }
//   }

} // namespace xml



template < typename POINT_TYPE >
inline ::xml::input_tree & operator >> (::xml::input_tree & xmlif, point_array_base < POINT_TYPE > & pointa)
{

   pointa.remove_all();

   string strPoints;

   xmlif.get_value(strPoints);

   string_array straPoints;

   straPoints.explode(";", strPoints);

   for (auto & strPoint : straPoints)
   {

      string_array straCoord;

      straCoord.explode(",", strPoint);

      add(POINT_TYPE(__conv < typename POINT_TYPE::UNIT_TYPE >(straCoord[0]),
                     __conv < typename POINT_TYPE::UNIT_TYPE >(straCoord[1])));


   }

   return xmlif;

}




template < typename POINT_TYPE >
inline ::xml::output_tree & operator << (::xml::output_tree & xmlof, point_array_base < POINT_TYPE > & pointa)
{

   string strPoints;

   string strFormat = __xmlpri < POINT_TYPE::UNIT_TYPE > +"," + __xmlpri < POINT_TYPE::UNIT_TYPE > + ";";

   for (auto & point : pointa)
   {

      string strPoint;

      strPoint.Format(strFormat, point.x, point.y);

      strPoints += strPoint;

   }

   xmlof.set_value(strPoints);

   return xmlof;

}




namespace xml
{


   template < i32 m_iNodeNameIndex, class TYPE >
   void
      pointer_array<m_iNodeNameIndex, TYPE>::
      xml_export(output_tree & xmlof)
   {
      xmlof.set_attribute("count", this->get_size());
      for (i32 i = 0; i < this->get_size(); i++)
      {
         node * pnode = xmlof.export_node(xmlof.get_node_name(m_iNodeNameIndex), this->operator()(i));
         pnode->set_attribute("array_index", i);
      }
   }


   template < i32 m_iNodeNameIndex, class TYPE >
   void
      pointer_array<m_iNodeNameIndex, TYPE>::
      xml_import(input_tree & xmlif)
   {
      i32 iSize;
      iSize = xmlif.attribute("count");
      this->set_size(iSize);
      for (i32 i = 0; i < this->get_size(); i++)
      {
         auto & pitem = this->sp_at(i);
         pitem->create(this);
         property_set set;
         set["array_index"] = i;
         xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex), set, *pitem);
      }
   }

} // namespace xml

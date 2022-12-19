#pragma once



//
//namespace file
//{
//
//
//   template < class T >
//   bool system::output(::particle * pparticle,const scoped_string & strOutput,T * p,bool (T::*lpfnOuput)(stream &,const char *),const char * lpszSource)
//   {
//
//      dir()->create(dir()->name(pszOutput),papp);
//
//      file_pointer fileOut = papp->get_session()->file_get_file(pszOutput,::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);
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
//   bool system::output(::particle * pparticle,const scoped_string & strOutput,T * p,bool (T::*lpfnOuput)(stream &,stream &),const char * lpszInput)
//   {
//
//      dir()->create(dir()->name(pszOutput),papp);
//
//      file_pointer fileOut = papp->get_session()->file_get_file(pszOutput,::file::e_open_create | ::file::e_open_binary | ::file::e_open_write);
//
//      if(fileOut.is_null())
//         return false;
//
//      file_pointer fileIn = papp->get_session()->file_get_file(lpszInput,::file::e_open_binary | ::file::e_open_read);
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
//   bool system::output(::particle * pparticle,const scoped_string & strOutput,T * p,bool (T::*lpfnOuput)(stream &,stream &),stream & istream)
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
//         attr_array attra(this->get_app());
//         attra.set_at("array_index",i);
//         xmlif.import_node(xmlif.get_node_name(m_iNodeNameIndex),attra,this->operator()(i));
//      }
//   }

} // namespace xml








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

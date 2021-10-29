#pragma once


//class CLASS_DECL_ACME base_edit :
//   public ::data::data_container
//{
//public:
//
//
//   base_edit(::matter * pobject);
//   virtual ~base_edit();
//
//
//   template < class DATA >
//   inline DATA * validate_data(::data::data * pdata)
//   {
//
//      if(pdata == m_spdata)
//      {
//         return dynamic_cast < DATA * > (pdata);
//      }
//
//      return nullptr;
//
//   }
//
//
//   virtual void apply();
//   virtual void on_subject();
//
//
//};
//
//namespace data
//{
//
//   template < class EDIT >
//   EDIT * data::validate_edit(base_edit * pedit)
//   {
//
//      if(pedit->m_spdata == this)
//      {
//         return dynamic_cast < EDIT * > (pedit);
//      }
//
//      return nullptr;
//
//   }
//
//} // namespace data
//
//
//template < class DATA >
//class edit :
//   public base_edit 
//{
//public:      
//
//
//   edit(::matter * pobject);
//   virtual ~edit();
//
//
//   DATA * validate_data(::data::data * pdata)
//   {
//
//      return base_edit::validate_data < DATA > (pdata);  
//
//   }
//
//};
//
//
//template < class DATA >
//edit < DATA >::edit(::matter * pobject) :
//   ::matter(pobject),
//   base_edit(pobject)
//{
//}
//
//template < class DATA >
//edit < DATA >::~edit()
//{
//}





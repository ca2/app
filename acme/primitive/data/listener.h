#pragma once


namespace data
{


   class data;


   class CLASS_DECL_ACME listener :
      virtual public ::matter
   {
   public:


      data_map             m_datamap;
      


      listener();
      ~listener() override;


      bool listen(data * pdata, bool bListen = true);


      virtual void on_update_data(data * pdata, i32 iHint);

   };


   template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type, class PAIR = pair < listener *, VALUE > >
   using listener_map = ::map < listener *, VALUE, ARG_VALUE, PAIR >;


} // namespace data





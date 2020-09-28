#pragma once


namespace data
{


   class data;


   class CLASS_DECL_APEX listener :
      virtual public ::elemental
   {
   public:


      data_map             m_datamap;
      


      listener();
      virtual ~listener();


      bool listen(data * pdata, bool bListen = true);


      virtual void on_update_data(data * pdata, i32 iHint);

   };

   template < class VALUE, class ARG_VALUE = const VALUE &, class PAIR = pair < listener *, VALUE > >
   using listener_map = map < listener *, listener *, VALUE, ARG_VALUE, PAIR >;


} // namespace data





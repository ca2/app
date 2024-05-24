#pragma once



#include "acid/primitive/data/data.h"


namespace data
{


   class data;


   class CLASS_DECL_ACID listener :
      virtual public ::particle
   {
   public:


      data_map             m_datamap;
      


      listener();
      ~listener() override;


      bool listen(data * pdata, bool bListen = true);


      virtual void on_update_data(data * pdata, i32 iHint);

   };


   template < class PAYLOAD, class PAIR = pair < listener *, PAYLOAD > >
   using listener_map = ::map < listener *, PAYLOAD, PAIR >;


} // namespace data





#pragma once


//#include "acme/prototype/prototype/matter.h"


class CLASS_DECL_APEX context :
   virtual public matter
{
public:


   long long       m_iUpdateSerial;


   context();
   ~context() override;


   virtual void start_task();


   virtual bool is_up_to_date(const ::topic * phandler) const;

   virtual void set_up_to_date(const ::topic * phandler);


};


using context_pointer = ::pointer<context>;





#pragma once


class CLASS_DECL_ACME change :
   virtual public matter
{
public:


   ::i64                         m_iUpdateSerial;
   bool                          m_bFork;


   change();
   virtual ~change();


   virtual ::estatus start_task();


   inline bool is_up_to_date(::update * pupdate) const;

   virtual void set_up_to_date(::update* pupdate);

   //inline ::id& id();
   //inline const ::id& id() const;

};



using change_pointer = __pointer(change);




#pragma once




//class CLASS_DECL_ACME synchronization_result
//{
//public:
//
//
//   enum_synchronization_result      m_esynchronizationresult;
//
//
//   //explicit synchronization_result(::u32 uStatus, ::count objectCount = 1);
//
//
//   synchronization_result(enum_synchronization_result esynchronizationresult)
//      : m_esynchronizationresult(esynchronizationresult)
//   {
//   
//   }
//
//   
//   synchronization_result()
//      : m_esynchronizationresult(e_synchronization_result_error)
//   {
//   
//   }
//
//
//   inline bool abandoned() const;
//
//
//   inline ::index abandoned_index() const;
//
//
//   inline bool error() const;
//
//
//   inline bool bad_thread() const;
//
//
//   inline bool timed_out() const;
//
//
//   inline bool signaled() const;
//
//
//   inline bool succeeded() const;
//
//
//   inline bool failed() const { return !succeeded(); }
//
//
//   bool operator !() const { return failed(); }
//
//
//   inline ::index signaled_index() const;
//
//
//   bool operator == (enum_synchronization_result eresult) const
//   {
//
//      return m_esynchronizationresult == eresult;
//
//   }
//
//
//};


inline ::i32 signaled_index(::enum_status estatus)
{

   return (estatus >= signaled_base && estatus < signaled_end) ? ((::i32)estatus - (::i32)signaled_base) : -1;

}


inline bool signaled(::enum_status estatus)
{

   return signaled_index(estatus) >= 0;

}


inline ::i32 abandoned_index(::enum_status estatus)
{

   return (estatus >= abandoned_base && estatus < abandoned_end) ? ((::i32)estatus - (::i32)abandoned_base) : -1;

}


inline bool abandoned(::enum_status estatus)
{

   return abandoned_index(estatus) >= 0;

}



inline bool wait_timeout(::enum_status estatus)
{

   return estatus == error_wait_timeout;

}


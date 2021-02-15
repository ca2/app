#pragma once


enum enum_synchronization_result : ::index
{


   e_synchronization_result_abandoned_base = -1024,
   e_synchronization_result_error = -16,	
   e_synchronization_result_io_completion = -3,
   e_synchronization_result_bad_thread = -2,
   e_synchronization_result_timed_out = -1,		
   e_synchronization_result_signaled_base = 0,	


};


class CLASS_DECL_ACME synchronization_result
{
public:


   enum_synchronization_result      m_esynchronizationresult;


   //explicit synchronization_result(::u32 uStatus, ::count objectCount = 1);


   synchronization_result(enum_synchronization_result esynchronizationresult)
      : m_esynchronizationresult(esynchronizationresult)
   {
   
   }

   
   synchronization_result()
      : m_esynchronizationresult(e_synchronization_result_error)
   {
   
   }


   inline bool abandoned() const;


   inline ::index abandoned_index() const;


   inline bool error() const;


   inline bool bad_thread() const;


   inline bool timed_out() const;


   inline bool signaled() const;


   inline bool succeeded() const;


   inline bool failed() const { return !succeeded(); }


   operator bool() const { return succeeded(); }


   bool operator !() const { return failed(); }


   inline ::index signaled_index() const;


};




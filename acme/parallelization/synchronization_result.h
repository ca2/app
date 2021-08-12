#pragma once


#ifndef WINDOWS


#define MAXIMUM_SYNCHRONIZING_OBJECTS 64


#endif


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


   bool operator !() const { return failed(); }


   inline ::index signaled_index() const;


   bool operator == (enum_synchronization_result eresult) const
   {

      return m_esynchronizationresult == eresult;

   }


};




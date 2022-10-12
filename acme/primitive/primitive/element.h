// Created by camilo on 2021-08-01 22:55 Thomas Month!! <3ThomasBS__!!
#pragma once



// ATTENTION
// Shared with:
// Objective-C++



class CLASS_DECL_ACME element :
   virtual public handler
{
public:

   
   element() {};
   ~element() override;


   // <3ThomasBorregaardSørensen__!! likes handler concept...
   //void route(::signal * psignal) override;
   //void signal(::signal * psignal) override;
   //void route(::topic * ptopic, ::context * pcontext) override;
   //void post_process(::topic * ptopic, ::context * pcontext) override;

   // <3TBS_!! handle -> call_member <3TBS_!!
   virtual void call_member(::i64 i64);
   // <3ThomasBS_!! handle -> handle <3ThomasBS_!!
   //void handle(const  emessage, i64 iData = 0, ::matter * pmatter = nullptr) override;
   //void handle(::topic * ptopic, ::context * pcontext) override;
   //void handle(::message::message * pmessage) override;


//   void run() override; 
   virtual ::payload realize();


   virtual ::element * clone() const;



   virtual void set_generic_object_name(const char* pszName);
   virtual void set_library_name(const char* pszLibraryName);
   // if this is an application/or nano application
   virtual void set_application_id(const char* pszApplicationId);


//   // currently expected returned statuses:
//   // ::error_failed
//   // ::error_wait_timeout
//   // ::success
//   // also see synchronization_object
//   virtual ::e_status wait();
//   virtual ::e_status wait(const class ::wait & wait);


   [[nodiscard]] virtual ::duration timeout() const;


   virtual void set_timeout(const ::duration & duration);


   virtual ::element * get_taskpool_container();


   virtual ::task_pool * taskpool();






   [[nodiscard]] virtual bool should_run_async() const;


   //virtual void to_string(string_exchange & str) const;


   [[nodiscard]] virtual ::enum_type get_payload_type() const;


   //virtual void exchange(::stream& s);
   //virtual void exchange(::payload_stream& s);

   virtual void write(::binary_stream& stream) const;
   virtual void read(::binary_stream& stream);


   virtual void add_composite(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual void add_reference(::element* pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual void release_composite2(::element * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual void finalize_composite(::element * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   virtual void release_reference(::element * pobject OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual void destroy();
   virtual void destroy_impl_data();
   virtual void destroy_os_data();







};




#ifndef _DEBUG

inline i64 element::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


inline i64 element::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = --m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


inline i64 element::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif




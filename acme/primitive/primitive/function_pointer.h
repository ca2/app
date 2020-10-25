#pragma once

//template < typename METHOD >
//class sync_method :
//   public METHOD
//{
//public:
//
//
//   __pointer(manual_reset_event)          m_peventCompleted;
//
//   sync_method();
//   virtual ~sync_method() { }
//
//   inline virtual ::estatus operator()() override;
//
//   virtual bool should_run_async() const override { return true; }
//
//   
//};


//class CLASS_DECL_ACME sync_function :
//   public ::function
//{
//public:
//
//
//   __pointer(manual_reset_event)    m_pevFunctionCompleted;
//
//
//   sync_function();
//   virtual ~sync_function() { }
//
//   virtual ::estatus operator()() override;
//
//   virtual void operator()(const var& var) override;
//
//
//};

//
using function_pointer = ::matter_pointer;
//
//


//class CLASS_DECL_ACME function
//{
//protected:
//
//
//   ::matter_pointer        m_pmatter;
//
//
//   function() {}
//   function(const ::matter_pointer & pmatter) : m_pmatter(m_pmatter) { }
//
//public:
//
//
//   inline operator bool () const { return ::is_set(m_pmatter); }
//
//   //inline operator const matter_pointer& () const { return m_pmatter; }
//
//   inline operator matter* () const { return m_pmatter; }
//
//   inline operator lparam () const { return m_pmatter.m_p; }
//
//
//};
//
//
//

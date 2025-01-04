// Created by camilo on 2024-06-11 05:31 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_function FUNCTION >
class add_signal_function_to_holder
{
public:

   ::data::signal < FUNCTION > * m_psignal;
   ::object * m_pobjectFunctionHolder;
   add_signal_function_to_holder(::data::signal < FUNCTION > & signal, ::object * pobjectFunctionHolder) :
      m_psignal(&signal), m_pobjectFunctionHolder(pobjectFunctionHolder)
   {

   }

   add_signal_function_to_holder & operator += (const FUNCTION & f);

};


namespace data
{


   template < primitive_function FUNCTION >
   class signal
   {
   public:


      ::comparable_array < FUNCTION >     m_functiona;


      signal & operator +=(const FUNCTION & function) { m_functiona += function; return *this; }
      signal & operator -=(const FUNCTION & function) { m_functiona -= function; return *this; }


   };


} // namespace data

CLASS_DECL_ACME ::huge_integer function_debugging_serial();
template < primitive_function FUNCTION >
void object::hold_signal_function(::data::signal<FUNCTION> * psignal, FUNCTION function)
{

   this->destroyinga() += [this, psignal, function]()
      {

         (*psignal) -= function;

      };
#if FUNCTION_DEBUGGING
   this->destroyinga().last().m_pszDebug = "hold signal function";
   this->destroyinga().last().m_iDebug = function_debugging_serial();
#endif

}


template < primitive_function FUNCTION >
add_signal_function_to_holder<FUNCTION> & add_signal_function_to_holder<FUNCTION>::operator += (const FUNCTION & f)
{

   (*m_psignal) += f;

   m_pobjectFunctionHolder->hold_signal_function(m_psignal, f);

   return *this;

}




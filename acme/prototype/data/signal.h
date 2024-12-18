// Created by camilo on 2024-06-11 05:31 <3ThomasBorregaardSorensen!!
#pragma once


template < primitive_function FUNCTION >
class add_signal_function_to_holder
{
public:

   ::data::signal < FUNCTION > * m_psignal;
   ::matter * m_pmatterFunctionHolder;
   add_signal_function_to_holder(::data::signal < FUNCTION > & signal, ::matter * pmatterFunctionHolder) :
      m_psignal(&signal), m_pmatterFunctionHolder(pmatterFunctionHolder)
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


template < primitive_function FUNCTION >
void matter::hold_signal_function(::data::signal<FUNCTION> * psignal, FUNCTION function)
{

   this->destroyinga() += [this, psignal, function]()
      {

         (*psignal) -= function;

      };

}


template < primitive_function FUNCTION >
add_signal_function_to_holder<FUNCTION> & add_signal_function_to_holder<FUNCTION>::operator += (const FUNCTION & f)
{

   (*m_psignal) += f;

   m_pmatterFunctionHolder->hold_signal_function(m_psignal, f);

   return *this;

}




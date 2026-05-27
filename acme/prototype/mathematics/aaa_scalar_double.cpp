// From template to class by camilo on 2022-11-17 04:35 ILoveYouThomasBorregaardSorensen!!
#include "framework.h"
#include "scalar.h"
////#include "acme/exception/exception.h"
//
////void f64_scalar_source::listener::on_set_scalar(f64_scalar_source * psource,enum_scalar escalar,::f64 dValue,::i32 iFlags)
////{
////
////   __UNREFERENCED_PARAMETER(psource);
////   __UNREFERENCED_PARAMETER(escalar);
////   __UNREFERENCED_PARAMETER(dValue);
////
////}
////
////f64_scalar_source::f64_scalar_source()
////{
////
////   m_plistener = nullptr;
////
////}
////
////
////bool f64_scalar_source::set_scalar(enum_scalar escalar,::f64 d,bool bForce,::i32 iFlags)
////{
////
////   if (!bForce)
////   {
////
////      if (!contains(escalar, d))
////         return false;
////
////   }
////
////   on_set_scalar(escalar, d, iFlags);
////
////   if (m_plistener != nullptr)
////   {
////
////      m_plistener->on_set_scalar(this, escalar, d, iFlags);
////
////   }
////
////   return true;
////
////}
////
////bool f64_scalar_source::constrain_scalar(enum_scalar escalar, ::f64 & dValue)
////{
////
////   bool bConstrain;
////
////   if ((bConstrain = constrain(escalar, dValue)))
////   {
////
////      ::f64 d = 0.0;
////
////      get_scalar(escalar, d);
////
////      if (dValue == d)
////         return true;
////
////   }
////
////   bool bSet = set_scalar(escalar, dValue);
////
////   return bConstrain && bSet;
////
////}
////
////
////::f64 f64_scalar_source::get_rate(enum_scalar escalar, ::f64 dDefault)
////{
////
////   ::f64 dMax = 0.0;
////
////   get_scalar_maximum(escalar, dMax);
////
////   ::f64 dMin = 0.0;
////
////   get_scalar_minimum(escalar, dMin);
////
////   ::f64 dDenominator = dMax - dMin;
////
////   if (dDenominator == 0)
////      return dDefault;
////
////   ::f64 dVal = 0.0;
////
////   get_scalar(escalar, dVal);
////
////   ::f64 dNumerator = dVal - dMin;
////
////   return dNumerator / dDenominator; // aproximate value along iDenominator and iNumerator evaluation
////
////}
////
////bool f64_scalar_source::set_rate(enum_scalar escalar,::f64 dValue,::i32 iFlags)
////{
////
////   if(dValue < 0.0)
////      return false;
////
////   if(dValue > 1.0)
////      return false;
////
////   ::f64 dMax = 0.0;
////
////   get_scalar_maximum(escalar,dMax);
////
////   ::f64 dMin = 0.0;
////
////   get_scalar_minimum(escalar,dMin);
////
////   ::f64 dDenominator = dMax - dMin;
////
////   on_set_scalar(escalar,dValue * dDenominator + dMin, iFlags);
////
////   return true;
////
////}
////
////
////bool f64_scalar_source::contains(enum_scalar escalar, ::f64 dValue)
////{
////
////   ::f64 dMin = 0.0;
////
////   get_scalar_minimum(escalar, dMin);
////
////   if (dValue < dMin)
////      return false;
////
////   ::f64 dMax = 0.0;
////
////   get_scalar_maximum(escalar, dMax);
////
////   if (dValue > dMax)
////      return false;
////
////   return true;
////
////}
////
////bool f64_scalar_source::constrain(enum_scalar escalar, ::f64 & dValue)
////{
////
////   ::f64 dMin = 0.0;
////   
////   get_scalar_minimum(escalar, dMin);
////
////   if (dValue < dMin)
////   {
////
////      dValue = dMin;
////
////      return true;
////
////   }
////
////   ::f64 dMax = 0.0;
////
////   get_scalar_maximum(escalar, dMax);
////
////   if (dValue > dMax)
////   {
////
////      dValue = dMax;
////
////      return true;
////
////   }
////
////   return false;
////
////}
////
////
////
bool scalar_source::on_set_real_scalar(enum_scalar escalar,::real d,::i32 iFlags)
{

   __UNREFERENCED_PARAMETER(escalar);

   __UNREFERENCED_PARAMETER(d);

   __UNREFERENCED_PARAMETER(iFlags);

   // does nothing.

   return false;

}
////
////void f64_scalar_source::get_scalar_minimum(enum_scalar escalar, ::f64 & d)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   d = 1.0; // by default
////
////}
////
////void f64_scalar_source::get_scalar(enum_scalar escalar, ::f64 & d)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   d = 1.0; // by default
////
////}
////
////void f64_scalar_source::get_scalar_maximum(enum_scalar escalar, ::f64 & d)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   d = 1.0; // by default
////
////}
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////void i32_scalar_source::listener::on_set_scalar(i32_scalar_source * psource,enum_scalar escalar,::i64 real,::i32 iFlags)
////{
////
////   __UNREFERENCED_PARAMETER(psource);
////   __UNREFERENCED_PARAMETER(escalar);
////   __UNREFERENCED_PARAMETER(real);
////   __UNREFERENCED_PARAMETER(iFlags);
////
////}
////
////
////i32_scalar_source::i32_scalar_source()
////{
////
////   m_plistener = nullptr;
////
////}
////
////
////bool i32_scalar_source::set_scalar(enum_scalar escalar,::i64 real,bool bForce,::i32 iFlags)
////{
////
////   if (!bForce)
////   {
////      if (!contains(escalar, real))
////         return false;
////   }
////
////   on_set_scalar(escalar, real, iFlags);
////
////   if (m_plistener != nullptr)
////   {
////      
////      m_plistener->on_set_scalar(this, escalar, real, iFlags);
////
////   }
////
////   return true;
////
////}
////
////bool i32_scalar_source::constrain_scalar(enum_scalar escalar, ::i64 & real)
////{
////
////   bool bConstrain;
////
////   if((bConstrain = constrain(escalar, real)))
////   {
////
////      ::i64 i = 0;
////
////      get_scalar(escalar, i);
////
////      if (real == i)
////         return true;
////
////   }
////
////   bool bSet = set_scalar(escalar, real);
////
////   return bConstrain && bSet;
////
////}
////
////void i32_scalar_source::increment_scalar(enum_scalar escalar, ::i64 iIncrement)
////{
////
////   ::i64 i = 0;
////
////   get_scalar(escalar, i);
////   
////   set_scalar(escalar, i + iIncrement);
////
////}
////
////bool i32_scalar_source::contains(enum_scalar escalar, ::i64 real)
////{
////
////   ::i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   if (real < iMin)
////      return false;
////
////   ::i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   if (real > iMax)
////      return false;
////
////   return true;
////
////}
////
////bool i32_scalar_source::constrain(enum_scalar escalar, ::i64 & real)
////{
////
////   ::i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   if (real < iMin)
////   {
////
////      real = iMin;
////
////      return true;
////
////   }
////
////   ::i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   if (real > iMax)
////   {
////
////      real = iMax;
////
////      return true;
////
////   }
////
////   return false;
////
////}
////
////
////
////void i32_scalar_source::on_set_scalar(enum_scalar escalar,::i64 real,::i32 iFlags)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   __UNREFERENCED_PARAMETER(real);
////
////   __UNREFERENCED_PARAMETER(iFlags);
////
////   // does nothing by default.
////
////}
////
////void i32_scalar_source::get_scalar_minimum(enum_scalar escalar, ::i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////
////   i = 0; // by default
////
////}
////
////void i32_scalar_source::get_scalar(enum_scalar escalar, ::i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   i = 1; // by default
////
////}
////
////void i32_scalar_source::get_scalar_maximum(enum_scalar escalar, ::i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   i = 1; // by default
////
////}
////
////::f64 i32_scalar_source::get_rate(enum_scalar escalar, ::f64 dDefault)
////{
////
////   ::i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   ::i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   ::i64 iDenominator = iMax - iMin;
////
////   if (iDenominator == 0)
////      return dDefault;
////
////   ::i64 iVal = 0;
////
////   get_scalar(escalar, iVal);
////
////   ::i64 iNumerator = iVal - iMin;
////
////   return (::f64) iNumerator / (::f64) iDenominator; // aproximate value along iDenominator and iNumerator evaluation
////
////}
////
////
////bool i32_scalar_source::set_rate(enum_scalar escalar,::f64 dValue,::i32 iFlags)
////{
////
////   if(dValue < 0.0)
////      return false;
////
////   if(dValue > 1.0)
////      return false;
////
////   ::i64 iMax = 0;
////
////   get_scalar_maximum(escalar,iMax);
////
////   ::i64 iMin = 0;
////
////   get_scalar_minimum(escalar,iMin);
////
////   ::i64 iDenominator = iMax - iMin;
////
////   on_set_scalar(escalar,(::i64) round(dValue * iDenominator) + iMin, iFlags);
////
////   return true;
////
////}
//
//::f64 scalar_base::get_rate(::f64 dDefault)
//{
//
//   return dDefault;
//
//}
//
//bool scalar_base::set_rate(::f64 dValue, ::i32 iFlags)
//{
//
//   __UNREFERENCED_PARAMETER(dValue);
//
//   __UNREFERENCED_PARAMETER(iFlags);
//
//   return false;
//
//}
//
//
//string scalar_base::Format(const ::scoped_string & scopedstrFormat)
//{
//
//   __UNREFERENCED_PARAMETER(strFormat);
//
//   return "";
//
//
//}
//
////
////
////
////real_scalar::real_scalar(f64_scalar_source * psource, enum_scalar escalar, const ::scoped_string & scopedstrFormat)
////{
////
////   m_psource = psource;
////   m_escalar = escalar;
////   m_strFormat = strFormat;
////}
////
////
////void real_scalar::set(::f64 dValue)
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return;
////
////   m_psource->set_scalar(m_escalar, dValue);
////
////}
////
////
////::f64 real_scalar::get()
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return 0.0;
////
////   ::f64 d = 0.0;
////
////   m_psource->get_scalar(m_escalar, d);
////
////   return d;
////
////}
////
////
////::f64 real_scalar::get_rate(::f64 dDefault)
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return dDefault;
////
////   return m_psource->get_rate(m_escalar, dDefault);
////
////}
////
////
////bool real_scalar::set_rate(::f64 dValue,::i32 iFlags)
////{
////
////   if(m_psource == nullptr || m_escalar == scalar_none)
////      return false;
////
////   return m_psource->set_rate(m_escalar,dValue, iFlags);
////
////}
////
////
////::f64 real_scalar::minimum()
////{
////
////   if (is_null())
////      return 0.0;
////
////   ::f64 d = 0.0;
////
////   m_psource->get_scalar_minimum(m_escalar, d);
////
////   return d;
////
////}
////
////
////::f64 real_scalar::maximum()
////{
////
////   if (is_null())
////      return 0.0;
////
////   ::f64 d = 0.0;
////
////   m_psource->get_scalar_maximum(m_escalar, d);
////
////   return d;
////
////}
////
////string real_scalar::Format(const ::scoped_string & scopedstrFormat)
////{
////
////   string str;
////
////   str.formatf(strFormat,get());
////
////   return str;
////
////}
////
////i32_scalar::i32_scalar(i32_scalar_source * psource, enum_scalar escalar, const ::scoped_string & scopedstrFormat)
////{
////
////   m_psource = psource;
////   m_escalar = escalar;
////   m_strFormat = strFormat;
////
////}
////
////
////void i32_scalar::set(::i64 real)
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return;
////
////   m_psource->set_scalar(m_escalar, real);
////
////}
////
////
////::i64 i32_scalar::get()
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return 0;
////
////   ::i64 i = 0;
////
////   m_psource->get_scalar(m_escalar, i);
////
////   return i;
////
////}
////
////
////::f64 i32_scalar::get_rate(::f64 dDefault)
////{
////   
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return dDefault;
////
////   return m_psource->get_rate(m_escalar, dDefault);
////
////}
////
////
////bool i32_scalar::set_rate(::f64 dValue,::i32 iFlags)
////{
////
////   if(m_psource == nullptr || m_escalar == scalar_none)
////      return false;
////
////   return m_psource->set_rate(m_escalar,dValue, iFlags);
////
////}
////
////
////::i64 i32_scalar::minimum()
////{
////   
////   if (is_null())
////      return 0;
////
////   ::i64 i = 0;
////
////   m_psource->get_scalar_minimum(m_escalar, i);
////
////   return i;
////
////}
////
////
////::i64 i32_scalar::maximum()
////{
////
////   if (is_null())
////      return 0;
////
////   ::i64 i = 0;
////
////   m_psource->get_scalar_maximum(m_escalar, i);
////
////   return i;
////
////}
////
////
////
////
////
////string i32_scalar::Format(const ::scoped_string & scopedstrFormat)
////{
////
////   string str;
////
////   str.formatf(strFormat,get());
////
////   return str;
////
////}

























bool scalar_source::listener::on_set_real_scalar(scalar_source* psource, enum_scalar escalar, ::real real, ::i32 iFlags)
{

   __UNREFERENCED_PARAMETER(psource);
   __UNREFERENCED_PARAMETER(escalar);
   __UNREFERENCED_PARAMETER(real);
   __UNREFERENCED_PARAMETER(iFlags);

   return false;

}



bool scalar_source::set_real_scalar(enum_scalar escalar, ::real real, bool bForce, ::i32 iFlags)
{

   if (!bForce)
   {

      if (!contains_real_scalar(escalar, real))
      {

         return false;

      }

   }

   on_set_real_scalar(escalar, real, iFlags);

   for (auto& plistener : m_scalarlistenera)
   {

      try
      {

         plistener->on_set_real_scalar(this, escalar, real, iFlags);

      }
      catch (...)
      {

      }

   }
   return true;

}


bool scalar_source::constrain_real_scalar(enum_scalar escalar, ::real & real)
{

   ::real realMinimum = 0;

   if (get_real_scalar_minimum(escalar, realMinimum))
   {

      if (real < realMinimum)
      {

         real = realMinimum;

         return true;

      }

   }

   ::real realMaximum = 0;

   if (get_real_scalar_maximum(escalar, realMaximum))
   {

      if (real > realMaximum)
      {

         real = realMaximum;

         return true;

      }

   }

   return false;

   //::real realCurrent = 0;

   //get_real_scalar(escalar, realCurrent);

   //if (realCurrent == real)
   //{

   //   return true;

   //}

   //return set_real_scalar(escalar, real);

}


void scalar_source::increment_real_scalar(enum_scalar escalar, ::real iIncrement)
{

   ::real i = 0;

   if (get_real_scalar(escalar, i))
   {

      set_real_scalar(escalar, i + iIncrement);

   }

}



bool scalar_source::contains_real_scalar(enum_scalar escalar, ::real real)
{

   ::real iMin = 0;

   if (get_real_scalar_minimum(escalar, iMin))
   {

      if (real < iMin)
      {

         return false;

      }

   }

   ::real iMax = 0;

   if (get_real_scalar_maximum(escalar, iMax))
   {

      if (real > iMax)
      {

         return false;

      }

   }

   return true;

}



//bool scalar_source::constrain_real_scalar(enum_scalar escalar, ::real& real)
//{
//
//   ::real iMin = 0;
//
//   if (get_scalar_minimum(escalar, iMin))
//   {
//
//      if (real < iMin)
//      {
//
//         real = iMin;
//
//         return true;
//
//      }
//
//   }
//
//   ::real iMax = 0;
//
//   if (get_scalar_maximum(escalar, iMax))
//   {
//
//      if (real > iMax)
//      {
//
//         real = iMax;
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//}
//
//
//
//void scalar_source::on_set_scalar(enum_scalar escalar,::real real,::i32 iFlags)
//{
//
//   __UNREFERENCED_PARAMETER(escalar);
//
//   __UNREFERENCED_PARAMETER(real);
//
//   __UNREFERENCED_PARAMETER(iFlags);
//
//   // does nothing by default.
//
//}
//
//
//
bool scalar_source::get_real_scalar_minimum(enum_scalar escalar,::real & i)
{

   __UNREFERENCED_PARAMETER(escalar);

   //i = 0; // by default

   return false;

}



bool scalar_source::get_real_scalar(enum_scalar escalar,::real & i)
{

   __UNREFERENCED_PARAMETER(escalar);

   //i = 1; // by default

   return false;

}


bool scalar_source ::get_real_scalar_maximum(enum_scalar escalar,::real & i)
{

   __UNREFERENCED_PARAMETER(escalar);

   // i = 1; // by default

   return false;

}



::f64 scalar_source::get_real_scalar_rate(enum_scalar escalar, ::f64 dDefault)
{

   ::real iMax = 0;

   if (!get_real_scalar_maximum(escalar, iMax))
   {

      throw exception(error_wrong_state);

   }

   ::real iMin = 0;

   if (!get_real_scalar_minimum(escalar, iMin))
   {

      throw exception(error_wrong_state);

   }

   ::real iDenominator = iMax - iMin;

   if (iDenominator == 0)
   {

      return dDefault;


   }

   ::real iVal = 0;

   get_real_scalar(escalar, iVal);

   ::real iNumerator = iVal - iMin;

   return (::f64)iNumerator / (::f64)iDenominator; // aproximate value along iDenominator and iNumerator evaluation

}



bool scalar_source::set_real_scalar_rate(enum_scalar escalar, ::f64 dValue, ::i32 iFlags)
{

   if (dValue < 0.0)
   {

      return false;

   }

   if (dValue > 1.0)
   {

      return false;

   }

   ::real iMax = 0;

   if (!get_real_scalar_maximum(escalar, iMax))
   {

      throw exception(error_wrong_state);

   }

   ::real iMin = 0;

   if (!get_real_scalar_minimum(escalar, iMin))
   {

      throw exception(error_wrong_state);

   }

   ::real iDenominator = iMax - iMin;

   on_set_real_scalar(escalar, (::real)(dValue * iDenominator) + iMin, iFlags);

   return true;

}




real_scalar::real_scalar(scalar_source* psource, enum_scalar escalar, const ::scoped_string & scopedstrFormat)
{

   m_psource = psource;
   m_escalar = escalar;
   m_strFormat = strFormat;

}


void real_scalar::set(::real real)
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
      return;

   m_psource->set_real_scalar(m_escalar, real);

}


::real real_scalar::get()
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
   {

      return 0;

   }

   ::real i = 0;

   m_psource->get_real_scalar(m_escalar, i);

   return i;

}


::f64 real_scalar::get_rate(::f64 dDefault)
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
   {

      return dDefault;

   }

   return m_psource->get_real_scalar_rate(m_escalar, dDefault);

}


bool real_scalar ::set_rate(::f64 dValue, ::i32 iFlags)
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
   {

      return false;

   }

   return m_psource->set_real_scalar_rate(m_escalar, dValue, iFlags);

}


::real real_scalar ::minimum()
{

   if (is_null())
   {

      return 0;

   }

   ::real i = 0;

   if (!m_psource->get_real_scalar_minimum(m_escalar, i))
   {

      throw ::exception(error_wrong_state);

   }

   return i;

}



::real real_scalar::maximum()
{

   if (is_null())
   {

      return 0;

   }

   ::real i = 0;

   if (!m_psource->get_real_scalar_maximum(m_escalar, i))
   {

      throw ::exception(error_wrong_state);

   }

   return i;

}


string real_scalar::printf(const ::scoped_string & scopedstrFormat)
{

   ::string str;

   str.formatf(strFormat, get());

   return str;

}




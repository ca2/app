// From template to class by camilo on 2022-11-17 04:50 ILoveYouThomasBorregaardSorensen!!
#include "framework.h"
#include "scalar.h"
//
////void double_scalar_source::listener::on_set_scalar(double_scalar_source * psource,enum_scalar escalar,double dValue,int iFlags)
////{
////
////   __UNREFERENCED_PARAMETER(psource);
////   __UNREFERENCED_PARAMETER(escalar);
////   __UNREFERENCED_PARAMETER(dValue);
////
////}
////
////double_scalar_source::double_scalar_source()
////{
////
////   m_plistener = nullptr;
////
////}
////
////
////bool double_scalar_source::set_scalar(enum_scalar escalar,double d,bool bForce,int iFlags)
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
////bool double_scalar_source::constrain_scalar(enum_scalar escalar, double & dValue)
////{
////
////   bool bConstrain;
////
////   if ((bConstrain = constrain(escalar, dValue)))
////   {
////
////      double d = 0.0;
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
////double double_scalar_source::get_rate(enum_scalar escalar, double dDefault)
////{
////
////   double dMax = 0.0;
////
////   get_scalar_maximum(escalar, dMax);
////
////   double dMin = 0.0;
////
////   get_scalar_minimum(escalar, dMin);
////
////   double dDenominator = dMax - dMin;
////
////   if (dDenominator == 0)
////      return dDefault;
////
////   double dVal = 0.0;
////
////   get_scalar(escalar, dVal);
////
////   double dNumerator = dVal - dMin;
////
////   return dNumerator / dDenominator; // aproximate value along iDenominator and iNumerator evaluation
////
////}
////
////bool double_scalar_source::set_rate(enum_scalar escalar,double dValue,int iFlags)
////{
////
////   if(dValue < 0.0)
////      return false;
////
////   if(dValue > 1.0)
////      return false;
////
////   double dMax = 0.0;
////
////   get_scalar_maximum(escalar,dMax);
////
////   double dMin = 0.0;
////
////   get_scalar_minimum(escalar,dMin);
////
////   double dDenominator = dMax - dMin;
////
////   on_set_scalar(escalar,dValue * dDenominator + dMin, iFlags);
////
////   return true;
////
////}
////
////
////bool double_scalar_source::contains(enum_scalar escalar, double dValue)
////{
////
////   double dMin = 0.0;
////
////   get_scalar_minimum(escalar, dMin);
////
////   if (dValue < dMin)
////      return false;
////
////   double dMax = 0.0;
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
////bool double_scalar_source::constrain(enum_scalar escalar, double & dValue)
////{
////
////   double dMin = 0.0;
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
////   double dMax = 0.0;
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
////void double_scalar_source::on_set_scalar(enum_scalar escalar,double d,int iFlags)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   __UNREFERENCED_PARAMETER(d);
////
////   __UNREFERENCED_PARAMETER(iFlags);
////
////   // does nothing.
////
////}
////
////void double_scalar_source::get_scalar_minimum(enum_scalar escalar, double & d)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   d = 1.0; // by default
////
////}
////
////void double_scalar_source::get_scalar(enum_scalar escalar, double & d)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   d = 1.0; // by default
////
////}
////
////void double_scalar_source::get_scalar_maximum(enum_scalar escalar, double & d)
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
////void int_scalar_source::listener::on_set_scalar(int_scalar_source * psource,enum_scalar escalar,i64 iValue,int iFlags)
////{
////
////   __UNREFERENCED_PARAMETER(psource);
////   __UNREFERENCED_PARAMETER(escalar);
////   __UNREFERENCED_PARAMETER(iValue);
////   __UNREFERENCED_PARAMETER(iFlags);
////
////}
////
////
////int_scalar_source::int_scalar_source()
////{
////
////   m_plistener = nullptr;
////
////}
////
////
////bool int_scalar_source::set_scalar(enum_scalar escalar,i64 iValue,bool bForce,int iFlags)
////{
////
////   if (!bForce)
////   {
////      if (!contains(escalar, iValue))
////         return false;
////   }
////
////   on_set_scalar(escalar, iValue, iFlags);
////
////   if (m_plistener != nullptr)
////   {
////      
////      m_plistener->on_set_scalar(this, escalar, iValue, iFlags);
////
////   }
////
////   return true;
////
////}
////
////bool int_scalar_source::constrain_scalar(enum_scalar escalar, i64 & iValue)
////{
////
////   bool bConstrain;
////
////   if((bConstrain = constrain(escalar, iValue)))
////   {
////
////      i64 i = 0;
////
////      get_scalar(escalar, i);
////
////      if (iValue == i)
////         return true;
////
////   }
////
////   bool bSet = set_scalar(escalar, iValue);
////
////   return bConstrain && bSet;
////
////}
////
////void int_scalar_source::increment_scalar(enum_scalar escalar, i64 iIncrement)
////{
////
////   i64 i = 0;
////
////   get_scalar(escalar, i);
////   
////   set_scalar(escalar, i + iIncrement);
////
////}
////
////bool int_scalar_source::contains(enum_scalar escalar, i64 iValue)
////{
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   if (iValue < iMin)
////      return false;
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   if (iValue > iMax)
////      return false;
////
////   return true;
////
////}
////
////bool int_scalar_source::constrain(enum_scalar escalar, i64 & iValue)
////{
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   if (iValue < iMin)
////   {
////
////      iValue = iMin;
////
////      return true;
////
////   }
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   if (iValue > iMax)
////   {
////
////      iValue = iMax;
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
////void int_scalar_source::on_set_scalar(enum_scalar escalar,i64 iValue,int iFlags)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   __UNREFERENCED_PARAMETER(iValue);
////
////   __UNREFERENCED_PARAMETER(iFlags);
////
////   // does nothing by default.
////
////}
////
////void int_scalar_source::get_scalar_minimum(enum_scalar escalar, i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////
////   i = 0; // by default
////
////}
////
////void int_scalar_source::get_scalar(enum_scalar escalar, i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   i = 1; // by default
////
////}
////
////void int_scalar_source::get_scalar_maximum(enum_scalar escalar, i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   i = 1; // by default
////
////}
////
////double int_scalar_source::get_rate(enum_scalar escalar, double dDefault)
////{
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   i64 iDenominator = iMax - iMin;
////
////   if (iDenominator == 0)
////      return dDefault;
////
////   i64 iVal = 0;
////
////   get_scalar(escalar, iVal);
////
////   i64 iNumerator = iVal - iMin;
////
////   return (double) iNumerator / (double) iDenominator; // aproximate value along iDenominator and iNumerator evaluation
////
////}
////
////
////bool int_scalar_source::set_rate(enum_scalar escalar,double dValue,int iFlags)
////{
////
////   if(dValue < 0.0)
////      return false;
////
////   if(dValue > 1.0)
////      return false;
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar,iMax);
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar,iMin);
////
////   i64 iDenominator = iMax - iMin;
////
////   on_set_scalar(escalar,(i64) round(dValue * iDenominator) + iMin, iFlags);
////
////   return true;
////
////}
//
//double scalar::get_rate(double dDefault)
//{
//
//   return dDefault;
//
//}
//
//bool scalar::set_rate(double dValue, int iFlags)
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
//string scalar::Format(const ::string & strFormat)
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
////scalar::scalar(double_scalar_source * psource, enum_scalar escalar, const ::string & strFormat)
////{
////
////   m_psource = psource;
////   m_escalar = escalar;
////   m_strFormat = strFormat;
////}
////
////
////void scalar::set(double dValue)
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
////double scalar::get()
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return 0.0;
////
////   double d = 0.0;
////
////   m_psource->get_scalar(m_escalar, d);
////
////   return d;
////
////}
////
////
////double scalar::get_rate(double dDefault)
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
////bool scalar::set_rate(double dValue,int iFlags)
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
////double scalar::minimum()
////{
////
////   if (is_null())
////      return 0.0;
////
////   double d = 0.0;
////
////   m_psource->get_scalar_minimum(m_escalar, d);
////
////   return d;
////
////}
////
////
////double scalar::maximum()
////{
////
////   if (is_null())
////      return 0.0;
////
////   double d = 0.0;
////
////   m_psource->get_scalar_maximum(m_escalar, d);
////
////   return d;
////
////}
////
////string scalar::Format(const ::string & strFormat)
////{
////
////   string str;
////
////   str.format(strFormat,get());
////
////   return str;
////
////}
////
////int_scalar::int_scalar(int_scalar_source * psource, enum_scalar escalar, const ::string & strFormat)
////{
////
////   m_psource = psource;
////   m_escalar = escalar;
////   m_strFormat = strFormat;
////
////}
////
////
////void int_scalar::set(i64 iValue)
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return;
////
////   m_psource->set_scalar(m_escalar, iValue);
////
////}
////
////
////i64 int_scalar::get()
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return 0;
////
////   i64 i = 0;
////
////   m_psource->get_scalar(m_escalar, i);
////
////   return i;
////
////}
////
////
////double int_scalar::get_rate(double dDefault)
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
////bool int_scalar::set_rate(double dValue,int iFlags)
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
////i64 int_scalar::minimum()
////{
////   
////   if (is_null())
////      return 0;
////
////   i64 i = 0;
////
////   m_psource->get_scalar_minimum(m_escalar, i);
////
////   return i;
////
////}
////
////
////i64 int_scalar::maximum()
////{
////
////   if (is_null())
////      return 0;
////
////   i64 i = 0;
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
////string int_scalar::Format(const ::string & strFormat)
////{
////
////   string str;
////
////   str.format(strFormat,get());
////
////   return str;
////
////}























scalar_source::scalar_source()
{

}





double scalar::get_rate(double dRate)
{


   return dRate;

}


bool scalar::set_rate(double dRate, int iFlags)
{


   return false;

}


//string scalar::Format(const ::string & strFormat)
//{
//
//   __UNREFERENCED_PARAMETER(strFormat);
//
//   return "";
//
//
//}






// From template to class by camilo on 2022-11-17 04:35 ILoveYouThomasBorregaardSorensen!!
#include "framework.h"
#include "scalar.h"
#include "acme/exception/exception.h"
//
////void double_scalar_source::listener::on_set_scalar(double_scalar_source * psource,enum_scalar escalar,double dValue,int iFlags)
////{
////
////   __UNREFERENCED_PARAMETER(psource);
////   __UNREFERENCED_PARAMETER(escalar);
////   __UNREFERENCED_PARAMETER(dValue);
////
////}
////
////double_scalar_source::double_scalar_source()
////{
////
////   m_plistener = nullptr;
////
////}
////
////
////bool double_scalar_source::set_scalar(enum_scalar escalar,double d,bool bForce,int iFlags)
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
////bool double_scalar_source::constrain_scalar(enum_scalar escalar, double & dValue)
////{
////
////   bool bConstrain;
////
////   if ((bConstrain = constrain(escalar, dValue)))
////   {
////
////      double d = 0.0;
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
////double double_scalar_source::get_rate(enum_scalar escalar, double dDefault)
////{
////
////   double dMax = 0.0;
////
////   get_scalar_maximum(escalar, dMax);
////
////   double dMin = 0.0;
////
////   get_scalar_minimum(escalar, dMin);
////
////   double dDenominator = dMax - dMin;
////
////   if (dDenominator == 0)
////      return dDefault;
////
////   double dVal = 0.0;
////
////   get_scalar(escalar, dVal);
////
////   double dNumerator = dVal - dMin;
////
////   return dNumerator / dDenominator; // aproximate value along iDenominator and iNumerator evaluation
////
////}
////
////bool double_scalar_source::set_rate(enum_scalar escalar,double dValue,int iFlags)
////{
////
////   if(dValue < 0.0)
////      return false;
////
////   if(dValue > 1.0)
////      return false;
////
////   double dMax = 0.0;
////
////   get_scalar_maximum(escalar,dMax);
////
////   double dMin = 0.0;
////
////   get_scalar_minimum(escalar,dMin);
////
////   double dDenominator = dMax - dMin;
////
////   on_set_scalar(escalar,dValue * dDenominator + dMin, iFlags);
////
////   return true;
////
////}
////
////
////bool double_scalar_source::contains(enum_scalar escalar, double dValue)
////{
////
////   double dMin = 0.0;
////
////   get_scalar_minimum(escalar, dMin);
////
////   if (dValue < dMin)
////      return false;
////
////   double dMax = 0.0;
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
////bool double_scalar_source::constrain(enum_scalar escalar, double & dValue)
////{
////
////   double dMin = 0.0;
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
////   double dMax = 0.0;
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
bool scalar_source::on_set_scalar(enum_scalar escalar, ::number d, int iFlags)
{

   __UNREFERENCED_PARAMETER(escalar);

   __UNREFERENCED_PARAMETER(d);

   __UNREFERENCED_PARAMETER(iFlags);

   // does nothing.

   return false;

}
////
////void double_scalar_source::get_scalar_minimum(enum_scalar escalar, double & d)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   d = 1.0; // by default
////
////}
////
////void double_scalar_source::get_scalar(enum_scalar escalar, double & d)
////{
////
////   __UNREFERENCED_PARAMETER(escalar);
////
////   d = 1.0; // by default
////
////}
////
////void double_scalar_source::get_scalar_maximum(enum_scalar escalar, double & d)
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
////void int_scalar_source::listener::on_set_scalar(int_scalar_source * psource,enum_scalar escalar,i64 number,int iFlags)
////{
////
////   __UNREFERENCED_PARAMETER(psource);
////   __UNREFERENCED_PARAMETER(escalar);
////   __UNREFERENCED_PARAMETER(number);
////   __UNREFERENCED_PARAMETER(iFlags);
////
////}
////
////
////int_scalar_source::int_scalar_source()
////{
////
////   m_plistener = nullptr;
////
////}
////
////
////bool int_scalar_source::set_scalar(enum_scalar escalar,i64 number,bool bForce,int iFlags)
////{
////
////   if (!bForce)
////   {
////      if (!contains(escalar, number))
////         return false;
////   }
////
////   on_set_scalar(escalar, number, iFlags);
////
////   if (m_plistener != nullptr)
////   {
////      
////      m_plistener->on_set_scalar(this, escalar, number, iFlags);
////
////   }
////
////   return true;
////
////}
////
////bool int_scalar_source::constrain_scalar(enum_scalar escalar, i64 & number)
////{
////
////   bool bConstrain;
////
////   if((bConstrain = constrain(escalar, number)))
////   {
////
////      i64 i = 0;
////
////      get_scalar(escalar, i);
////
////      if (number == i)
////         return true;
////
////   }
////
////   bool bSet = set_scalar(escalar, number);
////
////   return bConstrain && bSet;
////
////}
////
////void int_scalar_source::increment_scalar(enum_scalar escalar, i64 iIncrement)
////{
////
////   i64 i = 0;
////
////   get_scalar(escalar, i);
////   
////   set_scalar(escalar, i + iIncrement);
////
////}
////
////bool int_scalar_source::contains(enum_scalar escalar, i64 number)
////{
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   if (number < iMin)
////      return false;
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   if (number > iMax)
////      return false;
////
////   return true;
////
////}
////
////bool int_scalar_source::constrain(enum_scalar escalar, i64 & number)
////{
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   if (number < iMin)
////   {
////
////      number = iMin;
////
////      return true;
////
////   }
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   if (number > iMax)
////   {
////
////      number = iMax;
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
////void int_scalar_source::on_set_scalar(enum_scalar escalar,i64 number,int iFlags)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   __UNREFERENCED_PARAMETER(number);
////
////   __UNREFERENCED_PARAMETER(iFlags);
////
////   // does nothing by default.
////
////}
////
////void int_scalar_source::get_scalar_minimum(enum_scalar escalar, i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////
////   i = 0; // by default
////
////}
////
////void int_scalar_source::get_scalar(enum_scalar escalar, i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   i = 1; // by default
////
////}
////
////void int_scalar_source::get_scalar_maximum(enum_scalar escalar, i64 & i)
////{
////   
////   __UNREFERENCED_PARAMETER(escalar);
////   
////   i = 1; // by default
////
////}
////
////double int_scalar_source::get_rate(enum_scalar escalar, double dDefault)
////{
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar, iMax);
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar, iMin);
////
////   i64 iDenominator = iMax - iMin;
////
////   if (iDenominator == 0)
////      return dDefault;
////
////   i64 iVal = 0;
////
////   get_scalar(escalar, iVal);
////
////   i64 iNumerator = iVal - iMin;
////
////   return (double) iNumerator / (double) iDenominator; // aproximate value along iDenominator and iNumerator evaluation
////
////}
////
////
////bool int_scalar_source::set_rate(enum_scalar escalar,double dValue,int iFlags)
////{
////
////   if(dValue < 0.0)
////      return false;
////
////   if(dValue > 1.0)
////      return false;
////
////   i64 iMax = 0;
////
////   get_scalar_maximum(escalar,iMax);
////
////   i64 iMin = 0;
////
////   get_scalar_minimum(escalar,iMin);
////
////   i64 iDenominator = iMax - iMin;
////
////   on_set_scalar(escalar,(i64) round(dValue * iDenominator) + iMin, iFlags);
////
////   return true;
////
////}
//
//double scalar::get_rate(double dDefault)
//{
//
//   return dDefault;
//
//}
//
//bool scalar::set_rate(double dValue, int iFlags)
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
//string scalar::Format(const ::string & strFormat)
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
////scalar::scalar(double_scalar_source * psource, enum_scalar escalar, const ::string & strFormat)
////{
////
////   m_psource = psource;
////   m_escalar = escalar;
////   m_strFormat = strFormat;
////}
////
////
////void scalar::set(double dValue)
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
////double scalar::get()
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return 0.0;
////
////   double d = 0.0;
////
////   m_psource->get_scalar(m_escalar, d);
////
////   return d;
////
////}
////
////
////double scalar::get_rate(double dDefault)
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
////bool scalar::set_rate(double dValue,int iFlags)
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
////double scalar::minimum()
////{
////
////   if (is_null())
////      return 0.0;
////
////   double d = 0.0;
////
////   m_psource->get_scalar_minimum(m_escalar, d);
////
////   return d;
////
////}
////
////
////double scalar::maximum()
////{
////
////   if (is_null())
////      return 0.0;
////
////   double d = 0.0;
////
////   m_psource->get_scalar_maximum(m_escalar, d);
////
////   return d;
////
////}
////
////string scalar::Format(const ::string & strFormat)
////{
////
////   string str;
////
////   str.format(strFormat,get());
////
////   return str;
////
////}
////
////int_scalar::int_scalar(int_scalar_source * psource, enum_scalar escalar, const ::string & strFormat)
////{
////
////   m_psource = psource;
////   m_escalar = escalar;
////   m_strFormat = strFormat;
////
////}
////
////
////void int_scalar::set(i64 number)
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return;
////
////   m_psource->set_scalar(m_escalar, number);
////
////}
////
////
////i64 int_scalar::get()
////{
////
////   if (m_psource == nullptr || m_escalar == scalar_none)
////      return 0;
////
////   i64 i = 0;
////
////   m_psource->get_scalar(m_escalar, i);
////
////   return i;
////
////}
////
////
////double int_scalar::get_rate(double dDefault)
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
////bool int_scalar::set_rate(double dValue,int iFlags)
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
////i64 int_scalar::minimum()
////{
////   
////   if (is_null())
////      return 0;
////
////   i64 i = 0;
////
////   m_psource->get_scalar_minimum(m_escalar, i);
////
////   return i;
////
////}
////
////
////i64 int_scalar::maximum()
////{
////
////   if (is_null())
////      return 0;
////
////   i64 i = 0;
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
////string int_scalar::Format(const ::string & strFormat)
////{
////
////   string str;
////
////   str.format(strFormat,get());
////
////   return str;
////
////}

























bool scalar_source::listener::on_set_scalar(scalar_source* psource, enum_scalar escalar, ::number number, int iFlags)
{

   __UNREFERENCED_PARAMETER(psource);
   __UNREFERENCED_PARAMETER(escalar);
   __UNREFERENCED_PARAMETER(number);
   __UNREFERENCED_PARAMETER(iFlags);

   return false;

}



bool scalar_source::set_scalar(enum_scalar escalar, ::number number, bool bForce, int iFlags)
{

   if (!bForce)
   {

      if (!contains_scalar(escalar, number))
      {

         return false;

      }

   }

   on_set_scalar(escalar, number, iFlags);

   for (auto& plistener : m_scalarlistenera)
   {

      try
      {

         plistener->on_set_scalar(this, escalar, number, iFlags);

      }
      catch (...)
      {

      }

   }
   return true;

}


bool scalar_source::constrain_scalar(enum_scalar escalar, ::number& number)
{

   auto minimum = get_scalar_minimum(escalar);

   if (minimum.ok())
   {

      if (number < minimum)
      {

         number = minimum;

         return true;

      }

   }

   auto maximum = get_scalar_maximum(escalar);

   if (maximum.ok())
   {

      if (number > maximum)
      {

         number = maximum;

         return true;

      }

   }

   return false;

   //::number realCurrent = 0;

   //get_scalar(escalar, realCurrent);

   //if (realCurrent == number)
   //{

   //   return true;

   //}

   //return set_scalar(escalar, number);

}


void scalar_source::increment_scalar(enum_scalar escalar, ::number iIncrement)
{

   auto number = get_scalar(escalar);

   if (number.ok())
   {

      set_scalar(escalar, number + 1);

   }

}


bool scalar_source::contains_scalar(enum_scalar escalar, ::number number)
{

   auto minimum = get_scalar_minimum(escalar);

   if (number.ok())
   {

      if (number < minimum)
      {

         return false;

      }

   }

   auto maximum = get_scalar_maximum(escalar);

   if (number.ok())
   {

      if (number > maximum)
      {

         return false;

      }

   }

   return true;

}


//bool scalar_source::constrain_scalar(enum_scalar escalar, ::number& number)
//{
//
//   ::number iMin = 0;
//
//   if (get_scalar_minimum(escalar, iMin))
//   {
//
//      if (number < iMin)
//      {
//
//         number = iMin;
//
//         return true;
//
//      }
//
//   }
//
//   ::number iMax = 0;
//
//   if (get_scalar_maximum(escalar, iMax))
//   {
//
//      if (number > iMax)
//      {
//
//         number = iMax;
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
//void scalar_source::on_set_scalar(enum_scalar escalar,::number number,int iFlags)
//{
//
//   __UNREFERENCED_PARAMETER(escalar);
//
//   __UNREFERENCED_PARAMETER(number);
//
//   __UNREFERENCED_PARAMETER(iFlags);
//
//   // does nothing by default.
//
//}
//
//
//


number scalar_source::get_scalar_minimum(enum_scalar escalar)
{

   __UNREFERENCED_PARAMETER(escalar);

   //i = 0; // by default

   return false;

}



number scalar_source::get_scalar(enum_scalar escalar)
{

   __UNREFERENCED_PARAMETER(escalar);

   //i = 1; // by default

   return false;

}


number scalar_source::get_scalar_maximum(enum_scalar escalar)
{

   __UNREFERENCED_PARAMETER(escalar);

   // i = 1; // by default

   return false;

}



double scalar_source::get_scalar_rate(enum_scalar escalar, double dDefault)
{

   auto maximum = get_scalar_maximum(escalar);

   if (maximum.nok())
   {

      throw exception(error_wrong_state);

   }

   auto minimum = get_scalar_minimum(escalar);

   if(minimum.nok())
   {

      throw exception(error_wrong_state);

   }

   ::number range = maximum - minimum;

   if (range == 0)
   {

      return dDefault;

   }

   ::number current = get_scalar(escalar);

   ::number position = current - minimum;

   return position.get_f64() / range.get_f64(); // aproximate value along iDenominator and iNumerator evaluation

}



bool scalar_source::set_scalar_rate(enum_scalar escalar, double dRate, int iFlags)
{

   if (dRate < 0.0)
   {

      return false;

   }

   if (dRate > 1.0)
   {

      return false;

   }

   auto maximum = get_scalar_maximum(escalar);

   if (maximum.nok())
   {

      throw exception(error_wrong_state);

   }

   auto minimum = get_scalar_minimum(escalar);

   if (minimum.nok())
   {

      throw exception(error_wrong_state);

   }

   auto range = maximum - minimum;

   ::number numberNew;

   numberNew.m_enumber = range.m_enumber;

   numberNew.set((dRate * range.get_f64()) + minimum.get_f64());

   return on_set_scalar(escalar, numberNew, iFlags);

}


//scalar::scalar(scalar_source* psource, enum_scalar escalar, const ::string& strFormat)
scalar::scalar(scalar_source* psource, enum_scalar escalar)
{

   m_psource = psource;
   m_escalar = escalar;
   //m_strFormat = strFormat;

}


void scalar::set(::number number)
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
      return;

   m_psource->set_scalar(m_escalar, number);

}


::number scalar::get()
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
   {

      return 0;

   }

   return m_psource->get_scalar(m_escalar);

}


//double scalar::get_rate(double dDefault)
//{
//
//   if (m_psource == nullptr || m_escalar == e_scalar_none)
//   {
//
//      return dDefault;
//
//   }
//
//   return m_psource->get_scalar_rate(m_escalar, dDefault);
//
//}
//

//bool scalar::set_rate(double dValue, int iFlags)
//{
//
//   if (m_psource == nullptr || m_escalar == e_scalar_none)
//   {
//
//      return false;
//
//   }
//
//   return m_psource->set_scalar_rate(m_escalar, dValue, iFlags);
//
//}


::number scalar::minimum()
{

   if (is_null())
   {

      return 0;

   }

   return m_psource->get_scalar_minimum(m_escalar);

}



::number scalar::maximum()
{

   if (is_null())
   {

      return 0;

   }

   return m_psource->get_scalar_maximum(m_escalar);

}


//string scalar::printf(const ::string& strFormat)
//{
//
//   ::string str;
//
//   str.format(strFormat, get());
//
//   return str;
//
//}
//



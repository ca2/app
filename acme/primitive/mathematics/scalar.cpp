#include "framework.h"


//void double_scalar_source::listener::on_set_scalar(double_scalar_source * psource,e_scalar escalar,double dValue,int iFlags)
//{
//
//   UNREFERENCED_PARAMETER(psource);
//   UNREFERENCED_PARAMETER(escalar);
//   UNREFERENCED_PARAMETER(dValue);
//
//}
//
//double_scalar_source::double_scalar_source()
//{
//
//   m_plistener = nullptr;
//
//}
//
//
//bool double_scalar_source::set_scalar(e_scalar escalar,double d,bool bForce,int iFlags)
//{
//
//   if (!bForce)
//   {
//
//      if (!contains(escalar, d))
//         return false;
//
//   }
//
//   on_set_scalar(escalar, d, iFlags);
//
//   if (m_plistener != nullptr)
//   {
//
//      m_plistener->on_set_scalar(this, escalar, d, iFlags);
//
//   }
//
//   return true;
//
//}
//
//bool double_scalar_source::constrain_scalar(e_scalar escalar, double & dValue)
//{
//
//   bool bConstrain;
//
//   if ((bConstrain = constrain(escalar, dValue)))
//   {
//
//      double d = 0.0;
//
//      get_scalar(escalar, d);
//
//      if (dValue == d)
//         return true;
//
//   }
//
//   bool bSet = set_scalar(escalar, dValue);
//
//   return bConstrain && bSet;
//
//}
//
//
//double double_scalar_source::get_rate(e_scalar escalar, double dDefault)
//{
//
//   double dMax = 0.0;
//
//   get_scalar_maximum(escalar, dMax);
//
//   double dMin = 0.0;
//
//   get_scalar_minimum(escalar, dMin);
//
//   double dDenominator = dMax - dMin;
//
//   if (dDenominator == 0)
//      return dDefault;
//
//   double dVal = 0.0;
//
//   get_scalar(escalar, dVal);
//
//   double dNumerator = dVal - dMin;
//
//   return dNumerator / dDenominator; // aproximate value along iDenominator and iNumerator evaluation
//
//}
//
//bool double_scalar_source::set_rate(e_scalar escalar,double dValue,int iFlags)
//{
//
//   if(dValue < 0.0)
//      return false;
//
//   if(dValue > 1.0)
//      return false;
//
//   double dMax = 0.0;
//
//   get_scalar_maximum(escalar,dMax);
//
//   double dMin = 0.0;
//
//   get_scalar_minimum(escalar,dMin);
//
//   double dDenominator = dMax - dMin;
//
//   on_set_scalar(escalar,dValue * dDenominator + dMin, iFlags);
//
//   return true;
//
//}
//
//
//bool double_scalar_source::contains(e_scalar escalar, double dValue)
//{
//
//   double dMin = 0.0;
//
//   get_scalar_minimum(escalar, dMin);
//
//   if (dValue < dMin)
//      return false;
//
//   double dMax = 0.0;
//
//   get_scalar_maximum(escalar, dMax);
//
//   if (dValue > dMax)
//      return false;
//
//   return true;
//
//}
//
//bool double_scalar_source::constrain(e_scalar escalar, double & dValue)
//{
//
//   double dMin = 0.0;
//   
//   get_scalar_minimum(escalar, dMin);
//
//   if (dValue < dMin)
//   {
//
//      dValue = dMin;
//
//      return true;
//
//   }
//
//   double dMax = 0.0;
//
//   get_scalar_maximum(escalar, dMax);
//
//   if (dValue > dMax)
//   {
//
//      dValue = dMax;
//
//      return true;
//
//   }
//
//   return false;
//
//}
//
//
//
//void double_scalar_source::on_set_scalar(e_scalar escalar,double d,int iFlags)
//{
//
//   UNREFERENCED_PARAMETER(escalar);
//
//   UNREFERENCED_PARAMETER(d);
//
//   UNREFERENCED_PARAMETER(iFlags);
//
//   // does nothing.
//
//}
//
//void double_scalar_source::get_scalar_minimum(e_scalar escalar, double & d)
//{
//
//   UNREFERENCED_PARAMETER(escalar);
//
//   d = 1.0; // by default
//
//}
//
//void double_scalar_source::get_scalar(e_scalar escalar, double & d)
//{
//
//   UNREFERENCED_PARAMETER(escalar);
//
//   d = 1.0; // by default
//
//}
//
//void double_scalar_source::get_scalar_maximum(e_scalar escalar, double & d)
//{
//
//   UNREFERENCED_PARAMETER(escalar);
//
//   d = 1.0; // by default
//
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//void int_scalar_source::listener::on_set_scalar(int_scalar_source * psource,e_scalar escalar,i64 iValue,int iFlags)
//{
//
//   UNREFERENCED_PARAMETER(psource);
//   UNREFERENCED_PARAMETER(escalar);
//   UNREFERENCED_PARAMETER(iValue);
//   UNREFERENCED_PARAMETER(iFlags);
//
//}
//
//
//int_scalar_source::int_scalar_source()
//{
//
//   m_plistener = nullptr;
//
//}
//
//
//bool int_scalar_source::set_scalar(e_scalar escalar,i64 iValue,bool bForce,int iFlags)
//{
//
//   if (!bForce)
//   {
//      if (!contains(escalar, iValue))
//         return false;
//   }
//
//   on_set_scalar(escalar, iValue, iFlags);
//
//   if (m_plistener != nullptr)
//   {
//      
//      m_plistener->on_set_scalar(this, escalar, iValue, iFlags);
//
//   }
//
//   return true;
//
//}
//
//bool int_scalar_source::constrain_scalar(e_scalar escalar, i64 & iValue)
//{
//
//   bool bConstrain;
//
//   if((bConstrain = constrain(escalar, iValue)))
//   {
//
//      i64 i = 0;
//
//      get_scalar(escalar, i);
//
//      if (iValue == i)
//         return true;
//
//   }
//
//   bool bSet = set_scalar(escalar, iValue);
//
//   return bConstrain && bSet;
//
//}
//
//void int_scalar_source::increment_scalar(e_scalar escalar, i64 iIncrement)
//{
//
//   i64 i = 0;
//
//   get_scalar(escalar, i);
//   
//   set_scalar(escalar, i + iIncrement);
//
//}
//
//bool int_scalar_source::contains(e_scalar escalar, i64 iValue)
//{
//
//   i64 iMin = 0;
//
//   get_scalar_minimum(escalar, iMin);
//
//   if (iValue < iMin)
//      return false;
//
//   i64 iMax = 0;
//
//   get_scalar_maximum(escalar, iMax);
//
//   if (iValue > iMax)
//      return false;
//
//   return true;
//
//}
//
//bool int_scalar_source::constrain(e_scalar escalar, i64 & iValue)
//{
//
//   i64 iMin = 0;
//
//   get_scalar_minimum(escalar, iMin);
//
//   if (iValue < iMin)
//   {
//
//      iValue = iMin;
//
//      return true;
//
//   }
//
//   i64 iMax = 0;
//
//   get_scalar_maximum(escalar, iMax);
//
//   if (iValue > iMax)
//   {
//
//      iValue = iMax;
//
//      return true;
//
//   }
//
//   return false;
//
//}
//
//
//
//void int_scalar_source::on_set_scalar(e_scalar escalar,i64 iValue,int iFlags)
//{
//   
//   UNREFERENCED_PARAMETER(escalar);
//   
//   UNREFERENCED_PARAMETER(iValue);
//
//   UNREFERENCED_PARAMETER(iFlags);
//
//   // does nothing by default.
//
//}
//
//void int_scalar_source::get_scalar_minimum(e_scalar escalar, i64 & i)
//{
//   
//   UNREFERENCED_PARAMETER(escalar);
//
//   i = 0; // by default
//
//}
//
//void int_scalar_source::get_scalar(e_scalar escalar, i64 & i)
//{
//   
//   UNREFERENCED_PARAMETER(escalar);
//   
//   i = 1; // by default
//
//}
//
//void int_scalar_source::get_scalar_maximum(e_scalar escalar, i64 & i)
//{
//   
//   UNREFERENCED_PARAMETER(escalar);
//   
//   i = 1; // by default
//
//}
//
//double int_scalar_source::get_rate(e_scalar escalar, double dDefault)
//{
//
//   i64 iMax = 0;
//
//   get_scalar_maximum(escalar, iMax);
//
//   i64 iMin = 0;
//
//   get_scalar_minimum(escalar, iMin);
//
//   i64 iDenominator = iMax - iMin;
//
//   if (iDenominator == 0)
//      return dDefault;
//
//   i64 iVal = 0;
//
//   get_scalar(escalar, iVal);
//
//   i64 iNumerator = iVal - iMin;
//
//   return (double) iNumerator / (double) iDenominator; // aproximate value along iDenominator and iNumerator evaluation
//
//}
//
//
//bool int_scalar_source::set_rate(e_scalar escalar,double dValue,int iFlags)
//{
//
//   if(dValue < 0.0)
//      return false;
//
//   if(dValue > 1.0)
//      return false;
//
//   i64 iMax = 0;
//
//   get_scalar_maximum(escalar,iMax);
//
//   i64 iMin = 0;
//
//   get_scalar_minimum(escalar,iMin);
//
//   i64 iDenominator = iMax - iMin;
//
//   on_set_scalar(escalar,(i64) round(dValue * iDenominator) + iMin, iFlags);
//
//   return true;
//
//}

double scalar_base::get_rate(double dDefault)
{

   return dDefault;

}

bool scalar_base::set_rate(double dValue, int iFlags)
{

   UNREFERENCED_PARAMETER(dValue);

   UNREFERENCED_PARAMETER(iFlags);

   return false;

}


string scalar_base::Format(const ::string & strFormat)
{

   UNREFERENCED_PARAMETER(strFormat);

   return "";


}

//
//
//
//double_scalar::double_scalar(double_scalar_source * psource, e_scalar escalar, const ::string & strFormat)
//{
//
//   m_psource = psource;
//   m_escalar = escalar;
//   m_strFormat = strFormat;
//}
//
//
//void double_scalar::set(double dValue)
//{
//
//   if (m_psource == nullptr || m_escalar == scalar_none)
//      return;
//
//   m_psource->set_scalar(m_escalar, dValue);
//
//}
//
//
//double double_scalar::get()
//{
//
//   if (m_psource == nullptr || m_escalar == scalar_none)
//      return 0.0;
//
//   double d = 0.0;
//
//   m_psource->get_scalar(m_escalar, d);
//
//   return d;
//
//}
//
//
//double double_scalar::get_rate(double dDefault)
//{
//
//   if (m_psource == nullptr || m_escalar == scalar_none)
//      return dDefault;
//
//   return m_psource->get_rate(m_escalar, dDefault);
//
//}
//
//
//bool double_scalar::set_rate(double dValue,int iFlags)
//{
//
//   if(m_psource == nullptr || m_escalar == scalar_none)
//      return false;
//
//   return m_psource->set_rate(m_escalar,dValue, iFlags);
//
//}
//
//
//double double_scalar::minimum()
//{
//
//   if (is_null())
//      return 0.0;
//
//   double d = 0.0;
//
//   m_psource->get_scalar_minimum(m_escalar, d);
//
//   return d;
//
//}
//
//
//double double_scalar::maximum()
//{
//
//   if (is_null())
//      return 0.0;
//
//   double d = 0.0;
//
//   m_psource->get_scalar_maximum(m_escalar, d);
//
//   return d;
//
//}
//
//string double_scalar::Format(const ::string & strFormat)
//{
//
//   string str;
//
//   str.Format(strFormat,get());
//
//   return str;
//
//}
//
//int_scalar::int_scalar(int_scalar_source * psource, e_scalar escalar, const ::string & strFormat)
//{
//
//   m_psource = psource;
//   m_escalar = escalar;
//   m_strFormat = strFormat;
//
//}
//
//
//void int_scalar::set(i64 iValue)
//{
//
//   if (m_psource == nullptr || m_escalar == scalar_none)
//      return;
//
//   m_psource->set_scalar(m_escalar, iValue);
//
//}
//
//
//i64 int_scalar::get()
//{
//
//   if (m_psource == nullptr || m_escalar == scalar_none)
//      return 0;
//
//   i64 i = 0;
//
//   m_psource->get_scalar(m_escalar, i);
//
//   return i;
//
//}
//
//
//double int_scalar::get_rate(double dDefault)
//{
//   
//   if (m_psource == nullptr || m_escalar == scalar_none)
//      return dDefault;
//
//   return m_psource->get_rate(m_escalar, dDefault);
//
//}
//
//
//bool int_scalar::set_rate(double dValue,int iFlags)
//{
//
//   if(m_psource == nullptr || m_escalar == scalar_none)
//      return false;
//
//   return m_psource->set_rate(m_escalar,dValue, iFlags);
//
//}
//
//
//i64 int_scalar::minimum()
//{
//   
//   if (is_null())
//      return 0;
//
//   i64 i = 0;
//
//   m_psource->get_scalar_minimum(m_escalar, i);
//
//   return i;
//
//}
//
//
//i64 int_scalar::maximum()
//{
//
//   if (is_null())
//      return 0;
//
//   i64 i = 0;
//
//   m_psource->get_scalar_maximum(m_escalar, i);
//
//   return i;
//
//}
//
//
//
//
//
//string int_scalar::Format(const ::string & strFormat)
//{
//
//   string str;
//
//   str.Format(strFormat,get());
//
//   return str;
//
//}

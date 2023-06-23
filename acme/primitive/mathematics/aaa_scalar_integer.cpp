// From template to class by camilo on 2022-11-17 04:48 ILoveYouThomasBorregaardSorensen!!
#include "framework.h"
#include "scalar.h"
////#include "acme/exception/exception.h"


bool scalar_source::get_integer_scalar_minimum(enum_scalar escalar, ::integer& i)
{

   UNREFERENCED_PARAMETER(escalar);

   //i = 0; // by default

   return false;

}


bool scalar_source::get_integer_scalar(enum_scalar escalar,::integer & i)
{

   UNREFERENCED_PARAMETER(escalar);

   //i = 1; // by default

   return false;

}


bool scalar_source::get_integer_scalar_maximum(enum_scalar escalar, ::integer& i)
{

   UNREFERENCED_PARAMETER(escalar);

   // i = 1; // by default

   return false;

}


bool scalar_source::listener::on_set_integer_scalar(scalar_source* psource, enum_scalar escalar, ::integer iValue, int iFlags)
{

   UNREFERENCED_PARAMETER(psource);
   UNREFERENCED_PARAMETER(escalar);
   UNREFERENCED_PARAMETER(iValue);
   UNREFERENCED_PARAMETER(iFlags);

   return false;

}


bool scalar_source::set_integer_scalar(enum_scalar escalar, ::integer iValue, bool bForce, int iFlags)
{

   if (!bForce)
   {

      if (!contains_integer_scalar(escalar, iValue))
      {

         return false;

      }

   }

   on_set_integer_scalar(escalar, iValue, iFlags);

   for(auto & plistener : m_scalarlistenera)
   {

      try
      {

         plistener->on_set_integer_scalar(this, escalar, iValue, iFlags);

      }
      catch (...)
      {

      }

   }

   return true;

}


bool scalar_source::constrain_integer_scalar(enum_scalar escalar, ::integer& integer)
{

   ::integer integerMinimum = 0;

   if (get_integer_scalar_minimum(escalar, integerMinimum))
   {

      if (integer < integerMinimum)
      {

         integer = integerMinimum;

         return true;

      }

   }

   ::integer integerMaximum = 0;

   if (get_integer_scalar_maximum(escalar, integerMaximum))
   {

      if (integer > integerMaximum)
      {

         integer = integerMaximum;

         return true;

      }

   }

   return false;

   //::integer integerCurrent = 0;

   //get_integer_scalar(escalar, integerCurrent);

   //if (integerCurrent == integer)
   //{

   //   return true;

   //}

   //return set_integer_scalar(escalar, integer);

}


void scalar_source::increment_integer_scalar(enum_scalar escalar, ::integer iIncrement)
{

   ::integer i = 0;

   if (get_integer_scalar(escalar, i))
   {

      set_integer_scalar(escalar, i + iIncrement);

   }

}



bool scalar_source::contains_integer_scalar(enum_scalar escalar, ::integer iValue)
{

   ::integer iMin = 0;

   if (get_integer_scalar_minimum(escalar, iMin))
   {

      if (iValue < iMin)
      {

         return false;

      }

   }

   ::integer iMax = 0;

   if (get_integer_scalar_maximum(escalar, iMax))
   {

      if (iValue > iMax)
      {
         return false;

      }

   }

   return true;

}



//bool scalar_source::constrain_integer_scalar(enum_scalar escalar, ::integer& iValue)
//{
//
//   ::integer iMin = 0;
//
//   if (get_integer_scalar_minimum(escalar, iMin))
//   {
//
//      if (iValue < iMin)
//      {
//
//         iValue = iMin;
//
//         return true;
//
//      }
//
//   }
//
//   ::integer iMax = 0;
//
//   if (get_integer_scalar_maximum(escalar, iMax))
//   {
//
//      if (iValue > iMax)
//      {
//
//         iValue = iMax;
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
bool scalar_source::on_set_integer_scalar(enum_scalar escalar,::integer iValue,int iFlags)
{

   UNREFERENCED_PARAMETER(escalar);

   UNREFERENCED_PARAMETER(iValue);

   UNREFERENCED_PARAMETER(iFlags);

   // does nothing by default.

   return false;

}
//
//
//
//void scalar_source::get_scalar_minimum(enum_scalar escalar,::integer & i)
//{
//
//   UNREFERENCED_PARAMETER(escalar);
//
//   i = 0; // by default
//
//}
//
//void scalar_source < ::integer > ::get_scalar(enum_scalar escalar,::integer & i)
//{
//
//   UNREFERENCED_PARAMETER(escalar);
//
//   i = 1; // by default
//
//}
//
//void scalar_source < ::integer > ::get_scalar_maximum(enum_scalar escalar,::integer & i)
//{
//
//   UNREFERENCED_PARAMETER(escalar);
//
//   i = 1; // by default
//
//}



double scalar_source::get_integer_scalar_rate(enum_scalar escalar, double dDefault)
{

   ::integer iMax = 0;

   get_integer_scalar_maximum(escalar, iMax);

   ::integer iMin = 0;

   get_integer_scalar_minimum(escalar, iMin);

   ::integer iDenominator = iMax - iMin;

   if (iDenominator == 0)
      return dDefault;

   ::integer iVal = 0;

   get_integer_scalar(escalar, iVal);

   ::integer iNumerator = iVal - iMin;

   return (double)iNumerator / (double)iDenominator; // aproximate value along iDenominator and iNumerator evaluation

}



bool scalar_source::set_integer_scalar_rate(enum_scalar escalar, double dValue, int iFlags)
{

   if (dValue < 0.0)
      return false;

   if (dValue > 1.0)
      return false;

   ::integer iMax = 0;

   if (!get_integer_scalar_maximum(escalar, iMax))
   {

      throw exception(error_wrong_state);

   }

   ::integer iMin = 0;

   if (!get_integer_scalar_minimum(escalar, iMin))
   {

      throw exception(error_wrong_state);

   }

   ::integer iDenominator = iMax - iMin;

   on_set_integer_scalar(escalar, (::integer)(dValue * iDenominator) + iMin, iFlags);

   return true;

}




integer_scalar::integer_scalar(scalar_source* psource, enum_scalar escalar, const ::string& strFormat)
{

   m_psource = psource;
   m_escalar = escalar;
   m_strFormat = strFormat;

}


void integer_scalar::set(::integer iValue)
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
      return;

   m_psource->set_integer_scalar(m_escalar, iValue);

}


::integer integer_scalar::get()
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
   {

      return 0;

   }

   ::integer i = 0;

   if (m_psource->get_integer_scalar(m_escalar, i))
   {

      throw exception(error_wrong_state);

   }

   return i;

}


double integer_scalar::get_rate(double dDefault)
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
   {

      return dDefault;

   }

   return m_psource->get_integer_scalar_rate(m_escalar, dDefault);

}


bool integer_scalar::set_rate(double dValue, int iFlags)
{

   if (m_psource == nullptr || m_escalar == e_scalar_none)
      return false;

   return m_psource->set_integer_scalar_rate(m_escalar, dValue, iFlags);

}


::integer integer_scalar::minimum()
{

   if (is_null())
   {

      return 0;

   }

   ::integer i = 0;

   if (!m_psource->get_integer_scalar_minimum(m_escalar, i))
   {

      throw ::exception(error_wrong_state);

   }

   return i;

}



::integer integer_scalar::maximum()
{

   if (is_null())
   {

      return 0;

   }

   ::integer i = 0;

   if (!m_psource->get_integer_scalar_maximum(m_escalar, i))
   {

      throw ::exception(error_wrong_state);

   }

   return i;

}


string integer_scalar::printf(const ::string& strFormat)
{

   ::string str;

   str.format(strFormat, get());

   return str;

}




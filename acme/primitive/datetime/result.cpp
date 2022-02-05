#include "framework.h"


namespace datetime
{


   result::result(const ::datetime::time & time)
   {

      operator =(time);

   }


   result::result()
   {

      m_iYear     = 0;
      m_iMonth    = 0;
      m_iDay      = 0;
      m_iHour     = 0;
      m_iMinute   = 0;
      m_iSecond   = 0;
      m_bSpan     = false;

   }


   result::~result()
   {

   }


   double result::get_years() const
   {

      return m_iYear + m_iMonth / 12.0 +  (m_iDay + (m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0) / 24.0)) / 365.2425;

   }


   double result::get_months() const
   {

      return m_iYear / 12.0 + m_iMonth +  12.0 * (m_iDay + (m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0) / 24.0)) / 365.2425;

   }


   double result::get_days() const
   {

      return (m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) + (m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0) / 24.0);

   }


   double result::get_hours() const
   {

      return (m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) * 24.0 + m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0);

   }


   double result::get_minutes() const
   {
      return (((m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) * 24  + m_iHour) * 60.0) + m_iMinute + (m_iSecond / 60.0);
   }


   double result::get_seconds() const
   {

      return (((m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) * 24.0  + m_iHour) * 60.0 + m_iMinute) * 60.0 + m_iSecond;

   }


   ::datetime::time result::get_time() const
   {

      ASSERT(!m_bSpan);

      try
      {

         return ::datetime::time(m_iYear, m_iMonth, m_iDay, m_iHour, m_iMinute, m_iSecond);

      }
      catch(...)
      {

         return -1;

      }

   }


   ::datetime::time_span result::GetSpan() const
   {

      ASSERT(m_bSpan);

      return ::datetime::time_span((::i32) (m_iDay + m_iMonth * (365.0 * 4.0 + 1.0) /(12.0 *4.0) + m_iYear *(365.0 * 4.0 + 1.0) /(4.0)), m_iHour, m_iMinute, m_iSecond);

   }


   result & result::operator = (const ::datetime::time & time)
   {

      m_bSpan     = false;
      m_iYear     = time.year();
      m_iMonth    = time.month();
      m_iDay      = time.day();
      m_iHour     = time.hour();
      m_iMinute   = time.minute();
      m_iSecond   = time.second();

      return *this;

   }


} // namespace datetime


datetime::result operator + (const datetime::result & val1, const datetime::result & val2)
{
   datetime::result val;
   if(val1.m_bSpan && val2.m_bSpan)
   {
      val.m_bSpan = true;
      i32 iTotalSecond = val1.m_iSecond + val2.m_iSecond;
      i32 iTotalMinute = iTotalSecond / 60 + val1.m_iMinute + val2.m_iMinute;
      i32 iTotalHour = iTotalMinute / 60 + val1.m_iHour + val2.m_iHour;
      i32 iTotalDay = iTotalHour / 24 + val1.m_iDay + val2.m_iDay;
      val.m_iSecond = iTotalSecond % 60;
      val.m_iMinute = iTotalMinute % 60;
      val.m_iHour   = iTotalHour % 24;
      val.m_iDay    = iTotalDay;
      val.m_iMonth  = val1.m_iMonth + val2.m_iMonth;
      val.m_iYear   = val1.m_iYear + val2.m_iYear;
   }
   else if((val1.m_bSpan && !val2.m_bSpan) || (val2.m_bSpan && !val1.m_bSpan))
   {
      const datetime::result * pdate = nullptr;
      const datetime::result * pspan = nullptr;
      if(val1.m_bSpan)
      {
         pdate = &val2;
         pspan = &val1;
      }
      else
      {
         pdate = &val1;
         pspan = &val2;
      }
      val = ::datetime::time(pdate->get_time() + pspan->GetSpan());
   }
   else
   {

      __throw(error_bad_argument, "cannot add two dates");

   }

   return val;

}


datetime::result operator - (const datetime::result & val1, const datetime::result & val2)
{
   datetime::result val;
   if(val1.m_bSpan && val2.m_bSpan)
   {
      val.m_bSpan = true;
      i32 iTotalSecond = val1.m_iSecond - val2.m_iSecond;
      i32 iTotalMinute = iTotalSecond / 60 + val1.m_iMinute - val2.m_iMinute;
      i32 iTotalHour = iTotalMinute / 60 + val1.m_iHour - val2.m_iHour;
      i32 iTotalDay = iTotalHour / 24 + val1.m_iDay - val2.m_iDay;
      val.m_iSecond = iTotalSecond % 60;
      val.m_iMinute = iTotalMinute % 60;
      val.m_iHour   = iTotalHour % 24;
      val.m_iDay    = iTotalDay;
   }
   else if(val1.m_bSpan && !val2.m_bSpan)
   {
      __throw(error_bad_argument, "cannot subtract a date from a span");
   }
   else if(val2.m_bSpan && !val1.m_bSpan)
   {
      const datetime::result * pdate = &val1;
      const datetime::result * pspan = &val2;
      val = ::datetime::time(pdate->get_time() - pspan->GetSpan());
   }
   else
   {
      val.m_bSpan = true;
      i32 iTotalSecond = val1.m_iSecond - val2.m_iSecond;
      i32 iTotalMinute = iTotalSecond / 60 + val1.m_iMinute - val2.m_iMinute;
      i32 iTotalHour = iTotalMinute / 60 + val1.m_iHour - val2.m_iHour;
      i32 iTotalDay = iTotalHour / 24 + val1.m_iDay - val2.m_iDay;
      i32 iTotalMonth = iTotalDay / 31 + val1.m_iMonth - val2.m_iMonth;
      i32 iTotalYear = iTotalMonth / 12 + val1.m_iYear - val2.m_iYear;
      val.m_iSecond = iTotalSecond % 60;
      val.m_iMinute = iTotalMinute % 60;
      val.m_iHour   = iTotalHour % 24;
      val.m_iDay    = iTotalDay % 31;
      val.m_iMonth  = iTotalMonth % 12;
      val.m_iYear   = iTotalYear;
   }
   return val;
}

datetime::result operator * (const datetime::result & val1, double d)
{
   datetime::result val;
   if(val1.m_bSpan)
   {
      val.m_bSpan = true;
      double dTotalSecond
         = (val1.m_iSecond + (val1.m_iMinute + (val1.m_iHour + (val1.m_iDay * 24.0)) * 60.0) * 60.0) * d;
      double dTotalMinute = dTotalSecond / 60.0;
      double dTotalHour = dTotalMinute / 60.0;
      double dTotalDay = dTotalHour / 24.0;
      val.m_iSecond = (i32) fmod(dTotalSecond, 60.0);
      val.m_iMinute = (i32) fmod(dTotalMinute, 60.0);
      val.m_iHour   = (i32) fmod(dTotalHour, 24.0);
      val.m_iDay    = (i32) dTotalDay;
   }
   else
   {
      __throw(error_bad_argument, "cannot multiply a date");
   }
   return val;
}


datetime::result operator / (const datetime::result & val1, double d)
{
   
   datetime::result val;

   if(val1.m_bSpan)
   {

      val.m_bSpan = true;
      double dTotalSecond
         = (val1.m_iSecond
         + (val1.m_iMinute
         + (val1.m_iHour
         + (val1.m_iDay * 24.0)) * 60.0) * 60.0) / d;
      double dTotalMinute = dTotalSecond / 60.0;
      double dTotalHour = dTotalMinute / 60.0;
      double dTotalDay = dTotalHour / 24.0;
      val.m_iSecond = (i32) fmod(dTotalSecond, 60.0);
      val.m_iMinute = (i32) fmod(dTotalMinute, 60.0);
      val.m_iHour   = (i32) fmod(dTotalHour, 24.0);
      val.m_iDay    = (i32) dTotalDay;

   }
   else
   {
      
      __throw(error_bad_argument, "cannot multiply a date");

   }

   return val;

}



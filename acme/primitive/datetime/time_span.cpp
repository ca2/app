#include "framework.h"


namespace datetime
{


   const char * const szInvalidDateTimeSpan = "Invalid DateTimeSpan";


   //date_span::date_span()
   //{
   //   m_iMonth = 0;
   //   m_iYear = 0;
   //   m_bConstraintMonth = 0;

   //}
   /////////////////////////////////////////////////////////////////////////////
   // time_span
   /////////////////////////////////////////////////////////////////////////////

   string time_span::Format(const char * pFormat) const
   // formatting timespans is a little trickier than formatting CTimes
   //  * we are only interested in relative time formats, ie. it is illegal
   //      to format anything dealing with absolute time (i.e. years, months,
   //         day of week, day of year, timezones, ...)
   //  * the only valid formats:
   //      %D - # of days
   //      %H - hour in 24 hour format
   //      %M - minute (0-59)
   //      %S - seconds (0-59)
   //      %% - percent sign
   //   %#<any_of_mods> - skip leading zeros
   {
      ASSERT(pFormat != nullptr);
      if(pFormat == nullptr)
         __throw(error_invalid_argument);

      string strBuffer;
      // string hmsFormats [_CTIMESPANFORMATS] = {"%ca","%02ld","%d"};
      //   string dayFormats [_CTIMESPANFORMATS] = {"%ca","%I64d","%I64d"};
      //strBuffer.Preallocate(maxTimeBufferSize);
      char ch;

      while((ch = *pFormat++) != '\0')
      {
         enum _CTIMESPANFORMATSTEP formatstep = _CTFS_NONE;
         if(ch == '%')
         {
            formatstep = _CTFS_FORMAT;
            ch = *pFormat++;
            if(ch == '#')
            {
               formatstep = _CTFS_NZ;
               ch = *pFormat++;
            }
         }
         switch(ch)
         {
         case '%':
            strBuffer += ch;
            break;
         case 'D':
            //            strBuffer.AppendFormat(dayFormats[formatstep], formatstep ? GetDays()    : ch);
            break;
         case 'H':
            //            strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetHours()   : ch);
            break;
         case 'M':
            //            strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetMinutes() : ch);
            break;
         case 'S':
            //            strBuffer.AppendFormat(hmsFormats[formatstep], formatstep ? GetSeconds() : ch);
            break;
         default:
            if(formatstep)
            {
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant
               ENSURE(false);      // probably a bad format character
#pragma warning (pop)
            }
            else
            {
               strBuffer += ch;
#ifdef _MBCS
               if(_istlead(ch))
               {
                  strBuffer += *pFormat++;
               }
#endif
            }
            break;
         }
      }

      return strBuffer;
   }




} // namespace datetime




#ifdef __DEBUG


dump_context & operator <<(dump_context & dumpcontext,::datetime::time_span timeSpan)
{
   dumpcontext << "time_span(" << timeSpan.GetDays() << " days, " <<
               timeSpan.GetHours() << " hours, " <<
               timeSpan.GetMinutes() << " minutes and " <<
               timeSpan.GetSeconds() << " seconds)";

   return dumpcontext;
}

#endif

stream & operator << (stream & os, ::datetime::time_span span)
{

   os.write((i64)span.m_timeSpan);

   return os;

}


stream & operator >> (stream & is, ::datetime::time_span & span)
{

   is.read((i64 &)span.m_timeSpan);

   return is;

}





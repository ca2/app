#include "framework.h"

//#include <math.h>
#include <time.h>

namespace datetime
{


   const double float_time_span::FLOAT_TIME_HALF_SECOND = 1.0 / (2.0 * (60.0 * 60.0 * 24.0));


} // namespace datetime

#define DATE_MIN -657434
#define DATE_MAX 2958465


#define TICKSPERSEC        10000000




#define TIMEFLAG(i) ((dp.dwFlags[i] & DP_TIMESEP) << i)

#define IsLeapYear(y) (((y % 4) == 0) && (((y % 100) != 0) || ((y % 400) == 0)))

/* Determine if a day is valid in a given month of a given year */
static int_bool FLOATTIME_IsValidMonthDay(::u32 day, ::u32 month, ::u32 year)
{
  static const byte days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  if (day && month && month < 13)
  {
    if (day <= days[month] || (month == 2 && day == 29 && IsLeapYear(year)))
      return TRUE;
  }
  return FALSE;
}


/* Date string parsing */
#define DP_TIMESEP 0x01 /* Time separator ( _must_ remain 0x1, used as a bitmask) */
#define DP_DATESEP 0x02 /* Date separator */
#define DP_MONTH   0x04 /* Month name */
#define DP_AM      0x08 /* AM */
#define DP_PM      0x10 /* PM */


typedef struct tagDATEPARSE
{
    ::u32 dwCount;      /* Number of fields found so far (maximum 6) */
    ::u32 dwParseFlags; /* Global parse flags (DP_ Flags above) */
    ::u32 dwFlags[6];   /* Flags for each field */
    ::u32 dwValues[6];  /* Value of each field */
} DATEPARSE;




static inline HRESULT FLOATTIME_MakeDate(DATEPARSE *dp, ::u32 iDate, ::u32 offset, SYSTEMTIME *st);

/***********************************************************************
 *              SystemTimeToVariantTime [OLEAUT32.184]
 *
 * Convert a System format date and time into variant VT_DATE format.
 *
 * PARAMS
 *  lpSt     [I] System format date and time
 *  pDateOut [O] Destination for VT_DATE format date
 *
 * RETURNS
 *  Success: TRUE. *pDateOut contains the converted value.
 *  Failure: FALSE, if lpSt cannot be represented in VT_DATE format.
 */
CLASS_DECL_CA2_TIME ::i32 SystemTimeToFloatTime(LPSYSTEMTIME lpSt, double *pDateOut)
{
  UDATE ud;

/*  TRACE("(%p->%d/%d/%d %d:%d:%d,%p)\n", lpSt, lpSt->wDay, lpSt->wMonth,
        lpSt->wYear, lpSt->wHour, lpSt->wMinute, lpSt->wSecond, pDateOut);*/

  if (lpSt->wMonth > 12)
    return FALSE;

  ud.st = *lpSt;
  return FloatTimeFromUdate(&ud, 0, pDateOut) == S_OK;
}

#ifndef WINDOWS

/***********************************************************************
*              VariantTimeToSystemTime [OLEAUT32.185]
*
* Convert a variant VT_DATE into a System format date and time.
*
* PARAMS
*  datein [I] Variant VT_DATE format date
*  lpSt   [O] Destination for System format date and time
*
* RETURNS
*  Success: TRUE. *lpSt contains the converted value.
*  Failure: FALSE, if dateIn is too large or small.
*/
::i32 WINAPI FloatTimeToSystemTime(double dateIn, LPSYSTEMTIME lpSt)
{
  UDATE ud;

  //TRACE("(%g,%p)\n", dateIn, lpSt);

  if (FAILED(VarUdateFromDate(dateIn, 0, &ud)))
    return FALSE;

  *lpSt = ud.st;
  return TRUE;
}


#endif

/* Roll a date forwards or backwards to correct it */
static HRESULT FLOATTIME_RollUdate(UDATE *lpUd)
{
  static const byte days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int16_t iYear, iMonth, iDay, iHour, iMinute, iSecond;

  /* interpret values signed */
  iYear   = lpUd->st.wYear;
  iMonth  = lpUd->st.wMonth;
  iDay    = lpUd->st.wDay;
  iHour   = lpUd->st.wHour;
  iMinute = lpUd->st.wMinute;
  iSecond = lpUd->st.wSecond;

  /*TRACE("Raw date: %d/%d/%d %d:%d:%d\n", iDay, iMonth,
        iYear, iHour, iMinute, iSecond);*/

  if (iYear > 9999 || iYear < -9999)
    return E_INVALIDARG; /* Invalid value */
  /* Years < 100 are treated as 1900 + year */
  if (iYear > 0 && iYear < 100)
    iYear += 1900;

  iMinute += iSecond / 60;
  iSecond  = iSecond % 60;
  iHour   += iMinute / 60;
  iMinute  = iMinute % 60;
  iDay    += iHour / 24;
  iHour    = iHour % 24;
  iYear   += iMonth / 12;
  iMonth   = iMonth % 12;
  if (iMonth<=0) {iMonth+=12; iYear--;}
  while (iDay > days[iMonth])
  {
    if (iMonth == 2 && IsLeapYear(iYear))
      iDay -= 29;
    else
      iDay -= days[iMonth];
    iMonth++;
    iYear += iMonth / 12;
    iMonth = iMonth % 12;
  }
  while (iDay <= 0)
  {
    iMonth--;
    if (iMonth<=0) {iMonth+=12; iYear--;}
    if (iMonth == 2 && IsLeapYear(iYear))
      iDay += 29;
    else
      iDay += days[iMonth];
  }

  if (iSecond<0){iSecond+=60; iMinute--;}
  if (iMinute<0){iMinute+=60; iHour--;}
  if (iHour<0)  {iHour+=24; iDay--;}
  if (iYear<=0)  iYear+=2000;

  lpUd->st.wYear   = iYear;
  lpUd->st.wMonth  = iMonth;
  lpUd->st.wDay    = iDay;
  lpUd->st.wHour   = iHour;
  lpUd->st.wMinute = iMinute;
  lpUd->st.wSecond = iSecond;

  /*TRACE("Rolled date: %d/%d/%d %d:%d:%d\n", lpUd->st.wDay, lpUd->st.wMonth,
        lpUd->st.wYear, lpUd->st.wHour, lpUd->st.wMinute, lpUd->st.wSecond);*/
  return S_OK;
}

/* Convert a Julian Date to a VT_DATE value */
static inline int32_t FLOATTIME_DateFromJulian(int32_t dateIn)
{
  int32_t julianDays = dateIn;

  julianDays -= 1757585;  /* Convert to + days from 1 Jan 100 AD */
  julianDays += DATE_MIN; /* Convert to +/- days from 1 Jan 1899 AD */
  return julianDays;
}


/* Convert a Julian date to Day/Month/Year - from PostgreSQL */
/*static inline void FLOATTIME_DMYFromJulian(int32_t jd, USHORT *year, USHORT *month, USHORT *day)
{
  int32_t j, i, l, n;

  l = jd + 68569;
  n = l * 4 / 146097;
  l -= (n * 146097 + 3) / 4;
  i = (4000 * (l + 1)) / 1461001;
  l += 31 - (i * 1461) / 4;
  j = (l * 80) / 2447;
  *day = l - (j * 2447) / 80;
  l = j / 11;
  *month = (j + 2) - (12 * l);
  *year = 100 * (n - 49) + i + l;
}*/

/* Convert Day/Month/Year to a Julian date - from PostgreSQL */
static inline double FLOATTIME_JulianFromDMY(u16 year, u16 month, u16 day)
{
  int32_t m12 = (month - 14) / 12;

  return ((1461 * (year + 4800 + m12)) / 4 + (367 * (month - 2 - 12 * m12)) / 12 -
           (3 * ((year + 4900 + m12) / 100)) / 4 + day - 32075);
}

/***********************************************************************
 *              VarDateFromUdate [OLEAUT32.330]
 *
 * Convert an unpacked format date and time to a variant VT_DATE.
 *
 * PARAMS
 *  pUdateIn [I] Unpacked format date and time to convert
 *  dwFlags  [I] Flags controlling the conversion (VAR_ flags from "oleauto.h")
 *  pDateOut [O] Destination for variant VT_DATE.
 *
 * RETURNS
 *  Success: S_OK. *pDateOut contains the converted value.
 *  Failure: E_INVALIDARG, if pUdateIn cannot be represented in VT_DATE format.
 *
 * NOTES
 *  This function uses the United States English locale for the conversion. Use
 *  VarDateFromUdateEx() for alternate locales.
 */
CLASS_DECL_CA2_TIME HRESULT FloatTimeFromUdate(UDATE *pUdateIn, u32 dwFlags, DATE *pDateOut)
{
  LCID lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);

  return FloatTimeFromUdateEx(pUdateIn, lcid, dwFlags, pDateOut);
}


/***********************************************************************
 *              VarDateFromUdateEx [OLEAUT32.319]
 *
 * Convert an unpacked format date and time to a variant VT_DATE.
 *
 * PARAMS
 *  pUdateIn [I] Unpacked format date and time to convert
 *  lcid     [I] Locale identifier for the conversion
 *  dwFlags  [I] Flags controlling the conversion (VAR_ flags from "oleauto.h")
 *  pDateOut [O] Destination for variant VT_DATE.
 *
 * RETURNS
 *  Success: S_OK. *pDateOut contains the converted value.
 *  Failure: E_INVALIDARG, if pUdateIn cannot be represented in VT_DATE format.
 */
CLASS_DECL_CA2_TIME HRESULT FloatTimeFromUdateEx(UDATE *pUdateIn, LCID lcid, u32 dwFlags, DATE *pDateOut)
{
  UDATE ud;
  double dateVal, dateSign;

/*  TRACE("(%p->%d/%d/%d %d:%d:%d:%d %d %d,0x%08x,0x%08x,%p)\n", pUdateIn,
        pUdateIn->st.wMonth, pUdateIn->st.wDay, pUdateIn->st.wYear,
        pUdateIn->st.wHour, pUdateIn->st.wMinute, pUdateIn->st.wSecond,
        pUdateIn->st.wMilliseconds, pUdateIn->st.wDayOfWeek,
        pUdateIn->wDayOfYear, lcid, dwFlags, pDateOut);*/

//  if (lcid != MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT))
//    FIXME("lcid possibly not handled, treating as en-us\n");

  ud = *pUdateIn;

//  if (dwFlags & VAR_VALIDDATE)
//    WARN("Ignoring VAR_VALIDDATE\n");

  if (FAILED(FLOATTIME_RollUdate(&ud)))
    return E_INVALIDARG;

  /* Date */
  dateVal = FLOATTIME_DateFromJulian((int32_t) FLOATTIME_JulianFromDMY(ud.st.wYear, ud.st.wMonth, ud.st.wDay));

  /* Sign */
  dateSign = (dateVal < 0.0) ? -1.0 : 1.0;

  /* Time */
  dateVal += ud.st.wHour / 24.0 * dateSign;
  dateVal += ud.st.wMinute / 1440.0 * dateSign;
  dateVal += ud.st.wSecond / 86400.0 * dateSign;

  //TRACE("Returning %g\n", dateVal);
  *pDateOut = dateVal;
  return S_OK;
}



/******************************************************************************
 * VarDateFromStr [OLEAUT32.94]
 *
 * Convert a VT_BSTR to at VT_DATE.
 *
 * PARAMS
 *  strIn    [I] String to convert
 *  lcid     [I] Locale identifier for the conversion
 *  dwFlags  [I] Flags affecting the conversion (VAR_ flags from "oleauto.h")
 *  pdateOut [O] Destination for the converted value
 *
 * RETURNS
 *  Success: S_OK. pdateOut contains the converted value.
 *  FAILURE: An HRESULT error code indicating the problem.
 *
 * NOTES
 *  Any date format that can be created using the date formats from lcid
 *  (Either from kernel Nls functions, variant conversion or formatting) is a
 *  valid input to this function. In addition, a few more esoteric formats are
 *  also supported for compatibility with the native version. The date is
 *  interpreted according to the date settings in the control panel, unless
 *  the date is invalid in that format, in which the most compatible format
 *  that produces a valid date will be used.
 */
CLASS_DECL_CA2_TIME HRESULT FloatTimeFromStr(const char * strIn, LCID lcid, u32 dwFlags, DATE* pdateOut)
{
  static const u16 ParseDateTokens[] =
  {
    LOCALE_SMONTHNAME1, LOCALE_SMONTHNAME2, LOCALE_SMONTHNAME3, LOCALE_SMONTHNAME4,
    LOCALE_SMONTHNAME5, LOCALE_SMONTHNAME6, LOCALE_SMONTHNAME7, LOCALE_SMONTHNAME8,
    LOCALE_SMONTHNAME9, LOCALE_SMONTHNAME10, LOCALE_SMONTHNAME11, LOCALE_SMONTHNAME12,
    LOCALE_SMONTHNAME13,
    LOCALE_SABBREVMONTHNAME1, LOCALE_SABBREVMONTHNAME2, LOCALE_SABBREVMONTHNAME3,
    LOCALE_SABBREVMONTHNAME4, LOCALE_SABBREVMONTHNAME5, LOCALE_SABBREVMONTHNAME6,
    LOCALE_SABBREVMONTHNAME7, LOCALE_SABBREVMONTHNAME8, LOCALE_SABBREVMONTHNAME9,
    LOCALE_SABBREVMONTHNAME10, LOCALE_SABBREVMONTHNAME11, LOCALE_SABBREVMONTHNAME12,
    LOCALE_SABBREVMONTHNAME13,
    LOCALE_SDAYNAME1, LOCALE_SDAYNAME2, LOCALE_SDAYNAME3, LOCALE_SDAYNAME4,
    LOCALE_SDAYNAME5, LOCALE_SDAYNAME6, LOCALE_SDAYNAME7,
    LOCALE_SABBREVDAYNAME1, LOCALE_SABBREVDAYNAME2, LOCALE_SABBREVDAYNAME3,
    LOCALE_SABBREVDAYNAME4, LOCALE_SABBREVDAYNAME5, LOCALE_SABBREVDAYNAME6,
    LOCALE_SABBREVDAYNAME7,
    LOCALE_S1159, LOCALE_S2359,
    LOCALE_SDATE
  };
  static const byte ParseDateMonths[] =
  {
    1,2,3,4,5,6,7,8,9,10,11,12,13,
    1,2,3,4,5,6,7,8,9,10,11,12,13
  };
  ::u32 i;
  BSTR tokens[sizeof(ParseDateTokens)/sizeof(ParseDateTokens[0])];
  DATEPARSE dp;
  ::u32 dwDateSeps = 0, iDate = 0;
  HRESULT hRet = S_OK;

  if ((dwFlags & (VAR_TIMEVALUEONLY|VAR_DATEVALUEONLY)) ==
      (VAR_TIMEVALUEONLY|VAR_DATEVALUEONLY))
    return E_INVALIDARG;

  if (!strIn)
    return DISP_E_TYPEMISMATCH;

  *pdateOut = 0.0;

//  TRACE("(%s,0x%08x,0x%08x,%p)\n", debugstr_w(strIn), lcid, dwFlags, pdateOut);

  memset(&dp, 0, sizeof(dp));

#ifdef METROWIN

  _throw(todo(get_app()));

#else
  GetLocaleInfoW(lcid, LOCALE_IDATE|LOCALE_RETURN_NUMBER|(dwFlags & LOCALE_NOUSEROVERRIDE),
                 (LPWSTR)&iDate, sizeof(iDate)/sizeof(WCHAR));
//  TRACE("iDate is %d\n", iDate);

  /* Get the month/day/am/pm tokens for this locale */
  for (i = 0; i < sizeof(tokens)/sizeof(tokens[0]); i++)
  {
    WCHAR buff[128];
    LCTYPE lctype =  ParseDateTokens[i] | (dwFlags & LOCALE_NOUSEROVERRIDE);

    /* FIXME: Alternate calendars - should use GetCalendarInfo() and/or
     *        GetAltMonthNames(). We should really cache these strings too.
     */
    buff[0] = '\0';
    GetLocaleInfoW(lcid, lctype, buff, sizeof(buff)/sizeof(WCHAR));
    tokens[i] = SysAllocString(buff);
//    TRACE("token %d is %s\n", i, debugstr_w(tokens[i]));
  }

#endif

  /* Parse the string into our structure */
  while (*strIn)
  {
    if (dp.dwCount >= 6)
      break;

//xxx    if (isdigitW(*strIn))
    if (isdigit(*strIn))
    {
//xxx      dp.dwValues[dp.dwCount] = strtoulW(strIn, &strIn, 10);
      dp.dwCount++;
      strIn--;
    }
    else if (isalpha(*strIn))
    {
      int_bool bFound = FALSE;

      for (i = 0; i < sizeof(tokens)/sizeof(tokens[0]); i++)
      {
//xxx        ::u32 dwLen = strlenW(tokens[i]);
// xxx         ::u32 dwLen = strlen(tokens[i]);
         ::u32 dwLen = -1;
//xxx        if (dwLen && !strncmpiW(strIn, tokens[i], dwLen))
        //if (dwLen && !strnicmp_dup(strIn, tokens[i], dwLen))
//         if(dwLen && 0)
         if(false)
        {
          if (i <= 25)
          {
            dp.dwValues[dp.dwCount] = ParseDateMonths[i];
            dp.dwFlags[dp.dwCount] |= (DP_MONTH|DP_DATESEP);
            dp.dwCount++;
          }
          else if (i > 39 && i < 42)
          {
            if (!dp.dwCount || dp.dwParseFlags & (DP_AM|DP_PM))
              hRet = DISP_E_TYPEMISMATCH;
            else
            {
              dp.dwFlags[dp.dwCount - 1] |= (i == 40 ? DP_AM : DP_PM);
              dp.dwParseFlags |= (i == 40 ? DP_AM : DP_PM);
            }
          }
          strIn += (dwLen - 1);
          bFound = TRUE;
          break;
        }
      }

      if (!bFound)
      {
        if ((*strIn == 'a' || *strIn == 'A' || *strIn == 'p' || *strIn == 'P') &&
            (dp.dwCount && !(dp.dwParseFlags & (DP_AM|DP_PM))))
        {
          /* Special case - 'a' and 'p' are recognised as int16_t for am/pm */
          if (*strIn == 'a' || *strIn == 'A')
          {
            dp.dwFlags[dp.dwCount - 1] |= DP_AM;
            dp.dwParseFlags |=  DP_AM;
          }
          else
          {
            dp.dwFlags[dp.dwCount - 1] |= DP_PM;
            dp.dwParseFlags |=  DP_PM;
          }
          strIn++;
        }
        else
        {
//xxx          TRACE("No matching token for %s\n", debugstr_w(strIn));
          hRet = DISP_E_TYPEMISMATCH;
          break;
        }
      }
    }
    else if (*strIn == ':' ||  *strIn == '.')
    {
      if (!dp.dwCount || !strIn[1])
        hRet = DISP_E_TYPEMISMATCH;
      else
        if (tokens[42][0] == *strIn)
        {
          dwDateSeps++;
          if (dwDateSeps > 2)
            hRet = DISP_E_TYPEMISMATCH;
          else
            dp.dwFlags[dp.dwCount - 1] |= DP_DATESEP;
        }
        else
          dp.dwFlags[dp.dwCount - 1] |= DP_TIMESEP;
    }
    else if (*strIn == '-' || *strIn == '/')
    {
      dwDateSeps++;
      if (dwDateSeps > 2 || !dp.dwCount || !strIn[1])
        hRet = DISP_E_TYPEMISMATCH;
      else
        dp.dwFlags[dp.dwCount - 1] |= DP_DATESEP;
    }
//xxx    else if (*strIn == ',' || isspaceW(*strIn))
        else if (*strIn == ',' || isspace(*strIn))
    {
      if (*strIn == ',' && !strIn[1])
        hRet = DISP_E_TYPEMISMATCH;
    }
    else
    {
      hRet = DISP_E_TYPEMISMATCH;
    }
    strIn++;
  }

  if (!dp.dwCount || dp.dwCount > 6 ||
      (dp.dwCount == 1 && !(dp.dwParseFlags & (DP_AM|DP_PM))))
    hRet = DISP_E_TYPEMISMATCH;

  if (SUCCEEDED(hRet))
  {
    SYSTEMTIME st;
    ::u32 dwOffset = 0; /* Start of date fields in dp.dwValues */

    st.wDayOfWeek = st.wHour = st.wMinute = st.wSecond = st.wMilliseconds = 0;

    /* Figure out which numbers correspond to which fields.
     *
     * This switch statement works based on the fact that native interprets any
     * fields that are not joined with a time separator ('.' or ':') as date
     * fields. Thus we construct a value from 0-32 where each set bit indicates
     * a time field. This encapsulates the hundreds of permutations of 2-6 fields.
     * For valid permutations, we set dwOffset to point_i32 to the first date field
     * and shorten dp.dwCount by the number of time fields found. The real
     * magic here occurs in VARIANT_MakeDate() above, where we determine what
     * each date number must represent in the context of iDate.
     */
//xxx    TRACE("0x%08x\n", TIMEFLAG(0)|TIMEFLAG(1)|TIMEFLAG(2)|TIMEFLAG(3)|TIMEFLAG(4));

    switch (TIMEFLAG(0)|TIMEFLAG(1)|TIMEFLAG(2)|TIMEFLAG(3)|TIMEFLAG(4))
    {
    case 0x1: /* TT TTDD TTDDD */
      if (dp.dwCount > 3 &&
          ((dp.dwFlags[2] & (DP_AM|DP_PM)) || (dp.dwFlags[3] & (DP_AM|DP_PM)) ||
          (dp.dwFlags[4] & (DP_AM|DP_PM))))
        hRet = DISP_E_TYPEMISMATCH;
      else if (dp.dwCount != 2 && dp.dwCount != 4 && dp.dwCount != 5)
        hRet = DISP_E_TYPEMISMATCH;
      st.wHour = (::u16) dp.dwValues[0];
      st.wMinute  = (::u16) dp.dwValues[1];
      dp.dwCount -= 2;
      dwOffset = 2;
      break;

    case 0x3: /* TTT TTTDD TTTDDD */
      if (dp.dwCount > 4 &&
          ((dp.dwFlags[3] & (DP_AM|DP_PM)) || (dp.dwFlags[4] & (DP_AM|DP_PM)) ||
          (dp.dwFlags[5] & (DP_AM|DP_PM))))
        hRet = DISP_E_TYPEMISMATCH;
      else if (dp.dwCount != 3 && dp.dwCount != 5 && dp.dwCount != 6)
        hRet = DISP_E_TYPEMISMATCH;
      st.wHour   = (::u16) dp.dwValues[0];
      st.wMinute = (::u16) dp.dwValues[1];
      st.wSecond = (::u16) dp.dwValues[2];
      dwOffset = 3;
      dp.dwCount -= 3;
      break;

    case 0x4: /* DDTT */
      if (dp.dwCount != 4 ||
          (dp.dwFlags[0] & (DP_AM|DP_PM)) || (dp.dwFlags[1] & (DP_AM|DP_PM)))
        hRet = DISP_E_TYPEMISMATCH;

      st.wHour = (::u16) dp.dwValues[2];
      st.wMinute  = (::u16) dp.dwValues[3];
      dp.dwCount -= 2;
      break;

   case 0x0: /* T DD DDD TDDD TDDD */
      if (dp.dwCount == 1 && (dp.dwParseFlags & (DP_AM|DP_PM)))
      {
        st.wHour = (::u16) dp.dwValues[0]; /* T */
        dp.dwCount = 0;
        break;
      }
      else if (dp.dwCount > 4 || (dp.dwCount < 3 && dp.dwParseFlags & (DP_AM|DP_PM)))
      {
        hRet = DISP_E_TYPEMISMATCH;
      }
      else if (dp.dwCount == 3)
      {
        if (dp.dwFlags[0] & (DP_AM|DP_PM)) /* TDD */
        {
          dp.dwCount = 2;
          st.wHour = (::u16) dp.dwValues[0];
          dwOffset = 1;
          break;
        }
        if (dp.dwFlags[2] & (DP_AM|DP_PM)) /* DDT */
        {
          dp.dwCount = 2;
          st.wHour = (::u16) dp.dwValues[2];
          break;
        }
        else if (dp.dwParseFlags & (DP_AM|DP_PM))
          hRet = DISP_E_TYPEMISMATCH;
      }
      else if (dp.dwCount == 4)
      {
        dp.dwCount = 3;
        if (dp.dwFlags[0] & (DP_AM|DP_PM)) /* TDDD */
        {
          st.wHour = (::u16) dp.dwValues[0];
          dwOffset = 1;
        }
        else if (dp.dwFlags[3] & (DP_AM|DP_PM)) /* DDDT */
        {
          st.wHour = (::u16) dp.dwValues[3];
        }
        else
          hRet = DISP_E_TYPEMISMATCH;
        break;
      }
      /* .. fall through .. */

    case 0x8: /* DDDTT */
      if ((dp.dwCount == 2 && (dp.dwParseFlags & (DP_AM|DP_PM))) ||
          (dp.dwCount == 5 && ((dp.dwFlags[0] & (DP_AM|DP_PM)) ||
           (dp.dwFlags[1] & (DP_AM|DP_PM)) || (dp.dwFlags[2] & (DP_AM|DP_PM)))) ||
           dp.dwCount == 4 || dp.dwCount == 6)
        hRet = DISP_E_TYPEMISMATCH;
      st.wHour   = (::u16) dp.dwValues[3];
      st.wMinute = (::u16) dp.dwValues[4];
      if (dp.dwCount == 5)
        dp.dwCount -= 2;
      break;

    case 0xC: /* DDTTT */
      if (dp.dwCount != 5 ||
          (dp.dwFlags[0] & (DP_AM|DP_PM)) || (dp.dwFlags[1] & (DP_AM|DP_PM)))
        hRet = DISP_E_TYPEMISMATCH;
      st.wHour   = (::u16) dp.dwValues[2];
      st.wMinute = (::u16) dp.dwValues[3];
      st.wSecond = (::u16) dp.dwValues[4];
      dp.dwCount -= 3;
      break;

    case 0x18: /* DDDTTT */
      if ((dp.dwFlags[0] & (DP_AM|DP_PM)) || (dp.dwFlags[1] & (DP_AM|DP_PM)) ||
          (dp.dwFlags[2] & (DP_AM|DP_PM)))
        hRet = DISP_E_TYPEMISMATCH;
      st.wHour   = (::u16) dp.dwValues[3];
      st.wMinute = (::u16) dp.dwValues[4];
      st.wSecond = (::u16) dp.dwValues[5];
      dp.dwCount -= 3;
      break;

    default:
      hRet = DISP_E_TYPEMISMATCH;
      break;
    }

    if (SUCCEEDED(hRet))
    {
      hRet = FLOATTIME_MakeDate(&dp, iDate, dwOffset, &st);

      if (dwFlags & VAR_TIMEVALUEONLY)
      {
        st.wYear = 1899;
        st.wMonth = 12;
        st.wDay = 30;
      }
      else if (dwFlags & VAR_DATEVALUEONLY)
       st.wHour = st.wMinute = st.wSecond = 0;

      /* Finally, convert the value to a VT_DATE */
      if (SUCCEEDED(hRet))
        hRet = SystemTimeToFloatTime(&st, pdateOut) ? S_OK : DISP_E_TYPEMISMATCH;
    }
  }

  for (i = 0; i < sizeof(tokens)/sizeof(tokens[0]); i++)
    SysFreeString(tokens[i]);
  return hRet;
}


/* Possible orders for 3 numbers making up a date */
#define ORDER_MDY 0x01
#define ORDER_YMD 0x02
#define ORDER_YDM 0x04
#define ORDER_DMY 0x08
#define ORDER_MYD 0x10 /* Synthetic order, used only for funky 2 digit dates */

/* Determine a date for a particular locale, from 3 numbers */
static inline HRESULT FLOATTIME_MakeDate(DATEPARSE *dp, ::u32 iDate, ::u32 offset, SYSTEMTIME *st)
{
  ::u32 dwAllOrders, dwTry, dwCount = 0, v1, v2, v3;

  if (!dp->dwCount)
  {
    v1 = 30; /* Default to (Variant) 0 date part */
    v2 = 12;
    v3 = 1899;
    goto VARIANT_MakeDate_OK;
  }

  v1 = dp->dwValues[offset + 0];
  v2 = dp->dwValues[offset + 1];
  if (dp->dwCount == 2)
  {
    SYSTEMTIME current;
    GetSystemTime(&current);
    v3 = current.wYear;
  }
  else
    v3 = dp->dwValues[offset + 2];

//xxx  TRACE("(%d,%d,%d,%d,%d)\n", v1, v2, v3, iDate, offset);

  /* If one number must be a month (Because a month name was given), then only
   * consider orders with the month in that position.
   * If we took the current year as 'v3', then only allow a year in that position.
   */
  if (dp->dwFlags[offset + 0] & DP_MONTH)
  {
    dwAllOrders = ORDER_MDY;
  }
  else if (dp->dwFlags[offset + 1] & DP_MONTH)
  {
    dwAllOrders = ORDER_DMY;
    if (dp->dwCount > 2)
      dwAllOrders |= ORDER_YMD;
  }
  else if (dp->dwCount > 2 && dp->dwFlags[offset + 2] & DP_MONTH)
  {
    dwAllOrders = ORDER_YDM;
  }
  else
  {
    dwAllOrders = ORDER_MDY|ORDER_DMY;
    if (dp->dwCount > 2)
      dwAllOrders |= (ORDER_YMD|ORDER_YDM);
  }

VARIANT_MakeDate_Start:
//xxx  TRACE("dwAllOrders is 0x%08x\n", dwAllOrders);

  while (dwAllOrders)
  {
    ::u32 dwTemp;

    if (dwCount == 0)
    {
      /* First: Try the order given by iDate */
      switch (iDate)
      {
      case 0:  dwTry = dwAllOrders & ORDER_MDY; break;
      case 1:  dwTry = dwAllOrders & ORDER_DMY; break;
      default: dwTry = dwAllOrders & ORDER_YMD; break;
      }
    }
    else if (dwCount == 1)
    {
      /* Second: Try all the orders compatible with iDate */
      switch (iDate)
      {
      case 0:  dwTry = dwAllOrders & ~(ORDER_DMY|ORDER_YDM); break;
      case 1:  dwTry = dwAllOrders & ~(ORDER_MDY|ORDER_YMD|ORDER_MYD); break;
      default: dwTry = dwAllOrders & ~(ORDER_DMY|ORDER_YDM); break;
      }
    }
    else
    {
      /* Finally: Try any remaining orders */
      dwTry = dwAllOrders;
    }

//xxx    TRACE("Attempt %d, dwTry is 0x%08x\n", dwCount, dwTry);

    dwCount++;
    if (!dwTry)
      continue;

#define DATE_SWAP(x,y) do { dwTemp = x; x = y; y = dwTemp; } while (0)

    if (dwTry & ORDER_MDY)
    {
      if (FLOATTIME_IsValidMonthDay(v2,v1,v3))
      {
        DATE_SWAP(v1,v2);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_MDY;
    }
    if (dwTry & ORDER_YMD)
    {
      if (FLOATTIME_IsValidMonthDay(v3,v2,v1))
      {
        DATE_SWAP(v1,v3);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_YMD;
    }
    if (dwTry & ORDER_YDM)
    {
      if (FLOATTIME_IsValidMonthDay(v2,v3,v1))
      {
        DATE_SWAP(v1,v2);
        DATE_SWAP(v2,v3);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_YDM;
    }
    if (dwTry & ORDER_DMY)
    {
      if (FLOATTIME_IsValidMonthDay(v1,v2,v3))
        goto VARIANT_MakeDate_OK;
      dwAllOrders &= ~ORDER_DMY;
    }
    if (dwTry & ORDER_MYD)
    {
      /* Only occurs if we are trying a 2 year date as M/Y not D/M */
      if (FLOATTIME_IsValidMonthDay(v3,v1,v2))
      {
        DATE_SWAP(v1,v3);
        DATE_SWAP(v2,v3);
        goto VARIANT_MakeDate_OK;
      }
      dwAllOrders &= ~ORDER_MYD;
    }
  }

  if (dp->dwCount == 2)
  {
    /* We couldn't make a date as D/M or M/D, so try M/Y or Y/M */
    v3 = 1; /* 1st of the month */
    dwAllOrders = ORDER_YMD|ORDER_MYD;
    dp->dwCount = 0; /* Don't return to this code path again */
    dwCount = 0;
    goto VARIANT_MakeDate_Start;
  }

  /* No valid dates were able to be constructed */
  return DISP_E_TYPEMISMATCH;

VARIANT_MakeDate_OK:

  /* Check that the time part is ok */
  if (st->wHour > 23 || st->wMinute > 59 || st->wSecond > 59)
    return DISP_E_TYPEMISMATCH;

//xxx  TRACE("Time %d %d %d\n", st->wHour, st->wMinute, st->wSecond);
  if (st->wHour < 12 && (dp->dwParseFlags & DP_PM))
    st->wHour += 12;
  else if (st->wHour == 12 && (dp->dwParseFlags & DP_AM))
    st->wHour = 0;
//xxx  TRACE("Time %d %d %d\n", st->wHour, st->wMinute, st->wSecond);

  st->wDay = (::u16) v1;
  st->wMonth = (::u16) v2;
  /* FIXME: For 2 digit dates, I'm not sure if 30 is hard coded or not. It may
   * be retrieved from:
   * HKCU\Control Panel\International\Calendars\TwoDigitYearMax
   * But Wine doesn't have/use that key as at the time of writing.
   */
  st->wYear = (::u16) (v3 < 30 ? 2000 + v3 : v3 < 100 ? 1900 + v3 : v3);
//xxx  TRACE("Returning date %d/%d/%d\n", v1, v2, st->wYear);
  return S_OK;
}


#ifndef WINDOWS

static inline int VARIANT_JulianFromDate(int dateIn);
static inline void VARIANT_DMYFromJulian(int jd, u16 *year, u16 *month, u16 *day);
static HRESULT VARIANT_RollUdate(UDATE *lpUd);

/* Convert a VT_DATE value to a Julian Date */
static inline int VARIANT_JulianFromDate(int dateIn)
{
  int julianDays = dateIn;

  julianDays -= DATE_MIN; /* Convert to + days from 1 Jan 100 AD */
  julianDays += 1757585;  /* Convert to + days from 23 Nov 4713 BC (Julian) */
  return julianDays;
}




/* Convert a Julian date to Day/Month/Year - from PostgreSQL */
static inline void VARIANT_DMYFromJulian(int jd, u16 *year, u16 *month, u16 *day)
{
  int j, i, l, n;

  l = jd + 68569;
  n = l * 4 / 146097;
  l -= (n * 146097 + 3) / 4;
  i = (4000 * (l + 1)) / 1461001;
  l += 31 - (i * 1461) / 4;
  j = (l * 80) / 2447;
  *day = l - (j * 2447) / 80;
  l = j / 11;
  *month = (j + 2) - (12 * l);
  *year = 100 * (n - 49) + i + l;
}


/* Roll a date forwards or backwards to correct it */
static HRESULT VARIANT_RollUdate(UDATE *lpUd)
{
  static const byte days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  short iYear, iMonth, iDay, iHour, iMinute, iSecond;

  /* interpret values signed */
  iYear   = lpUd->st.wYear;
  iMonth  = lpUd->st.wMonth;
  iDay    = lpUd->st.wDay;
  iHour   = lpUd->st.wHour;
  iMinute = lpUd->st.wMinute;
  iSecond = lpUd->st.wSecond;

//  TRACE("Raw date: %d/%d/%d %d:%d:%d\n", iDay, iMonth, iYear, iHour, iMinute, iSecond);

  if (iYear > 9999 || iYear < -9999)
    return E_INVALIDARG; /* Invalid value */
  /* Years < 100 are treated as 1900 + year */
  if (iYear > 0 && iYear < 100)
    iYear += 1900;

  iMinute += iSecond / 60;
  iSecond  = iSecond % 60;
  iHour   += iMinute / 60;
  iMinute  = iMinute % 60;
  iDay    += iHour / 24;
  iHour    = iHour % 24;
  iYear   += iMonth / 12;
  iMonth   = iMonth % 12;
  if (iMonth<=0) {iMonth+=12; iYear--;}
  while (iDay > days[iMonth])
  {
    if (iMonth == 2 && IsLeapYear(iYear))
      iDay -= 29;
    else
      iDay -= days[iMonth];
    iMonth++;
    iYear += iMonth / 12;
    iMonth = iMonth % 12;
  }
  while (iDay <= 0)
  {
    iMonth--;
    if (iMonth<=0) {iMonth+=12; iYear--;}
    if (iMonth == 2 && IsLeapYear(iYear))
      iDay += 29;
    else
      iDay += days[iMonth];
  }

  if (iSecond<0){iSecond+=60; iMinute--;}
  if (iMinute<0){iMinute+=60; iHour--;}
  if (iHour<0)  {iHour+=24; iDay--;}
  if (iYear<=0)  iYear+=2000;

  lpUd->st.wYear   = iYear;
  lpUd->st.wMonth  = iMonth;
  lpUd->st.wDay    = iDay;
  lpUd->st.wHour   = iHour;
  lpUd->st.wMinute = iMinute;
  lpUd->st.wSecond = iSecond;

//  TRACE("Rolled date: %d/%d/%d %d:%d:%d\n", lpUd->st.wDay, lpUd->st.wMonth, lpUd->st.wYear, lpUd->st.wHour, lpUd->st.wMinute, lpUd->st.wSecond);
  return S_OK;
}



/***********************************************************************
*              VarUdateFromDate [OLEAUT32.331]
*
* Convert a variant VT_DATE into an unpacked format date and time.
*
* PARAMS
*  datein    [I] Variant VT_DATE format date
*  dwFlags   [I] Flags controlling the conversion (VAR_ flags from "oleauto.h")
*  lpUdate   [O] Destination for unpacked format date and time
*
* RETURNS
*  Success: S_OK. *lpUdate contains the converted value.
*  Failure: E_INVALIDARG, if dateIn is too large or small.
*/
HRESULT WINAPI VarUdateFromDate(DATE dateIn, u32 dwFlags, UDATE *lpUdate)
{
  /* Cumulative totals of days per month */
  static const u16 cumulativeDays[] =
  {
    0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
  };
  double datePart, timePart;
  int32_t julianDays;

//xxx  TRACE("(%g,0x%08x,%p)\n", dateIn, dwFlags, lpUdate);

  if (dateIn <= (DATE_MIN - 1.0) || dateIn >= (DATE_MAX + 1.0))
    return E_INVALIDARG;

  datePart = dateIn < 0.0 ? ceil(dateIn) : floor(dateIn);
  /* Compensate for int32_t truncation (always downwards) */
  timePart = fabs(dateIn - datePart) + 0.00000000001;
  if (timePart >= 1.0)
    timePart -= 0.00000000001;

  /* Date */
  julianDays = VARIANT_JulianFromDate(dateIn);
  VARIANT_DMYFromJulian(julianDays, &lpUdate->st.wYear, &lpUdate->st.wMonth,
                        &lpUdate->st.wDay);

  datePart = (datePart + 1.5) / 7.0;
  lpUdate->st.wDayOfWeek = (datePart - floor(datePart)) * 7;
  if (lpUdate->st.wDayOfWeek == 0)
    lpUdate->st.wDayOfWeek = 5;
  else if (lpUdate->st.wDayOfWeek == 1)
    lpUdate->st.wDayOfWeek = 6;
  else
    lpUdate->st.wDayOfWeek -= 2;

  if (lpUdate->st.wMonth > 2 && IsLeapYear(lpUdate->st.wYear))
    lpUdate->wDayOfYear = 1; /* After February, in a leap year */
  else
    lpUdate->wDayOfYear = 0;

  lpUdate->wDayOfYear += cumulativeDays[lpUdate->st.wMonth];
  lpUdate->wDayOfYear += lpUdate->st.wDay;

  /* Time */
  timePart *= 24.0;
  lpUdate->st.wHour = timePart;
  timePart -= lpUdate->st.wHour;
  timePart *= 60.0;
  lpUdate->st.wMinute = timePart;
  timePart -= lpUdate->st.wMinute;
  timePart *= 60.0;
  lpUdate->st.wSecond = timePart;
  timePart -= lpUdate->st.wSecond;
  lpUdate->st.wMilliseconds = 0;
  if (timePart > 0.5)
  {
    /* Round the milliseconds, adjusting the time/date forward if needed */
    if (lpUdate->st.wSecond < 59)
      lpUdate->st.wSecond++;
    else
    {
      lpUdate->st.wSecond = 0;
      if (lpUdate->st.wMinute < 59)
        lpUdate->st.wMinute++;
      else
      {
        lpUdate->st.wMinute = 0;
        if (lpUdate->st.wHour < 23)
          lpUdate->st.wHour++;
        else
        {
          lpUdate->st.wHour = 0;
          /* Roll over a whole day */
          if (++lpUdate->st.wDay > 28)
            VARIANT_RollUdate(lpUdate);
        }
      }
    }
  }
  return S_OK;
}



#else


int32_t __cdecl FloatTimeToSystemTime(double vtime, struct _SYSTEMTIME * pst)
{


   return VariantTimeToSystemTime(vtime, pst);


}


#endif

namespace datetime
{


   float_time &float_time::operator=(const FILETIME &filetimeSrc) RELEASENOTHROW
   {
      
      FILETIME ftl;

      SYSTEMTIME st;

      m_estatus =  ::FileTimeToLocalFileTime(&filetimeSrc, &ftl) && ::FileTimeToSystemTime(&ftl, &st) && ConvertSystemTimeToFloatTime(st) ? e_status_valid : e_status_invalid;

      return *this;

   }


   float_time WINAPI float_time::GetCurrentTime() RELEASENOTHROW
   {
        
#ifdef WINDOWS
        
        return float_time(::_time64(NULL));
        
#else
        
        return float_time(::time(NULL));
        
#endif
        
   }


    
} //    namespace datetime


#ifndef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
#ifdef APPLEOS
inline bool GetAsSystemTimeHelper(const time_t& timeSrc, SYSTEMTIME& timeDest)
#else
inline bool GetAsSystemTimeHelper(const time_t& timeSrc, SYSTEMTIME& timeDest)
#endif
{
    struct tm ttm;
    
#ifdef WINDOWS
    if (_localtime64_s(&ttm, &timeSrc) != 0)
    {
        return false;
    }
    
#else
    
    ttm = *localtime(&timeSrc);
    
    if(errno != 0)
    {
        return false;
    }
    
#endif
    
    timeDest.wYear = (::u16) (1900 + ttm.tm_year);
    timeDest.wMonth = (::u16) (1 + ttm.tm_mon);
    timeDest.wDayOfWeek = (::u16) ttm.tm_wday;
    timeDest.wDay = (::u16) ttm.tm_mday;
    timeDest.wHour = (::u16) ttm.tm_hour;
    timeDest.wMinute = (::u16) ttm.tm_min;
    timeDest.wSecond = (::u16) ttm.tm_sec;
    timeDest.wMilliseconds = 0;
    
    return true;
    
}

#endif // _ATL_USE_WINAPI_FAMILY_DESKTOP_APP


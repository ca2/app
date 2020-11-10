#include "framework.h"
#include "aura/os/cross/windows/e.h"

#undef WINAXISAPI
#define WINAXISAPI CLASS_DECL_AXIS

#define LOCALE_LOCALEINFOFLAGSMASK (LOCALE_NOUSEROVERRIDE|LOCALE_USE_CP_ACP|\
                                    LOCALE_RETURN_NUMBER|LOCALE_RETURN_GENITIVE_NAMES)



static LCID user_lcid, system_lcid;
//static LANGID user_ui_language, system_ui_language;
static LANGID system_ui_language;

::u32 setup_unix_locales(void);
int_bool is_genitive_name_supported( LCTYPE lctype );
LCID convert_default_lcid( LCID lcid, LCTYPE lctype );
const WCHAR *get_locale_value_name( ::u32 lctype );
INT get_registry_locale_info( LPCWSTR value, LPWSTR buffer, INT len );

/******************************************************************************
 *		GetLocaleInfoW (KERNEL32.@)
 *
 * See GetLocaleInfoA.
 */
#ifndef _UWP
#ifdef WINDOWS
WINAXISAPI
#endif
i32 WINAPI GetLocaleInfoW( LCID lcid, LCTYPE lctype, LPWSTR buffer, i32 len )
{
   LANGID lang_id;
   //HRSRC hrsrc;
   //HGLOBAL hmem;
   i32 ret;
   u32 lcflags;
   const WCHAR *point = nullptr;
   unsigned int i;

   if (len < 0 || (len && !buffer))
   {
      set_last_error( ERROR_INVALID_PARAMETER );
      return 0;
   }
   if (lctype & LOCALE_RETURN_GENITIVE_NAMES &&
         !is_genitive_name_supported( lctype ))
   {
      set_last_error( ERROR_INVALID_FLAGS );
      return 0;
   }

   if (!len) buffer = nullptr;

   lcid = convert_default_lcid( lcid, lctype );

   lcflags = lctype & LOCALE_LOCALEINFOFLAGSMASK;
   lctype &= 0xffff;

   //TRACE( "(lcid=0x%x,lctype=0x%x,%point,%d)\n", lcid, lctype, buffer, len );

   /* first check for overrides in the registry */

   if (!(lcflags & LOCALE_NOUSEROVERRIDE) &&
         lcid == convert_default_lcid( LOCALE_USER_DEFAULT, lctype ))
   {
      const WCHAR *value = get_locale_value_name(lctype);

      if (value)
      {
         if (lcflags & LOCALE_RETURN_NUMBER)
         {
            WCHAR tmp[16];
            ret = get_registry_locale_info( value, tmp, sizeof(tmp)/sizeof(WCHAR) );
            if (ret > 0)
            {
               const WCHAR *end;
               u32 number = (u32) wd16_to_i64(tmp, &end, 10 );
               if (*end)  /* invalid number */
               {
                  set_last_error( ERROR_INVALID_FLAGS );
                  return 0;
               }
               ret = sizeof(u32)/sizeof(WCHAR);
               if (!buffer) return ret;
               if (ret > len)
               {
                  set_last_error( ERROR_INSUFFICIENT_BUFFER );
                  return 0;
               }
               ::memcpy_dup( buffer, &number, sizeof(number) );
            }
         }
         else ret = get_registry_locale_info( value, buffer, len );

         if (ret != -1) return ret;
      }
   }

   /* now load it from kernel resources */

   lang_id = LANGIDFROMLCID( lcid );

   /* replace SUBLANG_NEUTRAL by SUBLANG_DEFAULT */
   if (SUBLANGID(lang_id) == SUBLANG_NEUTRAL)
      lang_id = MAKELANGID(PRIMARYLANGID(lang_id), SUBLANG_DEFAULT);

   point = nullptr;
   for (i = 0; i < (lctype & 0x0f); i++) point += *point + 1;

   if (lcflags & LOCALE_RETURN_NUMBER) ret = sizeof(u32)/sizeof(WCHAR);
   else if (is_genitive_name_supported( lctype ) && *point)
   {
      /* genitive form's stored after a nullptr separator from a nominative */
      for (i = 1; comparison::le(i, *point); i++) if (!point[i]) break;

      if (comparison::le(i, *point) && (lcflags & LOCALE_RETURN_GENITIVE_NAMES))
      {
         ret = *point - i + 1;
         point += i;
      }
      else ret = i;
   }
   else
      ret = (lctype == LOCALE_FONTSIGNATURE) ? *point : *point + 1;

   if (!buffer) return ret;

   if (ret > len)
   {
      set_last_error( ERROR_INSUFFICIENT_BUFFER );
      return 0;
   }

   if (lcflags & LOCALE_RETURN_NUMBER)
   {
      u32 number;
//        WCHAR *end, *tmp = HeapAlloc( GetProcessHeap(), 0, (*point + 1) * sizeof(WCHAR) );
      const WCHAR *end;
      WCHAR * tmp = (WCHAR *) malloc((*point + 1) * sizeof(WCHAR) );
      if (!tmp) return 0;
      ::memcpy_dup( tmp, point + 1, *point * sizeof(WCHAR) );
      tmp[*point] = 0;
      number = (u32) wd16_to_i64( tmp, &end, 10 );
      if (!*end)
         ::memcpy_dup( buffer, &number, sizeof(number) );
      else  /* invalid number */
      {
         set_last_error( ERROR_INVALID_FLAGS );
         ret = 0;
      }
//        HeapFree( GetProcessHeap(), 0, tmp );
      free(tmp);

      //TRACE( "(lcid=0x%x,lctype=0x%x,%point,%d) returning number %d\n", lcid, lctype, buffer, len, number );
   }
   else
   {
      ::memcpy_dup( buffer, point + 1, ret * sizeof(WCHAR) );
      if (lctype != LOCALE_FONTSIGNATURE) buffer[ret-1] = 0;

      //TRACE( "(lcid=0x%x,lctype=0x%x,%point,%d) returning %d %s\n", lcid, lctype, buffer, len, ret, debugstr_w(buffer) );
   }
   return ret;
}

#endif









/***********************************************************************
 *           is_genitive_name_supported
 *
 * Determine could LCTYPE basically support genitive name form or not.
 */
int_bool is_genitive_name_supported( LCTYPE lctype )
{
   switch(lctype & 0xffff)
   {
   case LOCALE_SMONTHNAME1:
   case LOCALE_SMONTHNAME2:
   case LOCALE_SMONTHNAME3:
   case LOCALE_SMONTHNAME4:
   case LOCALE_SMONTHNAME5:
   case LOCALE_SMONTHNAME6:
   case LOCALE_SMONTHNAME7:
   case LOCALE_SMONTHNAME8:
   case LOCALE_SMONTHNAME9:
   case LOCALE_SMONTHNAME10:
   case LOCALE_SMONTHNAME11:
   case LOCALE_SMONTHNAME12:
   case LOCALE_SMONTHNAME13:
      return TRUE;
   default:
      return FALSE;
   }
}





/* locale ids corresponding to the various Unix locale parameters */
static LCID lcid_LC_COLLATE;
static LCID lcid_LC_CTYPE;
//static LCID lcid_LC_MESSAGES;
static LCID lcid_LC_MONETARY;
static LCID lcid_LC_NUMERIC;
static LCID lcid_LC_TIME;
static LCID lcid_LC_PAPER;
static LCID lcid_LC_MEASUREMENT;
static LCID lcid_LC_TELEPHONE;




#ifndef _UWP

/***********************************************************************
 *           convert_default_lcid
 *
 * Get the default LCID to use for a given lctype in GetLocaleInfo.
 */
LCID convert_default_lcid( LCID lcid, LCTYPE lctype )
{
   if (lcid == LOCALE_SYSTEM_DEFAULT ||
         lcid == LOCALE_USER_DEFAULT ||
         lcid == LOCALE_NEUTRAL)
   {
      LCID default_id = 0;

      switch(lctype & 0xffff)
      {
      case LOCALE_SSORTNAME:
         default_id = lcid_LC_COLLATE;
         break;

      case LOCALE_FONTSIGNATURE:
      case LOCALE_IDEFAULTANSICODEPAGE:
      case LOCALE_IDEFAULTCODEPAGE:
      case LOCALE_IDEFAULTEBCDICCODEPAGE:
      case LOCALE_IDEFAULTMACCODEPAGE:
#ifndef _UWP
      case LOCALE_IDEFAULTUNIXCODEPAGE:
#endif
         default_id = lcid_LC_CTYPE;
         break;

      case LOCALE_ICURRDIGITS:
      case LOCALE_ICURRENCY:
      case LOCALE_IINTLCURRDIGITS:
      case LOCALE_INEGCURR:
      case LOCALE_INEGSEPBYSPACE:
      case LOCALE_INEGSIGNPOSN:
      case LOCALE_INEGSYMPRECEDES:
      case LOCALE_IPOSSEPBYSPACE:
      case LOCALE_IPOSSIGNPOSN:
      case LOCALE_IPOSSYMPRECEDES:
      case LOCALE_SCURRENCY:
      case LOCALE_SINTLSYMBOL:
      case LOCALE_SMONDECIMALSEP:
      case LOCALE_SMONGROUPING:
      case LOCALE_SMONTHOUSANDSEP:
      case LOCALE_SNATIVECURRNAME:
         default_id = lcid_LC_MONETARY;
         break;

      case LOCALE_IDIGITS:
      case LOCALE_IDIGITSUBSTITUTION:
      case LOCALE_ILZERO:
      case LOCALE_INEGNUMBER:
      case LOCALE_SDECIMAL:
      case LOCALE_SGROUPING:
      case LOCALE_SNAN:
      case LOCALE_SNATIVEDIGITS:
      case LOCALE_SNEGATIVESIGN:
      case LOCALE_SNEGINFINITY:
      case LOCALE_SPOSINFINITY:
      case LOCALE_SPOSITIVESIGN:
      case LOCALE_STHOUSAND:
         default_id = lcid_LC_NUMERIC;
         break;

      case LOCALE_ICALENDARTYPE:
      case LOCALE_ICENTURY:
      case LOCALE_IDATE:
      case LOCALE_IDAYLZERO:
      case LOCALE_IFIRSTDAYOFWEEK:
      case LOCALE_IFIRSTWEEKOFYEAR:
      case LOCALE_ILDATE:
      case LOCALE_IMONLZERO:
      case LOCALE_IOPTIONALCALENDAR:
      case LOCALE_ITIME:
      case LOCALE_ITIMEMARKPOSN:
      case LOCALE_ITLZERO:
      case LOCALE_S1159:
      case LOCALE_S2359:
      case LOCALE_SABBREVDAYNAME1:
      case LOCALE_SABBREVDAYNAME2:
      case LOCALE_SABBREVDAYNAME3:
      case LOCALE_SABBREVDAYNAME4:
      case LOCALE_SABBREVDAYNAME5:
      case LOCALE_SABBREVDAYNAME6:
      case LOCALE_SABBREVDAYNAME7:
      case LOCALE_SABBREVMONTHNAME1:
      case LOCALE_SABBREVMONTHNAME2:
      case LOCALE_SABBREVMONTHNAME3:
      case LOCALE_SABBREVMONTHNAME4:
      case LOCALE_SABBREVMONTHNAME5:
      case LOCALE_SABBREVMONTHNAME6:
      case LOCALE_SABBREVMONTHNAME7:
      case LOCALE_SABBREVMONTHNAME8:
      case LOCALE_SABBREVMONTHNAME9:
      case LOCALE_SABBREVMONTHNAME10:
      case LOCALE_SABBREVMONTHNAME11:
      case LOCALE_SABBREVMONTHNAME12:
      case LOCALE_SABBREVMONTHNAME13:
      case LOCALE_SDATE:
      case LOCALE_SDAYNAME1:
      case LOCALE_SDAYNAME2:
      case LOCALE_SDAYNAME3:
      case LOCALE_SDAYNAME4:
      case LOCALE_SDAYNAME5:
      case LOCALE_SDAYNAME6:
      case LOCALE_SDAYNAME7:
      case LOCALE_SDURATION:
      case LOCALE_SLONGDATE:
      case LOCALE_SMONTHNAME1:
      case LOCALE_SMONTHNAME2:
      case LOCALE_SMONTHNAME3:
      case LOCALE_SMONTHNAME4:
      case LOCALE_SMONTHNAME5:
      case LOCALE_SMONTHNAME6:
      case LOCALE_SMONTHNAME7:
      case LOCALE_SMONTHNAME8:
      case LOCALE_SMONTHNAME9:
      case LOCALE_SMONTHNAME10:
      case LOCALE_SMONTHNAME11:
      case LOCALE_SMONTHNAME12:
      case LOCALE_SMONTHNAME13:
      case LOCALE_SSHORTDATE:
      case LOCALE_SSHORTESTDAYNAME1:
      case LOCALE_SSHORTESTDAYNAME2:
      case LOCALE_SSHORTESTDAYNAME3:
      case LOCALE_SSHORTESTDAYNAME4:
      case LOCALE_SSHORTESTDAYNAME5:
      case LOCALE_SSHORTESTDAYNAME6:
      case LOCALE_SSHORTESTDAYNAME7:
      case LOCALE_STIME:
      case LOCALE_STIMEFORMAT:
      case LOCALE_SYEARMONTH:
         default_id = lcid_LC_TIME;
         break;

      case LOCALE_IPAPERSIZE:
         default_id = lcid_LC_PAPER;
         break;

      case LOCALE_IMEASURE:
         default_id = lcid_LC_MEASUREMENT;
         break;

      case LOCALE_ICOUNTRY:
         default_id = lcid_LC_TELEPHONE;
         break;
      }
      if (default_id) lcid = default_id;
   }
   return ConvertDefaultLocale( lcid );
}




#endif




/******************************************************************************
 *		get_locale_value_name
 *
 * Gets the registry value name for a given lctype.
 */
const WCHAR *get_locale_value_name( ::u32 lctype )
{
   static const WCHAR iCalendarTypeW[] = {'i','C','a','l','e','n','d','a','r','T','y','p','e',0};
   static const WCHAR iCountryW[] = {'i','C','o','u','n','t','r','y',0};
   static const WCHAR iCurrDigitsW[] = {'i','C','u','r','r','D','i','g','i','t','s',0};
   static const WCHAR iCurrencyW[] = {'i','C','u','r','r','e','n','c','y',0};
   static const WCHAR iDateW[] = {'i','D','a','t','e',0};
   static const WCHAR iDigitsW[] = {'i','D','i','g','i','t','s',0};
   static const WCHAR iFirstDayOfWeekW[] = {'i','F','i','r','s','t','D','a','y','O','f','W','e','e','k',0};
   static const WCHAR iFirstWeekOfYearW[] = {'i','F','i','r','s','t','W','e','e','k','O','f','Y','e','a','r',0};
   static const WCHAR iLDateW[] = {'i','L','D','a','t','e',0};
   static const WCHAR iLZeroW[] = {'i','L','Z','e','r','o',0};
   static const WCHAR iMeasureW[] = {'i','M','e','a','s','u','r','e',0};
   static const WCHAR iNegCurrW[] = {'i','N','e','g','C','u','r','r',0};
   static const WCHAR iNegNumberW[] = {'i','N','e','g','N','u','m','b','e','r',0};
   static const WCHAR iPaperSizeW[] = {'i','P','a','p','e','r','S','i','z','e',0};
   static const WCHAR iTLZeroW[] = {'i','T','L','Z','e','r','o',0};
   static const WCHAR iTimePrefixW[] = {'i','T','i','m','e','P','r','e','f','i','x',0};
   static const WCHAR iTimeW[] = {'i','T','i','m','e',0};
   static const WCHAR s1159W[] = {'s','1','1','5','9',0};
   static const WCHAR s2359W[] = {'s','2','3','5','9',0};
   static const WCHAR sCountryW[] = {'s','C','o','u','n','t','r','y',0};
   static const WCHAR sCurrencyW[] = {'s','C','u','r','r','e','n','c','y',0};
   static const WCHAR sDateW[] = {'s','D','a','t','e',0};
   static const WCHAR sDecimalW[] = {'s','D','e','c','i','m','a','l',0};
   static const WCHAR sGroupingW[] = {'s','G','r','o','u','p','i','n','g',0};
   static const WCHAR sLanguageW[] = {'s','L','a','n','g','u','a','g','e',0};
   static const WCHAR sListW[] = {'s','L','i','s','t',0};
   static const WCHAR sLongDateW[] = {'s','L','o','n','g','D','a','t','e',0};
   static const WCHAR sMonDecimalSepW[] = {'s','M','o','n','D','e','c','i','m','a','l','S','e','p',0};
   static const WCHAR sMonGroupingW[] = {'s','M','o','n','G','r','o','u','p','i','n','g',0};
   static const WCHAR sMonThousandSepW[] = {'s','M','o','n','T','h','o','u','s','a','n','d','S','e','p',0};
   static const WCHAR sNativeDigitsW[] = {'s','N','a','t','i','v','e','D','i','g','i','t','s',0};
   static const WCHAR sNegativeSignW[] = {'s','N','e','g','a','t','i','v','e','S','i','g','n',0};
   static const WCHAR sPositiveSignW[] = {'s','P','o','s','i','t','i','v','e','S','i','g','n',0};
   static const WCHAR sShortDateW[] = {'s','S','h','o','r','t','D','a','t','e',0};
   static const WCHAR sThousandW[] = {'s','T','h','o','u','s','a','n','d',0};
   static const WCHAR sTimeFormatW[] = {'s','T','i','m','e','F','o','r','m','a','t',0};
   static const WCHAR sTimeW[] = {'s','T','i','m','e',0};
   static const WCHAR sYearMonthW[] = {'s','Y','e','a','r','M','o','n','t','h',0};
   static const WCHAR NumShapeW[] = {'N','u','m','s','h','a','p','e',0};

   switch (lctype)
   {
   /* These values are used by SetLocaleInfo and GetLocaleInfo, and
    * the values are stored in the registry, confirmed under Windows.
    */
   case LOCALE_ICALENDARTYPE:    return iCalendarTypeW;
   case LOCALE_ICURRDIGITS:      return iCurrDigitsW;
   case LOCALE_ICURRENCY:        return iCurrencyW;
   case LOCALE_IDIGITS:          return iDigitsW;
   case LOCALE_IFIRSTDAYOFWEEK:  return iFirstDayOfWeekW;
   case LOCALE_IFIRSTWEEKOFYEAR: return iFirstWeekOfYearW;
   case LOCALE_ILZERO:           return iLZeroW;
   case LOCALE_IMEASURE:         return iMeasureW;
   case LOCALE_INEGCURR:         return iNegCurrW;
   case LOCALE_INEGNUMBER:       return iNegNumberW;
   case LOCALE_IPAPERSIZE:       return iPaperSizeW;
   case LOCALE_ITIME:            return iTimeW;
   case LOCALE_S1159:            return s1159W;
   case LOCALE_S2359:            return s2359W;
   case LOCALE_SCURRENCY:        return sCurrencyW;
   case LOCALE_SDATE:            return sDateW;
   case LOCALE_SDECIMAL:         return sDecimalW;
   case LOCALE_SGROUPING:        return sGroupingW;
   case LOCALE_SLIST:            return sListW;
   case LOCALE_SLONGDATE:        return sLongDateW;
   case LOCALE_SMONDECIMALSEP:   return sMonDecimalSepW;
   case LOCALE_SMONGROUPING:     return sMonGroupingW;
   case LOCALE_SMONTHOUSANDSEP:  return sMonThousandSepW;
   case LOCALE_SNEGATIVESIGN:    return sNegativeSignW;
   case LOCALE_SPOSITIVESIGN:    return sPositiveSignW;
   case LOCALE_SSHORTDATE:       return sShortDateW;
   case LOCALE_STHOUSAND:        return sThousandW;
   case LOCALE_STIME:            return sTimeW;
   case LOCALE_STIMEFORMAT:      return sTimeFormatW;
   case LOCALE_SYEARMONTH:       return sYearMonthW;

   /* The following are not listed under MSDN as supported,
    * but seem to be used and also stored in the registry.
    */
   case LOCALE_ICOUNTRY:         return iCountryW;
   case LOCALE_IDATE:            return iDateW;
   case LOCALE_ILDATE:           return iLDateW;
   case LOCALE_ITLZERO:          return iTLZeroW;
   case LOCALE_SCOUNTRY:         return sCountryW;
   case LOCALE_SABBREVLANGNAME:  return sLanguageW;

   /* The following are used in XP and later */
   case LOCALE_IDIGITSUBSTITUTION: return NumShapeW;
   case LOCALE_SNATIVEDIGITS:      return sNativeDigitsW;
   case LOCALE_ITIMEMARKPOSN:      return iTimePrefixW;
   }
   return nullptr;
}




/******************************************************************************
 *		get_registry_locale_info
 *
 * Retrieve user-modified locale info from the registry.
 * Return length, 0 on error, -1 if not found.
 */

//INT get_registry_locale_info( LPCWSTR value, LPWSTR buffer, INT len )
INT get_registry_locale_info(LPCWSTR, LPWSTR, INT)
{

   return 0;

}




















/***********************************************************************
 *           setup_unix_locales
 */
::u32 setup_unix_locales(void)
{
   return 0;
}


/***********************************************************************
 *		GetSystemDefaultLCID (KERNEL32.@)
 *
 * Get the default locale Id for the system.
 *
 * PARAMS
 *  None.
 *
 * RETURNS
 *  The current LCID of the default locale for the system.
 */
#ifdef WINDOWS
WINAXISAPI
#endif
LCID WINAPI GetSystemDefaultLCID(void)
{
   LCID lcid;
   NtQueryDefaultLocale( FALSE, &lcid );
   return lcid;
}

#ifndef _UWP
/******************************************************************************
 *		ConvertDefaultLocale (KERNEL32.@)
 *
 * Convert a default locale identifier into a real identifier.
 *
 * PARAMS
 *  lcid [I] LCID identifier of the locale to convert
 *
 * RETURNS
 *  lcid unchanged, if not a default locale or its sublanguage is
 *   not SUBLANG_NEUTRAL.
 *  GetSystemDefaultLCID(), if lcid == LOCALE_SYSTEM_DEFAULT.
 *  GetUserDefaultLCID(), if lcid == LOCALE_USER_DEFAULT or LOCALE_NEUTRAL.
 *  Otherwise, lcid with sublanguage changed to SUBLANG_DEFAULT.
 */
#ifdef WINDOWS
WINAXISAPI
#endif
LCID WINAPI ConvertDefaultLocale( LCID lcid )
{
   LANGID langid;

   switch (lcid)
   {
   case LOCALE_SYSTEM_DEFAULT:
      lcid = GetSystemDefaultLCID();
      break;
   case LOCALE_USER_DEFAULT:
   case LOCALE_NEUTRAL:
      lcid = GetUserDefaultLCID();
      break;
   default:
      /* Replace SUBLANG_NEUTRAL with SUBLANG_DEFAULT */
      langid = LANGIDFROMLCID(lcid);
      if (SUBLANGID(langid) == SUBLANG_NEUTRAL)
      {
         langid = MAKELANGID(PRIMARYLANGID(langid), SUBLANG_DEFAULT);
         lcid = MAKELCID(langid, SORTIDFROMLCID(lcid));
      }
   }
   return lcid;
}
#endif





/**********************************************************************
 *	NtQueryDefaultLocale  (NTDLL.@)
 */
NTSTATUS WINAPI NtQueryDefaultLocale( int_bool user, LCID *lcid )
{
   *lcid = user ? user_lcid : system_lcid;
#ifdef _UWP
   return 0;
#else
   return STATUS_SUCCESS;
#endif
}


/**********************************************************************
 *	NtSetDefaultLocale  (NTDLL.@)
 */
NTSTATUS WINAPI NtSetDefaultLocale( int_bool user, LCID lcid )
{
   if (user) user_lcid = lcid;
   else
   {
      system_lcid = lcid;
      system_ui_language = LANGIDFROMLCID(lcid); /* there is no separate call to set it */
   }
#ifdef _UWP
   return 0;
#else
   return STATUS_SUCCESS;
#endif
}



/***********************************************************************
 *		GetUserDefaultLCID (KERNEL32.@)
 *
 * Get the default locale Id for the current user.
 *
 * PARAMS
 *  None.
 *
 * RETURNS
 *  The current LCID of the default locale for the current user.
 */
#ifdef WINDOWS
WINAXISAPI
#endif
LCID WINAPI GetUserDefaultLCID(void)
{
   LCID lcid;
   NtQueryDefaultLocale( TRUE, &lcid );
   return lcid;
}

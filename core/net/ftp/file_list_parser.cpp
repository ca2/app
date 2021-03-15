////////////////////////////////////////////////////////////////////////////////
//
// Code taken from D. J. Bernstein (C ==> C++)
//
// ftpparse.c, ftpparse.h: library for parsing FTP LIST responses
// 20001223
// D. J. Bernstein, djb@cr.yp.to
// http://cr.yp.to/ftpparse.html
//
// Commercial use is fine, if you let me know what programs you're using this in.
//
// Currently covered formats:
// EPLF.
// UNIX ls, with or without gid.
// Microsoft FTP Service.
// Windows NT FTP Server.
// VMS.
// WFTPD.
// NetPresenz (Mac).
// NetWare.
// MSDOS.
//
// Definitely not covered:
// Long VMS filenames, with information split across two lines.
// NCSA Telnet FTP server. Has LIST = NLST (and bad NLST for directories).
//
////////////////////////////////////////////////////////////////////////////////

#include "framework.h"
#include "_.h"
#include <time.h>


namespace ftp
{



#ifndef INSERTIME
   void InsertTime(file_status& ftpFileStatus)
   {
      //tm m = { 0 };
      if (ftpFileStatus.m_timeModification > 0)
      {
         ftpFileStatus.m_strModificationTime = psystem->datetime().international().get_gmt_date_time(ftpFileStatus.m_timeModification);
      }
   }

#define INSERTIME(ftpFileStatus) InsertTime(ftpFileStatus);
#endif

   const char* file_list_parser::m_Months[12] = {
      ("jan"),("feb"),("mar"),("apr"),("may"),("jun"),
      ("jul"),("aug"),("sep"),("oct"),("nov"),("dec")
   };


   file_list_parser::file_list_parser() :
      m_lCurrentYear(-1)
   {

      m_tmBase = 0;

      tm tm = { 0 };

      time_t t = time(nullptr);

      gmtime_r(&t, &tm);

      m_tmBase = -(ToTAI(tm.tm_year + 1900, tm.tm_mon, tm.tm_mday) +
         tm.tm_hour * 3600 + tm.tm_min * 60 + tm.tm_sec);

      // assumes the right time, counting seconds.
      // base may be slightly off if time counts non-leap seconds.
   }

   file_list_parser::~file_list_parser()
   {
   }

   bool file_list_parser::CheckMonth(const char * pszBuffer, const char * pszMonthName) const
   {
      if (tolower(pszBuffer[0]) != pszMonthName[0] ||
         tolower(pszBuffer[1]) != pszMonthName[1] ||
         tolower(pszBuffer[2]) != pszMonthName[2])
         return false;

      return true;
   }

   int file_list_parser::GetMonth(const char * pszBuffer, int iLength) const
   {
      if (iLength == 3)
      {
         for (int i = 0; i < 12; ++i)
         {
            if (CheckMonth(pszBuffer, m_Months[i]))
               return i;
         }
      }
      return -1;
   }

   bool file_list_parser::GetLong(const char * pszLong, int iLength, long& lResult) const
   {
      string strLong(pszLong, iLength);

      lResult = atoi(strLong);

      return true;
   }

   long file_list_parser::ToTAI(long lYear, long lMonth, long lMDay) const
   {
      if (lMonth >= 2)
      {
         lMonth -= 2;
      }
      else
      {
         lMonth += 10;
         --lYear;
      }

      long lResult = (lMDay - 1) * 10 + 5 + 306 * lMonth;
      lResult /= 10;

      if (lResult == 365)
      {
         lYear -= 3;
         lResult = 1460;
      }
      else
         lResult += 365 * (lYear % 4);

      lYear /= 4;

      lResult += 1461 * (lYear % 25);

      lYear /= 25;

      if (lResult == 36524)
      {
         lYear -= 3;
         lResult = 146096;
      }
      else
      {
         lResult += 36524 * (lYear % 4);
      }

      lYear /= 4;
      lResult += 146097 * (lYear - 5);
      lResult += 11017;

      return lResult * 86400;
   }

   long file_list_parser::GetYear(time_t time) const
   {
      long lDay = static_cast<long>(time / 86400L);

      if ((time % 86400L) < 0)
         --lDay;

      lDay -= 11017;

      long lYear = 5 + lDay / 146097;

      lDay = lDay % 146097;
      if (lDay < 0)
      {
         lDay += 146097;
         --lYear;
      }
      lYear *= 4;

      if (lDay == 146096)
      {
         lYear += 3;
         lDay = 36524;
      }
      else
      {
         lYear += lDay / 36524;
         lDay %= 36524;
      }

      lYear *= 25;
      lYear += lDay / 1461;
      lDay %= 1461;
      lYear *= 4;

      if (lDay == 1460)
      {
         lYear += 3;
         lDay = 365;
      }
      else
      {
         lYear += lDay / 365;
         lDay %= 365;
      }

      lDay *= 10;
      if ((lDay + 5) / 306 >= 10)
         ++lYear;

      return lYear;
   }

   /// UNIX ls does not show the year for dates in the last six months.
   /// So we have to guess the year.
   /// Apparently NetWare uses ``twelve months'' instead of ``six months''; ugh.
   /// Some versions of ls also fail to show the year for future dates.
   long file_list_parser::GuessTAI(long lMonth, long lMDay)
   {
      ///////////////////////////*/*/*/*/
      time_t now = ::time(nullptr) - m_tmBase;

      if (m_lCurrentYear == -1)
      {
         m_lCurrentYear = GetYear(now);
      }

      long lTAI = 0;
      for (long lYear = m_lCurrentYear - 1; lYear < m_lCurrentYear + 100; ++lYear)
      {
         lTAI = ToTAI(lYear, lMonth, lMDay);
         if (now - lTAI < 350 * 86400)
            return lTAI;
      }
      return lTAI;
   }

   /// Easily Parsed LIST Format (EPLF)
   /// see http://pobox.com/~djb/proto/eplf.txt
   /// "+i8388621.29609,m824255902,/,\tdev"
   /// "+i8388621.44468,m839956783,r,s10376,\tRFCEPLF"
   bool file_list_parser::IsEPLS(const char * pszLine)
   {
      return pszLine && *pszLine == ('+');
   }

   bool file_list_parser::ParseEPLF(file_status& ftpFileStatus, const char * pszLine, int iLength)
   {
      if (!IsEPLS(pszLine))
         return false;

      long lTemp = 0;
      int i = 1;
      for (int j = 1; j < iLength; ++j)
      {
         if (pszLine[j] == ('\t'))
         {
            ftpFileStatus.m_strName = pszLine + j + 1;
            return true;
         }

         if (pszLine[j] == (','))
         {
            switch (pszLine[i])
            {
            case ('/'):
               ftpFileStatus.m_bCwdEnabled = true;
               break;
            case ('r'):
               ftpFileStatus.m_bRetrEnabled = true;
               break;
            case ('s'):
               ftpFileStatus.m_esize = file_status::size_binary;
               ftpFileStatus.m_filesize = atoi(string(pszLine + i + 1, j - i - 1));
                  ftpFileStatus.m_filesize = -1;
               break;
            case ('m'):
               ftpFileStatus.m_etimeModification = file_status::time_local;
               lTemp = atoi(string(pszLine + i + 1, j - i - 1));
               ftpFileStatus.m_timeModification = m_tmBase + lTemp;
               INSERTIME(ftpFileStatus);
               break;
            case ('i'):
               ftpFileStatus.m_eid = file_status::id_full;
               ftpFileStatus.m_strID = pszLine + i + 1;
               ftpFileStatus.m_strID = ftpFileStatus.m_strID.substr(0, j - i - 1);
            }
            i = j + 1;
         }
      }
      return false;
   }

   /// UNIX-style listing, without inum and without blocks
   /// "-rw-r--r--   1 root     other        531 Jan 29 03:26 README"
   /// "dr-xr-xr-x   2 root     other        512 Apr  8  1994 etc"
   /// "dr-xr-xr-x   2 root     512 Apr  8  1994 etc"
   /// "lrwxrwxrwx   1 root     other          7 Jan 25 00:17 bin -> usr/bin"
   ///
   /// Also produced by Microsoft's FTP servers for Windows:
   /// "----------   1 owner    group         1803128 Jul 10 10:18 ls-lR.Z"
   /// "d---------   1 owner    group               0 May  9 19:45 Softlib"
   ///
   /// Also WFTPD for MSDOS:
   /// "-rwxrwxrwx   1 noone    nogroup      322 Aug 19  1996 message.ftp"
   ///
   /// Also NetWare:
   /// "d [R----F--] supervisor            512       Jan 16 18:53    login"
   /// "- [R----F--] rhesus             214059       Oct 20 15:27    cx.exe"
   //
   /// Also NetPresenz for the Mac:
   /// "-------r--         326  1391972  1392298 Nov 22  1995 MegaPhone.sit"
   /// "drwxrwxr-x               folder        2 May 10  1996 network"
   bool file_list_parser::IsUNIXStyleListing(const char * pszLine)
   {
      if (pszLine == nullptr)
         return false;

      switch (*pszLine)
      {
      case ('b'):
      case ('c'):
      case ('d'):
      case ('l'):
      case ('p'):
      case ('s'):
      case ('-'):
         return true;
      }
      return false;
   }

   bool file_list_parser::ParseUNIXStyleListing(file_status& ftpFileStatus, const char * pszLine, int iLength)
   {
      if (!IsUNIXStyleListing(pszLine))
         return false;

      switch (*pszLine)
      {
      case ('d'): ftpFileStatus.m_bCwdEnabled = true; break;
      case ('-'): ftpFileStatus.m_bRetrEnabled = true; break;
      case ('l'): ftpFileStatus.m_bCwdEnabled = true;
         ftpFileStatus.m_bRetrEnabled = true;
      }

      int  iState = 1;
      int  i = 0;
      long lSize = 0;
      long lYear = 0;
      long lMonth = 0;
      long lMDay = 0;
      long lHour = 0;
      long lMinute = 0;

      for (int j = 1; j < iLength; ++j)
      {
         if (pszLine[j] == (' ') && pszLine[j - 1] != (' '))
         {
            switch (iState)
            {
            case 1: // skipping perm
               ftpFileStatus.m_strAttributes.assign(pszLine + i, j - i);
               iState = 2;
               break;
            case 2: // skipping nlink
               iState = 3;
               ftpFileStatus.m_strLink.assign(pszLine + i, j - i);
               if (j - i == 6 && pszLine[i] == ('f')) // for NetPresenz
                  iState = 4;
               break;
            case 3: // skipping uid
               iState = 4;
               ftpFileStatus.m_strUID.assign(pszLine + i, j - i);
               break;
            case 4: // getting tentative size_i32
               if (!GetLong(pszLine + i, j - i, lSize))
               {
                  lSize = -1;
                  ftpFileStatus.m_strGID.assign(pszLine + i, j - i);
               }
               iState = 5;
               break;
            case 5: // searching for month, otherwise getting tentative size_i32
               lMonth = GetMonth(pszLine + i, j - i);
               if (lMonth >= 0)
                  iState = 6;
               else
               {
                  if (!GetLong(pszLine + i, j - i, lSize))
                     lSize = -1;
               }
               break;
            case 6: // have size_i32 and month
               GetLong(pszLine + i, j - i, lMDay);
               iState = 7;
               break;
            case 7: // have size, month, mday
               if (j - i == 4 && pszLine[i + 1] == (':'))
               {
                  GetLong(pszLine + i, 1, lHour);
                  GetLong(pszLine + i + 2, 2, lMinute);
                  ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
                  ftpFileStatus.m_timeModification = m_tmBase + GuessTAI(lMonth, lMDay) + lHour * 3600 + lMinute * 60;
                  INSERTIME(ftpFileStatus);
               }
               else if (j - i == 5 && pszLine[i + 2] == (':'))
               {
                  GetLong(pszLine + i, 2, lHour);
                  GetLong(pszLine + i + 3, 2, lMinute);
                  ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
                  ftpFileStatus.m_timeModification = m_tmBase + GuessTAI(lMonth, lMDay) + lHour * 3600 + lMinute * 60;
                  INSERTIME(ftpFileStatus);
               }
               else if (j - i >= 4)
               {
                  GetLong(pszLine + i, j - i, lYear);
                  ftpFileStatus.m_etimeModification = file_status::time_remote_day;
                  ftpFileStatus.m_timeModification = m_tmBase + file_list_parser::ToTAI(lYear, lMonth, lMDay);
                  INSERTIME(ftpFileStatus);
               }
               else
                  return false;

               ftpFileStatus.m_strName = pszLine + j + 1;
               iState = 8;
               break;
            case 8: // twiddling thumbs
               break;
            }

            i = j + 1;
            while (i < iLength && pszLine[i] == (' '))
               ++i;
         }
      }

      if (iState != 8)
         return false;

      ftpFileStatus.m_filesize = lSize;
      ftpFileStatus.m_esize = file_status::size_binary;

      // handle links
      if (pszLine[0] == ('l'))
      {
         strsize pos = ftpFileStatus.m_strName.find((" -> "));
         if (pos>= 0)
            ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(0, pos);
      }

      // eliminate extra NetWare spaces
      if (pszLine[1] == (' ') || pszLine[1] == ('['))
      {
         if (ftpFileStatus.m_strName.length() > 3 && ftpFileStatus.m_strName.substr(0, 3) == ("   "))
            ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(3);
      }

      return true;
   }

   /// MultiNet (some spaces removed from examples)
   /// "00README.TXT;1      2 30-DEC-1996 17:44 [SYSTEM] (RWED,RWED,RE,RE)"
   /// "CORE.DIR;1          1  8-SEP-1996 16:09 [SYSTEM] (RWE,RWE,RE,RE)"
   /// and non-MutliNet VMS:
   /// "CII-MANUAL.TEX;1  213/216  29-JAN-1996 03:33:12  [ANONYMOU,ANONYMOUS]   (RWED,RWED,,)"
   bool file_list_parser::IsMultiNetListing(const char * pszLine)
   {
      return pszLine && strchr(pszLine, ';') != nullptr;
   }

   bool file_list_parser::ParseMultiNetListing(file_status& ftpFileStatus, const char * pszLine, int iLength)
   {
      if (!IsMultiNetListing(pszLine))
         return false;

      // name lookup of `i' changed for new ISO `for' scoping
      int i = 0;
      for (; i < iLength; ++i)
         if (pszLine[i] == (';'))
            break;

      if (i < iLength)
      {
         ftpFileStatus.m_strName = pszLine;
         ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(0, i);
         if (i > 4 && ansi_count_compare(pszLine + i - 4, (".DIR"), 4) == 0)
         {
            ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(0, ftpFileStatus.m_strName.length() - 4);
            ftpFileStatus.m_bCwdEnabled = true;
         }
         else
            ftpFileStatus.m_bRetrEnabled = true;

         while (pszLine[i] != (' ')) if (++i == iLength) return false;
         while (pszLine[i] == (' ')) if (++i == iLength) return false;
         while (pszLine[i] != (' ')) if (++i == iLength) return false;
         while (pszLine[i] == (' ')) if (++i == iLength) return false;

         int j = i;
         while (pszLine[j] != ('-')) if (++j == iLength) return false;
         long lMDay = 0;
         GetLong(pszLine + i, j - i, lMDay);

         while (pszLine[j] == ('-')) if (++j == iLength) return false;
         i = j;
         while (pszLine[j] != ('-')) if (++j == iLength) return false;
         long lMonth = GetMonth(pszLine + i, j - i);
         if (lMonth < 0) return false;

         while (pszLine[j] == ('-')) if (++j == iLength) return false;
         i = j;
         while (pszLine[j] != (' ')) if (++j == iLength) return false;
         long lYear = 0;
         GetLong(pszLine + i, j - i, lYear);

         while (pszLine[j] == (' ')) if (++j == iLength) return false;
         i = j;
         while (pszLine[j] != (':')) if (++j == iLength) return false;
         long lHour = 0;
         GetLong(pszLine + i, j - i, lHour);

         while (pszLine[j] == (':')) if (++j == iLength) return false;
         i = j;
         while (pszLine[j] != (':') && pszLine[j] != (' ')) if (++j == iLength) return false;
         long lMinute = 0;
         GetLong(pszLine + i, j - i, lMinute);

         ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
         ftpFileStatus.m_timeModification = m_tmBase + file_list_parser::ToTAI(lYear, lMonth, lMDay) + lHour * 3600 + lMinute * 60;
         INSERTIME(ftpFileStatus);
      }

      return true;
   }

   /// MSDOS format
   /// 04-27-00  09:09PM       <DIR>          licensed
   /// 07-18-00  10:16AM       <DIR>          pub
   /// 04-14-00  03:47PM                  589 readme.htm
   bool file_list_parser::IsMSDOSListing(const char * pszLine)
   {
      return pszLine && ansi_char_is_digit(pszLine[0]);
   }

   bool file_list_parser::ParseMSDOSListing(file_status& ftpFileStatus, const char * pszLine, int iLength)
   {
      if (!IsMSDOSListing(pszLine))
         return false;

      int i = 0;
      int j = 0;
      while (pszLine[j] != ('-')) if (++j == iLength) return false;
      long lMonth = 0;
      GetLong(pszLine + i, j - i, lMonth); //+# -1

      while (pszLine[j] == ('-')) if (++j == iLength) return false;
      i = j;
      while (pszLine[j] != ('-')) if (++j == iLength) return false;
      long lMDay = 0;
      GetLong(pszLine + i, j - i, lMDay);

      while (pszLine[j] == ('-')) if (++j == iLength) return false;
      i = j;
      while (pszLine[j] != (' ')) if (++j == iLength) return false;
      long lYear = 0;
      GetLong(pszLine + i, j - i, lYear);

      if (lYear < 50)
         lYear += 2000;

      if (lYear < 1000)
         lYear += 1900;

      while (pszLine[j] == (' ')) if (++j == iLength) return false;
      i = j;
      while (pszLine[j] != (':')) if (++j == iLength) return false;
      long lHour = 0;
      GetLong(pszLine + i, j - i, lHour);

      while (pszLine[j] == (':')) if (++j == iLength) return false;
      i = j;
      while ((pszLine[j] != ('A')) && (pszLine[j] != ('P'))) if (++j == iLength) return false;
      long lMinute = 0;
      GetLong(pszLine + i, j - i, lMinute);

      if (lHour == 12)
         lHour = 0;

      if (pszLine[j] == ('A')) if (++j == iLength) return false;
      if (pszLine[j] == ('P')) { lHour += 12; if (++j == iLength) return false; }
      if (pszLine[j] == ('M')) if (++j == iLength) return false;

      while (pszLine[j] == (' ')) if (++j == iLength) return false;
      if (pszLine[j] == ('<'))
      {
         ftpFileStatus.m_bCwdEnabled = true;
         while (pszLine[j] != (' ')) if (++j == iLength) return false;
      }
      else
      {
         i = j;
         while (pszLine[j] != (' ')) if (++j == iLength) return false;
         ftpFileStatus.m_filesize = atoi(string(pszLine + i, j - i));
            ftpFileStatus.m_filesize = -1;
         ftpFileStatus.m_esize = file_status::size_binary;
         ftpFileStatus.m_bRetrEnabled = true;
      }
      while (pszLine[j] == (' ')) if (++j == iLength) return false;

      ftpFileStatus.m_strName = pszLine + j;

      ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
      ftpFileStatus.m_timeModification = m_tmBase + file_list_parser::ToTAI(lYear, lMonth, lMDay) + lHour * 3600 + lMinute * 60;
      INSERTIME(ftpFileStatus);

      return true;
   }

   bool file_list_parser::Parse(file_status& ftpFileStatus, const string& strLineToParse)
   {
      ftpFileStatus.reset();
      const char *   pszLine = strLineToParse.c_str();
      const int iLength = static_cast<int>(strLineToParse.length());

      if (iLength < 2) // an empty name in EPLF, with no info, could be 2 chars
         return false;

      if (IsEPLS(pszLine))
      {
         if (!ParseEPLF(ftpFileStatus, pszLine, iLength))
            return false;
      }
      else if (IsUNIXStyleListing(pszLine))
      {
         if (!ParseUNIXStyleListing(ftpFileStatus, pszLine, iLength))
            return false;
      }
      else if (IsMultiNetListing(pszLine))
      {
         if (!ParseMultiNetListing(ftpFileStatus, pszLine, iLength))
            return false;
      }
      else if (IsMSDOSListing(pszLine))
      {
         if (!ParseMSDOSListing(ftpFileStatus, pszLine, iLength))
            return false;
      }
      else
      {
         // Some useless lines, safely ignored:
         // "Total of 11 Files, 10966 Blocks." (VMS)
         // "total 14786" (UNIX)
         // "DISK$ANONFTP:[ANONYMOUS]" (VMS)
         // "Directory DISK$PCSA:[ANONYM]" (VMS)
         return false;
      }

      return true;
   }


} // namespace ftp



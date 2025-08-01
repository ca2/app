////////////////////////////////////////////////////////////////////////////////
//
// Code taken from D. J. Bernstein (C ==> C++)
//
// ftpparse.c, ftpparse.h: library for parsing FTP LIST responses
// 20001223
// D. J. Bernstein, djb@color32.yp.to
// http://color32.yp.to/ftpparse.html
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
#include "file_list_parser.h"
#include "file_status.h"
#include "core/platform/system.h"
#include <time.h>
#include "acme/operating_system/ansi/datetime_c.h"


namespace ftp
{



//#ifndef system()->InsertTime
  
//#define system()->InsertTime(ftpFileStatus) InsertTime(ftpFileStatus);
//#endif

   const_char_pointer file_list_parser::m_Months[12] = {
      ("jan"),("feb"),("mar"),("apr"),("may"),("jun"),
      ("jul"),("aug"),("sep"),("oct"),("nov"),("dec")
   };


   file_list_parser::file_list_parser() :
      m_lCurrentYear(-1)
   {

      m_tmBase.Null();

      ::earth::time time(now_t{});

      //tm tm = { 0 };

      //posix_time t = time(nullptr);

      //gmtime_r(&t, &tm);

      m_tmBase = posix_time{ posix_time_t{},-(ToTAI(time.year(), time.month(), time.day()) +
         time.hour() * 3600 + time.minute() * 60 + time.second()) };

      // assumes the right time, counting seconds.
      // base may be slightly off if time counts non-leap seconds.
   }

   file_list_parser::~file_list_parser()
   {

   }


   bool file_list_parser::CheckMonth(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrMonthName) const
   {
      if (character_tolower(scopedstr.begin()[0]) != scopedstrMonthName[0] ||
         character_tolower(scopedstr.begin()[1]) != scopedstrMonthName[1] ||
         character_tolower(scopedstr.begin()[2]) != scopedstrMonthName[2])
         return false;

      return true;
   }


   int file_list_parser::GetMonth(const ::scoped_string & scopedstr) const
   {

      if (scopedstr.size() == 3)
      {

         for (int i = 0; i < 12; ++i)
         {

            if (CheckMonth(scopedstr, m_Months[i]))
            {

               return i;

            }

         }

      }
      
      return -1;

   }


   bool file_list_parser::GetLong(const ::scoped_string & scopedstrLong, long& lResult) const
   {

      string strLong(scopedstrLong);

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

   long file_list_parser::GetYear(posix_time time) const
   {
      long lDay = static_cast<long>(time.m_iSecond / 86400L);

      if ((time.m_iSecond % 86400L) < 0)
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
      auto now = m_tmBase.elapsed();

      if (m_lCurrentYear == -1)
      {
         m_lCurrentYear = GetYear(now);
      }

      long lTAI = 0;
      for (long lYear = m_lCurrentYear - 1; lYear < m_lCurrentYear + 100; ++lYear)
      {
         lTAI = ToTAI(lYear, lMonth, lMDay);
         if (now.m_iSecond - lTAI < 350 * 86400)
            return lTAI;
      }
      return lTAI;
   }

   /// Easily Parsed LIST Format (EPLF)
   /// see http://pobox.com/~djb/proto/eplf.txt
   /// "+i8388621.29609,m824255902,/,\tdev"
   /// "+i8388621.44468,m839956783,r,s10376,\tRFCEPLF"
   bool file_list_parser::IsEPLS(const ::scoped_string & scopedstrLine)
   {
      
      return scopedstrLine.begin() && *scopedstrLine.begin() == ('+');

   }


   bool file_list_parser::ParseEPLF(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine)
   {

      if (!IsEPLS(scopedstrLine))
      {

         return false;

      }

      long lTemp = 0;
      int i = 1;
      for (int j = 1; j < scopedstrLine.size(); ++j)
      {
         
         if (scopedstrLine.begin()[j] == ('\t'))
         {

            ftpFileStatus.m_strName = scopedstrLine.begin() + j + 1;

            return true;

         }

         if (scopedstrLine.begin()[j] == (','))
         {
            switch (scopedstrLine.begin()[i])
            {
            case ('/'):
               ftpFileStatus.m_bCwdEnabled = true;
               break;
            case ('r'):
               ftpFileStatus.m_bRetrEnabled = true;
               break;
            case ('s'):
               ftpFileStatus.m_esize = file_status::size_binary;
               ftpFileStatus.m_filesize = atoi(string(scopedstrLine.begin() + i + 1, j - i - 1));
                  ftpFileStatus.m_filesize = -1;
               break;
            case ('m'):
               ftpFileStatus.m_etimeModification = file_status::time_local;
               lTemp = atoi(string(scopedstrLine.begin() + i + 1, j - i - 1));
               ftpFileStatus.m_timeModification.m_iSecond = m_tmBase.m_iSecond + lTemp;
               system()->InsertTime(ftpFileStatus);
               break;
            case ('i'):
               ftpFileStatus.m_eid = file_status::id_full;
               ftpFileStatus.m_strID = scopedstrLine.begin() + i + 1;
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
   bool file_list_parser::IsUNIXStyleListing(const ::scoped_string & scopedstrLine)
   {
      if (scopedstrLine.begin() == nullptr)
         return false;

      switch (*scopedstrLine.begin())
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


   bool file_list_parser::ParseUNIXStyleListing(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine)
   {
      if (!IsUNIXStyleListing(scopedstrLine.begin()))
         return false;

      switch (*scopedstrLine.begin())
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

      for (int j = 1; j < scopedstrLine.size(); ++j)
      {
         if (scopedstrLine.begin()[j] == (' ') && scopedstrLine.begin()[j - 1] != (' '))
         {
            switch (iState)
            {
            case 1: // skipping perm
               ftpFileStatus.m_strAttributes.assign_range(scopedstrLine(i, j - i));
               iState = 2;
               break;
            case 2: // skipping nlink
               iState = 3;
               ftpFileStatus.m_strLink.assign_range(scopedstrLine(i, j - i));
               if (j - i == 6 && scopedstrLine.begin()[i] == ('f')) // for NetPresenz
                  iState = 4;
               break;
            case 3: // skipping uid
               iState = 4;
               ftpFileStatus.m_strUID.assign_range(scopedstrLine(i, j - i));
               break;
            case 4: // getting tentative int_size
               if (!GetLong(scopedstrLine(i, j - i), lSize))
               {
                  lSize = -1;
                  ftpFileStatus.m_strGID.assign_range(scopedstrLine(i, j - i));
               }
               iState = 5;
               break;
            case 5: // searching for month, otherwise getting tentative int_size
               lMonth = GetMonth(scopedstrLine(i, j - i));
               if (lMonth >= 0)
                  iState = 6;
               else
               {
                  if (!GetLong(scopedstrLine(i, j - i), lSize))
                     lSize = -1;
               }
               break;
            case 6: // have int_size and month
               GetLong(scopedstrLine(i, j - i), lMDay);
               iState = 7;
               break;
            case 7: // have size, month, mday
               if (j - i == 4 && scopedstrLine.begin()[i + 1] == (':'))
               {
                  GetLong(scopedstrLine(i, 1), lHour);
                  GetLong(scopedstrLine(i + 2, 2), lMinute);
                  ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
                  ftpFileStatus.m_timeModification.m_iSecond = m_tmBase.m_iSecond + GuessTAI(lMonth, lMDay) + lHour * 3600 + lMinute * 60;
                  system()->InsertTime(ftpFileStatus);
               }
               else if (j - i == 5 && scopedstrLine.begin()[i + 2] == (':'))
               {
                  GetLong(scopedstrLine(i, 2), lHour);
                  GetLong(scopedstrLine(i + 3, 2), lMinute);
                  ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
                  ftpFileStatus.m_timeModification.m_iSecond = m_tmBase.m_iSecond +GuessTAI(lMonth, lMDay) + lHour * 3600 + lMinute * 60;
                  system()->InsertTime(ftpFileStatus);
               }
               else if (j - i >= 4)
               {
                  GetLong(scopedstrLine(i, j - i), lYear);
                  ftpFileStatus.m_etimeModification = file_status::time_remote_day;
                  ftpFileStatus.m_timeModification.m_iSecond = m_tmBase.m_iSecond + file_list_parser::ToTAI(lYear, lMonth, lMDay);
                  system()->InsertTime(ftpFileStatus);
               }
               else
                  return false;

               ftpFileStatus.m_strName = scopedstrLine.begin() + j + 1;
               iState = 8;
               break;
            case 8: // twiddling thumbs
               break;
            }

            i = j + 1;
            while (i < scopedstrLine.size() && scopedstrLine.begin()[i] == (' '))
               ++i;
         }
      }

      if (iState != 8)
         return false;

      ftpFileStatus.m_filesize = lSize;
      ftpFileStatus.m_esize = file_status::size_binary;

      // handle links
      if (scopedstrLine.begin()[0] == ('l'))
      {
         auto pos = ftpFileStatus.m_strName.find_index((" -> "));
         if (pos>= 0)
            ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(0, pos);
      }

      // eliminate extra NetWare spaces
      if (scopedstrLine.begin()[1] == (' ') || scopedstrLine.begin()[1] == ('['))
      {
         if (ftpFileStatus.m_strName.length() > 3 && ftpFileStatus.m_strName.substr(0, 3) == ("   "))
            ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(3);
      }

      return true;
   }

   /// MultiNet (some spaces erased from examples)
   /// "00README.TXT;1      2 30-DEC-1996 17:44 [SYSTEM] (RWED,RWED,RE,RE)"
   /// "CORE.DIR;1          1  8-SEP-1996 16:09 [SYSTEM] (RWE,RWE,RE,RE)"
   /// and non-MutliNet VMS:
   /// "CII-MANUAL.TEX;1  213/216  29-JAN-1996 03:33:12  [ANONYMOU,ANONYMOUS]   (RWED,RWED,,)"
   bool file_list_parser::IsMultiNetListing(const ::scoped_string & scopedstrLine)
   {
      return scopedstrLine.begin() && ansi_chr(scopedstrLine.begin(), ';') != nullptr;
   }

   bool file_list_parser::ParseMultiNetListing(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine)
   {
      if (!IsMultiNetListing(scopedstrLine.begin()))
         return false;

      // name lookup of `i' changed for ___new ISO `for' scoping
      int i = 0;
      for (; i < scopedstrLine.size(); ++i)
         if (scopedstrLine.begin()[i] == (';'))
            break;

      if (i < scopedstrLine.size())
      {
         ftpFileStatus.m_strName = scopedstrLine.begin();
         ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(0, i);
         if (i > 4 && ansi_count_compare(scopedstrLine.begin() + i - 4, (".DIR"), 4) == 0)
         {
            ftpFileStatus.m_strName = ftpFileStatus.m_strName.substr(0, ftpFileStatus.m_strName.length() - 4);
            ftpFileStatus.m_bCwdEnabled = true;
         }
         else
            ftpFileStatus.m_bRetrEnabled = true;

         while (scopedstrLine.begin()[i] != (' ')) if (++i == scopedstrLine.size()) return false;
         while (scopedstrLine.begin()[i] == (' ')) if (++i == scopedstrLine.size()) return false;
         while (scopedstrLine.begin()[i] != (' ')) if (++i == scopedstrLine.size()) return false;
         while (scopedstrLine.begin()[i] == (' ')) if (++i == scopedstrLine.size()) return false;

         int j = i;
         while (scopedstrLine.begin()[j] != ('-')) if (++j == scopedstrLine.size()) return false;
         long lMDay = 0;
         GetLong(scopedstrLine(i, j - i), lMDay);

         while (scopedstrLine.begin()[j] == ('-')) if (++j == scopedstrLine.size()) return false;
         i = j;
         while (scopedstrLine.begin()[j] != ('-')) if (++j == scopedstrLine.size()) return false;
         long lMonth = GetMonth(scopedstrLine(i, j - i));
         if (lMonth < 0) return false;

         while (scopedstrLine.begin()[j] == ('-')) if (++j == scopedstrLine.size()) return false;
         i = j;
         while (scopedstrLine.begin()[j] != (' ')) if (++j == scopedstrLine.size()) return false;
         long lYear = 0;
         GetLong(scopedstrLine(i, j - i), lYear);

         while (scopedstrLine.begin()[j] == (' ')) if (++j == scopedstrLine.size()) return false;
         i = j;
         while (scopedstrLine.begin()[j] != (':')) if (++j == scopedstrLine.size()) return false;
         long lHour = 0;
         GetLong(scopedstrLine(i, j - i), lHour);

         while (scopedstrLine.begin()[j] == (':')) if (++j == scopedstrLine.size()) return false;
         i = j;
         while (scopedstrLine.begin()[j] != (':') && scopedstrLine.begin()[j] != (' ')) if (++j == scopedstrLine.size()) return false;
         long lMinute = 0;
         GetLong(scopedstrLine(i, j - i), lMinute);

         ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
         ftpFileStatus.m_timeModification.m_iSecond = m_tmBase.m_iSecond + file_list_parser::ToTAI(lYear, lMonth, lMDay) + lHour * 3600 + lMinute * 60;
         system()->InsertTime(ftpFileStatus);
      }

      return true;
   }

   /// MSDOS format
   /// 04-27-00  09:09PM       <DIR>          licensed
   /// 07-18-00  10:16AM       <DIR>          pub
   /// 04-14-00  03:47PM                  589 readme.htm
   bool file_list_parser::IsMSDOSListing(const ::scoped_string & scopedstrLine)
   {
      return scopedstrLine && ansi_char_isdigit(scopedstrLine[0]);
   }

   bool file_list_parser::ParseMSDOSListing(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine)
   {
      if (!IsMSDOSListing(scopedstrLine))
         return false;

      int i = 0;
      int j = 0;
      while (scopedstrLine.begin()[j] != ('-')) if (++j == scopedstrLine.size()) return false;
      long lMonth = 0;
      GetLong(scopedstrLine(i, j - i), lMonth); //+# -1

      while (scopedstrLine.begin()[j] == ('-')) if (++j == scopedstrLine.size()) return false;
      i = j;
      while (scopedstrLine.begin()[j] != ('-')) if (++j == scopedstrLine.size()) return false;
      long lMDay = 0;
      GetLong(scopedstrLine(i, j - i), lMDay);

      while (scopedstrLine.begin()[j] == ('-')) if (++j == scopedstrLine.size()) return false;
      i = j;
      while (scopedstrLine.begin()[j] != (' ')) if (++j == scopedstrLine.size()) return false;
      long lYear = 0;
      GetLong(scopedstrLine(i, j - i), lYear);

      if (lYear < 50)
         lYear += 2000;

      if (lYear < 1000)
         lYear += 1900;

      while (scopedstrLine.begin()[j] == (' ')) if (++j == scopedstrLine.size()) return false;
      i = j;
      while (scopedstrLine.begin()[j] != (':')) if (++j == scopedstrLine.size()) return false;
      long lHour = 0;
      GetLong(scopedstrLine(i, j - i), lHour);

      while (scopedstrLine.begin()[j] == (':')) if (++j == scopedstrLine.size()) return false;
      i = j;
      while ((scopedstrLine.begin()[j] != ('A')) && (scopedstrLine.begin()[j] != ('P'))) if (++j == scopedstrLine.size()) return false;
      long lMinute = 0;
      GetLong(scopedstrLine(i, j - i), lMinute);

      if (lHour == 12)
         lHour = 0;

      if (scopedstrLine.begin()[j] == ('A')) if (++j == scopedstrLine.size()) return false;
      if (scopedstrLine.begin()[j] == ('P')) { lHour += 12; if (++j == scopedstrLine.size()) return false; }
      if (scopedstrLine.begin()[j] == ('M')) if (++j == scopedstrLine.size()) return false;

      while (scopedstrLine.begin()[j] == (' ')) if (++j == scopedstrLine.size()) return false;
      if (scopedstrLine.begin()[j] == ('<'))
      {
         ftpFileStatus.m_bCwdEnabled = true;
         while (scopedstrLine.begin()[j] != (' ')) if (++j == scopedstrLine.size()) return false;
      }
      else
      {
         i = j;
         while (scopedstrLine.begin()[j] != (' ')) if (++j == scopedstrLine.size()) return false;
         ftpFileStatus.m_filesize = atoi(string(scopedstrLine(i, j - i)));
            ftpFileStatus.m_filesize = -1;
         ftpFileStatus.m_esize = file_status::size_binary;
         ftpFileStatus.m_bRetrEnabled = true;
      }
      while (scopedstrLine.begin()[j] == (' ')) if (++j == scopedstrLine.size()) return false;

      ftpFileStatus.m_strName = scopedstrLine.begin() + j;

      ftpFileStatus.m_etimeModification = file_status::time_remote_minute;
      ftpFileStatus.m_timeModification.m_iSecond = m_tmBase.m_iSecond + file_list_parser::ToTAI(lYear, lMonth, lMDay) + lHour * 3600 + lMinute * 60;
      system()->InsertTime(ftpFileStatus);

      return true;
   }

   bool file_list_parser::Parse(file_status& ftpFileStatus, const ::scoped_string & scopedstrLineToParse)
   {
      ftpFileStatus.reset();
      auto scopedstrLine = scopedstrLineToParse();
      auto iLineSize = scopedstrLine.size();

      if (iLineSize < 2) // an empty name in EPLF, with no info, could be 2 chars
         return false;

      if (IsEPLS(scopedstrLine))
      {
         if (!ParseEPLF(ftpFileStatus, scopedstrLine.begin()))
            return false;
      }
      else if (IsUNIXStyleListing(scopedstrLine.begin()))
      {
         if (!ParseUNIXStyleListing(ftpFileStatus, scopedstrLine.begin()))
            return false;
      }
      else if (IsMultiNetListing(scopedstrLine.begin()))
      {
         if (!ParseMultiNetListing(ftpFileStatus, scopedstrLine.begin()))
            return false;
      }
      else if (IsMSDOSListing(scopedstrLine.begin()))
      {
         if (!ParseMSDOSListing(ftpFileStatus, scopedstrLine.begin()))
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



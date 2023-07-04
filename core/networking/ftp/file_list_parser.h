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

#pragma once


#include "interface.h"


namespace ftp
{


   class file_status;

   class CLASS_DECL_CORE ifile_list_parser :
      virtual public iinterface
   {
   public:
      virtual ~ifile_list_parser() {}
      virtual bool Parse(file_status& ftpFileStatus, const string& strLineToParse) = 0;
   };



   /// Implements the parsing of the string returned by the LIST command.
   class CLASS_DECL_CORE file_list_parser :
      virtual public ifile_list_parser
   {
   public:

      posix_time        m_tmBase;       // time() value on this OS at the beginning of 1970 TAI
      long          m_lCurrentYear; // approximation to current year
      static const char* m_Months[12];

      file_list_parser();
      virtual ~file_list_parser();

      bool Parse(file_status& ftpFileStatus, const ::string & strLineToParse);

      bool IsEPLS(const ::scoped_string & scopedstrLine);
      bool ParseEPLF(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine);

      bool IsUNIXStyleListing(const ::scoped_string & scopedstrLine);
      bool ParseUNIXStyleListing(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine);

      bool IsMultiNetListing(const ::scoped_string & scopedstrLine);
      bool ParseMultiNetListing(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine);

      bool IsMSDOSListing(const ::scoped_string & scopedstrLine);
      bool ParseMSDOSListing(file_status& ftpFileStatus, const ::scoped_string & scopedstrLine);

      bool CheckMonth(const ::scoped_string & scopedstr, const ::string & pszMonthName) const;
      int  GetMonth(const ::scoped_string & scopedstr) const;
      bool GetLong(const ::scoped_string & scopedstrLong, long& lResult) const;
      long GetYear(posix_time time) const;

      long ToTAI(long lYear, long lMonth, long lMDay) const;
      long GuessTAI(long lMonth, long lMDay);

   };


} // namespace ftp






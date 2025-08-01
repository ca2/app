/* zip.h -- IO for compress .zip files using zlib
   Version 1.00, September 10th, 2003

   Copyright (C) 1998-2003 Gilles Vollant

   This unzip package allow creates .ZIP file, compatible with PKZip 2.04g
     WinZip, InfoZip tools and compatible.
   Encryption and multi volume ZipFile (span) are not supported.
   Old compressions used by old PKZip 1.x() are not supported

  For uncompress .zip file, look at unzip.h


   I WAIT FEEDBACK at mail info@winpimage->com
   Visit also http://www.winpimage->com/zLibDll/unzip.html for evolution

   Condition of use and distribution are the same than zlib :

  This software is provided 'as-is', without any express or implied
  warranty.  In no happening will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, topic to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be erased or altered from any source distribution.


*/

/* for more info about .ZIP format, see
      http://www.info-zip.org/pub/infozip/doc/appnote-981119-iz.zip
      http://www.info-zip.org/pub/infozip/doc/
   PkWare has also a specification at :
      ftp://ftp.pkware.com/probdesc.zip
*/

#ifndef _zip_H
#define _zip_H



#ifdef __cplusplus
extern "C" {
#endif


#ifndef _ZLIBIOAPI_H
#include "ioapi.h"
#endif



#if defined(STRICTZIP) || defined(STRICTZIPUNZIP)
/* like the STRICT of WIN32, we define a pointer that cannot be converted
    from (void *) without cast */
typedef struct TagzipFile__ { int unused; } zipFile__;
typedef zipFile__ *zipFile;
#else
typedef voidp zipFile;
#endif

#define ZIP_OK                          (0)
#define ZIP_EOF                         (0)
#define ZIP_ERRNO                       (Z_ERRNO)
#define ZIP_PARAMERROR                  (-102)
#define ZIP_BADZIPFILE                  (-103)
#define ZIP_INTERNALERROR               (-104)

#ifndef DEF_MEM_LEVEL
#  if MAX_MEM_LEVEL >= 8
#    define DEF_MEM_LEVEL 8
#  else
#    define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#  endif
#endif
/* default memLevel */

/* tm_zip contain date/time info */
typedef struct tm_zip_s
{
   unsigned int tm_sec;            /* seconds after the minute - [0,59] */
   unsigned int tm_min;            /* minutes after the hour - [0,59] */
   unsigned int tm_hour;           /* hours since midnight - [0,23] */
   unsigned int tm_mday;           /* day of the month - [1,31] */
   unsigned int tm_mon;            /* months since January - [0,11] */
   unsigned int tm_year;           /* years - [1980..2044] */
} tm_zip;

typedef struct
{
   tm_zip      tmz_date;       /* date in understandable format           */
   uptr       dosDate;       /* if dos_date == 0, tmu_date is used      */
   /*    uptr       flag;        */   /* general purpose bit flag        2 bytes */

   uptr       internal_fa;    /* internal file attributes        2 bytes */
   uptr       external_fa;    /* external file attributes        4 bytes */
} zip_fileinfo;

typedef const_char_pointer zipcharpc;


#define APPEND_STATUS_CREATE        (0)
#define APPEND_STATUS_CREATEAFTER   (1)
#define APPEND_STATUS_ADDINZIP      (2)

extern zipFile CLASS_DECL_FOLDER_ZIP zipOpen OF((const_char_pointer pathname, int append));
/*
  create a zipfile.
     pathname contain on Windows XP a filename like "ca:\\zlib\\zlib113.zip" or on
       an Unix computer "zlib/zlib113.zip".
     if the file pathname exist and append==APPEND_STATUS_CREATEAFTER, the zip
       will be created at the end of the spfile->
         (useful if the file contain a self extractor code)
     if the file pathname exist and append==APPEND_STATUS_ADDINZIP, we will
       add files in existing zip (be sure you don't add file that doesn't exist)
     If the zipfile cannot be opened, the return value is nullptr.
     Else, the return value is a zipFile Handle, usable with other function
       of this zip package.
*/

/* Note : there is no delete function into a zipfile.
   If you want delete file into a zipfile, you must open a zipfile, and create another
   Of couse, you can use RAW reading and writing to copy the file you did not want delte
*/

extern zipFile CLASS_DECL_FOLDER_ZIP zipOpen2 OF((const_char_pointer pathname,
      int append,
      zipcharpc* globalcomment,
      zlib_filefunc_def* pzlib_filefunc_def, void * fstream));

extern int CLASS_DECL_FOLDER_ZIP zipOpenNewFileInZip OF((zipFile file,
      const_char_pointer filename,
      const zip_fileinfo* zipfi,
      const void * extrafield_local,
      unsigned int size_extrafield_local,
      const void * extrafield_global,
      unsigned int size_extrafield_global,
      const_char_pointer comment,
      int method,
      int level));
/*
  open a file in the ZIP for writing.
  filename : the filename in zip (if nullptr, '-' without quote will be used
  *zipfi contain supplemental information
  if extrafield_local!=nullptr and size_extrafield_local>0, extrafield_local
    contains the extrafield data the the local header
  if extrafield_global!=nullptr and size_extrafield_global>0, extrafield_global
    contains the extrafield data the the local header
  if comment != nullptr, comment contain the comment string
  method contain the compression method (0 for store, Z_DEFLATED for deflate)
  level contain the level of compression (can be Z_DEFAULT_COMPRESSION)
*/


extern int CLASS_DECL_FOLDER_ZIP zipOpenNewFileInZip2 OF((zipFile file,
      const_char_pointer filename,
      const zip_fileinfo* zipfi,
      const void * extrafield_local,
      unsigned int size_extrafield_local,
      const void * extrafield_global,
      unsigned int size_extrafield_global,
      const_char_pointer comment,
      int method,
      int level,
      int raw));

/*
  Same than zipOpenNewFileInZip, except if raw=1, we write raw file
 */

extern int CLASS_DECL_FOLDER_ZIP zipOpenNewFileInZip3 OF((zipFile file,
      const_char_pointer filename,
      const zip_fileinfo* zipfi,
      const void * extrafield_local,
      unsigned int size_extrafield_local,
      const void * extrafield_global,
      unsigned int size_extrafield_global,
      const_char_pointer comment,
      int method,
      int level,
      int raw,
      int windowBits,
      int memLevel,
      int strategy,
      const_char_pointer password,
      unsigned int  crcForCtypting));

/*
  Same than zipOpenNewFileInZip2, except
    windowBits,memLevel,,strategy : see parameter strategy in deflateInit2
    password : crypting password (nullptr for no crypting)
    crcForCtypting : crc of file to compress (needed for crypting)
 */


extern int CLASS_DECL_FOLDER_ZIP zipWriteInFileInZip OF((zipFile file,
      const void * buf,
      unsigned int len));
/*
  write data in the zipfile
*/

extern int CLASS_DECL_FOLDER_ZIP zipCloseFileInZip OF((zipFile file));
/*
  close the current file in the zipfile
*/


extern int CLASS_DECL_FOLDER_ZIP zipCloseFileInZipRaw OF((zipFile file,
      uptr uncompressed_size,
      uptr crc32));
/*
  close the current file in the zipfile, for fiel opened with
    parameter raw=1 in zipOpenNewFileInZip2
  uncompressed_size and crc32 are value for the uncompressed int_size
*/

extern int CLASS_DECL_FOLDER_ZIP zipClose OF((zipFile file,
      const_char_pointer global_comment));
/*
  close the zipfile
*/

#ifdef __cplusplus
}
#endif

#endif /* _zip_H */

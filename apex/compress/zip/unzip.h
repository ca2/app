/* unzip.h -- IO for uncompress .zip files using zlib
   Version 1.00, September 10th, 2003

   Copyright (C) 1998-2003 Gilles Vollant

   This unzip package allow extract file from .ZIP file, compatible with PKZip 2.04g
     WinZip, InfoZip tools and compatible.
   Encryption and multi volume ZipFile (span) are not supported.
   Old compressions used by old PKZip 1.x are not supported


   I WAIT FEEDBACK at mail info@winpimage->com
   Visit also http://www.winpimage->com/zLibDll/unzip.htm for evolution

   Condition of use and distribution are the same than zlib :

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.


*/

/* for more info about .ZIP format, see
      http://www.info-zip.org/pub/infozip/doc/appnote-981119-iz.zip
      http://www.info-zip.org/pub/infozip/doc/
   PkWare has also a specification at :
      ftp://ftp.pkware.com/probdesc.zip
*/

#ifndef _unz_H
#define _unz_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ZLIB_H
#include "zlib.h"
#endif

#ifndef _ZLIBIOAPI_H
#include "ioapi.h"
#endif

#ifndef __cplusplus
#include "apex/ca_c.h"
#endif

#if defined(STRICTUNZIP) || defined(STRICTZIPUNZIP)
/* like the STRICT of WIN32, we define a pointer that cannot be converted
    from (void *) without cast */
typedef struct TagunzFile__ { i32 unused; } unzFile__;
typedef unzFile__ *unzFile;
#else
typedef voidp unzFile;
#endif


#define UNZ_OK                          (0)
#define UNZ_END_OF_LIST_OF_FILE         (-100)
#define UNZ_ERRNO                       (Z_ERRNO)
#define UNZ_EOF                         (0)
#define UNZ_PARAMERROR                  (-102)
#define UNZ_BADZIPFILE                  (-103)
#define UNZ_INTERNALERROR               (-104)
#define UNZ_CRCERROR                    (-105)

/* tm_unz contain date/time info */
typedef struct tm_unz_s
{
   u32 tm_sec;            /* seconds after the minute - [0,59] */
   u32 tm_min;            /* minutes after the hour - [0,59] */
   u32 tm_hour;           /* hours since midnight - [0,23] */
   u32 tm_mday;           /* day of the month - [1,31] */
   u32 tm_mon;            /* months since January - [0,11] */
   u32 tm_year;           /* years - [1980..2044] */
} tm_unz;

/* unz_global_info structure contain global data about the ZIPfile
   These data comes from the end of central dir */
typedef struct unz_global_info_s
{
   uptr number_entry;         /* total number of entries in
                       the central dir on this disk */
   uptr size_comment;         /* size of the global comment of the zipfile */
} unz_global_info;


/* unz_file_info contain information about a file in the zipfile */
typedef struct unz_file_info_s
{
   uptr version;              /* version made by                 2 bytes */
   uptr version_needed;       /* version needed to extract       2 bytes */
   uptr flag;                 /* general purpose bit flag        2 bytes */
   uptr compression_method;   /* compression method              2 bytes */
   uptr dosDate;              /* last mod file date in Dos fmt   4 bytes */
   uptr crc;                  /* crc-32                          4 bytes */
   uptr compressed_size;      /* compressed size                 4 bytes */
   uptr uncompressed_size;    /* uncompressed size               4 bytes */
   uptr size_filename;        /* filename length                 2 bytes */
   uptr size_file_extra;      /* extra field length              2 bytes */
   uptr size_file_comment;    /* file comment length             2 bytes */

   uptr disk_num_start;       /* disk number start               2 bytes */
   uptr internal_fa;          /* internal file attributes        2 bytes */
   uptr external_fa;          /* external file attributes        4 bytes */

   tm_unz tmu_date;
} unz_file_info;

extern i32 CLASS_DECL_APEX unzStringFileNameCompare OF ((const char* fileName1,
      const char* fileName2,
      i32 iCaseSensitivity));
/*
   Compare two filename (fileName1,fileName2).
   If iCaseSenisivity = 1, comparision is case sensitivity (like strcmp)
   If iCaseSenisivity = 2, comparision is not case sensitivity (like _strcmpi
                                or strcasecmp)
   If iCaseSenisivity = 0, case sensitivity is defaut of your operating system
    (like 1 on Unix, 2 on Windows)
*/


extern unzFile CLASS_DECL_APEX unzOpen OF((const char *path));
/*
  open a Zip spfile-> path contain the full pathname (by example,
     on a Windows XP computer "ca:\\zlib\\zlib113.zip" or on an Unix computer
     "zlib/zlib113.zip".
     If the zipfile cannot be opened (file don't exist or in not valid), the
       return value is nullptr.
     Else, the return value is a unzFile Handle, usable with other function
       of this unzip package.
*/

extern unzFile CLASS_DECL_APEX unzOpen2 OF((const char *path,
      zlib_filefunc_def* pzlib_filefunc_def));
/*
   open a Zip file, like unzOpen, but provide a set of file low level API
      for read/write the zip file (see ioapi.h)
*/

extern i32 CLASS_DECL_APEX unzClose OF((unzFile file));
/*
  close a ZipFile opened with unzipOpen.
  If there is files inside the .Zip opened with unzOpenCurrentFile (see later),
    these files MUST be closed with unzipCloseCurrentFile before call unzipClose.
  return UNZ_OK if there is no problem. */

extern i32 CLASS_DECL_APEX unzGetGlobalInfo OF((unzFile file,
      unz_global_info *pglobal_info));
/*
  write info about the ZipFile in the *pglobal_info structure.
  No preparation of the structure is needed
  return UNZ_OK if there is no problem. */


extern i32 CLASS_DECL_APEX unzGetGlobalComment OF((unzFile file,
      char *szComment,
      uptr uSizeBuf));
/*
  get the global comment string of the ZipFile, in the szComment buffer.
  uSizeBuf is the size of the szComment buffer.
  return the number of byte copied or an error code <0
*/


/***************************************************************************/
/* Unzip package allow you browse the directory of the zipfile */

extern i32 CLASS_DECL_APEX unzGoToFirstFile OF((unzFile file));
/*
  set the current file of the zipfile to the first spfile->
  return UNZ_OK if there is no problem
*/

extern i32 CLASS_DECL_APEX unzGoToNextFile OF((unzFile file));
/*
  set the current file of the zipfile to the next spfile->
  return UNZ_OK if there is no problem
  return UNZ_END_OF_LIST_OF_FILE if the actual file was the latest.
*/

extern i32 CLASS_DECL_APEX unzLocateFile OF((unzFile file,
      const char *szFileName,
      i32 iCaseSensitivity));
/*
  Try locate the file szFileName in the zipfile.
  For the iCaseSensitivity signification, see unzStringFileNameCompare

  return value :
  UNZ_OK if the file is found. It becomes the current spfile->
  UNZ_END_OF_LIST_OF_FILE if the file is not found
*/


/* ****************************************** */
/* Ryan supplied functions */
/* unz_file_info contain information about a file in the zipfile */
typedef struct unz_file_pos_s
{
   uptr pos_in_zip_directory;   /* offset in zip file directory */
   uptr num_of_file;            /* # of file */
} unz_file_pos;

extern i32 CLASS_DECL_APEX unzGetFilePos(
unzFile file,
unz_file_pos* file_pos);

extern i32 CLASS_DECL_APEX unzGoToFilePos(
unzFile file,
unz_file_pos* file_pos);

/* ****************************************** */

extern i32 CLASS_DECL_APEX unzGetCurrentFileInfo OF((unzFile file,
      unz_file_info *pfile_info,
      char *szFileName,
      uptr fileNameBufferSize,
      void *extraField,
      uptr extraFieldBufferSize,
      char *szComment,
      uptr commentBufferSize));
/*
  get Info about the current file
  if pfile_info!=nullptr, the *pfile_info structure will contain somes info about
        the current file
  if szFileName!=nullptr, the filemane string will be copied in szFileName
            (fileNameBufferSize is the size of the buffer)
  if extraField!=nullptr, the extra field information will be copied in extraField
            (extraFieldBufferSize is the size of the buffer).
            This is the Central-header version of the extra field
  if szComment!=nullptr, the comment string of the file will be copied in szComment
            (commentBufferSize is the size of the buffer)
*/

/***************************************************************************/
/* for reading the content of the current zipfile, you can open it, read data
   from it, and close it (you can close it before reading all the file)
   */

extern i32 CLASS_DECL_APEX unzOpenCurrentFile OF((unzFile file));
/*
  open for reading data the current file in the zipfile.
  If there is no error, the return value is UNZ_OK.
*/

extern i32 CLASS_DECL_APEX unzOpenCurrentFilePassword OF((unzFile file,
      const char* password));
/*
  open for reading data the current file in the zipfile.
  password is a crypting password
  If there is no error, the return value is UNZ_OK.
*/

extern i32 CLASS_DECL_APEX unzOpenCurrentFile2 OF((unzFile file,
      i32* method,
      i32* level,
      i32 raw));
/*
  Same than unzOpenCurrentFile, but open for read raw the file (not uncompress)
    if raw==1
  *method will receive method of compression, *level will receive level of
     compression
  note : you can set level parameter as nullptr (if you did not want known level,
         but you CANNOT set method parameter as nullptr
*/

extern i32 CLASS_DECL_APEX unzOpenCurrentFile3 OF((unzFile file,
      i32* method,
      i32* level,
      i32 raw,
      const char* password));
/*
  Same than unzOpenCurrentFile, but open for read raw the file (not uncompress)
    if raw==1
  *method will receive method of compression, *level will receive level of
     compression
  note : you can set level parameter as nullptr (if you did not want known level,
         but you CANNOT set method parameter as nullptr
*/


extern i32 CLASS_DECL_APEX unzCloseCurrentFile OF((unzFile file));
/*
  close the file in zip opened with unzOpenCurrentFile
  Return UNZ_CRCERROR if all the file was read but the CRC is not good
*/

extern i32 CLASS_DECL_APEX unzReadCurrentFile OF((unzFile file,
      voidp buf,
      u32 len));
/*
  read bytes from the current file (opened by unzOpenCurrentFile)
  buf contain buffer where data must be copied
  len the size of buf.

  return the number of byte copied if somes bytes are copied
  return 0 if the end of file was reached
  return <0 with error code if there is an error
    (UNZ_ERRNO for IO error, or zLib error for uncompress error)
*/

extern iptr CLASS_DECL_APEX unztell OF((unzFile file));
/*
  Give the current position in uncompressed data
*/

extern i32 CLASS_DECL_APEX unzeof OF((unzFile file));
/*
  return 1 if the end of file was reached, 0 elsewhere
*/

extern i32 CLASS_DECL_APEX unzGetLocalExtrafield OF((unzFile file,
      voidp buf,
      u32 len));
/*
  read extra field from the current file (opened by unzOpenCurrentFile)
  This is the local-header version of the extra field (sometimes, there is
    more info in the local-header version than in the central-header)

  if buf==nullptr, it return the size of the local extra field

  if buf!=nullptr, len is the size of the buffer, the extra header is copied in
    buf.
  the return value is the number of bytes copied in buf, or (if <0)
    the error code
*/

#ifdef __cplusplus
}
#endif

#endif /* _unz_H */

/* unzip.ca -- IO for uncompress .zip files using zlib
   Version 1.00, September 10th, 2003

   Copyright (C) 1998-2003 Gilles Vollant

   read unzip.h for more info
*/

/* Decryption code comes from crypt.ca by Info-ZIP but has been greatly reduced in terms of
compatibility with older software. The following is from the original crypt.ca. Code
woven in by Terry Thorsen 1/2003.
*/
/*
  Copyright (ca) 1990-2000 Info-ZIP.

  See the accompanying file LICENSE, version 2000-Apr-09 or later
  (the contents of which are also included in zip.h) for terms of use.
  If, for some reason, all these files are missing, the Info-ZIP license
  also may be found at:  ftp://ftp.info-zip.org/pub/infozip/license.html
*/
/*
  crypt.ca (full version) by Info-ZIP.      Last revised:  [see crypt.h]

  The encryption/decryption parts of this source code (as opposed to the
  non-echoing password parts) were originally written in Europe.  The
  whole source package can be freely distributed, including from the USA.
  (Prior to January 2000, re-export from the US was a violation of US law.)
 */

/*
  This encryption code is a direct transcription of the algorithm from
  Roger Schlafly, described by Phil Katz in the file appnote.txt.  This
  file (appnote.txt) is distributed with the PKZIP program (even in the
  version without encryption capabilities).
 */
#include "framework.h"
#include "unzip.h"
#include "crypt.h"

#if defined(WINDOWS) || defined(LINUX)
extern const z_crc_t * zip_get_crc_table();
#else
extern const uLongf * zip_get_crc_table();
#endif


/* compile with -Dlocal if your debugger can't find static symbols */


#ifndef CASESENSITIVITYDEFAULT_NO
#  if !defined(unix) && !defined(CASESENSITIVITYDEFAULT_YES)
#    define CASESENSITIVITYDEFAULT_NO
#  endif
#endif


#ifndef UNZ_BUFSIZE
#define UNZ_BUFSIZE (16384)
#endif

#ifndef UNZ_MAXFILENAMEINZIP
#define UNZ_MAXFILENAMEINZIP (256)
#endif

#ifndef ALLOC
# define ALLOC(size) (malloc(size))
#endif
#ifndef TRYFREE
# define TRYFREE(point) {if (point) free(point);}
#endif

#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)




const char unz_copyright[] =
" unzip 1.00 Copyright 1998-2003 Gilles Vollant - http://www.winpimage->com/zLibDll";

/* unz_file_info_interntal contain internal info about a file in zipfile*/
typedef struct unz_file_info_internal_s
{
   uptr offset_curfile;/* relative offset of static header 4 bytes */
} unz_file_info_internal;


/* file_in_zip_read_info_s contain internal information about a file in zipfile,
    when reading and decompress it */
typedef struct
{
   char  *read_buffer;         /* internal buffer for compressed data */
   z_stream stream;            /* zLib stream structure for inflate */

   uptr pos_in_zipfile;       /* position in byte on the zipfile, for fseek*/
   uptr stream_initialised;   /* flag set if stream structure is initialised*/

   uptr offset_local_extrafield;/* offset of the static extra field */
   u32  size_local_extrafield;/* size_i32 of the static extra field */
   uptr pos_local_extrafield;   /* position in the static extra field in read*/

   u32 crc32;                /* crc32 of all data uncompressed */
   uptr crc32_wait;           /* crc32 we must obtain after decompress all */
   uptr rest_read_compressed; /* number of byte to be decompressed */
   uptr rest_read_uncompressed;/*number of byte to be obtained after decomp*/
   zlib_filefunc_def z_filefunc;
   voidpf filestream;        /* io structore of the zipfile */
   uptr compression_method;   /* compression method (0==store) */
   uptr byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/
   i32   raw;
} file_in_zip_read_info_s;


/* unz_s contain internal information about the zipfile
*/
typedef struct
{
   zlib_filefunc_def z_filefunc;
   voidpf filestream;        /* io structore of the zipfile */
   unz_global_info gi;       /* public global information */
   uptr byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/
   uptr num_file;             /* number of the current file in the zipfile*/
   uptr pos_in_central_dir;   /* pos of the current file in the central dir*/
   uptr current_file_ok;      /* flag about the usability of the current file*/
   uptr central_pos;          /* position of the beginning of the central dir*/

   uptr size_central_dir;     /* size_i32 of the central directory  */
   uptr offset_central_dir;   /* offset of start of central directory with
                                   respect to the starting disk number */

   unz_file_info cur_file_info; /* public info about the current file in zip*/
   unz_file_info_internal cur_file_info_internal; /* private info about it*/
   file_in_zip_read_info_s* pfile_in_zip_read; /* structure about the current
                                        file if we are decompressing it */
   i32 encrypted;
#    ifndef NOUNCRYPT
   u32 keys[3];     /* keys defining the pseudo-random sequence */
#if defined(WINDOWS) || defined(LINUX)
   const z_crc_t * pcrc_32_tab;
#else
   const uLongf * pcrc_32_tab;
#endif
#    endif
} unz_s;


#ifndef NOUNCRYPT
//#include"crypt.h"
#endif

/* ===========================================================================
     read a byte from a gz_stream; update next_in and avail_in. Return EOF
   for end of spfile->
   IN assertion: the stream s has been sucessfully opened for reading.
*/


static i32 unzlocal_getByte OF((
                                  const zlib_filefunc_def* pzlib_filefunc_def,
                                  voidpf filestream,
                                  i32 *pi));

static i32 unzlocal_getByte(const zlib_filefunc_def * pzlib_filefunc_def, voidpf filestream, i32 * pi)
{
   uchar ca;
   i32 err = (i32)ZREAD(*pzlib_filefunc_def,filestream,&ca,1);
   if (err==1)
   {
      *pi = (i32)ca;
      return UNZ_OK;
   }
   else
   {
      if (ZERROR(*pzlib_filefunc_def,filestream))
         return UNZ_ERRNO;
      else
         return UNZ_EOF;
   }
}


/* ===========================================================================
   Reads a long in LSB order from the given gz_stream. Sets
*/
static i32 unzlocal_getShort OF((
                                   const zlib_filefunc_def* pzlib_filefunc_def,
                                   voidpf filestream,
                                   uptr *pX));

static i32 unzlocal_getShort (const zlib_filefunc_def * pzlib_filefunc_def, voidpf filestream, uptr * pX)
{
   uptr x ;
   i32 i = 0;
   i32 err;

   err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
   x = (uptr)i;

   if (err==UNZ_OK)
      err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<8;

   if (err==UNZ_OK)
      *pX = x;
   else
      *pX = 0;
   return err;
}

static i32 unzlocal_getLong OF((
                                  const zlib_filefunc_def* pzlib_filefunc_def,
                                  voidpf filestream,
                                  uptr *pX));

static i32 unzlocal_getLong (
const zlib_filefunc_def* pzlib_filefunc_def,
voidpf filestream,
uptr *pX)
{
   uptr x ;
   i32 i;
   i32 err;

   err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
   x = (uptr)i;

   if (err==UNZ_OK)
      err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<8;

   if (err==UNZ_OK)
      err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<16;

   if (err==UNZ_OK)
      err = unzlocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<24;

   if (err==UNZ_OK)
      *pX = x;
   else
      *pX = 0;
   return err;
}


/* My own _strcmpi / strcasecmp */
static i32 strcmpcasenosensitive_internal (const char * fileName1, const char * fileName2)
{
   for (;;)
   {
      char c1=*(fileName1++);
      char c2=*(fileName2++);
      if ((c1>='a') && (c1<='z'))
         c1 -= 0x20;
      if ((c2>='a') && (c2<='z'))
         c2 -= 0x20;
      if (c1=='\0')
         return ((c2=='\0') ? 0 : -1);
      if (c2=='\0')
         return 1;
      if (c1<c2)
         return -1;
      if (c1>c2)
         return 1;
   }
}


#ifdef  CASESENSITIVITYDEFAULT_NO
#define CASESENSITIVITYDEFAULTVALUE 2
#else
#define CASESENSITIVITYDEFAULTVALUE 1
#endif

#ifndef STRCMPCASENOSENTIVEFUNCTION
#define STRCMPCASENOSENTIVEFUNCTION strcmpcasenosensitive_internal
#endif

/*
   compare two filename (fileName1,fileName2).
   If iCaseSenisivity = 1, comparision is case sensitivity (like strcmp)
   If iCaseSenisivity = 2, comparision is not case sensitivity (like _strcmpi
                                                                or strcasecmp)
   If iCaseSenisivity = 0, case sensitivity is defaut of your operating system
        (like 1 on Unix, 2 on Windows)

*/
extern i32 CLASS_DECL_ACME unzStringFileNameCompare (
const char* fileName1,
const char* fileName2,
i32 iCaseSensitivity)
{
   if (iCaseSensitivity==0)
      iCaseSensitivity=CASESENSITIVITYDEFAULTVALUE;

   if (iCaseSensitivity==1)
      return strcmp(fileName1,fileName2);

   return STRCMPCASENOSENTIVEFUNCTION(fileName1,fileName2);
}

#ifndef BUFREADCOMMENT
#define BUFREADCOMMENT (0x400)
#endif

/*
  Locate the Central directory of a zipfile (at the end, just before
    the global comment)
*/
static uptr unzlocal_SearchCentralDir OF((
      const zlib_filefunc_def* pzlib_filefunc_def,
      voidpf filestream));
i32 isEndOfCentralDir(uchar * buf);

i32 isEndOfCentralDir(uchar * buf)
{
   long * pl = (long *) buf;
   if(*pl == 0x06054b50
         || * pl == 0x0D004A11)
   {
      return 1;
   }
   else
      return 0;
}

static uptr unzlocal_SearchCentralDir(
const zlib_filefunc_def* pzlib_filefunc_def,
voidpf filestream)
{
   uchar* buf;
   uptr uSizeFile;
   uptr uBackRead;
   uptr uMaxBack=0xffff; /* maximum size_i32 of global comment */
   uptr uPosFound=0;

   if (ZSEEK(*pzlib_filefunc_def,filestream,0,ZLIB_FILEFUNC_SEEK_END) != 0)
      return 0;


   uSizeFile = ZTELL(*pzlib_filefunc_def,filestream);

   if (uMaxBack>uSizeFile)
      uMaxBack = uSizeFile;

   buf = (uchar*)ALLOC(BUFREADCOMMENT+4);
   if (buf==nullptr)
      return 0;

   uBackRead = 4;
   while (uBackRead<uMaxBack)
   {
      uptr uReadSize,uReadPos ;
      i32 i;
      if (uBackRead+BUFREADCOMMENT>uMaxBack)
         uBackRead = uMaxBack;
      else
         uBackRead+=BUFREADCOMMENT;
      uReadPos = uSizeFile-uBackRead ;

      uReadSize = ((BUFREADCOMMENT+4) < (uSizeFile-uReadPos)) ?
                  (BUFREADCOMMENT+4) : (uSizeFile-uReadPos);
      if (ZSEEK(*pzlib_filefunc_def,filestream,uReadPos,ZLIB_FILEFUNC_SEEK_SET)!=0)
         break;

      if (ZREAD(*pzlib_filefunc_def,filestream,buf,uReadSize)!=uReadSize)
         break;

      for (i = (i32)uReadSize - 3; (i--) > 0;)
      {
         //if (((*(buf+i))==0x50) && ((*(buf+i+1))==0x4b) &&
         //           ((*(buf+i+2))==0x05) && ((*(buf+i+3))==0x06))
         if (isEndOfCentralDir(&buf[i]))
         {
            uPosFound = uReadPos + i;
            break;
         }
      }

      if (uPosFound!=0)
         break;
   }
   TRYFREE(buf);
   return uPosFound;
}

/*
  open a Zip spfile-> path contain the full pathname (by example,
     on a Windows NT computer "ca:\\test\\zlib114.zip" or on an Unix computer
     "zlib/zlib114.zip".
     If the zipfile cannot be opened (file doesn't exist or in not valid), the
       return value is nullptr.
     Else, the return value is a unzFile Handle, usable with other function
       of this unzip package.
*/
extern unzFile CLASS_DECL_ACME unzOpen2 (
const char *path,
zlib_filefunc_def* pzlib_filefunc_def)
{
   unz_s us;
   unz_s *s;
   uptr central_pos,uL;

   uptr number_disk;          /* number of the current dist, used for
                                   spaning ZIP, unsupported, always 0*/
   uptr number_disk_with_CD;  /* number the the disk with central dir, used
                                   for spaning ZIP, unsupported, always 0*/
   uptr number_entry_CD;      /* total number of entries in
                                   the central dir
                                   (same than number_entry on nospan) */

   i32 err=UNZ_OK;

   if (unz_copyright[0]!=' ')
      return nullptr;

   if (pzlib_filefunc_def==nullptr)
      fill_fopen_filefunc(&us.z_filefunc);
   else
      us.z_filefunc = *pzlib_filefunc_def;

   us.filestream= (*(us.z_filefunc.zopen_file))(us.z_filefunc.opaque,
                  path,
                  ZLIB_FILEFUNC_MODE_READ |
                  ZLIB_FILEFUNC_MODE_EXISTING);
   if (us.filestream==nullptr)
      return nullptr;

   central_pos = unzlocal_SearchCentralDir(&us.z_filefunc,us.filestream);
   if (central_pos==0)
      err=UNZ_ERRNO;

   if (ZSEEK(us.z_filefunc, us.filestream,
             central_pos,ZLIB_FILEFUNC_SEEK_SET)!=0)
      err=UNZ_ERRNO;

   /* the signature, already checked */
   if (unzlocal_getLong(&us.z_filefunc, us.filestream,&uL)!=UNZ_OK)
      err=UNZ_ERRNO;

   /* number of this disk */
   if (unzlocal_getShort(&us.z_filefunc, us.filestream,&number_disk)!=UNZ_OK)
      err=UNZ_ERRNO;

   /* number of the disk with the start of the central directory */
   if (unzlocal_getShort(&us.z_filefunc, us.filestream,&number_disk_with_CD)!=UNZ_OK)
      err=UNZ_ERRNO;

   /* total number of entries in the central dir on this disk */
   if (unzlocal_getShort(&us.z_filefunc, us.filestream,&us.gi.number_entry)!=UNZ_OK)
      err=UNZ_ERRNO;

   /* total number of entries in the central dir */
   if (unzlocal_getShort(&us.z_filefunc, us.filestream,&number_entry_CD)!=UNZ_OK)
      err=UNZ_ERRNO;

   if ((number_entry_CD!=us.gi.number_entry) ||
         (number_disk_with_CD!=0) ||
         (number_disk!=0))
      err=UNZ_BADZIPFILE;

   /* size_i32 of the central directory */
   if (unzlocal_getLong(&us.z_filefunc, us.filestream,&us.size_central_dir)!=UNZ_OK)
      err=UNZ_ERRNO;

   /* offset of start of central directory with respect to the
         starting disk number */
   if (unzlocal_getLong(&us.z_filefunc, us.filestream,&us.offset_central_dir)!=UNZ_OK)
      err=UNZ_ERRNO;

   /* zipfile comment length */
   if (unzlocal_getShort(&us.z_filefunc, us.filestream,&us.gi.size_comment)!=UNZ_OK)
      err=UNZ_ERRNO;

   if ((central_pos<us.offset_central_dir+us.size_central_dir) &&
         (err==UNZ_OK))
      err=UNZ_BADZIPFILE;

   if (err!=UNZ_OK)
   {
      ZCLOSE(us.z_filefunc, us.filestream);
      return nullptr;
   }

   us.byte_before_the_zipfile = central_pos -
                                (us.offset_central_dir+us.size_central_dir);
   us.central_pos = central_pos;
   us.pfile_in_zip_read = nullptr;
   us.encrypted = 0;


   s=(unz_s*)ALLOC(sizeof(unz_s));
   *s=us;
   unzGoToFirstFile((unzFile)s);
   return (unzFile)s;
}


extern unzFile CLASS_DECL_ACME unzOpen (const char * path)
{
   return unzOpen2(path, nullptr);
}

/*
  close a ZipFile opened with unzipOpen.
  If there is files inside the .Zip opened with unzipOpenCurrentFile (see later),
    these files MUST be closed with unzipCloseCurrentFile before call unzipClose.
  return UNZ_OK if there is no problem. */
extern i32 CLASS_DECL_ACME unzClose (unzFile file)
{
   unz_s* s;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;

   if (s->pfile_in_zip_read!=nullptr)
      unzCloseCurrentFile(file);

   ZCLOSE(s->z_filefunc, s->filestream);
   TRYFREE(s);
   return UNZ_OK;
}


/*
  write info about the ZipFile in the *pglobal_info structure.
  No preparation of the structure is needed
  return UNZ_OK if there is no problem. */
extern i32 CLASS_DECL_ACME unzGetGlobalInfo (unzFile file,
      unz_global_info *pglobal_info)
{
   unz_s* s;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   *pglobal_info=s->gi;
   return UNZ_OK;
}


/*
   Translate date/time from Dos format to tm_unz (readable more easilty)
*/
static void unzlocal_DosDateToTmuDate(
uptr ulDosDate,
tm_unz* ptm)
{
   uptr uDate;
   uDate = (uptr)(ulDosDate>>16);
   ptm->tm_mday = (u32)(uDate&0x1f) ;
   ptm->tm_mon =  (u32)((((uDate)&0x1E0)/0x20)-1) ;
   ptm->tm_year = (u32)(((uDate&0x0FE00)/0x0200)+1980) ;

   ptm->tm_hour = (u32) ((ulDosDate &0xF800)/0x800);
   ptm->tm_min =  (u32) ((ulDosDate&0x7E0)/0x20) ;
   ptm->tm_sec =  (u32) (2*(ulDosDate&0x1f)) ;
}

/*
  get Info about the current file in the zipfile, with internal only info
*/
static i32 unzlocal_GetCurrentFileInfoInternal OF((unzFile file,
      unz_file_info *pfile_info,
      unz_file_info_internal
      *pfile_info_internal,
      char *szFileName,
      uptr fileNameBufferSize,
      void *extraField,
      uptr extraFieldBufferSize,
      char *szComment,
      uptr commentBufferSize));

static i32 unzlocal_GetCurrentFileInfoInternal (
unzFile file,
unz_file_info *pfile_info,
unz_file_info_internal *pfile_info_internal,
char *szFileName,
uptr fileNameBufferSize,
void *extraField,
uptr extraFieldBufferSize,
char *szComment,
uptr commentBufferSize)
{
   unz_s* s;
   unz_file_info file_info;
   unz_file_info_internal file_info_internal;
   i32 err=UNZ_OK;
   uptr uMagic;
   uptr lSeek=0;

   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   if (ZSEEK(s->z_filefunc, s->filestream,
             s->pos_in_central_dir+s->byte_before_the_zipfile,
             ZLIB_FILEFUNC_SEEK_SET)!=0)
      err=UNZ_ERRNO;


   /* we check the magic */
   if (err==UNZ_OK)
   {
      if (unzlocal_getLong(&s->z_filefunc, s->filestream,&uMagic) != UNZ_OK)
      {
         err=UNZ_ERRNO;
      }
      else if (uMagic!=0x02014b50
               && uMagic != 0x2b5fa067
         && uMagic != 0x2b5fa067)
      {
         err=UNZ_BADZIPFILE;
      }
   }

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.version) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.version_needed) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.flag) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.compression_method) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&file_info.dosDate) != UNZ_OK)
      err=UNZ_ERRNO;

   unzlocal_DosDateToTmuDate(file_info.dosDate,&file_info.tmu_date);

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&file_info.crc) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&file_info.compressed_size) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&file_info.uncompressed_size) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.size_filename) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.size_file_extra) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.size_file_comment) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.disk_num_start) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&file_info.internal_fa) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&file_info.external_fa) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&file_info_internal.offset_curfile) != UNZ_OK)
      err=UNZ_ERRNO;

   lSeek+=file_info.size_filename;
   if ((err==UNZ_OK) && (szFileName!=nullptr))
   {
      uptr uSizeRead ;
      if (file_info.size_filename<fileNameBufferSize)
      {
         *(szFileName+file_info.size_filename)='\0';
         uSizeRead = file_info.size_filename;
      }
      else
         uSizeRead = fileNameBufferSize;

      if ((file_info.size_filename>0) && (fileNameBufferSize>0))
         if (ZREAD(s->z_filefunc, s->filestream,szFileName,uSizeRead)!=uSizeRead)
            err=UNZ_ERRNO;
      lSeek -= uSizeRead;
   }


   if ((err==UNZ_OK) && (extraField!=nullptr))
   {
      uptr uSizeRead ;
      if (file_info.size_file_extra<extraFieldBufferSize)
         uSizeRead = file_info.size_file_extra;
      else
         uSizeRead = extraFieldBufferSize;

      if (lSeek!=0)
      {
         if (ZSEEK(s->z_filefunc, s->filestream,lSeek,ZLIB_FILEFUNC_SEEK_CUR)==0)
         {
            lSeek=0;
         }
         else
         {
            err=UNZ_ERRNO;
         }
      }
      if ((file_info.size_file_extra>0) && (extraFieldBufferSize>0))
         if (ZREAD(s->z_filefunc, s->filestream,extraField,uSizeRead)!=uSizeRead)
            err=UNZ_ERRNO;
      lSeek += file_info.size_file_extra - uSizeRead;
   }
   else
      lSeek+=file_info.size_file_extra;


   if ((err==UNZ_OK) && (szComment!=nullptr))
   {
      uptr uSizeRead ;
      if (file_info.size_file_comment<commentBufferSize)
      {
         *(szComment+file_info.size_file_comment)='\0';
         uSizeRead = file_info.size_file_comment;
      }
      else
         uSizeRead = commentBufferSize;

      if (lSeek!=0)
      {
         if (ZSEEK(s->z_filefunc, s->filestream,lSeek,ZLIB_FILEFUNC_SEEK_CUR)==0)
         {
            lSeek=0;
         }
         else
         {
            err=UNZ_ERRNO;
         }
      }
      if ((file_info.size_file_comment>0) && (commentBufferSize>0))
         if (ZREAD(s->z_filefunc, s->filestream,szComment,uSizeRead)!=uSizeRead)
            err=UNZ_ERRNO;
      lSeek+=file_info.size_file_comment - uSizeRead;
   }
   else
      lSeek+=file_info.size_file_comment;

   if ((err==UNZ_OK) && (pfile_info!=nullptr))
      *pfile_info=file_info;

   if ((err==UNZ_OK) && (pfile_info_internal!=nullptr))
      *pfile_info_internal=file_info_internal;

   return err;
}



/*
  write info about the ZipFile in the *pglobal_info structure.
  No preparation of the structure is needed
  return UNZ_OK if there is no problem.
*/
extern i32 CLASS_DECL_ACME unzGetCurrentFileInfo (
unzFile file,
unz_file_info *pfile_info,
char *szFileName,
uptr fileNameBufferSize,
void *extraField,
uptr extraFieldBufferSize,
char *szComment,
uptr commentBufferSize)
{
   return unzlocal_GetCurrentFileInfoInternal(file,pfile_info,nullptr,
          szFileName,fileNameBufferSize,
          extraField,extraFieldBufferSize,
          szComment,commentBufferSize);
}

/*
  set the current file of the zipfile to the first spfile->
  return UNZ_OK if there is no problem
*/
extern i32 CLASS_DECL_ACME unzGoToFirstFile (unzFile file)
{
   i32 err=UNZ_OK;
   unz_s* s;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   s->pos_in_central_dir=s->offset_central_dir;
   s->num_file=0;
   err=unzlocal_GetCurrentFileInfoInternal(file,&s->cur_file_info,
                                           &s->cur_file_info_internal,
                                           nullptr,0,nullptr,0,nullptr,0);
   s->current_file_ok = (err == UNZ_OK);
   return err;
}

/*
  set the current file of the zipfile to the next spfile->
  return UNZ_OK if there is no problem
  return UNZ_END_OF_LIST_OF_FILE if the actual file was the latest.
*/
extern i32 CLASS_DECL_ACME unzGoToNextFile (unzFile file)
{
   unz_s* s;
   i32 err;

   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   if (!s->current_file_ok)
      return UNZ_END_OF_LIST_OF_FILE;
   if (s->num_file+1==s->gi.number_entry)
      return UNZ_END_OF_LIST_OF_FILE;

   s->pos_in_central_dir += SIZECENTRALDIRITEM + s->cur_file_info.size_filename +
                            s->cur_file_info.size_file_extra + s->cur_file_info.size_file_comment ;
   s->num_file++;
   err = unzlocal_GetCurrentFileInfoInternal(file,&s->cur_file_info,
         &s->cur_file_info_internal,
         nullptr,0,nullptr,0,nullptr,0);
   s->current_file_ok = (err == UNZ_OK);
   return err;
}


/*
  Try locate the file szFileName in the zipfile.
  For the iCaseSensitivity signification, see unzipStringFileNameCompare

  return value :
  UNZ_OK if the file is found. It becomes the current spfile->
  UNZ_END_OF_LIST_OF_FILE if the file is not found
*/
extern i32 CLASS_DECL_ACME unzLocateFile (
unzFile file,
const char *szFileName,
i32 iCaseSensitivity)
{
   unz_s* s;
   i32 err;

   /* We remember the 'current' position in the file so that we can jump
    * back there if we fail.
    */
   unz_file_info cur_file_infoSaved;
   unz_file_info_internal cur_file_info_internalSaved;
   uptr num_fileSaved;
   uptr pos_in_central_dirSaved;


   if (file==nullptr)
      return UNZ_PARAMERROR;

   if (strlen(szFileName)>=UNZ_MAXFILENAMEINZIP)
      return UNZ_PARAMERROR;

   s=(unz_s*)file;
   if (!s->current_file_ok)
      return UNZ_END_OF_LIST_OF_FILE;

   /* Save the current state */
   num_fileSaved = s->num_file;
   pos_in_central_dirSaved = s->pos_in_central_dir;
   cur_file_infoSaved = s->cur_file_info;
   cur_file_info_internalSaved = s->cur_file_info_internal;

   err = unzGoToFirstFile(file);

   while (err == UNZ_OK)
   {
      char szCurrentFileName[UNZ_MAXFILENAMEINZIP+1];
      err = unzGetCurrentFileInfo(file,nullptr,
                                  szCurrentFileName,sizeof(szCurrentFileName)-1,
                                  nullptr,0,nullptr,0);
      if (err == UNZ_OK)
      {
         if (unzStringFileNameCompare(szCurrentFileName,
                                      szFileName,iCaseSensitivity)==0)
            return UNZ_OK;
         err = unzGoToNextFile(file);
      }
   }

   /* We failed, so restore the state of the 'current file' to where we
    * were.
    */
   s->num_file = num_fileSaved ;
   s->pos_in_central_dir = pos_in_central_dirSaved ;
   s->cur_file_info = cur_file_infoSaved;
   s->cur_file_info_internal = cur_file_info_internalSaved;
   return err;
}


/*
///////////////////////////////////////////
// Contributed by Ryan Haksi (mailto://cryogen@infoserve.net)
// I need random access
//
// Further optimization could be realized by adding an ability
// to cache the directory in memory. The goal being a single
// comprehensive file read to put the file I need in a memory.
*/

/*
typedef struct unz_file_pos_s
{
    uptr pos_in_zip_directory;   // offset in file
    uptr num_of_file;            // # of file
} unz_file_pos;
*/

extern i32 CLASS_DECL_ACME unzGetFilePos(
unzFile file,
unz_file_pos* file_pos)
{
   unz_s* s;

   if (file==nullptr || file_pos==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   if (!s->current_file_ok)
      return UNZ_END_OF_LIST_OF_FILE;

   file_pos->pos_in_zip_directory  = s->pos_in_central_dir;
   file_pos->num_of_file           = s->num_file;

   return UNZ_OK;
}

extern i32 CLASS_DECL_ACME unzGoToFilePos(
unzFile file,
unz_file_pos* file_pos)
{
   unz_s* s;
   i32 err;

   if (file==nullptr || file_pos==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;

   /* jump to the right spot */
   s->pos_in_central_dir = file_pos->pos_in_zip_directory;
   s->num_file           = file_pos->num_of_file;

   /* set the current file */
   err = unzlocal_GetCurrentFileInfoInternal(file,&s->cur_file_info,
         &s->cur_file_info_internal,
         nullptr,0,nullptr,0,nullptr,0);
   /* return results */
   s->current_file_ok = (err == UNZ_OK);
   return err;
}

/*
// Unzip helper Functions - should be here?
///////////////////////////////////////////
*/

/*
  read the static header of the current zipfile
  Check the coherency of the static header and info in the end of central
        directory about this file
  store in *piSizeVar the size_i32 of extra info in static header
        (filename and size_i32 of extra field data)
*/
static i32 unzlocal_CheckCurrentFileCoherencyHeader (
unz_s* s,
u32* piSizeVar,
uptr *poffset_local_extrafield,
u32  *psize_local_extrafield)
{
   uptr uMagic,uData,uFlags;
   uptr size_filename;
   uptr size_extra_field;
   i32 err=UNZ_OK;

   *piSizeVar = 0;
   *poffset_local_extrafield = 0;
   *psize_local_extrafield = 0;

   if (ZSEEK(s->z_filefunc, s->filestream,s->cur_file_info_internal.offset_curfile +
             s->byte_before_the_zipfile,ZLIB_FILEFUNC_SEEK_SET)!=0)
      return UNZ_ERRNO;


   if (err==UNZ_OK)
   {
      if (unzlocal_getLong(&s->z_filefunc, s->filestream,&uMagic) != UNZ_OK)
      {
         err=UNZ_ERRNO;
      }
      else if (uMagic!=0x04034b50 &&
               uMagic != 0x30D60A87)
      {
         err=UNZ_BADZIPFILE;
      }
   }


   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&uData) != UNZ_OK)
      err=UNZ_ERRNO;
   /*
       else if ((err==UNZ_OK) && (uData!=s->cur_file_info.wVersion))
           err=UNZ_BADZIPFILE;
   */
   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&uFlags) != UNZ_OK)
      err=UNZ_ERRNO;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&uData) != UNZ_OK)
      err=UNZ_ERRNO;
   else if ((err==UNZ_OK) && (uData!=s->cur_file_info.compression_method))
      err=UNZ_BADZIPFILE;

   if ((err==UNZ_OK) && (s->cur_file_info.compression_method!=0) &&
         (s->cur_file_info.compression_method!=Z_DEFLATED))
      err=UNZ_BADZIPFILE;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&uData) != UNZ_OK) /* date/time */
      err=UNZ_ERRNO;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&uData) != UNZ_OK) /* crc */
      err=UNZ_ERRNO;
   else if ((err==UNZ_OK) && (uData!=s->cur_file_info.crc) &&
            ((uFlags & 8)==0))
      err=UNZ_BADZIPFILE;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&uData) != UNZ_OK) /* size_i32 compr */
      err=UNZ_ERRNO;
   else if ((err==UNZ_OK) && (uData!=s->cur_file_info.compressed_size) &&
            ((uFlags & 8)==0))
      err=UNZ_BADZIPFILE;

   if (unzlocal_getLong(&s->z_filefunc, s->filestream,&uData) != UNZ_OK) /* size_i32 uncompr */
      err=UNZ_ERRNO;
   else if ((err==UNZ_OK) && (uData!=s->cur_file_info.uncompressed_size) &&
            ((uFlags & 8)==0))
      err=UNZ_BADZIPFILE;


   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&size_filename) != UNZ_OK)
      err=UNZ_ERRNO;
   else if ((err==UNZ_OK) && (size_filename!=s->cur_file_info.size_filename))
      err=UNZ_BADZIPFILE;

   *piSizeVar += (u32)size_filename;

   if (unzlocal_getShort(&s->z_filefunc, s->filestream,&size_extra_field) != UNZ_OK)
      err=UNZ_ERRNO;
   *poffset_local_extrafield= s->cur_file_info_internal.offset_curfile +
                              SIZEZIPLOCALHEADER + size_filename;
   *psize_local_extrafield = (u32)size_extra_field;

   *piSizeVar += (u32)size_extra_field;

   return err;
}

/*
  open for reading data the current file in the zipfile.
  If there is no error and the file is opened, the return value is UNZ_OK.
*/
extern i32 CLASS_DECL_ACME unzOpenCurrentFile3 (unzFile file, i32 * method, i32 * level, i32 raw, const char * password)
{
   i32 err=UNZ_OK;
   u32 iSizeVar;
   unz_s* s;
   file_in_zip_read_info_s* pfile_in_zip_read_info;
   uptr offset_local_extrafield;  /* offset of the static extra field */
   u32  size_local_extrafield;    /* size_i32 of the static extra field */
#    ifndef NOUNCRYPT
   char source[12];
#    else
   if (password != nullptr)
      return UNZ_PARAMERROR;
#    endif

   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   if (!s->current_file_ok)
      return UNZ_PARAMERROR;

   if (s->pfile_in_zip_read != nullptr)
      unzCloseCurrentFile(file);

   if (unzlocal_CheckCurrentFileCoherencyHeader(s,&iSizeVar,
         &offset_local_extrafield,&size_local_extrafield)!=UNZ_OK)
      return UNZ_BADZIPFILE;

   pfile_in_zip_read_info = (file_in_zip_read_info_s*)
                            ALLOC(sizeof(file_in_zip_read_info_s));
   if (pfile_in_zip_read_info==nullptr)
      return UNZ_INTERNALERROR;

   pfile_in_zip_read_info->read_buffer=(char*)ALLOC(UNZ_BUFSIZE);
   pfile_in_zip_read_info->offset_local_extrafield = offset_local_extrafield;
   pfile_in_zip_read_info->size_local_extrafield = size_local_extrafield;
   pfile_in_zip_read_info->pos_local_extrafield=0;
   pfile_in_zip_read_info->raw=raw;

   if (pfile_in_zip_read_info->read_buffer==nullptr)
   {
      TRYFREE(pfile_in_zip_read_info);
      return UNZ_INTERNALERROR;
   }

   pfile_in_zip_read_info->stream_initialised=0;

   if (method!=nullptr)
      *method = (i32)s->cur_file_info.compression_method;

   if (level!=nullptr)
   {
      *level = 6;
      switch (s->cur_file_info.flag & 0x06)
      {
      case 6 : *level = 1; break;
      case 4 : *level = 2; break;
      case 2 : *level = 9; break;
      }
   }

   if ((s->cur_file_info.compression_method!=0) &&
         (s->cur_file_info.compression_method!=Z_DEFLATED))
      err=UNZ_BADZIPFILE;

   pfile_in_zip_read_info->crc32_wait=s->cur_file_info.crc;
   pfile_in_zip_read_info->crc32=0;
   pfile_in_zip_read_info->compression_method =
   s->cur_file_info.compression_method;
   pfile_in_zip_read_info->filestream=s->filestream;
   pfile_in_zip_read_info->z_filefunc=s->z_filefunc;
   pfile_in_zip_read_info->byte_before_the_zipfile=s->byte_before_the_zipfile;

   pfile_in_zip_read_info->stream.total_out = 0;

   if ((s->cur_file_info.compression_method==Z_DEFLATED) &&
         (!raw))
   {
      pfile_in_zip_read_info->stream.zalloc = (alloc_func)0;
      pfile_in_zip_read_info->stream.zfree = (free_func)0;
      pfile_in_zip_read_info->stream.opaque = (voidpf)0;
      pfile_in_zip_read_info->stream.next_in = (byte* )0;
      pfile_in_zip_read_info->stream.avail_in = 0;

      err=inflateInit2(&pfile_in_zip_read_info->stream, -MAX_WBITS);
      if (err == Z_OK)
         pfile_in_zip_read_info->stream_initialised=1;
      else
         return err;
      /* windowBits is passed < 0 to tell that there is no zlib header.
       * Note that in this case inflate *requires* an extra "dummy" byte
       * after the compressed stream in order to complete decompression and
       * return Z_STREAM_END.
       * In unzip, i don't wait absolutely Z_STREAM_END because I known the
       * size_i32 of both compressed and uncompressed data
       */
   }
   pfile_in_zip_read_info->rest_read_compressed =
   s->cur_file_info.compressed_size ;
   pfile_in_zip_read_info->rest_read_uncompressed =
   s->cur_file_info.uncompressed_size ;


   pfile_in_zip_read_info->pos_in_zipfile =
   s->cur_file_info_internal.offset_curfile + SIZEZIPLOCALHEADER +
   iSizeVar;

   pfile_in_zip_read_info->stream.avail_in = (u32)0;

   s->pfile_in_zip_read = pfile_in_zip_read_info;

#    ifndef NOUNCRYPT
   if (password != nullptr)
   {
      i32 i;
      s->pcrc_32_tab = zip_get_crc_table();
      init_keys(password,s->keys,s->pcrc_32_tab);
      if (ZSEEK(s->z_filefunc, s->filestream,
                s->pfile_in_zip_read->pos_in_zipfile +
                s->pfile_in_zip_read->byte_before_the_zipfile,
                SEEK_SET)!=0)
         return UNZ_INTERNALERROR;
      if(ZREAD(s->z_filefunc, s->filestream,source, 12)<12)
         return UNZ_INTERNALERROR;

      for (i = 0; i<12; i++)
         zdecode(s->keys,s->pcrc_32_tab,source[i]);

      s->pfile_in_zip_read->pos_in_zipfile+=12;
      s->encrypted=1;
   }
#    endif


   return UNZ_OK;
}

extern i32 CLASS_DECL_ACME unzOpenCurrentFile (
unzFile file)
{
   return unzOpenCurrentFile3(file, nullptr, nullptr, 0, nullptr);
}

extern i32 CLASS_DECL_ACME unzOpenCurrentFilePassword (
unzFile file,
const char* password)
{
   return unzOpenCurrentFile3(file, nullptr, nullptr, 0, password);
}

extern i32 CLASS_DECL_ACME unzOpenCurrentFile2 (
unzFile file,
i32* method,
i32* level,
i32 raw)
{
   return unzOpenCurrentFile3(file, method, level, raw, nullptr);
}

/*
  read bytes from the current spfile->
  buf contain buffer where data must be copied
  len the size_i32 of buf.

  return the number of byte copied if somes bytes are copied
  return 0 if the end of file was reached
  return <0 with error code if there is an error
    (UNZ_ERRNO for IO error, or zLib error for uncompress error)
*/
extern i32 CLASS_DECL_ACME unzReadCurrentFile  (
unzFile file,
voidp buf,
u32 len)
{
   i32 err=UNZ_OK;
   uptr iRead = 0;
   unz_s* s;
   file_in_zip_read_info_s* pfile_in_zip_read_info;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   pfile_in_zip_read_info=s->pfile_in_zip_read;

   if (pfile_in_zip_read_info==nullptr)
      return UNZ_PARAMERROR;


   if (pfile_in_zip_read_info->read_buffer == nullptr)
      return UNZ_END_OF_LIST_OF_FILE;
   if (len==0)
      return 0;

   pfile_in_zip_read_info->stream.next_out = (byte*)buf;

   pfile_in_zip_read_info->stream.avail_out = (u32)len;

   if (len>pfile_in_zip_read_info->rest_read_uncompressed)
      pfile_in_zip_read_info->stream.avail_out =
      (u32)pfile_in_zip_read_info->rest_read_uncompressed;

   while (pfile_in_zip_read_info->stream.avail_out>0)
   {
      if ((pfile_in_zip_read_info->stream.avail_in==0) &&
            (pfile_in_zip_read_info->rest_read_compressed>0))
      {
         u32 uReadThis = UNZ_BUFSIZE;
         if (pfile_in_zip_read_info->rest_read_compressed<uReadThis)
            uReadThis = (u32)pfile_in_zip_read_info->rest_read_compressed;
         if (uReadThis == 0)
            return UNZ_EOF;
         if (ZSEEK(pfile_in_zip_read_info->z_filefunc,
                   pfile_in_zip_read_info->filestream,
                   pfile_in_zip_read_info->pos_in_zipfile +
                   pfile_in_zip_read_info->byte_before_the_zipfile,
                   ZLIB_FILEFUNC_SEEK_SET)!=0)
            return UNZ_ERRNO;
         if (ZREAD(pfile_in_zip_read_info->z_filefunc,
                   pfile_in_zip_read_info->filestream,
                   pfile_in_zip_read_info->read_buffer,
                   uReadThis)!=uReadThis)
            return UNZ_ERRNO;


#            ifndef NOUNCRYPT
         if(s->encrypted)
         {
            u32 i;
            for(i=0; i<uReadThis; i++)
               pfile_in_zip_read_info->read_buffer[i] =
               zdecode(s->keys,s->pcrc_32_tab,
                       pfile_in_zip_read_info->read_buffer[i]);
         }
#            endif


         pfile_in_zip_read_info->pos_in_zipfile += uReadThis;

         pfile_in_zip_read_info->rest_read_compressed-=uReadThis;

         pfile_in_zip_read_info->stream.next_in =
         (byte*)pfile_in_zip_read_info->read_buffer;
         pfile_in_zip_read_info->stream.avail_in = (u32)uReadThis;
      }

      if ((pfile_in_zip_read_info->compression_method==0) || (pfile_in_zip_read_info->raw))
      {
         uptr uDoCopy,i ;

         if ((pfile_in_zip_read_info->stream.avail_in == 0) &&
               (pfile_in_zip_read_info->rest_read_compressed == 0))
            return (iRead==0) ? UNZ_EOF : (i32) iRead;

         if (pfile_in_zip_read_info->stream.avail_out <
               pfile_in_zip_read_info->stream.avail_in)
            uDoCopy = pfile_in_zip_read_info->stream.avail_out ;
         else
            uDoCopy = pfile_in_zip_read_info->stream.avail_in ;

         for (i=0; i<uDoCopy; i++)
            *(pfile_in_zip_read_info->stream.next_out+i) =
            *(pfile_in_zip_read_info->stream.next_in+i);

         pfile_in_zip_read_info->crc32 = (u32) crc32(pfile_in_zip_read_info->crc32,
                                         pfile_in_zip_read_info->stream.next_out,
                                         (u32) uDoCopy);
         pfile_in_zip_read_info->rest_read_uncompressed-=uDoCopy;
         pfile_in_zip_read_info->stream.avail_in -= (::u32) uDoCopy;
         pfile_in_zip_read_info->stream.avail_out -= (::u32) uDoCopy;
         pfile_in_zip_read_info->stream.next_out += uDoCopy;
         pfile_in_zip_read_info->stream.next_in += uDoCopy;
         pfile_in_zip_read_info->stream.total_out += (uLong) uDoCopy;
         iRead += uDoCopy;
      }
      else
      {
         uptr uTotalOutBefore,uTotalOutAfter;
         const u8 *bufBefore;
         uptr uOutThis;
         i32 flush=Z_SYNC_FLUSH;

         uTotalOutBefore = pfile_in_zip_read_info->stream.total_out;
         bufBefore = pfile_in_zip_read_info->stream.next_out;

         /*
         if ((pfile_in_zip_read_info->rest_read_uncompressed ==
                  pfile_in_zip_read_info->stream.avail_out) &&
             (pfile_in_zip_read_info->rest_read_compressed == 0))
             flush = Z_FINISH;
         */
         err=inflate(&pfile_in_zip_read_info->stream,flush);

         uTotalOutAfter = pfile_in_zip_read_info->stream.total_out;
         uOutThis = uTotalOutAfter-uTotalOutBefore;

         pfile_in_zip_read_info->crc32 = (u32)
                                         crc32(pfile_in_zip_read_info->crc32,bufBefore,
                                               (u32)(uOutThis));

         pfile_in_zip_read_info->rest_read_uncompressed -=
         uOutThis;

         iRead += (u32)(uTotalOutAfter - uTotalOutBefore);

         if (err==Z_STREAM_END)
            return (iRead==0) ? UNZ_EOF : (i32) iRead;
         if (err!=Z_OK)
            break;
      }
   }

   if (err==Z_OK)
      return (i32) iRead;
   return err;
}


/*
  Give the current position in uncompressed data
*/
extern iptr CLASS_DECL_ACME unztell (
unzFile file)
{
   unz_s* s;
   file_in_zip_read_info_s* pfile_in_zip_read_info;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   pfile_in_zip_read_info=s->pfile_in_zip_read;

   if (pfile_in_zip_read_info==nullptr)
      return UNZ_PARAMERROR;

   return (iptr)pfile_in_zip_read_info->stream.total_out;
}


/*
  return 1 if the end of file was reached, 0 elsewhere
*/
extern i32 CLASS_DECL_ACME unzeof (
unzFile file)
{
   unz_s* s;
   file_in_zip_read_info_s* pfile_in_zip_read_info;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   pfile_in_zip_read_info=s->pfile_in_zip_read;

   if (pfile_in_zip_read_info==nullptr)
      return UNZ_PARAMERROR;

   if (pfile_in_zip_read_info->rest_read_uncompressed == 0)
      return 1;
   else
      return 0;
}



/*
  read extra field from the current file (opened by unzOpenCurrentFile)
  This is the static-header version of the extra field (sometimes, there is
    more info in the static-header version than in the central-header)

  if buf==nullptr, it return the size_i32 of the static extra field that can be read

  if buf!=nullptr, len is the size_i32 of the buffer, the extra header is copied in
    buf.
  the return value is the number of bytes copied in buf, or (if <0)
    the error code
*/
extern i32 CLASS_DECL_ACME unzGetLocalExtrafield (
unzFile file,
voidp buf,
u32 len)
{
   unz_s* s;
   file_in_zip_read_info_s* pfile_in_zip_read_info;
   u32 read_now;
   uptr size_to_read;

   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   pfile_in_zip_read_info=s->pfile_in_zip_read;

   if (pfile_in_zip_read_info==nullptr)
      return UNZ_PARAMERROR;

   size_to_read = (pfile_in_zip_read_info->size_local_extrafield -
                   pfile_in_zip_read_info->pos_local_extrafield);

   if (buf==nullptr)
      return (i32)size_to_read;

   if (len>size_to_read)
      read_now = (u32)size_to_read;
   else
      read_now = (u32)len ;

   if (read_now==0)
      return 0;

   if (ZSEEK(pfile_in_zip_read_info->z_filefunc,
             pfile_in_zip_read_info->filestream,
             pfile_in_zip_read_info->offset_local_extrafield +
             pfile_in_zip_read_info->pos_local_extrafield,
             ZLIB_FILEFUNC_SEEK_SET)!=0)
      return UNZ_ERRNO;

   if (ZREAD(pfile_in_zip_read_info->z_filefunc,
             pfile_in_zip_read_info->filestream,
             buf,size_to_read)!=size_to_read)
      return UNZ_ERRNO;

   return (i32)read_now;
}

/*
  close the file in zip opened with unzipOpenCurrentFile
  Return UNZ_CRCERROR if all the file was read but the CRC is not good
*/
extern i32 CLASS_DECL_ACME unzCloseCurrentFile (
unzFile file)
{
   i32 err=UNZ_OK;

   unz_s* s;
   file_in_zip_read_info_s* pfile_in_zip_read_info;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;
   pfile_in_zip_read_info=s->pfile_in_zip_read;

   if (pfile_in_zip_read_info==nullptr)
      return UNZ_PARAMERROR;


   if ((pfile_in_zip_read_info->rest_read_uncompressed == 0) &&
         (!pfile_in_zip_read_info->raw))
   {
      if (pfile_in_zip_read_info->crc32 != pfile_in_zip_read_info->crc32_wait)
         err=UNZ_CRCERROR;
   }


   TRYFREE(pfile_in_zip_read_info->read_buffer);
   pfile_in_zip_read_info->read_buffer = nullptr;
   if (pfile_in_zip_read_info->stream_initialised)
      inflateEnd(&pfile_in_zip_read_info->stream);

   pfile_in_zip_read_info->stream_initialised = 0;
   TRYFREE(pfile_in_zip_read_info);

   s->pfile_in_zip_read=nullptr;

   return err;
}


/*
  get the global comment string of the ZipFile, in the szComment buffer.
  uSizeBuf is the size_i32 of the szComment buffer.
  return the number of byte copied or an error code <0
*/
extern i32 CLASS_DECL_ACME unzGetGlobalComment (
unzFile file,
char *szComment,
uptr uSizeBuf)
{
//    i32 err=UNZ_OK;
   unz_s* s;
   uptr uReadThis ;
   if (file==nullptr)
      return UNZ_PARAMERROR;
   s=(unz_s*)file;

   uReadThis = uSizeBuf;
   if (uReadThis>s->gi.size_comment)
      uReadThis = s->gi.size_comment;

   if (ZSEEK(s->z_filefunc,s->filestream,s->central_pos+22,ZLIB_FILEFUNC_SEEK_SET)!=0)
      return UNZ_ERRNO;

   if (uReadThis>0)
   {
      *szComment='\0';
      if (ZREAD(s->z_filefunc,s->filestream,szComment,uReadThis)!=uReadThis)
         return UNZ_ERRNO;
   }

   if ((szComment != nullptr) && (uSizeBuf > s->gi.size_comment))
      *(szComment+s->gi.size_comment)='\0';
   return (i32)uReadThis;
}

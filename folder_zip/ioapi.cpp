/* ioapi.ca -- IO axis function header for compress/uncompress .zip
   files using zlib + zip or unzip API

   Version 1.00, September 10th, 2003

   Copyright (C) 1998-2003 Gilles Vollant
*/
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


#include <stdio.h>

/* I've found an old Unix (a SunOS 4.1.3_U1) without all SEEK_* defined.... */

#ifndef SEEK_CUR
#define SEEK_CUR    1
#endif

#ifndef SEEK_END
#define SEEK_END    2
#endif

#ifndef SEEK_SET
#define SEEK_SET    0
#endif

extern "C" voidpf ZCALLBACK fopen_file_func OF((
      voidpf opaque,
      const char* filename,
      i32 mode));

extern "C" uptr ZCALLBACK fread_file_func OF((
      voidpf opaque,
      voidpf stream,
      void * buf,
      uptr size));

extern "C" uptr ZCALLBACK fwrite_file_func OF((
      voidpf opaque,
      voidpf stream,
      const void * buf,
      uptr size));

extern "C" long ZCALLBACK ftell_file_func OF((
      voidpf opaque,
      voidpf stream));

extern "C" long ZCALLBACK fseek_file_func OF((
      voidpf opaque,
      voidpf stream,
      uptr offset,
      i32 origin));

extern "C" i32 ZCALLBACK fclose_file_func OF((
      voidpf opaque,
      voidpf stream));

extern "C" i32 ZCALLBACK ferror_file_func OF((
      voidpf opaque,
      voidpf stream));


extern "C" voidpf ZCALLBACK fopen_file_func (voidpf opaque, const char * filename, i32 mode)
{
   FILE* file = nullptr;
   const char* mode_fopen = nullptr;
   errno_t err = 0;
   if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER)==ZLIB_FILEFUNC_MODE_READ)
      mode_fopen = "rb";
   else if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
      mode_fopen = "r+b";
   else if (mode & ZLIB_FILEFUNC_MODE_CREATE)
      mode_fopen = "wb";


   if ((filename!=nullptr) && (mode_fopen != nullptr))
#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(SOLARIS) || defined(FREEBSD)
   {
      file = fopen(filename, mode_fopen);
      if(file == nullptr)
         err = errno;
   }
#else
      err = fopen_s(&file, filename, mode_fopen);
#endif
   if(err != 0)
      return nullptr;
   else
      return file;
}


extern "C" uptr ZCALLBACK fread_file_func (voidpf opaque, voidpf stream, void * buf, uptr size)
{
   uptr ret;
   ret = (uptr) fread(buf, 1, (size_t) size, (FILE *)stream);
   return ret;
}


extern "C" uptr ZCALLBACK fwrite_file_func (voidpf opaque, voidpf stream, const void * buf, uptr size)
{
   uptr ret;
   ret = (uptr) fwrite(buf, 1, (size_t) size, (FILE *)stream);
   return ret;
}

extern "C" long ZCALLBACK ftell_file_func (voidpf opaque, voidpf stream)
{
   long ret;
   ret = ftell((FILE *)stream);
   return ret;
}

extern "C" long ZCALLBACK fseek_file_func (voidpf opaque, voidpf stream, uptr offset, i32 origin)
{
   i32 fseek_origin=0;
   long ret;
   switch (origin)
   {
   case ZLIB_FILEFUNC_SEEK_CUR :
      fseek_origin = SEEK_CUR;
      break;
   case ZLIB_FILEFUNC_SEEK_END :
      fseek_origin = SEEK_END;
      break;
   case ZLIB_FILEFUNC_SEEK_SET :
      fseek_origin = SEEK_SET;
      break;
   default: return -1;
   }
   ret = 0;
   i32 iSeek = (i32) minimum((u32) INT_MAX, offset);
   fseek((FILE *)stream, iSeek, fseek_origin);
   while(true)
   {
      offset -= iSeek;
      if(offset <= 0)
         break;
      iSeek = (i32) minimum((u32) INT_MAX, offset);
      fseek((FILE *)stream, fseek_origin == ZLIB_FILEFUNC_SEEK_END ? -iSeek : iSeek, SEEK_CUR);
   }
   return ret;
}

extern "C" i32 ZCALLBACK fclose_file_func (voidpf opaque, voidpf stream)
{
   i32 ret;
   ret = fclose((FILE *)stream);
   return ret;
}

extern "C" i32 ZCALLBACK ferror_file_func  (voidpf opaque, voidpf stream)
{
   i32 ret;
   ret = ferror((FILE *)stream);
   return ret;
}

void fill_fopen_filefunc (zlib_filefunc_def * pzlib_filefunc_def)
{
   pzlib_filefunc_def->zopen_file = fopen_file_func;
   pzlib_filefunc_def->zread_file = fread_file_func;
   pzlib_filefunc_def->zwrite_file = fwrite_file_func;
   pzlib_filefunc_def->ztell_file = ftell_file_func;
   pzlib_filefunc_def->zseek_file = fseek_file_func;
   pzlib_filefunc_def->zclose_file = fclose_file_func;
   pzlib_filefunc_def->zerror_file = ferror_file_func;
   pzlib_filefunc_def->opaque = nullptr;
}

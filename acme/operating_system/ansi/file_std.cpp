#include "framework.h"
//#include "acme/filesystem/filesystem/path.h"
#include <stdio.h>


FILE * FILE_open(const_char_pointer path, const_char_pointer attr, int iShare)
{

#if defined(WINDOWS)

   wstring wstrPath(path);

   wstring wstrAttr(attr);

   return _wfsopen(wstrPath, wstrAttr, iShare);

#else

   return fopen(path, attr);

#endif

}


int FILE_close(FILE *fp)
{

   return fclose(fp);

}


int FILE_eof(FILE *fp)
{

   return feof(fp);

}


int FILE_flush(FILE * fp)
{

   return fflush(fp);

}


filesize FILE_seek(FILE *fp, filesize offset, int origin)
{

   return fseek(fp, (long) (offset), origin);

}


filesize FILE_tell(FILE *fp)
{

   return ftell(fp);

}


filesize FILE_read(void *buffer, memsize size, memsize count, FILE *str)
{

   return fread(buffer, (size_t) size, (size_t) count, str);

}


filesize FILE_write(const void *buffer, memsize size, memsize count, FILE *str)
{

   return fwrite(buffer, (size_t) size, (size_t) count, str);

}


char * FILE_gets(char * str, character_count n, FILE *s)
{

   return fgets(str, (int) n, s);

}


int FILE_getc(FILE * s)
{

   return ::getc(s);

   /*if (s == 0 || FILE_eof(s))
   {

      return EOF;

   }

   uchar c;

   FILE_read(&c, 1, sizeof(uchar), s);

   return (int)c;*/
}


int FILE_ungetc(int c, FILE *s)
{

   return ::ungetc(c, s);

   //if (s == 0)
   //{

   //   return EOF;

   //}

   //FILE_seek(s, -1, SEEK_CUR);

   //return (int)c;

}


int FILE_error(FILE *fp)
{

   return ferror(fp);

}


filesize FILE_get_size(FILE * fp)
{

#ifdef WINDOWS
   auto pos = _ftelli64(fp);
#elif (defined(__ANDROID__) && __ANDROID_API__ < 24) || defined(__APPLE__) || defined(__BSD__)
   auto pos = ftello(fp);
#else
   auto pos = ftello64(fp);
#endif

   fseek(fp, 0, SEEK_END);

#ifdef WINDOWS
   auto len = _ftelli64(fp);
#elif (defined(__ANDROID__) && __ANDROID_API__ < 24) || defined(__APPLE__) || defined(__BSD__)
   auto len = ftello(fp);
#else
   auto len = ftello64(fp);
#endif

#ifdef WINDOWS
   _fseeki64(fp, (long) (pos), SEEK_SET);
#elif (defined(__ANDROID__) && __ANDROID_API__ < 24) || defined(__APPLE__) || defined(__BSD__)
   fseeko(fp, (long)(pos), SEEK_SET);
#else
   fseeko64(fp, (long) (pos), SEEK_SET);
#endif

   return len;

}


//filesize FILE_get_size(FILE * str)
//{
//
//   return FILE_get_size(str);
//
//}



#if !defined(__APPLE__) && !defined(WINDOWS) && !defined(__BSD__)

::file::path __xxxnode_full_file_path(file::path path)
{

   string str;

   return realpath(path.c_str(), str.get_buffer(PATH_MAX * 8));

}


#endif


int file_touch(const ::scoped_string & scopedstr)
{

   FILE * pfile = ::fopen(scopedstr.c_str(), "a");

   if (pfile == nullptr)
   {

      return false;

   }

   ::fclose(pfile);

   return true;

}







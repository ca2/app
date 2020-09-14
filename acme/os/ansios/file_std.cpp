#include "framework.h"

#include <stdio.h>







FILE *fopen_dup(const char *path, const char *attr, int iShare)
{

#if defined(WINDOWS)

   wstring wstrPath(path);

   wstring wstrAttr(attr);

   return _wfsopen(wstrPath, wstrAttr, iShare);

#else

   return fopen(path, attr);

#endif

}



i32 fclose_dup(FILE *fp)
{


   return fclose(fp);
}

i32 feof_dup(FILE *fp)
{


   return feof(fp);


}

i32 fflush_dup(FILE * fp)
{

   return fflush(fp);

}

filesize fseek_dup(FILE *fp, filesize offset, i32 origin)
{

   return fseek(fp, (long) (offset), origin);

}

filesize ftell_dup(FILE *fp)
{


   return ftell(fp);
}


filesize fread_dup(void *buffer, memsize size, memsize count, FILE *str)
{

   return fread(buffer, (size_t) size, (size_t) count, str);

}


filesize fwrite_dup(const void *buffer, memsize size, memsize count, FILE *str)
{

   return fwrite(buffer, (size_t) size, (size_t) count, str);

}


char * fgets_dup(char * str, strsize n, FILE *s)
{

   return fgets(str, (int) n, s);

}


i32 fgetc_dup(FILE * s)
{

   if (s == 0 || feof_dup(s))
   {

      return EOF;

   }

   uchar c;

   fread_dup(&c, 1, sizeof(uchar), s);

   return (i32)c;
}


i32 ungetc_dup(i32 c, FILE *s)
{

   if (s == 0)
   {

      return EOF;

   }

   fseek_dup(s, -1, SEEK_CUR);

   return (i32)c;
}


i32 ferror_dup(FILE *fp)
{

   return ferror(fp);

}


filesize fsize_dup(FILE * fp)
{

   auto pos = ftell(fp);

   fseek(fp, 0, SEEK_END);

   auto len = ftell(fp);

   fseek(fp, (long) (pos), SEEK_SET);

   return len;

}


filesize flen_dup(FILE * str)
{

   return fsize_dup(str);

}



#if !defined(__APPLE__) && !defined(WINDOWS)

::file::path __node_full_file_path(file::path path)
{

   string str;

   return realpath(path, str.get_string_buffer(PATH_MAX * 8));

}


#endif


i32 file_touch_dup(const char * psz)
{

   FILE * pfile = ::fopen(psz, "a");

   if (pfile == nullptr)
   {

      return FALSE;

   }

   ::fclose(pfile);

   return TRUE;

}







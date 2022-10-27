#pragma once


#ifndef WINDOWS

#define _SH_DENYNO 0
#define _SH_DENYWR 0
#define _SH_DENYRW 0

#endif


//CLASS_DECL_ACME int_bool dir_mk(const char * psz);
//CLASS_DECL_ACME int_bool dir_appdata(char * psz, size_t size);
//CLASS_DECL_ACME int_bool file_is_true_dup(const char * path);

//CLASS_DECL_ACME int_bool file_path_is_relative(const char * psz);

//CLASS_DECL_ACME int_bool acmefile()->exists(const char * path);


//CLASS_DECL_ACME int_bool is_file_ok(const char * path1, const char * pszTemplate);
//CLASS_DECL_ACME int_bool xxxfile_put_contents(const char * path, const void * contents, memsize len);
//CLASS_DECL_ACME int_bool get_temp_file_name_dup(char * szRet, count iBufferSize, const char * lpszName, const char * pszExtension);
//CLASS_DECL_ACME int_bool get_temp_file_name_template(char * szRet, strsize iBufferSize, const char * lpszName, const char * pszExtension, const char * pszTemplate);
//CLASS_DECL_ACME filesize file_length(const char * path);



//CLASS_DECL_ACME bool file_path_is_equal(const char * pszPath1, const char * pszPath2);


//CLASS_DECL_ACME int_bool file_copy_dup(const char * pszDup, const char * pszSrc, int_bool bOverwrite);


//CLASS_DECL_ACME void _init_FILE();
//
//CLASS_DECL_ACME FILE * FILE_open(const char *path, const char *attrs, int iShare);
//CLASS_DECL_ACME i32 FILE_printf(FILE *fp, const char *s, ...);
//CLASS_DECL_ACME i32 FILE_close(FILE *fp);
//CLASS_DECL_ACME i32 FILE_eof(FILE *fp);
//CLASS_DECL_ACME filesize FILE_seek(FILE *str, filesize offset, i32 origin);
//CLASS_DECL_ACME filesize FILE_tell(FILE *fp);
//CLASS_DECL_ACME filesize FILE_read(void * buffer, memsize size, memsize count, FILE * str);
//CLASS_DECL_ACME filesize FILE_write(const void * buffer, memsize size, memsize count, FILE * str);
//CLASS_DECL_ACME char * FILE_gets(char * str, strsize n, FILE *s);
//CLASS_DECL_ACME i32 FILE_getc(FILE *s);
//CLASS_DECL_ACME i32 FILE_ungetc(i32 c,FILE *s);
//CLASS_DECL_ACME i32 FILE_error(FILE *s);
//CLASS_DECL_ACME i32 FILE_flush(FILE *s);
//CLASS_DECL_ACME filesize FILE_get_size(FILE *s);
//CLASS_DECL_ACME i32 FILE_touch(const char * psz);
//
//
//#ifdef WINDOWS
//CLASS_DECL_ACME FILE *FILE_wopen(const unichar * path, const unichar * attrs, int iShare);
//CLASS_DECL_ACME i32 FILE_wprintf(FILE * fp, const unichar * s, ...);
//CLASS_DECL_ACME unichar *FILE_getws(unichar * str, strsize n, FILE * s);
//CLASS_DECL_ACME wint_t FILE_getwc(FILE * s);
//CLASS_DECL_ACME wint_t FILE_ungetwc(wint_t w, FILE * s);
//#endif
//
//
//CLASS_DECL_ACME filesize FILE_size(FILE * f);
//
//CLASS_DECL_ACME int_bool fd_set_size(i32 fd,size_t iSize);
//CLASS_DECL_ACME int_bool FILE_set_size(FILE * file,size_t iSize);
//
//
//
//
//
//
//
//
//
////   #pragma once
//
//
//
////typedef u64  filesize;
////typedef u64  filesize;
////typedef i64   filesize;
//

CLASS_DECL_ACME bool is_directory(const char * path);

CLASS_DECL_ACME void create_directory(const char * path);

CLASS_DECL_ACME void erase_directory(const char* path);

CLASS_DECL_ACME bool file_exists(const char * path);

CLASS_DECL_ACME void file_delete(const char * path);




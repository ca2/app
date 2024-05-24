#pragma once


#ifndef WINDOWS

#define _SH_DENYNO 0
#define _SH_DENYWR 0
#define _SH_DENYRW 0

#endif


//CLASS_DECL_ACID int_bool dir_mk(const ::scoped_string & scopedstr);
//CLASS_DECL_ACID int_bool dir_appdata(char * psz, size_t size);
//CLASS_DECL_ACID int_bool file_is_true_dup(const ::file::path & path);

//CLASS_DECL_ACID int_bool file_path_is_relative(const ::scoped_string & scopedstr);

//CLASS_DECL_ACID int_bool acefile()->exists(const ::file::path & path);


//CLASS_DECL_ACID int_bool is_file_ok(const ::file::path & path1, const ::scoped_string & scopedstrTemplate);
//CLASS_DECL_ACID int_bool xxxfile_put_contents(const ::file::path & path, const void * contents, memsize len);
//CLASS_DECL_ACID int_bool get_temp_file_name_dup(char * szRet, count iBufferSize, const char * lpszName, const ::scoped_string & scopedstrExtension);
//CLASS_DECL_ACID int_bool get_temp_file_name_template(char * szRet, strsize iBufferSize, const char * lpszName, const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrTemplate);
//CLASS_DECL_ACID filesize file_length(const ::file::path & path);



//CLASS_DECL_ACID bool file_path_is_equal(const ::file::path & path1, const ::file::path & path2);


//CLASS_DECL_ACID int_bool file_copy_dup(const ::scoped_string & scopedstrDup, const ::scoped_string & scopedstrSrc, int_bool bOverwrite);


//CLASS_DECL_ACID void _init_FILE();
//
//CLASS_DECL_ACID FILE * FILE_open(const char *path, const char *attrs, int iShare);
//CLASS_DECL_ACID i32 FILE_printf(FILE *fp, const char *s, ...);
//CLASS_DECL_ACID i32 FILE_close(FILE *fp);
//CLASS_DECL_ACID i32 FILE_eof(FILE *fp);
//CLASS_DECL_ACID filesize FILE_seek(FILE *str, filesize offset, i32 origin);
//CLASS_DECL_ACID filesize FILE_tell(FILE *fp);
//CLASS_DECL_ACID filesize FILE_read(void * buffer, memsize size, memsize count, FILE * str);
//CLASS_DECL_ACID filesize FILE_write(const void * buffer, memsize size, memsize count, FILE * str);
//CLASS_DECL_ACID char * FILE_gets(char * str, strsize n, FILE *s);
//CLASS_DECL_ACID i32 FILE_getc(FILE *s);
//CLASS_DECL_ACID i32 FILE_ungetc(i32 c,FILE *s);
//CLASS_DECL_ACID i32 FILE_error(FILE *s);
//CLASS_DECL_ACID i32 FILE_flush(FILE *s);
//CLASS_DECL_ACID filesize FILE_get_size(FILE *s);
//CLASS_DECL_ACID i32 FILE_touch(const ::scoped_string & scopedstr);
//
//
//#ifdef WINDOWS
//CLASS_DECL_ACID FILE *FILE_wopen(const unichar * path, const unichar * attrs, int iShare);
//CLASS_DECL_ACID i32 FILE_wprintf(FILE * fp, const unichar * s, ...);
//CLASS_DECL_ACID unichar *FILE_getws(unichar * str, strsize n, FILE * s);
//CLASS_DECL_ACID wint_t FILE_getwc(FILE * s);
//CLASS_DECL_ACID wint_t FILE_ungetwc(wint_t w, FILE * s);
//#endif
//
//
//CLASS_DECL_ACID filesize FILE_size(FILE * f);
//
//CLASS_DECL_ACID int_bool fd_set_size(i32 fd,size_t iSize);
//CLASS_DECL_ACID int_bool FILE_set_size(FILE * file,size_t iSize);
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

CLASS_DECL_ACID bool is_directory(const ::file::path & path);

CLASS_DECL_ACID void create_directory(const ::file::path & path);

CLASS_DECL_ACID void erase_directory(const ::file::path & path);

CLASS_DECL_ACID bool file_exists(const ::file::path & path);

CLASS_DECL_ACID void file_delete(const ::file::path & path);




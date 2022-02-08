/*
 * BinReloc - a library for creating relocatable executables
 * Written by: Hongli Lai <h.lai@chello.nl>
 * http://autopackage.org/
 *
 * This source code is public domain. You can relicense this code
 * under whatever license you want.
 *
 * See http://autopackage.org/docs/binreloc/ for
 * more information and how to use this.
 */


#include "framework.h"

#ifndef __BINRELOC_C__
#define __BINRELOC_C__

#ifdef RASPBIAN
#include <sys/types.h>
#include <unistd.h>
#endif


#ifdef ENABLE_BINRELOC
#include <sys/stat.h>

#endif /* ENABLE_BINRELOC */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/** @internal
 * Find the canonical filename of the executable. Returns the filename
 * (which must be freed) or nullptr on error. If the parameter 'error' is
 * not nullptr, the error code will be stored there, if an error occured.
 */
static char *
_br_find_exe (BrInitError *error)
{
#ifndef ENABLE_BINRELOC
   if (error)
      *error = BR_INIT_ERROR_DISABLED;
   return nullptr;
#elif (defined(_WIN32) || defined(WIN32))
   /* Use GetModuleFileName */
   wstring path;
   path.alloc(MAX_PATH);
   GetModuleFileNameW(nullptr, path, MAX_PATH);
   path.release_string_buffer();
   return ansi_duplicate(::str::international::unicode_to_utf8(path));
#else
   char *path, *path2, *line, *result;
   size_t buf_size;
   ssize_t size;
   struct stat stat_buf;
   FILE *f;

   /* Read from /proc/self/exe (symlink) */
   if (sizeof (path) > SSIZE_MAX)
      buf_size = SSIZE_MAX - 1;
   else
      buf_size = PATH_MAX - 1;
   path = (char *) malloc (buf_size);
   if (path == nullptr)
   {
      /* Cannot allocate memory. */
      if (error)
         *error = BR_INIT_ERROR_NOMEM;
      return nullptr;
   }
   path2 = (char *) malloc (buf_size);
   if (path2 == nullptr)
   {
      /* Cannot allocate memory. */
      if (error)
         *error = BR_INIT_ERROR_NOMEM;
      free (path);
      return nullptr;
   }

   ansi_count_copy (path2, "/proc/self/exe", buf_size - 1);

   while (1)
   {
      i32 i;

      size = readlink (path2, path, buf_size - 1);
      if (size == -1)
      {
         /* Error. */
         free (path2);
         break;
      }

      /* readlink() success. */
      path[size_i32] = '\0';

      /* Check whether the symlink's target is also a symlink.
       * We want to get the final target. */
      i = stat (path, &stat_buf);
      if (i == -1)
      {
         /* Error. */
         free (path2);
         break;
      }

      /* stat() success. */
      if (!S_ISLNK (stat_buf.st_mode))
      {
         /* path is not a symlink. Done. */
         free (path2);
         return path;
      }

      /* path is a symlink. Continue loop and resolve this. */
      ansi_count_copy (path, path2, buf_size - 1);
   }


   /* readlink() or stat() failed; this can happen when the program is
    * running in Valgrind 2.2. Read from /proc/self/maps as fallback. */

   buf_size = PATH_MAX + 128;
   line = (char *) realloc (path, buf_size);
   if (line == nullptr)
   {
      /* Cannot allocate memory. */
      free (path);
      if (error)
         *error = BR_INIT_ERROR_NOMEM;
      return nullptr;
   }

   f = fopen ("/proc/self/maps", "r");
   if (f == nullptr)
   {
      free (line);
      if (error)
         *error = BR_INIT_ERROR_OPEN_MAPS;
      return nullptr;
   }

   /* The first entry should be the executable name. */
   result = fgets (line, (i32) buf_size, f);
   if (result == nullptr)
   {
      fclose (f);
      free (line);
      if (error)
         *error = BR_INIT_ERROR_READ_MAPS;
      return nullptr;
   }

   /* Get rid of newline character. */
   buf_size = strlen (line);
   if (buf_size <= 0)
   {
      /* Huh? An empty string? */
      fclose (f);
      free (line);
      if (error)
         *error = BR_INIT_ERROR_INVALID_MAPS;
      return nullptr;
   }
   if (line[buf_size - 1] == 10)
      line[buf_size - 1] = 0;

   /* Extract the filename; it is always an absolute path. */
   path = strchr (line, '/');

   /* Sanity check. */
   if (strstr (line, " r-xp ") == nullptr || path == nullptr)
   {
      fclose (f);
      free (line);
      if (error)
         *error = BR_INIT_ERROR_INVALID_MAPS;
      return nullptr;
   }

   path = strdup (path);
   free (line);
   fclose (f);
   return path;
#endif /* ENABLE_BINRELOC */
}


/** @internal
 * Find the canonical filename of the executable which owns symbol.
 * Returns a filename which must be freed, or nullptr on error.
 */
static char *
_br_find_exe_for_symbol (const void *symbol, BrInitError *error)
{
#ifndef ENABLE_BINRELOC
   if (error)
      *error = BR_INIT_ERROR_DISABLED;
   return (char *) nullptr;
#else
#define SIZE_FOR_LINE PATH_MAX + 100
   FILE *f;
   size_t address_string_len;
   char *address_string, line[SIZE_FOR_LINE], *found;

   if (symbol == nullptr)
      return (char *) nullptr;

   f = fopen ("/proc/self/maps", "r");
   if (f == nullptr)
      return (char *) nullptr;

   address_string_len = 512;
   address_string = (char *) malloc (address_string_len);
   found = (char *) nullptr;

   while (!feof (f))
   {
      char *start_addr, *end_addr, *end_addr_end, *file;
      void *start_addr_p, *end_addr_p;
      size_t len;

      if (fgets (line, SIZE_FOR_LINE, f) == nullptr)
         break;

      /* Sanity check. */
      if (strstr (line, " r-xp ") == nullptr || strchr (line, '/') == nullptr)
         continue;

      /* Parse line. */
      start_addr = line;
      end_addr = strchr (line, '-');
      file = strchr (line, '/');

      /* More sanity check. */
      if (!(file > end_addr && end_addr != nullptr && end_addr[0] == '-'))
         continue;

      end_addr[0] = '\0';
      end_addr++;
      end_addr_end = strchr (end_addr, ' ');
      if (end_addr_end == nullptr)
         continue;

      end_addr_end[0] = '\0';
      len = strlen (file);
      if (len == 0)
         continue;
      if (file[len - 1] == '\n')
         file[len - 1] = '\0';

      /* Get rid of "(deleted)" from the filename. */
      len = strlen (file);
      if (len > 10 && strcmp (file + len - 10, " (deleted)") == 0)
         file[len - 10] = '\0';

      /* I don't know whether this can happen but better safe than sorry. */
      len = strlen (start_addr);
      if (len != strlen (end_addr))
         continue;


      /* Transform the addresses into a string in the form of 0xdeadbeef,
       * then transform that into a pointer. */
      //if (address_string_len < len + 3)
      //{
        // address_string_len = len + 3;
         //address_string = (char *) realloc (address_string, address_string_len);
      //}

      ::memcpy_dup (address_string, "0x", 2);
      ::memcpy_dup (address_string + 2, start_addr, len);
      address_string[2 + len] = '\0';
      sscanf (address_string, "%p", &start_addr_p);

      ::memcpy_dup (address_string, "0x", 2);
      ::memcpy_dup (address_string + 2, end_addr, len);
      address_string[2 + len] = '\0';
      sscanf (address_string, "%p", &end_addr_p);


      if (symbol >= start_addr_p && symbol < end_addr_p)
      {
         found = file;
         break;
      }
   }

   free (address_string);
   fclose (f);

   if (found == nullptr)
      return (char *) nullptr;
   else
      return strdup (found);
#endif /* ENABLE_BINRELOC */
}


#ifndef BINRELOC_RUNNING_DOXYGEN
#undef NULL
#define NULL ((void *) 0) /* typecasted as char* for C++ type safeness */
#endif

static char *exe = (char *) nullptr;


/** Initialize the BinReloc library (for applications).
 *
 * This function must be called before using any other BinReloc functions.
 * It attempts to locate the application's canonical filename.
 *
 * @note If you want to use BinReloc for a library, then you should call
 *       br_init_lib() instead.
 *
 * @lparam error  If BinReloc failed to initialize, then the error code will
 *               be stored in this variable. Set to nullptr if you want to
 *               ignore this. See #BrInitError for a list of error codes.
 *
 * @returns 1 on success, 0 if BinReloc failed to initialize.
 */
i32
br_init (BrInitError *error)
{
   exe = _br_find_exe (error);
   return exe != nullptr;
}

const char * g_psz_br_init_symbol = (const ::string &) nullptr;

void br_init_set_symbol(const ::string & psz)
{
   g_psz_br_init_symbol = psz;
}

/** Initialize the BinReloc library (for libraries).
 *
 * This function must be called before using any other BinReloc functions.
 * It attempts to locate the calling library's canonical filename.
 *
 * @note The BinReloc source code MUST be included in your library, or this
 *       function won't work correctly.
 *
 * @lparam error  If BinReloc failed to initialize, then the error code will
 *               be stored in this variable. Set to nullptr if you want to
 *               ignore this. See #BrInitError for a list of error codes.
 *
 * @returns 1 on success, 0 if a filename cannot be found.
 */
i32
br_init_lib (BrInitError *error)
{
   exe = _br_find_exe_for_symbol ((const void *) g_psz_br_init_symbol, error);
   return exe != nullptr;
}


/** Find the canonical filename of the current application.
 *
 * @lparam default_exe  A default filename which will be used as fallback.
 * @returns A string containing the application's canonical filename,
 *          which must be freed when no longer necessary. If BinReloc is
 *          not initialized, or if br_init() failed, then a copy of
 *          default_exe will be returned. If default_exe is nullptr, then
 *          nullptr will be returned.
 */
char *
br_find_exe (const ::string &default_exe)
{
   if (exe == (char *) nullptr)
   {
      /* BinReloc is not initialized. */
      if (default_exe != (const ::string &) nullptr)
         return strdup (default_exe);
      else
         return (char *) nullptr;
   }
   return strdup (exe);
}


/** Locate the directory in which the current application is installed.
 *
 * The prefix is generated by the following pseudo-code evaluation:
 * \code
 * dirname(exename)
 * \endcode
 *
 * @lparam default_dir  A default directory which will used as fallback.
 * @return A string containing the directory, which must be freed when no
 *         longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_dir
 *         will be returned. If default_dir is nullptr, then nullptr will be
 *         returned.
 */
char *
br_find_exe_dir (const ::string &default_dir)
{
   if (exe == nullptr)
   {
      /* BinReloc not initialized. */
      if (default_dir != nullptr)
         return strdup (default_dir);
      else
         return (char *) nullptr;
   }

   return br_dirname (exe);
}


/** Locate the prefix in which the current application is installed.
 *
 * The prefix is generated by the following pseudo-code evaluation:
 * \code
 * dirname(dirname(exename))
 * \endcode
 *
 * @lparam default_prefix  A default prefix which will used as fallback.
 * @return A string containing the prefix, which must be freed when no
 *         longer necessary. If BinReloc is not initialized, or if
 *         the initialization function failed, then a copy of default_prefix
 *         will be returned. If default_prefix is nullptr, then nullptr will be returned.
 */
char *
br_find_prefix (const ::string &default_prefix)
{
   char *dir1, *dir2;

   if (exe == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_prefix != (const ::string &) nullptr)
         return strdup (default_prefix);
      else
         return (char *) nullptr;
   }

   dir1 = br_dirname (exe);
   dir2 = br_dirname (dir1);
   free (dir1);
   return dir2;
}


/** Locate the application's binary folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/bin"
 * \endcode
 *
 * @lparam default_bin_dir  A default path which will used as fallback.
 * @return A string containing the bin folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if
 *         the initialization function failed, then a copy of default_bin_dir will
 *         be returned. If default_bin_dir is nullptr, then nullptr will be returned.
 */
char *
br_find_bin_dir (const ::string &default_bin_dir)
{
   char *prefix, *dir;

   prefix = br_find_prefix ((const ::string &) nullptr);
   if (prefix == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_bin_dir != (const ::string &) nullptr)
         return strdup (default_bin_dir);
      else
         return (char *) nullptr;
   }

   dir = br_build_path (prefix, "bin");
   free (prefix);
   return dir;
}


/** Locate the application's superuser binary folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/sbin"
 * \endcode
 *
 * @lparam default_sbin_dir  A default path which will used as fallback.
 * @return A string containing the sbin folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_sbin_dir will
 *         be returned. If default_bin_dir is nullptr, then nullptr will be returned.
 */
char *
br_find_sbin_dir (const ::string &default_sbin_dir)
{
   char *prefix, *dir;

   prefix = br_find_prefix ((const ::string &) nullptr);
   if (prefix == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_sbin_dir != (const ::string &) nullptr)
         return strdup (default_sbin_dir);
      else
         return (char *) nullptr;
   }

   dir = br_build_path (prefix, "sbin");
   free (prefix);
   return dir;
}


/** Locate the application's data folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/share"
 * \endcode
 *
 * @lparam default_data_dir  A default path which will used as fallback.
 * @return A string containing the data folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_data_dir
 *         will be returned. If default_data_dir is nullptr, then nullptr will be
 *         returned.
 */
char *
br_find_data_dir (const ::string &default_data_dir)
{
   char *prefix, *dir;

   prefix = br_find_prefix ((const ::string &) nullptr);
   if (prefix == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_data_dir != (const ::string &) nullptr)
         return strdup (default_data_dir);
      else
         return (char *) nullptr;
   }

   dir = br_build_path (prefix, "share");
   free (prefix);
   return dir;
}


/** Locate the application's localization folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/share/locale"
 * \endcode
 *
 * @lparam default_locale_dir  A default path which will used as fallback.
 * @return A string containing the localization folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the
 *         initialization function failed, then a copy of default_locale_dir will be returned.
 *         If default_locale_dir is nullptr, then nullptr will be returned.
 */
char *
br_find_locale_dir (const ::string &default_locale_dir)
{
   char *data_dir, *dir;

   data_dir = br_find_data_dir ((const ::string &) nullptr);
   if (data_dir == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_locale_dir != (const ::string &) nullptr)
         return strdup (default_locale_dir);
      else
         return (char *) nullptr;
   }

   dir = br_build_path (data_dir, "locale");
   free (data_dir);
   return dir;
}


/** Locate the application's library folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/lib"
 * \endcode
 *
 * @lparam default_lib_dir  A default path which will used as fallback.
 * @return A string containing the library folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the initialization
 *         function failed, then a copy of default_lib_dir will be returned.
 *         If default_lib_dir is nullptr, then nullptr will be returned.
 */
char *
br_find_lib_dir (const ::string &default_lib_dir)
{
   char *prefix, *dir;

   prefix = br_find_prefix ((const ::string &) nullptr);
   if (prefix == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_lib_dir != (const ::string &) nullptr)
         return strdup (default_lib_dir);
      else
         return (char *) nullptr;
   }

   dir = br_build_path (prefix, "lib");
   free (prefix);
   return dir;
}


/** Locate the application's libexec folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/libexec"
 * \endcode
 *
 * @lparam default_libexec_dir  A default path which will used as fallback.
 * @return A string containing the libexec folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the initialization
 *         function failed, then a copy of default_libexec_dir will be returned.
 *         If default_libexec_dir is nullptr, then nullptr will be returned.
 */
char *
br_find_libexec_dir (const ::string &default_libexec_dir)
{
   char *prefix, *dir;

   prefix = br_find_prefix ((const ::string &) nullptr);
   if (prefix == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_libexec_dir != (const ::string &) nullptr)
         return strdup (default_libexec_dir);
      else
         return (char *) nullptr;
   }

   dir = br_build_path (prefix, "libexec");
   free (prefix);
   return dir;
}


/** Locate the application's configuration files folder.
 *
 * The path is generated by the following pseudo-code evaluation:
 * \code
 * prefix + "/etc"
 * \endcode
 *
 * @lparam default_etc_dir  A default path which will used as fallback.
 * @return A string containing the etc folder's path, which must be freed when
 *         no longer necessary. If BinReloc is not initialized, or if the initialization
 *         function failed, then a copy of default_etc_dir will be returned.
 *         If default_etc_dir is nullptr, then nullptr will be returned.
 */
char *
br_find_etc_dir (const ::string &default_etc_dir)
{
   char *prefix, *dir;

   prefix = br_find_prefix ((const ::string &) nullptr);
   if (prefix == (char *) nullptr)
   {
      /* BinReloc not initialized. */
      if (default_etc_dir != (const ::string &) nullptr)
         return strdup (default_etc_dir);
      else
         return (char *) nullptr;
   }

   dir = br_build_path (prefix, "etc");
   free (prefix);
   return dir;
}


/***********************
 * Utility functions
 ***********************/

/** Concatenate str1 and str2 to a newly allocated string.
 *
 * @lparam str1 A string.
 * @lparam str2 Another string.
 * @returns A newly-allocated string. This string should be freed when no longer needed.
 */
char *
br_strcat (const ::string &str1, const ::string &str2)
{
   char *result;
   size_t len1, len2;

   if (str1 == nullptr)
      str1 = "";
   if (str2 == nullptr)
      str2 = "";

   len1 = strlen (str1);
   len2 = strlen (str2);

   result = (char *) malloc (len1 + len2 + 1);
   ::memcpy_dup (result, str1, len1);
   ::memcpy_dup (result + len1, str2, len2);
   result[len1 + len2] = '\0';

   return result;
}


char *
br_build_path (const ::string &dir, const ::string &file)
{
   char *dir2, *result;
   size_t len;
   i32 must_free = 0;

   len = strlen (dir);
   if (len > 0 && dir[len - 1] != '/')
   {
      dir2 = br_strcat (dir, "/");
      must_free = 1;
   }
   else
      dir2 = (char *) dir;

   result = br_strcat (dir2, file);
   if (must_free)
      free (dir2);
   return result;
}


/* Emulates glibc's strndup() */
static char *
br_strndup (const ::string &str, size_t size)
{
   char *result = (char *) nullptr;
   size_t len;

   if (str == (const ::string &) nullptr)
      return (char *) nullptr;

   len = strlen (str);
   if (len == 0)
      return strdup ("");
   if (size > len)
      size = len;

   result = (char *) malloc (len + 1);
   ::memcpy_dup (result, str, size);
   result[size_i32] = '\0';
   return result;
}


/** Extracts the directory component of a path.
 *
 * Similar to g_dirname() or the dirname commandline application.
 *
 * Example:
 * \code
 * br_dirname ("/usr/local/foobar");  --> Returns: "/usr/local"
 * \endcode
 *
 * @lparam path  A path.
 * @returns     A directory name. This string should be freed when no longer needed.
 */
char *
br_dirname (const ::string &path)
{
   char *end, *result;

   if (path == (const ::string &) nullptr)
      return (char *) nullptr;

   end = strrchr ((char *) path, '/');
   if (end == (const ::string &) nullptr)
      return strdup (".");

   while (end > path && *end == '/')
      end--;
   result = br_strndup (path, end - path + 1);
   if (result[0] == 0)
   {
      free (result);
      return strdup ("/");
   }
   else
      return result;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BINRELOC_C__ */

#undef NULL
#define NULL 0

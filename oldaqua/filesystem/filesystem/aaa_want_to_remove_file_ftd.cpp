#include "framework.h"
//#include "file_ftd.h"
//
//
//#include <openssl/md5.h>
//
//
//#ifdef WINDOWS
//CLASS_DECL_AQUA void file_read_n_number_dup(HANDLE hfile,MD5_CTX * pctx,i32 & iNumber);
//CLASS_DECL_AQUA void file_read_gen_string_dup(HANDLE hfile,MD5_CTX * pctx,string & str);
//#else
//CLASS_DECL_AQUA void file_read_n_number_dup(FILE * hfile,MD5_CTX * pctx,i32 & iNumber);
//CLASS_DECL_AQUA void file_read_gen_string_dup(FILE * hfile,MD5_CTX * pctx,string & str);
//#endif
//
//
//
//
//int_bool file_ftd_dup(const char * pszDir,const char * pszFile)
//{
//
//   HANDLE hfile1 = NULL;
//
//   HANDLE hfile2 = NULL;
//
//   wstring wstr(pszFile);
//
//   hfile1 = create_file(pszFile,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
//
//   if(hfile1 == INVALID_HANDLE_VALUE)
//      return FALSE;
//
//   string strVersion;
//
//
//   file_read_gen_string_dup(hfile1,NULL,strVersion);
//
//   i32 n;
//
//   string strRelative;
//
//   string strMd5;
//
//   string strMd5New;
//
//   i32 iBufSize = 1024 * 1024;
//
//   uchar * buf = (uchar *)memory_alloc(iBufSize);
//
//   i32 iLen;
//   MD5_CTX ctx;
//   DWORD dwRead;
//   DWORD dwWritten;
//   if(strVersion == "fileset v1")
//   {
//      while(true)
//      {
//         file_read_n_number_dup(hfile1,NULL,n);
//         if(n == 2)
//            break;
//         file_read_gen_string_dup(hfile1,NULL,strMd5);
//         MD5_Init(&ctx);
//         file_read_gen_string_dup(hfile1,&ctx,strRelative);
//         string strPath = dir::path(pszDir,strRelative);
//         dir::mk(dir::name(strPath));
//         hfile2 = create_file(strPath,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
//         if(hfile2 == INVALID_HANDLE_VALUE)
//            return FALSE;
//         file_read_n_number_dup(hfile1,&ctx,iLen);
//         while(iLen > 0)
//         {
//            if(!ReadFile(hfile1,buf,MIN(iBufSize,iLen),&dwRead,NULL))
//               break;
//            if(dwRead == 0)
//               break;
//            WriteFile(hfile2,buf,dwRead,&dwWritten,NULL);
//            MD5_Update(&ctx,buf,dwRead);
//            iLen -= dwRead;
//         }
//         CloseHandle(hfile2);
//         hfile2 = NULL;
//
//         strMd5New.clear();
//         string strFormat;
//         strMd5New = ::to_string(ctx);
//         if(strMd5.compare_ci(strMd5New) != 0)
//            return FALSE;
//      }
//   }
//   CloseHandle(hfile1);
//   if(hfile2 != INVALID_HANDLE_VALUE)
//      CloseHandle(hfile2);
//   return true;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//void file_read_n_number_dup(HANDLE hfile,MD5_CTX * pctx,i32 & iNumber)
//{
//
//   string str;
//
//   char ch;
//
//   DWORD dwRead;
//
//   while(ReadFile(hfile,&ch,1,&dwRead,NULL) && dwRead == 1)
//   {
//      if(ch >= '0' && ch <= '9')
//         str += ch;
//      else
//         break;
//      if(pctx != NULL)
//      {
//         MD5_Update(pctx,&ch,1);
//      }
//   }
//   if(ch != 'n')
//      return;
//   if(pctx != NULL)
//   {
//      MD5_Update(pctx,&ch,1);
//   }
//   iNumber = atoi_dup(str);
//}
//
//void file_read_gen_string_dup(HANDLE hfile,MD5_CTX * pctx,string & str)
//{
//   i32 iLen;
//   file_read_n_number_dup(hfile,pctx,iLen);
//   LPSTR lpsz = (LPSTR)memory_alloc(iLen + 1);
//   DWORD dwRead;
//   ReadFile(hfile,lpsz,iLen,&dwRead,NULL);
//   if(pctx != NULL)
//   {
//      MD5_Update(pctx,lpsz,iLen);
//   }
//   lpsz[iLen] = '\0';
//   str = lpsz;
//   memory_free_dbg(lpsz,0);
//}

#pragma once


// Common/Types.h
// from 7-zip
namespace aura
{
   
   //#include "../../C/Types.h"
   // from 7-zip

   /* Types.h -- Basic types
   2010-10-09 : Igor Pavlov : Public domain */

   #ifndef EXTERN_C_BEGIN
   #ifdef __cplusplus
   #define EXTERN_C_BEGIN extern "C" {
   #define EXTERN_C_END }
   #else
   #define EXTERN_C_BEGIN
   #define EXTERN_C_END
   #endif
   #endif

   EXTERN_C_BEGIN

   #define SZ_OK 0

   #define SZ_ERROR_DATA 1
   #define SZ_ERROR_MEM 2
   #define SZ_ERROR_CRC 3
   #define SZ_ERROR_UNSUPPORTED 4
   #define SZ_ERROR_PARAM 5
   #define SZ_ERROR_INPUT_EOF 6
   #define SZ_ERROR_OUTPUT_EOF 7
   #define SZ_ERROR_READ 8
   #define SZ_ERROR_WRITE 9
   #define SZ_ERROR_PROGRESS 10
   #define SZ_ERROR_FAIL 11
   #define SZ_ERROR_THREAD 12

   #define SZ_ERROR_ARCHIVE 16
   #define SZ_ERROR_NO_ARCHIVE 17

   typedef i32 SRes;

   #ifdef _WIN32
   typedef u32 WRes;
   #else
   typedef i32 WRes;
   #endif


   /* The following interfaces use first parameter as pointer to structure */

   typedef struct
   {
      byte (*Read)(void *point); /* reads one byte, returns 0 in case of EOF or error */
   } IByteIn;

   typedef struct
   {
      void (*Write)(void *point, byte b);
   } IByteOut;

   //typedef struct
   //{
   //  SRes (*Read)(void *point, void *buf, size_t *size);
   //    /* if (input(*size) != 0 && output(*size) == 0) means end_of_stream.
   //       (output(*size) < input(*size)) is allowed */
   //} ISeqInStream;

   ///* it can return SZ_ERROR_INPUT_EOF */
   //SRes SeqInStream_Read(ISeqInStream *stream, void *buf, size_t size);
   //SRes SeqInStream_Read2(ISeqInStream *stream, void *buf, size_t size, SRes errorType);
   //SRes SeqInStream_ReadByte(ISeqInStream *stream, u8 *buf);

   //typedef struct
   //{
   //  size_t (*Write)(void *point, const void *buf, size_t size);
   //    /* Returns: result - the number of actually written bytes.
   //       (result < size) means error */
   //} ISeqOutStream;

   //typedef enum
   //{
   //  SZ_SEEK_SET = 0,
   //  SZ_SEEK_CUR = 1,
   //  SZ_SEEK_END = 2
   //} ESzSeek;

   //typedef struct
   //{
   //  SRes (*Read)(void *point, void *buf, size_t *size);  /* same as ISeqInStream::Read */
   //  SRes (*Seek)(void *point, Int64 *pos, ESzSeek origin);
   //} ISeekInStream;

   //typedef struct
   //{
   //  SRes (*Look)(void *point, const void **buf, size_t *size);
   //    /* if (input(*size) != 0 && output(*size) == 0) means end_of_stream.
   //       (output(*size) > input(*size)) is not allowed
   //       (output(*size) < input(*size)) is allowed */
   //  SRes (*Skip)(void *point, size_t offset);
   //    /* offset must be <= output(*size) of Look */

   //  SRes (*Read)(void *point, void *buf, size_t *size);
   //    /* reads directly (without buffer). It's same as ISeqInStream::Read */
   //  SRes (*Seek)(void *point, Int64 *pos, ESzSeek origin);
   //} ILookInStream;

   //SRes LookInStream_LookRead(ILookInStream *stream, void *buf, size_t *size);
   //SRes LookInStream_SeekTo(ILookInStream *stream, u64 offset);

   ///* reads via ILookInStream::Read */
   //SRes LookInStream_Read2(ILookInStream *stream, void *buf, size_t size, SRes errorType);
   //SRes LookInStream_Read(ILookInStream *stream, void *buf, size_t size);

   //#define LookToRead_BUF_SIZE (1 << 14)

   //typedef struct
   //{
   //  ILookInStream s;
   //  ISeekInStream *realStream;
   //  size_t pos;
   //  size_t size;
   //  byte buf[LookToRead_BUF_SIZE];
   //} CLookToRead;

   //void LookToRead_CreateVTable(CLookToRead *point, i32 lookahead);
   //void LookToRead_Init(CLookToRead *point);

   //typedef struct
   //{
   //  ISeqInStream s;
   //  ILookInStream *realStream;
   //} CSecToLook;

   //void SecToLook_CreateVTable(CSecToLook *point);

   //typedef struct
   //{
   //  ISeqInStream s;
   //  ILookInStream *realStream;
   //} CSecToRead;

   //void SecToRead_CreateVTable(CSecToRead *point);

   //typedef struct
   //{
   //  SRes (*Progress)(void *point, u64 inSize, u64 outSize);
   //    /* Returns: result. (result != SZ_OK) means break.
   //       Value (u64)(Int64)-1 for size means unknown value. */
   //} ICompressProgress;

   typedef struct
   {
     void *(*Alloc)(void *point, size_t size);
     void (*Free)(void *point, void *address); /* address can be 0 */
   } ISzAlloc;

   #define IAlloc_Alloc(point, size) (point)->Alloc((point), size)
   #define IAlloc_Free(point, a) (point)->Free((point), a)

   #ifdef _WIN32

   #define CHAR_PATH_SEPARATOR '\\'
   #define WCHAR_PATH_SEPARATOR L'\\'
   #define STRING_PATH_SEPARATOR "\\"
   #define WSTRING_PATH_SEPARATOR L"\\"

   #else

   #define CHAR_PATH_SEPARATOR '/'
   #define WCHAR_PATH_SEPARATOR L'/'
   #define STRING_PATH_SEPARATOR "/"
   #define WSTRING_PATH_SEPARATOR L"/"

   #endif

   EXTERN_C_END






} // namespace aura


#include "StdAfx.h"

void * DECL_C _malloc_debug(size_t _Size, int _BlockType, const char * _Filename, int _LineNumber)
{
   return malloc(_Size);
}

void * DECL_C _calloc_debug(size_t _Count, size_t _Size, int _BlockType, const char * _Filename, int _LineNumber)
{
   return malloc(_Count * _Size);
}

void * DECL_C _realloc_debug(void * _Memory, size_t _NewSize, int _BlockType, const char * _Filename, int _LineNumber)
{
   return realloc(_Memory, _NewSize);
}

void * DECL_C _recalloc_debug(void * _Memory, size_t _NumOfElements, size_t _SizeOfElements, int _BlockType, const char * _Filename, int _LineNumber)
{
   return realloc(_Memory, _NumOfElements * _SizeOfElements);
}

void * DECL_C _expand_debug(void * _Memory, size_t _NewSize, int _BlockType, const char * _Filename, int _LineNumber)
{
   return realloc(_Memory, _NewSize);
}

void DECL_C _free_debug(void * _Memory, int _BlockType)
{
   free(_Memory);
}

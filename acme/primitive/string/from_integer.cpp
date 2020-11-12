#include "framework.h"


 string i64toa_dup(i64 i, i32 iBase)
{

   char sz[128 + 64];

   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return sz;
   }
   bool bNegative = false;
   if(i < 0)
   {
      i = -i;
      bNegative = true;
   }
   i32 iIndex = 0;
   while(i > 0)
   {
      i32 iDigit = (i % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      i = i / iBase;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = '-';
      iIndex++;
   }
   sz[iIndex] = '\0';
   ansi_reverse(sz);

   return sz;

}


 string i64toa_dup(i64 i)
{

   return i64toa_dup(i, 10);

}



 string ui64toa_dup(i64 i, i32 iBase)
{

   char sz[128 + 64];

   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return sz;
   }
   i32 iIndex = 0;
   while(i > 0)
   {
      i32 iDigit = (i % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      i = i / iBase;
      iIndex++;
   }
   sz[iIndex] = '\0';
   ansi_reverse(sz);

   return sz;

}


 string ui64toa_dup(i64 i)
{

   return ui64toa_dup(i, 10);

}





// void ansi_from_u64(char * sz, u64 u, i32 iBase)
//{
//   if(u == 0)
//   {
//      sz[0] = '0';
//      sz[1] = '\0';
//      return;
//   }
//   i32 iIndex = 0;
//   while(u > 0)
//   {
//      i32 iDigit = (u % iBase);
//      char ch;
//      if(iDigit <= 9)
//      {
//         ch = iDigit + '0';
//      }
//      else
//      {
//         ch = iDigit - 10 + 'a';
//      }
//      sz[iIndex] =  ch;
//      u = u / iBase;
//      iIndex++;
//   }
//   sz[iIndex] = '\0';
//   ansi_reverse(sz);
//}
//
//
//
//void ansi_from_i64(char * sz, i64 i, i32 iBase)
//{
//   if(i == 0)
//   {
//      sz[0] = '0';
//      sz[1] = '\0';
//      return;
//   }
//   bool bNegative = false;
//   if(i < 0)
//   {
//      i = -i;
//      bNegative = true;
//   }
//   i32 iIndex = 0;
//   while(i > 0)
//   {
//      i32 iDigit = (i % iBase);
//      char ch;
//      if(iDigit <= 9)
//      {
//         ch = iDigit + '0';
//      }
//      else
//      {
//         ch = iDigit - 10 + 'a';
//      }
//      sz[iIndex] =  ch;
//      i = i / iBase;
//      iIndex++;
//   }
//   if(bNegative)
//   {
//      sz[iIndex] = '-';
//      iIndex++;
//   }
//   sz[iIndex] = '\0';
//   ansi_reverse(sz);
//}
//
//

























//void wide_from_u64_base(unichar * sz, u64 u, i32 iBase)
//{
//   if(u == 0)
//   {
//      sz[0] = L'0';
//      sz[1] = L'\0';
//      return;
//   }
//   i32 iIndex = 0;
//   while(u > 0)
//   {
//      i32 iDigit = (u % iBase);
//      unichar wch;
//      if(iDigit <= 9)
//      {
//         wch = iDigit + L'0';
//      }
//      else
//      {
//         wch = iDigit - 10 + L'a';
//      }
//      sz[iIndex] =  wch;
//      u = u / iBase;
//      iIndex++;
//   }
//   sz[iIndex] = L'\0';
//   wide_reverse(sz);
//}
//
//
//
//void wide_from_i64_base(unichar * sz, i64 i, i32 iBase)
//{
//   if(i == 0)
//   {
//      sz[0] = L'0';
//      sz[1] = L'\0';
//      return;
//   }
//   bool bNegative = false;
//   if(i < 0)
//   {
//      i = -i;
//      bNegative = true;
//   }
//   i32 iIndex = 0;
//   while(i > 0)
//   {
//      i32 iDigit = (i % iBase);
//      unichar wch;
//      if(iDigit <= 9)
//      {
//         wch = iDigit + L'0';
//      }
//      else
//      {
//         wch = iDigit - 10 + L'a';
//      }
//      sz[iIndex] =  wch;
//      i = i / iBase;
//      iIndex++;
//   }
//   if(bNegative)
//   {
//      sz[iIndex] = L'-';
//      iIndex++;
//   }
//   sz[iIndex] = L'\0';
//   wide_reverse(sz);
//}
//
//
//
//
//
//
//
//

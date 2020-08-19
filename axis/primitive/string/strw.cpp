#include "framework.h"


#define NULWCHAR     L'\0'
#define TABWCHAR     L'\t'
#define SLASHWCHAR   L'\\'
#define SPACEWCHAR   L' '
#define DQUOTEWCHAR  L'\"'


CLASS_DECL_AURA void wide_parse_command_line(widechar *cmdstart, widechar **argv, widechar *args, i32 * numargs, i32 * numchars)
{

   widechar *point;
   widechar c;
   i32 inquote;                    /* 1 = inside quotes */
   i32 copychar;                   /* 1 = copy char to *args */
   u32 numslash;              /* num of backslashes seen */

   *numchars = 0;
   *numargs = 1;                   /* the program name at least */

   /* first scan the program name, copy it, and ::count the bytes */
   point = cmdstart;
   if (argv)
      *argv++ = args;

#ifdef WILDCARD
   /* To handle later wild card expansion, we prefix each entry by
   it's first character before quote handling.  This is done
   so _[w]cwild() knows whether to expand an entry or not. */
   if (args)
      *args++ = *point;
   ++*numchars;

#endif  /* WILDCARD */

   /* A quoted program name is handled here. The handling is much
      simpler than for other arguments. Basically, whatever lies
      between the leading double-quote and next one, or a terminal nullptr
      character is simply accepted. Fancier handling is not required
      because the program name must be a legal NTFS/HPFS file name.
      Note that the double-quote characters are not copied, nor do they
      contribute to numchars. */
   if ( *point == DQUOTEWCHAR ) {
      /* scan from just past the first double-quote through the next
         double-quote, or up to a nullptr, whichever comes first */
      while ( (*(++point) != DQUOTEWCHAR) && (*point != NULWCHAR) ) {

            ++*numchars;
            if ( args )
               *args++ = *point;
      }
      /* append the terminating nullptr */
      ++*numchars;
      if ( args )
            *args++ = NULWCHAR;

      /* if we stopped on a double-quote (usual case), skip over it */
      if ( *point == DQUOTEWCHAR )
            point++;
   }
   else {
      /* Not a quoted program name */
      do {
            ++*numchars;
            if (args)
               *args++ = *point;

            c = (widechar) *point++;

      } while ( c != SPACEWCHAR && c != NULWCHAR && c != TABWCHAR );

      if ( c == NULWCHAR ) {
            point--;
      } else {
            if (args)
               *(args-1) = NULWCHAR;
      }
   }

   inquote = 0;

   /* loop on each argument */
   for(;;) {

      if ( *point ) {
            while (*point == SPACEWCHAR || *point == TABWCHAR)
               ++point;
      }

      if (*point == NULWCHAR)
            break;              /* end of args */

      /* scan an argument */
      if (argv)
            *argv++ = args;     /* store ptr to arg */
      ++*numargs;

#ifdef WILDCARD
   /* To handle later wild card expansion, we prefix each entry by
   it's first character before quote handling.  This is done
   so _[w]cwild() knows whether to expand an entry or not. */
   if (args)
      *args++ = *point;
   ++*numchars;

#endif  /* WILDCARD */

   /* loop through scanning one argument */
   for (;;) {
      copychar = 1;
      /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
         2N+1 backslashes + " ==> N backslashes + literal "
         N backslashes ==> N backslashes */
      numslash = 0;
      while (*point == SLASHWCHAR) {
            /* ::count number of backslashes for use below */
            ++point;
            ++numslash;
      }
      if (*point == DQUOTEWCHAR) {
            /* if 2N backslashes before, start/end quote, otherwise
               copy literally */
            if (numslash % 2 == 0) {
               if (inquote) {
                  if (point[1] == DQUOTEWCHAR)
                        point++;    /* Double quote inside quoted string */
                  else        /* skip first quote char and copy second */
                        copychar = 0;
               } else
                  copychar = 0;       /* don't copy quote */

               inquote = !inquote;
            }
            numslash /= 2;          /* divide numslash by two */
      }

      /* copy slashes */
      while (numslash--) {
            if (args)
               *args++ = SLASHWCHAR;
            ++*numchars;
      }

      /* if at end of arg, break loop */
      if (*point == NULWCHAR || (!inquote && (*point == SPACEWCHAR || *point == TABWCHAR)))
            break;

      if (copychar) {
            if (args)
               *args++ = *point;
            ++*numchars;
      }
      ++point;
      }

      /* nullptr-terminate the argument */

      if (args)
            *args++ = NULWCHAR;          /* terminate string */
      ++*numchars;
   }

   /* We put one last argument in -- a nullptr ptr */
   if (argv)
      *argv++ = nullptr;
   ++*numargs;
}

//
//unichar * wide_concatenate(unichar * dest, const unichar * cat)
//{
//
//   if (::is_null(dest)) return nullptr;
//   if (::is_null(cat)) return nullptr;
//   #ifdef WINDOWS
//   return wcscat(dest, cat);
//   #else
//   unichar * destParam = dest;
//   while(*dest != 0)
//      dest++;
//   while(*cat != 0)
//      *dest++ = *cat++;
//   *dest = L'\0';
//   return destParam;
//   #endif
//}
//
//
//
//

//void wide_from_u64_base(unichar * sz, u32 ui, i32 iBase)
//{
//   if(ui == 0)
//   {
//      sz[0] = L'0';
//      sz[1] = L'\0';
//      return;
//   }
//   i32 iIndex = 0;
//   while(ui > 0)
//   {
//      i32 iDigit = (ui % iBase);
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
//      ui = ui / iBase;
//      iIndex++;
//   }
//   sz[iIndex] = L'\0';
//   wide_reverse(sz);
//}



//void wide_from_i32_base(unichar * sz, i32 i, i32 iBase)
//{
//   if(i == 0)
//   {
//      sz[0] = L'0';
//      sz[1] =  L'\0';
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




//void wide_reverse(unichar * sz)
//{
//
//   ::count iLen = wide_length(sz);
//
//   ::count iMid = iLen / 2;
//
//   ::count iL = 0;
//
//   ::count iR = iLen - 1;
//
//   unichar ch;
//
//   for(; iL < iMid; iL++, iR--)
//   {
//      ch = sz[iL];
//      sz[iL] = sz[iR];
//      sz[iR] = ch;
//   }
//
//}

//void w_zero_pad(unichar * sz, ::count iPad)
//{
//
//   ::count iLen = wide_length(sz);
//
//   ::count iZeroCount = iPad - iLen;
//
//   if(iZeroCount > 0)
//   {
//
//      ::count iEnd = iLen - 1;
//
//      ::count iFinalEnd = iEnd + iZeroCount;
//
//      sz[iFinalEnd + 1] = L'\0';
//
//      for(; iEnd >= 0; iEnd--, iFinalEnd--)
//      {
//         sz[iFinalEnd] = sz[iEnd];
//      }
//
//      for(; iFinalEnd >= 0; iFinalEnd--)
//      {
//         sz[iFinalEnd] = L'0';
//      }
//
//   }
//
//}




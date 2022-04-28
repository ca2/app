// Created by camilo on 2022-04-24 05:22 <3ThomasBorregaardSørensen!! (Thomas likes number 5!!)
#include "framework.h"


#define NULCHAR     '\0'
#define TABCHAR     '\t'
#define SLASHCHAR   '\\'
#define SPACECHAR   ' '
#define DQUOTECHAR  '\"'


void ansi_parse_command_line(char * cmdstart, char ** argv, char * args, i32 * numargs, i32 * numchars)
{


   char * p;
   char c;
   i32 inquote;                    /* 1 = inside quotes */
   i32 copychar;                   /* 1 = copy char to *args */
   u32 numslash;              /* num of backslashes seen */

   *numchars = 0;
   *numargs = 1;                   /* the program name at least */

   /* first scan the program name, copy it, and ::count the bytes */
   p = cmdstart;
   if (argv)
      *argv++ = args;

#ifdef WILDCARD
   /* To handle later wild card expansion, we prefix each entry by
   it's first character before quote handling.  This is done
   so _[w]cwild() knows whether to expand an entry or not. */
   if (args)
      *args++ = *p;
   ++ * numchars;

#endif  /* WILDCARD */

   /* A quoted program name is handled here. The handling is much
      simpler than for other arguments. Basically, whatever lies
      between the leading double-quote and next one, or a terminal nullptr
      character is simply accepted. Fancier handling is not required
      because the program name must be a legal NTFS/HPFS file name.
      Note that the double-quote characters are not copied, nor do they
      contribute to numchars. */
   if (*p == DQUOTECHAR)
   {
      /* scan from just past the first double-quote through the next
         double-quote, or up to a nullptr, whichever comes first */
      while ((*(++p) != DQUOTECHAR) && (*p != NULCHAR))
      {

         ++ * numchars;
         if (args)
            *args++ = *p;
      }
      /* append the terminating nullptr */
      ++ * numchars;
      if (args)
         *args++ = NULCHAR;

      /* if we stopped on a double-quote (usual case), skip over it */
      if (*p == DQUOTECHAR)
         p++;
   }
   else
   {
      /* Not a quoted program name */
      do
      {
         ++ * numchars;
         if (args)
            *args++ = *p;

         c = (char)*p++;


      } while (c != SPACECHAR && c != NULCHAR && c != TABCHAR);

      if (c == NULCHAR)
      {
         p--;
      }
      else
      {
         if (args)
            *(args - 1) = NULCHAR;
      }
   }

   inquote = 0;

   /* loop on each argument */
   for (;;)
   {

      if (*p)
      {
         while (*p == SPACECHAR || *p == TABCHAR)
            ++p;
      }

      if (*p == NULCHAR)
         break;              /* end of args */

      /* scan an argument */
      if (argv)
         *argv++ = args;     /* store ptr to arg */
      ++ * numargs;

#ifdef WILDCARD
      /* To handle later wild card expansion, we prefix each entry by
      it's first character before quote handling.  This is done
      so _[w]cwild() knows whether to expand an entry or not. */
      if (args)
         *args++ = *p;
      ++ * numchars;

#endif  /* WILDCARD */

      /* loop through scanning one argument */
      for (;;)
      {
         copychar = 1;
         /* Rules: 2N backslashes + " ==> N backslashes and begin/end quote
            2N+1 backslashes + " ==> N backslashes + literal "
            N backslashes ==> N backslashes */
         numslash = 0;
         while (*p == SLASHCHAR)
         {
            /* ::count number of backslashes for use below */
            ++p;
            ++numslash;
         }
         if (*p == DQUOTECHAR)
         {
            /* if 2N backslashes before, start/end quote, otherwise
                copy literally */
            if (numslash % 2 == 0)
            {
               if (inquote)
               {
                  if (p[1] == DQUOTECHAR)
                     p++;    /* Double quote inside quoted string */
                  else        /* skip first quote char and copy second */
                     copychar = 0;
               }
               else
                  copychar = 0;       /* don't copy quote */

               inquote = !inquote;
            }
            numslash /= 2;          /* divide numslash by two */
         }

         /* copy slashes */
         while (numslash--)
         {
            if (args)
               *args++ = SLASHCHAR;
            ++ * numchars;
         }

         /* if at end of arg, break loop */
         if (*p == NULCHAR || (!inquote && (*p == SPACECHAR || *p == TABCHAR)))
            break;

         if (copychar)
         {
            if (args)
               *args++ = *p;
            ++ * numchars;
         }
         ++p;
         //#endif  /* _MBCS */
      }

      /* nullptr-terminate the argument */

      if (args)
         *args++ = NULCHAR;          /* terminate string */
      ++ * numchars;
   }

   /* We put one last argument in -- a nullptr ptr */
   if (argv)
      *argv++ = nullptr;
   ++ * numargs;
}

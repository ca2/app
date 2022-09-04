/*-
 * Copyright 2003-2005 Colin Percival
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted providing that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/
#include <bzlib.h>

//#include "../bzlib_private.h"

#include "framework.h"
#if defined(LINUX) || defined(__APPLE__) || defined(__GNUC__)
#include<stdarg.h>
#endif
//#include"axis/bzip2/bzlib.h"
//#include"libbsdiff.h"


int err(int i, const char* str, ...)
{
   va_list a_list;
   va_start(a_list,str);

    if(str != NULL)
    {
       vprintf(str,a_list);

    }

   return (i);

}

/*
int err(int i, const char* str)
{

   printf("%s",str);

   return i;

}
*/

//off_t libbsdiff_offtin(u_char *buf)
//{
//   off_t y;
//
//   y=buf[7]&0x7F;
//   y=y*256;y+=buf[6];
//   y=y*256;y+=buf[5];
//   y=y*256;y+=buf[4];
//   y=y*256;y+=buf[3];
//   y=y*256;y+=buf[2];
//   y=y*256;y+=buf[1];
//   y=y*256;y+=buf[0];
//
//   if(buf[7]&0x80) y=-y;
//
//   return y;
//}

int bspatch(const char * oldfile, const char * newfile, const char * patchfile)
{
   FILE * f, * cpf, * dpf, * epf;
   BZFILE * cpfbz2, * dpfbz2, * epfbz2;
   int cbz2err, dbz2err, ebz2err;
   FILE * fd;
   ssize_t oldsize,newsize;
   ssize_t bzctrllen,bzdatalen;
   u_char header[32],buf[8];
   u_char *old = NULL;
   u_char *_new = NULL;
   off_t oldpos,newpos;
   off_t ctrl[3];
   off_t lenread;
   off_t i;
   //errno_t errno_result;

   /* fopen patch file */
   if ((f = fopen(patchfile, "rb")) == NULL)
      return err(1, "fopen_s(%s)", patchfile);

   /*
   File format:
      0   8   "BSDIFF40"
      8   8   X
      16   8   Y
      24   8   sizeof(newfile)
      32   X   bzip2(control block)
      32+X   Y   bzip2(diff block)
      32+X+Y   ???   bzip2(extra block)
   with control block a set of triples (x,y,z) meaning "add x bytes
   from oldfile to x bytes from the diff block; copy y bytes from the
   extra block; seek forwards in oldfile by z bytes".
   */

   /* _read header */
   if (fread(header, 1, 32, f) < 32) {
      if (feof(f))
      {
         fclose(f);
         return err(1, "Corrupt patch\n");
      }
      fclose(f);
      return  err(1, "fread(%s)", patchfile);
   }

   /* Check for appropriate magic */
   if (memcmp(header, "BSDIFF40", 8) != 0)
   {
      fclose(f);
      return err(1, "Corrupt patch\n");
   }

   /* _read lengths from header */
   bzctrllen=libbsdiff_offtin(header+8);
   bzdatalen=libbsdiff_offtin(header+16);
   newsize=libbsdiff_offtin(header+24);
   if((bzctrllen<0) || (bzdatalen<0) || (newsize<0))
   {
      fclose(f);
      return err(1,"Corrupt patch\n");
   }

   /* fclose patch file and re-fopen it via libbzip2 at the right places */
   if (fclose(f))
      return err(1, "fclose(%s)", patchfile);
   if ((cpf = fopen( patchfile, "rb")) == 0)
      return err(1, "fopen_s(%s)", patchfile);
   if (fseek(cpf, 32, SEEK_SET))
   {
      fclose(cpf);
      return err(1, "fseeko(%s, %d)", patchfile, 32);
   }
   if ((cpfbz2 = BZ2_bzReadOpen(&cbz2err, cpf, 0, 0, NULL, 0)) == NULL)
   {
      fclose(cpf);
      return err(1, "BZ2_bzReadOpen, bz2err = %d", cbz2err);
   }
   if ((dpf = fopen(patchfile, "rb")) == 0)
   {
      fclose(cpf);
      return err(1, "fopen_s(%s)", patchfile);
   }
   if (fseek(dpf, 32 + bzctrllen, SEEK_SET))
   {
      fclose(cpf);
      fclose(dpf);
      return err(1, "fseeko(%s, %d)", patchfile,
          (32 + bzctrllen));
   }
   if ((dpfbz2 = BZ2_bzReadOpen(&dbz2err, dpf, 0, 0, NULL, 0)) == NULL)
   {
      fclose(cpf);
      fclose(dpf);
      return err(1, "BZ2_bzReadOpen, bz2err = %d", dbz2err);
   }
   if ((epf = fopen(patchfile, "rb")) == 0)
   {
      fclose(cpf);
      fclose(dpf);
      return err(1, "fopen_s(%s)", patchfile);
   }
   if (fseek(epf, 32 + bzctrllen + bzdatalen, SEEK_SET))
   {
      fclose(cpf);
      fclose(dpf);
      fclose(epf);
      return err(1, "fseeko(%s, %d)", patchfile,
          (32 + bzctrllen + bzdatalen));
   }
   if ((epfbz2 = BZ2_bzReadOpen(&ebz2err, epf, 0, 0, NULL, 0)) == NULL)
   {
      fclose(cpf);
      fclose(dpf);
      fclose(epf);
      return err(1, "BZ2_bzReadOpen, bz2err = %d", ebz2err);
   }

   //org:
   //if(((fd=fopen(oldfile,O_RDONLY,0))<0) ||
   //   ((oldsize=fseek(fd,0,SEEK_END))==-1) ||
   //   ((old=malloc(oldsize+1))==NULL) ||
   //   (fseek(fd,0,SEEK_SET)!=0) ||
   //   (_read(fd,old,oldsize)!=oldsize) ||
   //   (fclose(fd)==-1)) return err(1,"%s",oldfile);
   //new:
   //_read in chunks, don't rely on _read always returns full data!
   if(((fd=fopen(oldfile,"rb"))==0) ||
      ((oldsize = (ssize_t) fseek(fd,0,SEEK_END))==-1) ||
      ((old=(u_char*)malloc(oldsize+1))==NULL) ||
      (fseek(fd,0,SEEK_SET)!=0))
   {
      fclose(cpf);
      fclose(dpf);
      fclose(epf);
      if(fd != 0)
      {
         fclose(fd);
      }
      if(old != NULL)
      {
         free(old);
      }
      return err(1,"%s",oldfile);
   }

   size_t r = oldsize;

   while(r > 0 && (i = (off_t) fread(old+oldsize-r,r, 1, fd)) > 0)
      r-=i;

   if (r>0 || fclose(fd)==-1)
   {
      fclose(cpf);
      fclose(dpf);
      fclose(epf);
      free(old);
      return err(1,"%s",oldfile);
   }

   if((_new=(u_char*)malloc(newsize+1))==NULL)
   {
      fclose(cpf);
      fclose(dpf);
      fclose(epf);
      fclose(fd);
      free(old);
      return err(1,NULL);
   }

   oldpos=0;newpos=0;
   while(newpos < newsize) {
      /* _read control data */
      for(i=0;i<=2;i++) {
         lenread = BZ2_bzRead(&cbz2err, cpfbz2, buf, 8);
         if ((lenread < 8) || ((cbz2err != BZ_OK) &&
             (cbz2err != BZ_STREAM_END)))
         {
            fclose(cpf);
            fclose(dpf);
            fclose(epf);
            fclose(fd);
            free(_new);
            free(old);
            return err(1, "Corrupt patch\n");
         }
         ctrl[i]=libbsdiff_offtin(buf);
      };

      /* Sanity-check */
      if(newpos + ctrl[0] > newsize)
      {
         fclose(cpf);
         fclose(dpf);
         fclose(epf);
         fclose(fd);
         free(_new);
         free(old);
         return err(1,"Corrupt patch\n");
      }

      /* _read diff string */
      lenread = BZ2_bzRead(&dbz2err, dpfbz2, _new + newpos, (int)ctrl[0]);
      if ((lenread < ctrl[0]) ||
          ((dbz2err != BZ_OK) && (dbz2err != BZ_STREAM_END)))
      {
         fclose(cpf);
         fclose(dpf);
         fclose(epf);
         fclose(fd);
         free(_new);
         free(old);
         return err(1, "Corrupt patch\n");
      }

      /* add old data to diff string */
      for(i=0;i<ctrl[0];i++)
         if((oldpos+i>=0) && (oldpos + i <oldsize))
            _new[newpos+i]+=old[oldpos+i];

      /* Adjust pointers */
      newpos+=ctrl[0];
      oldpos+=ctrl[0];

      /* Sanity-check */
      if(newpos + ctrl[1] >newsize)
      {
         fclose(cpf);
         fclose(dpf);
         fclose(epf);
         fclose(fd);
         free(_new);
         free(old);
         return err(1,"Corrupt patch\n");
      }

      /* _read extra string */
      lenread = BZ2_bzRead(&ebz2err, epfbz2, _new + newpos, (int)ctrl[1]);
      if ((lenread < ctrl[1]) ||
          ((ebz2err != BZ_OK) && (ebz2err != BZ_STREAM_END)))
      {
         fclose(cpf);
         fclose(dpf);
         fclose(epf);
         fclose(fd);
         free(_new);
         free(old);
         return err(1, "Corrupt patch\n");
      }

      /* Adjust pointers */
         newpos+=ctrl[1];
         oldpos+=ctrl[2];
      };

   /* Clean up the bzip2 reads */
   BZ2_bzReadClose(&cbz2err, cpfbz2);
   BZ2_bzReadClose(&dbz2err, dpfbz2);
   BZ2_bzReadClose(&ebz2err, epfbz2);
   if (fclose(cpf) || fclose(dpf) || fclose(epf))
   {
      free(_new);
      free(old);
      return err(1, "fclose(%s)", patchfile);
   }

   /* _write the new file */
   //org:
   //if(((fd=fopen(newfile,O_CREAT|O_TRUNC|O_WRONLY,0666))<0) ||
   //new:
   if(((fd=fopen(newfile,"wb")) == 0) ||
      (fwrite(_new,newsize,1, fd)!=newsize) || (fclose(fd)==-1))
   {
      free(_new);
      free(old);
      return err(1,"%s",newfile);
   }

   free(_new);
   free(old);

   return 0;
}

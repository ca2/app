#include "framework.h"
//#include"libbsdiff.h"
//#include"axis/bzip2/bzlib.h"

//#include <bzlib_private.h>

#include <bzlib.h>


int err(int i,const char* str,...);


//void split(bs_offset *I,bs_offset *V,bs_offset start,bs_offset len,bs_offset h)
//{
//   bs_offset i,j,k,x,tmp,jj,kk;
//
//   if(len<16) {
//      for(k=start;k<start+len;k+=j) {
//         j=1;x=V[I[k]+h];
//         for(i=1;k+i<start+len;i++) {
//            if(V[I[k+i]+h]<x) {
//               x=V[I[k+i]+h];
//               j=0;
//            };
//            if(V[I[k+i]+h]==x) {
//               tmp=I[k+j];I[k+j]=I[k+i];I[k+i]=tmp;
//               j++;
//            };
//         };
//         for(i=0;i<j;i++) V[I[k+i]]=k+j-1;
//         if(j==1) I[k]=-1;
//      };
//      return;
//   };
//
//   x=V[I[start+len/2]+h];
//   jj=0;kk=0;
//   for(i=start;i<start+len;i++) {
//      if(V[I[i]+h]<x) jj++;
//      if(V[I[i]+h]==x) kk++;
//   };
//   jj+=start;kk+=jj;
//
//   i=start;j=0;k=0;
//   while(i<jj) {
//      if(V[I[i]+h]<x) {
//         i++;
//      } else if(V[I[i]+h]==x) {
//         tmp=I[i];I[i]=I[jj+j];I[jj+j]=tmp;
//         j++;
//      } else {
//         tmp=I[i];I[i]=I[kk+k];I[kk+k]=tmp;
//         k++;
//      };
//   };
//
//   while(jj+j<kk) {
//      if(V[I[jj+j]+h]==x) {
//         j++;
//      } else {
//         tmp=I[jj+j];I[jj+j]=I[kk+k];I[kk+k]=tmp;
//         k++;
//      };
//   };
//
//   if(jj>start) split(I,V,start,jj-start,h);
//
//   for(i=0;i<kk-jj;i++) V[I[jj+i]]=kk-1;
//   if(jj==kk-1) I[jj]=-1;
//
//   if(start+len>kk) split(I,V,kk,start+len-kk,h);
//}
//
//static void qsufsort(bs_offset *I,bs_offset *V,u_char *old, bs_offset oldsize)
//{
//   bs_offset buckets[256];
//   bs_offset i,h,len;
//
//   for(i=0;i<256;i++) buckets[i]=0;
//   for(i=0;i<oldsize;i++) buckets[old[i]]++;
//   for(i=1;i<256;i++) buckets[i]+=buckets[i-1];
//   for(i=255;i>0;i--) buckets[i]=buckets[i-1];
//   buckets[0]=0;
//
//   for(i=0;i<oldsize;i++) I[++buckets[old[i]]]=i;
//   I[0]=oldsize;
//   for(i=0;i<oldsize;i++) V[i]=buckets[old[i]];
//   V[oldsize]=0;
//   for(i=1;i<256;i++) if(buckets[i]==buckets[i-1]+1) I[buckets[i]]=-1;
//   I[0]=-1;
//
//   for(h=1;I[0]!=-(oldsize+1);h+=h) {
//      len=0;
//      for(i=0;i<oldsize+1;) {
//         if(I[i]<0) {
//            len-=I[i];
//            i-=I[i];
//         } else {
//            if(len) I[i-len]=-len;
//            len=V[I[i]]+1-i;
//            split(I,V,i,len,h);
//            i+=len;
//            len=0;
//         };
//      };
//      if(len) I[i-len]=-len;
//   };
//
//   for(i=0;i<oldsize+1;i++) I[V[i]]=i;
//}
//
//static bs_offset matchlen(u_char *old,bs_offset oldsize,u_char *_new,bs_offset newsize)
//{
//   bs_offset i;
//
//   for(i=0;(i<oldsize)&&(i<newsize);i++)
//      if(old[i]!=_new[i]) break;
//
//   return i;
//}
//
//static bs_offset search(bs_offset *I,u_char *old,bs_offset oldsize,
//      u_char *_new,bs_offset newsize,bs_offset st,bs_offset en, bs_offset *pos)
//{
//   bs_offset x,y;
//
//   if(en-st<2) {
//      x=matchlen(old+I[st],oldsize-I[st],_new,newsize);
//      y=matchlen(old+I[en],oldsize-I[en],_new,newsize);
//
//      if(x>y) {
//         *pos=I[st];
//         return x;
//      } else {
//         *pos=I[en];
//         return y;
//      }
//   };
//
//   x=st+(en-st)/2;
//   if(memcmp(old+I[x],_new, (size_t) min(oldsize-I[x],newsize))<0) {
//      return search(I,old,oldsize,_new,newsize,x,en,pos);
//   } else {
//      return search(I,old,oldsize,_new,newsize,st,x,pos);
//   };
//}
//
//static void offtout(bs_offset x,u_char *buf)
//{
//   bs_offset y;
//
//   if(x<0) y=-x; else y=x;
//
//      buf[0]=y%256;y-=buf[0];
//   y=y/256;buf[1]=y%256;y-=buf[1];
//   y=y/256;buf[2]=y%256;y-=buf[2];
//   y=y/256;buf[3]=y%256;y-=buf[3];
//   y=y/256;buf[4]=y%256;y-=buf[4];
//   y=y/256;buf[5]=y%256;y-=buf[5];
//   y=y/256;buf[6]=y%256;y-=buf[6];
//   y=y/256;buf[7]=y%256;
//
//   if(x<0) buf[7]|=0x80;
//}

int bsdiff(const char * oldfile, const char * newfile, const char * patchfile)
{
   FILE *        fd = 0;
   u_char *       old = NULL;
   u_char *       _new = NULL;
   bs_offset    oldsize,newsize;
   bs_offset *  I = NULL;
   bs_offset *  V = NULL;
   bs_offset    scan;
   bs_offset    len;
   bs_offset    pos = 0;
   bs_offset    lastscan;
   bs_offset    lastoffset;
   bs_offset    lastpos;
   bs_offset    oldscore,scsc;
   bs_offset    s,Sf,lenf,Sb,lenb;
   bs_offset    overlap,Ss,lens;
   bs_offset    i;
   bs_offset    dblen,eblen;
   u_char *       db = NULL;
   u_char *       eb = NULL;
   u_char         buf[8];
   u_char         header[32];
   FILE *        pf = NULL;
   BZFILE *       pfbz2 = NULL;
   int        bz2err;

   /* allocate oldsize+1 bytes instead of oldsize bytes to ensure
      that we never try to malloc(0) and get a NULL pointer */
   //org:
   //if(((fd=_open(oldfile,O_RDONLY,0))<0) ||
   //   ((oldsize=fseek(fd,0,SEEK_END))==-1) ||
   //   ((old=malloc(oldsize+1))==NULL) ||
   //   (fseek(fd,0,SEEK_SET)!=0) ||
   //   (fread_dup(fd,old,oldsize)!=oldsize) ||
   //   (fclose(fd)==-1)) return err(1,"%s",oldfile);
   //new:
   //fread_dup in chunks, don't rely on fread_dup always returns full data!
   if(((fd=fopen(oldfile,"rb")) ==0) ||
      ((oldsize=fseek(fd,0,SEEK_END))==-1) ||
      ((old=(u_char*)malloc((size_t) (oldsize + 1)))==NULL) ||
      (fseek(fd,0,SEEK_SET)!=0))
   {
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

   bs_offset r = oldsize;

   while(r > 0 && (i = (bs_offset) fread(old + oldsize - r, 1, (size_t) r, fd)) > 0)
      r-=i;
   if (r>0 || fclose(fd)>0)
   {
      free(old);
      return err(1,"%s",oldfile);
   }


   if(((I=(bs_offset*)malloc((size_t) ((oldsize+1)*sizeof(bs_offset))))==NULL) ||
      ((V=(bs_offset*)malloc((size_t) ((oldsize+1)*sizeof(bs_offset))))==NULL))
   {
      free(old);
      if(I != NULL)
      {
         free(I);
      }
      if(V != NULL)
      {
         free(V);
      }
      return err(1,NULL);
   }

   libbsdiff_qsufsort(I,V,old,oldsize);

   free(V);

   /* allocate newsize+1 bytes instead of newsize bytes to ensure
      that we never try to malloc(0) and get a NULL pointer */
   //org:
   //if(((fd=_open(newfile,O_RDONLY,0))<0) ||
   //   ((newsize=fseek(fd,0,SEEK_END))==-1) ||
   //   ((_new=malloc(newsize+1))==NULL) ||
   //   (fseek(fd,0,SEEK_SET)!=0) ||
   //   (fread_dup(fd,_new,newsize)!=newsize) ||
   //   (fclose(fd)==-1)) return err(1,"%s",newfile);
   //new:
   //fread_dup in chunks, don't rely on fread_dup always returns full data!
   if(((fd=fopen(newfile,"rb"))== NULL) ||
      ((newsize=fseek(fd,0,SEEK_END))==-1) ||
      ((_new=(u_char*)malloc((size_t) (newsize + 1)))==NULL) ||
      (fseek(fd,0,SEEK_SET)!=0))
   {
      if(fd != 0)
      {
         fclose(fd);
      }
      free(old);
      free(I);
      return err(1,"%s",newfile);
   }

   r=newsize;
   while(r > 0 && (i = (bs_offset) fread(_new + newsize - r, 1, (size_t) r, fd)) > 0)
      r-=i;
   if (r>0 || fclose(fd)> 0)
   {
      free(old);
      free(_new);
      free(I);
      return err(1,"%s",oldfile);
   }

   if(((db=(u_char*)malloc((size_t) (newsize + 1)))==NULL) ||
      ((eb=(u_char*)malloc((size_t) (newsize + 1)))==NULL))
   {
      free(old);
      free(_new);
      free(I);
      if(db != NULL)
      {
         free(db);
      }
      if(eb != NULL)
      {
         free(eb);
      }
      return err(1,NULL);
   }
   dblen=0;
   eblen=0;

   /* Create the patch file */
   //org:
   //if ((pf = fopen(patchfile, "w")) == NULL)
   //new:
   //if((fd=_open(patchfile,O_CREAT|O_TRUNC|O_WRONLY|O_BINARY|O_NOINHERIT,0666))<0)
   if ((pf = fopen(patchfile, "wb")) == NULL)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      return err(1,"%s",patchfile);
   }

   /* Header is
      0   8    "BSDIFF40"
      8   8   length of bzip2ed ctrl block
      16   8   length of bzip2ed diff block
      24   8   length of new file */
   /* File is
      0   32   Header
      32   ??   Bzip2ed ctrl block
      ??   ??   Bzip2ed diff block
      ??   ??   Bzip2ed extra block */
   ::memcpy_dup(header,"BSDIFF40",8);
   libbsdiff_offtout(0,header + 8);
   libbsdiff_offtout(0,header + 16);
   libbsdiff_offtout(newsize,header + 24);
   if (fwrite(header, 32, 1, pf) != 1)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "fwrite(%s)", patchfile);
   }

   /* Compute the differences, writing ctrl as we go */
   if ((pfbz2 = BZ2_bzWriteOpen(&bz2err, pf, 9, 0, 0)) == NULL)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWriteOpen, bz2err = %d", bz2err);
   }
   scan=0;len=0;
   lastscan=0;lastpos=0;lastoffset=0;
   while(scan<newsize) {
      oldscore=0;

      for(scsc=scan+=len;scan<newsize;scan++) {
         len=libbsdiff_search(I,old,oldsize,_new + scan,newsize - scan,
               0,oldsize,&pos);

         for(;scsc<scan+len;scsc++)
         if((scsc+lastoffset<oldsize) &&
            (old[scsc+lastoffset] == _new[scsc]))
            oldscore++;

         if(((len==oldscore) && (len!=0)) ||
            (len>oldscore+8)) break;

         if((scan+lastoffset<oldsize) &&
            (old[scan+lastoffset] == _new[scan]))
            oldscore--;
      };

      if((len!=oldscore) || (scan==newsize)) {
         s=0;Sf=0;lenf=0;
         for(i=0;(lastscan+i<scan)&&(lastpos+i<oldsize);) {
            if(old[lastpos+i]==_new[lastscan+i]) s++;
            i++;
            if(s*2-i>Sf*2-lenf) { Sf=s; lenf=i; };
         };

         lenb=0;
         if(scan<newsize) {
            s=0;Sb=0;
            for(i=1;(scan>=lastscan+i)&&(pos>=i);i++) {
               if(old[pos-i]==_new[scan-i]) s++;
               if(s*2-i>Sb*2-lenb) { Sb=s; lenb=i; };
            };
         };

         if(lastscan+lenf>scan-lenb) {
            overlap=(lastscan+lenf)-(scan-lenb);
            s=0;Ss=0;lens=0;
            for(i=0;i<overlap;i++) {
               if(_new[lastscan+lenf-overlap+i]==
                  old[lastpos+lenf-overlap+i]) s++;
               if(_new[scan-lenb+i]==
                  old[pos-lenb+i]) s--;
               if(s>Ss) { Ss=s; lens=i+1; };
            };

            lenf+=lens-overlap;
            lenb-=lens;
         };

         for(i=0;i<lenf;i++)
            db[dblen+i]=_new[lastscan+i]-old[lastpos+i];
         for(i=0;i<(scan-lenb)-(lastscan+lenf);i++)
            eb[eblen+i]=_new[lastscan+lenf+i];

         dblen+=lenf;
         eblen+=(scan-lenb)-(lastscan+lenf);

         libbsdiff_offtout(lenf,buf);
         BZ2_bzWrite(&bz2err, pfbz2, buf, 8);
         if (bz2err != BZ_OK)
         {
            free(old);
            free(_new);
            free(I);
            free(db);
            free(eb);
            fclose(pf);
            return err(1, "BZ2_bzWrite, bz2err = %d", bz2err);
         }

         libbsdiff_offtout((scan - lenb) - (lastscan + lenf),buf);
         BZ2_bzWrite(&bz2err, pfbz2, buf, 8);
         if (bz2err != BZ_OK)
         {
            free(old);
            free(_new);
            free(I);
            free(db);
            free(eb);
            fclose(pf);
            return err(1, "BZ2_bzWrite, bz2err = %d", bz2err);
         }

         libbsdiff_offtout((pos - lenb) - (lastpos + lenf),buf);
         BZ2_bzWrite(&bz2err, pfbz2, buf, 8);
         if (bz2err != BZ_OK)
         {
            free(old);
            free(_new);
            free(I);
            free(db);
            free(eb);
            fclose(pf);
            return err(1, "BZ2_bzWrite, bz2err = %d", bz2err);
         }

         lastscan=scan-lenb;
         lastpos=pos-lenb;
         lastoffset=pos-scan;
      };
   };
   BZ2_bzWriteClose(&bz2err, pfbz2, 0, NULL, NULL);
   if (bz2err != BZ_OK)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWriteClose, bz2err = %d", bz2err);
   }

   /* Compute size of compressed ctrl data */
   if ((len = ftell(pf)) == -1)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "ftello");
   }
   libbsdiff_offtout(len - 32,header + 8);

   /* _write compressed diff data */
   if ((pfbz2 = BZ2_bzWriteOpen(&bz2err, pf, 9, 0, 0)) == NULL)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWriteOpen, bz2err = %d", bz2err);
   }
   BZ2_bzWrite(&bz2err, pfbz2, db, (int)dblen);
   if (bz2err != BZ_OK)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWrite, bz2err = %d", bz2err);
   }
   BZ2_bzWriteClose(&bz2err, pfbz2, 0, NULL, NULL);
   if (bz2err != BZ_OK)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWriteClose, bz2err = %d", bz2err);
   }

   /* Compute size of compressed diff data */
   if ((newsize = ftell(pf)) == -1)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "ftello");
   }
   libbsdiff_offtout(newsize - len,header + 16);

   /* _write compressed extra data */
   if ((pfbz2 = BZ2_bzWriteOpen(&bz2err, pf, 9, 0, 0)) == NULL)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWriteOpen, bz2err = %d", bz2err);
   }
   BZ2_bzWrite(&bz2err, pfbz2, eb, (int) eblen);
   if (bz2err != BZ_OK)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWrite, bz2err = %d", bz2err);
   }
   BZ2_bzWriteClose(&bz2err, pfbz2, 0, NULL, NULL);
   if (bz2err != BZ_OK)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "BZ2_bzWriteClose, bz2err = %d", bz2err);
   }

   /* seek to the beginning, _write the header, and fclose the file */
   if (fseek(pf, 0, SEEK_SET))
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "fseeko");
   }
   if (fwrite(header, 32, 1, pf) != 1)
   {
      free(old);
      free(_new);
      free(I);
      free(db);
      free(eb);
      fclose(pf);
      return err(1, "fwrite(%s)", patchfile);
   }
   if (fclose(pf))
   {
      fclose(pf);
      return err(1, "fclose");
   }

   /* Free the memory we used */
   free(db);
   free(eb);
   free(I);
   free(old);
   free(_new);

   return 0;
}

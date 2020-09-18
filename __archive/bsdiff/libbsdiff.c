/*-
 * libbsddiff: Extracted from bsdiff-4.3 by Andrew Snow (andrew@modulus.org)
 *
 * This work is largely derived from bsdiff, and the changes are distributed
 * under the same BSD license as bsdiff, see below.
 *
 *
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



//#define CLASS_DECL_ACME CLASS_DECL_EXPORT

//#include <string.h>

#if defined(_WIN32) || defined(LINUX)
//#include <malloc.h>
#endif

//#include "libbsdiff.h"



#ifndef min
#define min(x,y) (((x)<(y)) ? (x) : (y))
#endif

void libbsdiff_split(bs_offset *I,bs_offset *V,bs_offset start,bs_offset len,bs_offset h)
{
	bs_offset i,j,k,x,tmp,jj,kk;

	if(len<16) {
		for(k=start;k<start+len;k+=j) {
			j=1;x=V[I[k]+h];
			for(i=1;k+i<start+len;i++) {
				if(V[I[k+i]+h]<x) {
					x=V[I[k+i]+h];
					j=0;
				};
				if(V[I[k+i]+h]==x) {
					tmp=I[k+j];I[k+j]=I[k+i];I[k+i]=tmp;
					j++;
				};
			};
			for(i=0;i<j;i++) V[I[k+i]]=k+j-1;
			if(j==1) I[k]=-1;
		};
		return;
	};

	x=V[I[start+len/2]+h];
	jj=0;kk=0;
	for(i=start;i<start+len;i++) {
		if(V[I[i]+h]<x) jj++;
		if(V[I[i]+h]==x) kk++;
	};
	jj+=start;kk+=jj;

	i=start;j=0;k=0;
	while(i<jj) {
		if(V[I[i]+h]<x) {
			i++;
		} else if(V[I[i]+h]==x) {
			tmp=I[i];I[i]=I[jj+j];I[jj+j]=tmp;
			j++;
		} else {
			tmp=I[i];I[i]=I[kk+k];I[kk+k]=tmp;
			k++;
		};
	};

	while(jj+j<kk) {
		if(V[I[jj+j]+h]==x) {
			j++;
		} else {
			tmp=I[jj+j];I[jj+j]=I[kk+k];I[kk+k]=tmp;
			k++;
		};
	};

   if(jj>start) libbsdiff_split(I,V,start,jj - start,h);

	for(i=0;i<kk-jj;i++) V[I[jj+i]]=kk-1;
	if(jj==kk-1) I[jj]=-1;

   if(start + len>kk) libbsdiff_split(I,V,kk,start + len - kk,h);
}

void libbsdiff_qsufsort(bs_offset *I,bs_offset *V,unsigned char *old,bs_offset oldsize)
{
	bs_offset buckets[256];
	bs_offset i,h,len;

	for(i=0;i<256;i++) buckets[i]=0;
	for(i=0;i<oldsize;i++) buckets[old[i]]++;
	for(i=1;i<256;i++) buckets[i]+=buckets[i-1];
	for(i=255;i>0;i--) buckets[i]=buckets[i-1];
	buckets[0]=0;

	for(i=0;i<oldsize;i++) I[++buckets[old[i]]]=i;
	I[0]=oldsize;
	for(i=0;i<oldsize;i++) V[i]=buckets[old[i]];
	V[oldsize]=0;
	for(i=1;i<256;i++) if(buckets[i]==buckets[i-1]+1) I[buckets[i]]=-1;
	I[0]=-1;

	for(h=1;I[0]!=-(oldsize+1);h+=h) {
		len=0;
		for(i=0;i<oldsize+1;) {
			if(I[i]<0) {
				len-=I[i];
				i-=I[i];
			} else {
				if(len) I[i-len]=-len;
				len=V[I[i]]+1-i;
            libbsdiff_split(I,V,i,len,h);
				i+=len;
				len=0;
			};
		};
		if(len) I[i-len]=-len;
	};

	for(i=0;i<oldsize+1;i++) I[V[i]]=i;
}

bs_offset libbsdiff_matchlen(unsigned char *old,bs_offset oldsize,unsigned char *new,bs_offset newsize)
{
	bs_offset i;

	for(i=0;(i<oldsize)&&(i<newsize);i++)
		if(old[i]!=new[i]) break;

	return i;
}

bs_offset libbsdiff_search(bs_offset *I,unsigned char *old,bs_offset oldsize, unsigned char *new,bs_offset newsize,bs_offset st,bs_offset en,bs_offset *pos)
{
	bs_offset x,y;

	if(en-st<2) {
      x=libbsdiff_matchlen(old + I[st],oldsize - I[st],new,newsize);
      y=libbsdiff_matchlen(old + I[en],oldsize - I[en],new,newsize);

		if(x>y) {
			*pos=I[st];
			return x;
		} else {
			*pos=I[en];
			return y;
		}
	};

	x=st+(en-st)/2;
	if(memcmp(old+I[x],new,min(oldsize-I[x],newsize))<0) {
      return libbsdiff_search(I,old,oldsize,new,newsize,x,en,pos);
	} else {
      return libbsdiff_search(I,old,oldsize,new,newsize,st,x,pos);
	};
}

void libbsdiff_offtout(bs_offset x,unsigned char *buf)
{
	bs_offset y;

	if(x<0) y=-x; else y=x;

		buf[0]=y%256;y-=buf[0];
	y=y/256;buf[1]=y%256;y-=buf[1];
	y=y/256;buf[2]=y%256;y-=buf[2];
	y=y/256;buf[3]=y%256;y-=buf[3];
	y=y/256;buf[4]=y%256;y-=buf[4];
	y=y/256;buf[5]=y%256;y-=buf[5];
	y=y/256;buf[6]=y%256;y-=buf[6];
	y=y/256;buf[7]=y%256;

	if(x<0) buf[7]|=0x80;
}

#define BSDIFF_HEADER_LEN 32

int libbsdiff_diff(bs_offset * bsret,unsigned char *old,bs_offset oldsize,unsigned char *new,bs_offset newsize,unsigned char *patch,bs_offset patch_size)
{
	bs_offset *I,*V;
	bs_offset scan,pos,len;
	bs_offset lastscan,lastpos,lastoffset;
	bs_offset oldscore,scsc;
	bs_offset s,Sf,lenf,Sb,lenb;
	bs_offset overlap,Ss,lens;
	bs_offset i;
	bs_offset dblen,eblen;
	unsigned char *db,*eb;
	unsigned char buf[8];
	unsigned char *header;

#define ADD_TO_PATCH(buffer, length) { 							\
        if((patch_index + length) > patch_size)						\
                goto FAIL;								\
        ::memcpy_dup(patch + patch_index, buffer, length);					\
        patch_index += length;								\
        size_counter += length;								\
        }


	bs_offset size_counter, patch_index=BSDIFF_HEADER_LEN;
	bs_offset retval=0;

	if(patch_size < BSDIFF_HEADER_LEN)
	        return(0);
        header = patch;

	if(((I=malloc((oldsize+1)*sizeof(bs_offset)))==NULL) ||
	  ((V=malloc((oldsize+1)*sizeof(bs_offset)))==NULL)) return -1;

   libbsdiff_qsufsort(I,V,old,oldsize);

	free(V);

	if(((db=malloc(newsize+1))==NULL) ||
		((eb=malloc(newsize+1))==NULL)) return -1;
	dblen=0;
	eblen=0;

	/* Header is
		0	8	 "BSDIFF40"
		8	8	length of bzip2ed ctrl block
		16	8	length of bzip2ed diff block
		24	8	length of new file */
	/* File is
		0	32	Header
		32	??	Bzip2ed ctrl block
		??	??	Bzip2ed diff block
		??	??	Bzip2ed extra block */

	::memcpy_dup(header,"BSDIFF40",8);
   libbsdiff_offtout(0,header + 8);
   libbsdiff_offtout(0,header + 16);
   libbsdiff_offtout(newsize,header + 24);


	/* Compute the differences, writing ctrl as we go */
	scan=0;len=0;
	lastscan=0;lastpos=0;lastoffset=0;
	size_counter=0;
	while(scan<newsize) {
		oldscore=0;

		for(scsc=scan+=len;scan<newsize;scan++) {
         len=libbsdiff_search(I,old,oldsize,new + scan,newsize - scan,
					0,oldsize,&pos);

			for(;scsc<scan+len;scsc++)
			if((scsc+lastoffset<oldsize) &&
				(old[scsc+lastoffset] == new[scsc]))
				oldscore++;

			if(((len==oldscore) && (len!=0)) ||
				(len>oldscore+8)) break;

			if((scan+lastoffset<oldsize) &&
				(old[scan+lastoffset] == new[scan]))
				oldscore--;
		};

		if((len!=oldscore) || (scan==newsize)) {
			s=0;Sf=0;lenf=0;
			for(i=0;(lastscan+i<scan)&&(lastpos+i<oldsize);) {
				if(old[lastpos+i]==new[lastscan+i]) s++;
				i++;
				if(s*2-i>Sf*2-lenf) { Sf=s; lenf=i; };
			};

			lenb=0;
			if(scan<newsize) {
				s=0;Sb=0;
				for(i=1;(scan>=lastscan+i)&&(pos>=i);i++) {
					if(old[pos-i]==new[scan-i]) s++;
					if(s*2-i>Sb*2-lenb) { Sb=s; lenb=i; };
				};
			};

			if(lastscan+lenf>scan-lenb) {
				overlap=(lastscan+lenf)-(scan-lenb);
				s=0;Ss=0;lens=0;
				for(i=0;i<overlap;i++) {
					if(new[lastscan+lenf-overlap+i]==
					   old[lastpos+lenf-overlap+i]) s++;
					if(new[scan-lenb+i]==
					   old[pos-lenb+i]) s--;
					if(s>Ss) { Ss=s; lens=i+1; };
				};

				lenf+=lens-overlap;
				lenb-=lens;
			};

			for(i=0;i<lenf;i++)
				db[dblen+i]=new[lastscan+i]-old[lastpos+i];
			for(i=0;i<(scan-lenb)-(lastscan+lenf);i++)
				eb[eblen+i]=new[lastscan+lenf+i];

			dblen+=lenf;
			eblen+=(scan-lenb)-(lastscan+lenf);

         libbsdiff_offtout(lenf,buf);
			ADD_TO_PATCH(buf, 8);

         libbsdiff_offtout((scan - lenb) - (lastscan + lenf),buf);
			ADD_TO_PATCH(buf, 8);

         libbsdiff_offtout((pos - lenb) - (lastpos + lenf),buf);
			ADD_TO_PATCH(buf, 8);

			lastscan=scan-lenb;
			lastpos=pos-lenb;
			lastoffset=pos-scan;
		};
	};

	/* Store size of ctrl data */
   libbsdiff_offtout(size_counter,header + 8);

	/* Write compressed diff data */
	ADD_TO_PATCH(db, dblen);

	/* Store size of compressed diff data */
   libbsdiff_offtout(dblen,header + 16);

	/* Write compressed extra data */
	ADD_TO_PATCH(eb, eblen);

        retval = size_counter;

	/* Free the memory we used */
FAIL:	free(db);
	free(eb);
	free(I);

   *bsret =(retval);
	return 0;
}

bs_offset libbsdiff_offtin(unsigned char *buf)
{
	bs_offset y;

	y=buf[7]&0x7F;
	y=y*256;y+=buf[6];
	y=y*256;y+=buf[5];
	y=y*256;y+=buf[4];
	y=y*256;y+=buf[3];
	y=y*256;y+=buf[2];
	y=y*256;y+=buf[1];
	y=y*256;y+=buf[0];

	if(buf[7]&0x80) y=-y;

	return y;
}


bs_offset libbsdiff_size_of_patched(unsigned char *patch)
{
   return(libbsdiff_offtin(patch + 24));
}

int libbsdiff_patch(unsigned char *old, bs_offset oldsize, unsigned char *patch, bs_offset patch_size, unsigned char *new)
{
	bs_offset newsize;
	unsigned char *header, buf[8];
	bs_offset oldpos,newpos;
	bs_offset ctrl[3];
//	bs_offset lenread;
	bs_offset i;
	unsigned char *cpp, *dpp, *epp;	/* stream pointers */
	bs_offset cpi=0, dpi=0, epi=0;	/* stream index */
	bs_offset cpl, dpl;		/* stream length */
   bs_offset epl = 0;

#define READ_FROM_PATCH(stream, buffer, length) {				\
	if(((stream##i) + (length)) > (stream##l))				\
		return(0);							\
	::memcpy_dup((buffer), (stream##p) + (stream##i), (length));			\
	stream##i += length;							\
        }


	/*
	File format:
		0	8	"BSDIFF40"
		8	8	X
		16	8	Y
		24	8	sizeof(newfile)
		32	X	bzip2(control block)
		32+X	Y	bzip2(diff block)
		32+X+Y	???	bzip2(extra block)
	with control block a set of triples (x,y,z) meaning "add x bytes
	from oldfile to x bytes from the diff block; copy y bytes from the
	extra block; seek forwards in oldfile by z bytes".
	*/

	/* Read header */
	header = patch;

	/* Check for appropriate magic */
	if (memcmp(header, "BSDIFF40", 8) != 0)
		return(0);

	/* Read lengths from header */
	cpl=libbsdiff_offtin(header+8);
	dpl=libbsdiff_offtin(header+16);
	newsize=libbsdiff_offtin(header+24);
	if((cpl<0) || (dpl<0) || (newsize<0))
		return(0);

	/* Set up the stream pointers to various points in the input */
        cpp = patch + BSDIFF_HEADER_LEN;	/* control */
        dpp = cpp + cpl;			/* diff */
        epp = dpp + dpl;			/* extra */

	oldpos=0;newpos=0;
	while(newpos<newsize) {
		/* Read control data */
		for(i=0;i<=2;i++) {
		        READ_FROM_PATCH(cp, buf, 8);
			ctrl[i]=libbsdiff_offtin(buf);
		};

		/* Sanity-check */
		if(newpos+ctrl[0]>newsize)
			return(0);

		/* Read diff string */
		READ_FROM_PATCH(dp, new + newpos, ctrl[0]);

		/* Add old data to diff string */
		for(i=0;i<ctrl[0];i++)
			if((oldpos+i>=0) && (oldpos+i<oldsize))
				new[newpos+i]+=old[oldpos+i];

		/* Adjust pointers */
		newpos+=ctrl[0];
		oldpos+=ctrl[0];

		/* Sanity-check */
		if(newpos+ctrl[1]>newsize)
			return(0);

		/* Read extra string */
		READ_FROM_PATCH(ep, new + newpos, ctrl[1]);

		/* Adjust pointers */
		newpos+=ctrl[1];
		oldpos+=ctrl[2];
	};

	return 1;
}

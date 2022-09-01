#pragma once

#if defined(_M_IA64) || defined(_M_AMD64)
#define bs_offset long long
#else
#define bs_offset long
#endif



BZ_EXTERN int libbsdiff_diff(bs_offset * bsret,unsigned char *old,bs_offset oldsize,unsigned char *pnew,bs_offset newsize,unsigned char *patch,bs_offset patch_size);
BZ_EXTERN bs_offset libbsdiff_size_of_patched(unsigned char *patch);
//BZ_EXTERN int libbsdiff_patch(unsigned char *old,bs_offset oldsize,unsigned char *patch,bs_offset patch_size,unsigned char *pnew);
BZ_EXTERN bs_offset libbsdiff_offtin(unsigned char *buf);
BZ_EXTERN void libbsdiff_qsufsort(bs_offset *I,bs_offset *V,unsigned char *old,bs_offset oldsize);
BZ_EXTERN void libbsdiff_split(bs_offset *I,bs_offset *V,bs_offset start,bs_offset len,bs_offset h);
BZ_EXTERN bs_offset libbsdiff_matchlen(unsigned char *old,bs_offset oldsize,unsigned char *puchNew,bs_offset newsize);
BZ_EXTERN bs_offset libbsdiff_search(bs_offset *I,unsigned char *old,bs_offset oldsize,unsigned char *puchNew,bs_offset newsize,bs_offset st,bs_offset en,bs_offset *pos);
BZ_EXTERN void libbsdiff_offtout(bs_offset x,unsigned char *buf);


BZ_EXTERN int bsdiff(const ::string & oldfile, const ::string & newfile, const ::string & patchfile);
BZ_EXTERN int bspatch(const ::string & oldfile, const ::string & newfile, const ::string & patchfile);



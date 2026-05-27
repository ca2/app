#pragma once

#if defined(_M_IA64) || defined(_M_AMD64)
#define bs_offset ::i64
#else
#define bs_offset long
#endif



BZ_EXTERN ::i32 libbsdiff_diff(bs_offset * bsret,::u8 *old,bs_offset oldsize,::u8 *pnew,bs_offset newsize,::u8 *patch,bs_offset patch_size);
BZ_EXTERN bs_offset libbsdiff_size_of_patched(::u8 *patch);
//BZ_EXTERN ::i32 libbsdiff_patch(::u8 *old,bs_offset oldsize,::u8 *patch,bs_offset patch_size,::u8 *pnew);
BZ_EXTERN bs_offset libbsdiff_offtin(::u8 *buf);
BZ_EXTERN void libbsdiff_qsufsort(bs_offset *I,bs_offset *V,::u8 *old,bs_offset oldsize);
BZ_EXTERN void libbsdiff_split(bs_offset *I,bs_offset *V,bs_offset start,bs_offset len,bs_offset h);
BZ_EXTERN bs_offset libbsdiff_matchlen(::u8 *old,bs_offset oldsize,::u8 *puchNew,bs_offset newsize);
BZ_EXTERN bs_offset libbsdiff_search(bs_offset *I,::u8 *old,bs_offset oldsize,::u8 *puchNew,bs_offset newsize,bs_offset st,bs_offset en,bs_offset *pos);
BZ_EXTERN void libbsdiff_offtout(bs_offset x,::u8 *buf);


BZ_EXTERN ::i32 bsdiff(const ::string & oldfile, const ::string & newfile, const ::scoped_string & scopedstratchfile);
BZ_EXTERN ::i32 bspatch(const ::string & oldfile, const ::string & newfile, const ::scoped_string & scopedstratchfile);



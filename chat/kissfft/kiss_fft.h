#ifndef KISS_FFT_H
#define KISS_FFT_H


#ifdef __cplusplus
extern "C" {
#endif

/*
 ATTENTION!
 If you would like a :
 -- a utility that will handle the caching of fft objects
 -- real-only FFT
 -- a multi-dimensional FFT
 -- a command-line utility to perform ffts
 -- a command-line utility to perform fast-convolution filtering

 then see tools/
 */

#ifdef FIXED_POINT
# define kiss_fft_scalar i16
#else
# ifndef kiss_fft_scalar
/*  default is double */
#   define kiss_fft_scalar double
# endif
#endif

typedef struct {
    kiss_fft_scalar r;
    kiss_fft_scalar i;
}kiss_fft_cpx;

typedef struct kiss_fft_state* kiss_fft_cfg;

/*
 *  kiss_fft_alloc
 *
 *  Initialize a FFT (or IFFT) algorithm's cfg/state buffer.
 *
 *  typical usage:      kiss_fft_cfg mycfg=kiss_fft_alloc(1024,0,nullptr,nullptr);
 *
 *  The return value from fft_alloc is a cfg buffer used internally
 *  by the fft routine or nullptr.
 *
 *  If lenmem is nullptr, then kiss_fft_alloc will allocate a cfg buffer using malloc.
 *  The returned value should be free()d when done to avoid memory leaks.
 *
 *  The state can be placed in a ::account::user supplied buffer 'mem':
 *  If lenmem is not nullptr and mem is not nullptr and *lenmem is large enough,
 *      then the function places the cfg in mem and the size_i32 used in *lenmem
 *      and returns mem.
 *
 *  If lenmem is not nullptr and ( mem is nullptr or *lenmem is not large enough),
 *      then the function returns nullptr and places the minimum cfg
 *      buffer size_i32 in *lenmem.
 * */

kiss_fft_cfg kiss_fft_alloc(i32 nfft,i32 inverse_fft,void * mem,size_t * lenmem);

/*
 * kiss_fft(cfg,in_out_buf)
 *
 * Perform an FFT on a complex input buffer.
 * for a forward FFT,
 * fin should be  f[0] , f[1] , ... ,f[nfft-1]
 * fout will be   F[0] , F[1] , ... ,F[nfft-1]
 * Note that each matter is complex and can be accessed like
    f[k].r and f[k].i
 * */
void kiss_fft(kiss_fft_cfg cfg,const kiss_fft_cpx *fin,kiss_fft_cpx *fout);

void kiss_fft_stride(kiss_fft_cfg cfg,const kiss_fft_cpx *fin,kiss_fft_cpx *fout,i32 fin_stride);

/* If kiss_fft_alloc allocated a buffer, it is one contiguous
   buffer and can be simply free()d when no longer needed*/
#define kiss_fft_free free

#ifdef __cplusplus
}
#endif

#endif

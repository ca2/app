#pragma once




CLASS_DECL_AURA void vertical_swap_copy_colorref(color32_t * pcolorrefDst, int cx, int cy, int iStrideDst, const color32_t * pcolorrefSrc, int iStrideSrc);
CLASS_DECL_AURA void copy_colorref(color32_t * pcolorrefDst, int cx, int cy, int iStrideDst, const color32_t * pcolorrefSrc, int iStrideSrc);
CLASS_DECL_AURA void copy_colorref(color32_t * pcolorrefDst, int x, int y, int cx, int cy, int iStrideDst, const color32_t * pcolorrefSrc, int iStrideSrc);

inline void copy_colorref(color32_t* pcolorrefDst, const ::size& size, int iStrideDst, const color32_t* pcolorrefSrc, int iStrideSrc);

typedef void FUNCTION_FACTORY_EXCHANGE();

typedef FUNCTION_FACTORY_EXCHANGE * PFUNCTION_FACTORY_EXCHANGE;

#if (defined(CUBE) || defined(ANDROID))

extern PFUNCTION_FACTORY_EXCHANGE g_pfnfactoryexchangeDraw2d;
extern PFUNCTION_FACTORY_EXCHANGE g_pfnfactoryexchangeImaging;

void initialize_draw2d_factory_exchange();
void initialize_imaging_factory_exchange();

// extern "C"
// void draw2d_factory_exchange();

// extern "C"
// void imaging_factory_exchange();

#endif






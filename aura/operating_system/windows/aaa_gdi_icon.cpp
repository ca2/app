#include "framework.h"



// http://stackoverflow.com/questions/7375003/how-to-convert-hicon-to-hbitmap-in-vc

// answered Aug 12 at 15:34
// befzz
// 10714


CLASS_DECL_AURA HBITMAP get_icon_hbitmap(HICON hICON)
{

//HICON hICON = /*your code here*/
HBITMAP hBITMAPcopy;
ICONINFOEX IconInfo;
//BITMAP BM_32_bit_color;
//BITMAP BM_1_bit_mask;

// 1. From HICON to HBITMAP for color and mask separately
//.cbSize required
//memory_set((void*)&IconInfo, 0, sizeof(ICONINFOEX));
IconInfo.cbSize = sizeof(ICONINFOEX);
GetIconInfoEx(hICON,&IconInfo);


//HBITMAP IconInfo.hbmColor is 32bit per pxl, however alpha bytes can be zeroed or can be not.
//HBITMAP IconInfo.hbmMask is 1bit per pxl

// 2. From HBITMAP to BITMAP for color
//    (HBITMAP without raw data -> HBITMAP with raw data)
//         LR_CREATEDIBSECTION - DIB section will be created,
//         so .bmBits pointer will not be null
hBITMAPcopy = (HBITMAP)CopyImage(IconInfo.hbmColor,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);
//    (HBITMAP to BITMAP)
//GetObject(hBITMAPcopy,sizeof(BITMAP),&BM_32_bit_color);
//Now: BM_32_bit_color.bmBits pointing to BGRA data.(.bmWidth * .bmHeight * (.bmBitsPixel/8))

// 3. From HBITMAP to BITMAP for mask
//hBITMAPcopy = (HBITMAP)CopyImage(IconInfo.hbmMask,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);
//GetObject(hBITMAPcopy,sizeof(BITMAP),&BM_1_bit_mask);
//Now: BM_1_bit_mask.bmBits pointing to mask data (.bmWidth * .bmHeight Bits!)

return hBITMAPcopy;
}

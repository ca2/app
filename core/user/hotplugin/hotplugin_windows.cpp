#include "framework.h"





namespace hotplugin
{

   u32 g_entry_hall_windows_on_paint_dwSync = 0;
   i32 g_entry_hall_windows_on_paint_iDelta = 5000;


   //// Create a hatched bit pattern.
   ////::u16 HatchBits[8] ={0x55,0xAA,0x55,0xAA,0x55, 0xAA,0x55,0xAA};
   ////::u16 HatchBits[8] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
   //::u16 HatchBits[8] ={0,0,0,0,0,0,0,0};

   //// Use the bit pattern to create a bitmap.
   //HBITMAP hbm = ::CreateBitmap(8,8,1,1,HatchBits);


   //HBRUSH hbrushBack = (HBRUSH) ::CreatePatternBrush(hbm);
   //::DeleteObject(hbm);
   //HBRUSH hbrushDark = ::CreateSolidBrush(RGB(90, 90, 80));
   //HBRUSH hbrushLate = ::CreateSolidBrush(RGB(140,140,77 + 42));
   //HBRUSH hbrushLite = ::CreateSolidBrush(RGB(255,255,250));
   //HBRUSH hbrushGren = ::CreateSolidBrush(RGB(77,184,123));

   //HPEN hpen = (HPEN) ::GetStockObject(NULL_PEN);

   //HBRUSH hbrushNull = (HBRUSH) ::GetStockObject(NULL_BRUSH);

   //HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc,hbrushBack);

   //HPEN hpenOld = (HPEN) ::SelectObject(hdc,hpen);

   ////::rectangle_i32(hdc,rectangle.left,rectangle.top,rectangle.right,rectangle.bottom);

   //::SelectObject(hdc,hbrushDark);

   //HPEN hpenLite = ::CreatePen(PS_DOT,1,RGB(184,184,177));

   //

   ////::rectangle_i32(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

   ////rectBar.deflate(2,2);

   //::SetTextColor(hdc,RGB(84,255,84));

   //::SetBkColor(hdc,RGB(0,255,0));

   //::SetBkMode(hdc,TRANSPARENT);

   //::SelectObject(hdc,hbrushBack);

   ////::SelectObject(hdc,hpen);

   ////rectBar.right++;

   ////rectBar.bottom++;

   //int old = SetROP2(hdc,R2_MASKPEN);

   //

   //::rectangle_i32(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

   //::SetTextColor(hdc,RGB(184,184,177));

   //::rectangle_i32(hdc,rectBar.left-1,rectBar.top-1,rectBar.right + 1,rectBar.top);
   //::rectangle_i32(hdc,rectBar.left - 1,rectBar.bottom,rectBar.right + 1,rectBar.bottom+1);
   //::rectangle_i32(hdc,rectBar.left - 1,rectBar.top - 1,rectBar.left,rectBar.bottom+1);
   //::rectangle_i32(hdc,rectBar.right,rectBar.top - 1,rectBar.right+1,rectBar.bottom + 1);

   //SetROP2(hdc,old);

   ////::rectangle_i32(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

   //

   ////::SelectObject(hdc,hpenLite);

   ////::SelectObject(hdc,hbrushNull);

   //int v = ::GetTickCount() * 484 / 1000;

   //::SelectObject(hdc,hpen);

   //::SelectObject(hdc,hbrushGren);

   //int x = v % rectBar.width();

   //::rectangle_i32 rectBrick(left + x,rectBar.top,left + x + w,rectBar.bottom);
   //::rectangle_i32 rectDraw;

   //if(rectDraw.intersect(rectBar,rectBrick))
   //{

   //   ::rectangle_i32(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

   //}

   //rectBrick.offset(-rectBar.width(),0);

   //if(rectDraw.intersect(rectBar,rectBrick))
   //{

   //   ::rectangle_i32(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

   //}

   //rectBrick.offset(rectBar.width() * 2,0);

   //if(rectDraw.intersect(rectBar,rectBrick))
   //{

   //   ::rectangle_i32(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

   //}

   //string str(strEntryHallText);
   //

   //if(str.is_empty())
   //{

   //   //str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

   //   str = "Opening ca2...";

   //}

   //::SetBkMode(hdc,TRANSPARENT);

   //::SetTextColor(hdc,RGB(250,250,250));

   ////HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);

   ////HFONT hfontOld = (HFONT) ::SelectObject(hdc,hStockFont);

   ////::text_out(hdc,rectBar.left - 1,rectBar.bottom + 2,str,str.get_length());

   ////rectBar.left++;
   ////rectBar.top++;
   ////rectBar.right--;
   ////rectBar.bottom--;

   //rectBar.left += 4;

   //HFONT hFont = CreateFont(23,0,0,0,FW_DONTCARE,false,false,false,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
   //   CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,VARIABLE_PITCH,TEXT("Calibri"));
   //HFONT hfontOld = (HFONT) ::SelectObject(hdc,hFont);

   //::DrawText(hdc,str,str.get_length(),&rectBar,DT_SINGLELINE| e_align_left_center);

   //::DeleteObject(hFont);

   //::SelectObject(hdc,hfontOld);

   //::SelectObject(hdc,hpenOld);

   //::SelectObject(hdc,hbrushOld);

   ////::DeleteObject(hbrushNull);
   //::DeleteObject(hbrushDark);
   //::DeleteObject(hbrushLite);
   //::DeleteObject(hbrushLate);
   //::DeleteObject(hbrushBack);
   //::DeleteObject(hbrushGren);
   //::DeleteObject(hpenLite);

//      const ::rectangle_i32 & rectangle;

//int h = 33;
//int m = 49 * 2;

//int top;
//int bottom;
//int left;
//int right;

//if(height(rectangle) < h)
//{
//   top = rectangle.top;
//   bottom = rectangle.bottom;
//}
//else
//{
//   top = rectangle.top + height(rectangle) / 2 - h / 2;
//   bottom = rectangle.top + height(rectangle) / 2 + h / 2;
//}

//if(width(rectangle) < m)
//{
//   left = rectangle.left;
//   right = rectangle.right;
//}
//else
//{

//   left = rectangle.left + min(m / 2,width(rectangle) / 2);
//   right = rectangle.right - min(m / 2,width(rectangle) / 2);

//}

//::rectangle_i32 rectBar(left,top,right,bottom);


} // namespace hotplugin



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
   //HBRUSH hbrushDark = ::CreateSolidBrush(rgb(90, 90, 80));
   //HBRUSH hbrushLate = ::CreateSolidBrush(rgb(140,140,77 + 42));
   //HBRUSH hbrushLite = ::CreateSolidBrush(rgb(255,255,250));
   //HBRUSH hbrushGren = ::CreateSolidBrush(rgb(77,184,123));

   //HPEN hpen = (HPEN) ::GetStockObject(NULL_PEN);

   //HBRUSH hbrushNull = (HBRUSH) ::GetStockObject(NULL_BRUSH);

   //HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc,hbrushBack);

   //HPEN hpenOld = (HPEN) ::SelectObject(hdc,hpen);

   ////::rectangle_i32(hdc,rectangle.left,rectangle.top,rectangle.right,rectangle.bottom);

   //::SelectObject(hdc,hbrushDark);

   //HPEN hpenLite = ::CreatePen(PS_DOT,1,rgb(184,184,177));

   //

   ////::rectangle_i32(hdc,rectangleBar.left,rectangleBar.top,rectangleBar.right,rectangleBar.bottom);

   ////rectangleBar.deflate(2,2);

   //::SetTextColor(hdc,rgb(84,255,84));

   //::SetBkColor(hdc,rgb(0,255,0));

   //::SetBkMode(hdc,TRANSPARENT);

   //::SelectObject(hdc,hbrushBack);

   ////::SelectObject(hdc,hpen);

   ////rectangleBar.right++;

   ////rectangleBar.bottom++;

   //int old = SetROP2(hdc,R2_MASKPEN);

   //

   //::rectangle_i32(hdc,rectangleBar.left,rectangleBar.top,rectangleBar.right,rectangleBar.bottom);

   //::SetTextColor(hdc,rgb(184,184,177));

   //::rectangle_i32(hdc,rectangleBar.left-1,rectangleBar.top-1,rectangleBar.right + 1,rectangleBar.top);
   //::rectangle_i32(hdc,rectangleBar.left - 1,rectangleBar.bottom,rectangleBar.right + 1,rectangleBar.bottom+1);
   //::rectangle_i32(hdc,rectangleBar.left - 1,rectangleBar.top - 1,rectangleBar.left,rectangleBar.bottom+1);
   //::rectangle_i32(hdc,rectangleBar.right,rectangleBar.top - 1,rectangleBar.right+1,rectangleBar.bottom + 1);

   //SetROP2(hdc,old);

   ////::rectangle_i32(hdc,rectangleBar.left,rectangleBar.top,rectangleBar.right,rectangleBar.bottom);

   //

   ////::SelectObject(hdc,hpenLite);

   ////::SelectObject(hdc,hbrushNull);

   //int v = ::GetTickCount() * 484 / 1000;

   //::SelectObject(hdc,hpen);

   //::SelectObject(hdc,hbrushGren);

   //int x = v % rectangleBar.width();

   //::rectangle_i32 rectangleBrick(left + x,rectangleBar.top,left + x + w,rectangleBar.bottom);
   //::rectangle_i32 rectangleDraw;

   //if(rectangleDraw.intersect(rectangleBar,rectangleBrick))
   //{

   //   ::rectangle_i32(hdc,rectangleDraw.left,rectangleDraw.top,rectangleDraw.right,rectangleDraw.bottom);

   //}

   //rectangleBrick.offset(-rectangleBar.width(),0);

   //if(rectangleDraw.intersect(rectangleBar,rectangleBrick))
   //{

   //   ::rectangle_i32(hdc,rectangleDraw.left,rectangleDraw.top,rectangleDraw.right,rectangleDraw.bottom);

   //}

   //rectangleBrick.offset(rectangleBar.width() * 2,0);

   //if(rectangleDraw.intersect(rectangleBar,rectangleBrick))
   //{

   //   ::rectangle_i32(hdc,rectangleDraw.left,rectangleDraw.top,rectangleDraw.right,rectangleDraw.bottom);

   //}

   //string str(strEntryHallText);
   //

   //if(str.is_empty())
   //{

   //   //str = "ca2 plugin for Browsers : Internet Explorer compatible - ActiveX Tecnhology, Mozilla Firefox compatible - NPAPI : Netscape Plugin API";

   //   str = "Opening ca2...";

   //}

   //::SetBkMode(hdc,TRANSPARENT);

   //::SetTextColor(hdc,rgb(250,250,250));

   ////HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);

   ////HFONT hfontOld = (HFONT) ::SelectObject(hdc,hStockFont);

   ////::text_out(hdc,rectangleBar.left - 1,rectangleBar.bottom + 2,str,str.get_length());

   ////rectangleBar.left++;
   ////rectangleBar.top++;
   ////rectangleBar.right--;
   ////rectangleBar.bottom--;

   //rectangleBar.left += 4;

   //HFONT hFont = CreateFont(23,0,0,0,FW_DONTCARE,false,false,false,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
   //   CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,VARIABLE_PITCH,TEXT("Calibri"));
   //HFONT hfontOld = (HFONT) ::SelectObject(hdc,hFont);

   //::DrawText(hdc,str,str.get_length(),&rectangleBar,DT_SINGLELINE| e_align_left_center);

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

//   left = rectangle.left + minimum(m / 2,width(rectangle) / 2);
//   right = rectangle.right - minimum(m / 2,width(rectangle) / 2);

//}

//::rectangle_i32 rectangleBar(left,top,right,bottom);


} // namespace hotplugin



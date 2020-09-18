#include "framework.h"





namespace hotplugin
{

   u32 g_entry_hall_windows_on_paint_dwSync = 0;
   i32 g_entry_hall_windows_on_paint_iDelta = 5000;


   //// Create a hatched bit pattern.
   ////WORD HatchBits[8] ={0x55,0xAA,0x55,0xAA,0x55, 0xAA,0x55,0xAA};
   ////WORD HatchBits[8] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
   //WORD HatchBits[8] ={0,0,0,0,0,0,0,0};

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

   ////::rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);

   //::SelectObject(hdc,hbrushDark);

   //HPEN hpenLite = ::CreatePen(PS_DOT,1,RGB(184,184,177));

   //

   ////::rectangle(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

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

   //::rectangle(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

   //::SetTextColor(hdc,RGB(184,184,177));

   //::rectangle(hdc,rectBar.left-1,rectBar.top-1,rectBar.right + 1,rectBar.top);
   //::rectangle(hdc,rectBar.left - 1,rectBar.bottom,rectBar.right + 1,rectBar.bottom+1);
   //::rectangle(hdc,rectBar.left - 1,rectBar.top - 1,rectBar.left,rectBar.bottom+1);
   //::rectangle(hdc,rectBar.right,rectBar.top - 1,rectBar.right+1,rectBar.bottom + 1);

   //SetROP2(hdc,old);

   ////::rectangle(hdc,rectBar.left,rectBar.top,rectBar.right,rectBar.bottom);

   //

   ////::SelectObject(hdc,hpenLite);

   ////::SelectObject(hdc,hbrushNull);

   //int v = ::GetTickCount() * 484 / 1000;

   //::SelectObject(hdc,hpen);

   //::SelectObject(hdc,hbrushGren);

   //int x = v % rectBar.width();

   //::rect rectBrick(left + x,rectBar.top,left + x + w,rectBar.bottom);
   //::rect rectDraw;

   //if(rectDraw.intersect(rectBar,rectBrick))
   //{

   //   ::rectangle(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

   //}

   //rectBrick.offset(-rectBar.width(),0);

   //if(rectDraw.intersect(rectBar,rectBrick))
   //{

   //   ::rectangle(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

   //}

   //rectBrick.offset(rectBar.width() * 2,0);

   //if(rectDraw.intersect(rectBar,rectBrick))
   //{

   //   ::rectangle(hdc,rectDraw.left,rectDraw.top,rectDraw.right,rectDraw.bottom);

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

   //HFONT hFont = CreateFont(23,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
   //   CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,VARIABLE_PITCH,TEXT("Calibri"));
   //HFONT hfontOld = (HFONT) ::SelectObject(hdc,hFont);

   //::DrawText(hdc,str,str.get_length(),&rectBar,DT_SINGLELINE| DT_VCENTER | DT_LEFT);

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

//      const ::rect & rect;

//int h = 33;
//int m = 49 * 2;

//int top;
//int bottom;
//int left;
//int right;

//if(height(rect) < h)
//{
//   top = rect.top;
//   bottom = rect.bottom;
//}
//else
//{
//   top = rect.top + height(rect) / 2 - h / 2;
//   bottom = rect.top + height(rect) / 2 + h / 2;
//}

//if(width(rect) < m)
//{
//   left = rect.left;
//   right = rect.right;
//}
//else
//{

//   left = rect.left + min(m / 2,width(rect) / 2);
//   right = rect.right - min(m / 2,width(rect) / 2);

//}

//::rect rectBar(left,top,right,bottom);


} // namespace hotplugin



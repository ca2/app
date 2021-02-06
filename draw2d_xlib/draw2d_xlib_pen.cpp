#include "framework.h"


namespace draw2d_xlib
{


   pen::pen(::layered * pobjectContext) :
      ::object(pobject)
   {
   }
   pen::~pen()
   {
   }
/*   pen::operator HPEN() const
   {
      return (HPEN)(this == nullptr ? nullptr : get_handle());
   }*/
/*   pen* PASCAL pen::from_handle(::object * pobject, HPEN hPen)
   {
      return dynamic_cast < pen* > (::win::object::from_handle(papp, hPen));
   }*/
/*   int_bool pen::CreatePen(i32 nPenStyle, i32 nWidth, color32_t crColor)
   { return Attach(::CreatePen(nPenStyle, nWidth, crColor)); }*/
/*   int_bool pen::CreatePenIndirect(LPLOGPEN lpLogPen)
   { return Attach(::CreatePenIndirect(lpLogPen)); }*/
/*   int_bool pen::CreatePen(i32 nPenStyle, i32 nWidth, const LOGBRUSH* pLogBrush,
      i32 nStyleCount, const ::u32* lpStyle)
   { return Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
   lpStyle)); }*/
/*   i32 pen::GetExtLogPen(EXTLOGPEN* pLogPen)
   { ASSERT(get_handle() != nullptr);
   return ::GetObject(get_handle(), sizeof(EXTLOGPEN), pLogPen); }
*/
/*   i32 pen::GetLogPen(LOGPEN* pLogPen)
   {
      if(get_handle() == nullptr)
         return 0;
      return ::GetObject(get_handle(), sizeof(LOGPEN), pLogPen);
   }
*/

/*   void pen::construct(i32 nPenStyle, i32 nWidth, color32_t crColor)
   {
      if (!Attach(::CreatePen(nPenStyle, nWidth, crColor)))
         AfxThrowResourceException();
   }
*/
/*
   void pen::construct(i32 nPenStyle, i32 nWidth, const LOGBRUSH* pLogBrush,
      i32 nStyleCount, const ::u32* lpStyle)
   {
      if (!Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount,
         lpStyle)))
         AfxThrowResourceException();
   }
*/
   /////////////////////////////////////////////////////////////////////////////


#ifdef _DEBUG

   void pen::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);
//
  //    if (get_handle() == nullptr)
    //     return;

/*      if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
      {
         // not a valid object
         dumpcontext << "has ILLEGAL HPEN!";
         return;
      }
*/
  /*    LOGPEN lp;
      VERIFY(GetObject(sizeof(lp), &lp));
      dumpcontext << "lgpn.lopnStyle = " << lp.lopnStyle;
      dumpcontext << "\nlgpn.lopnWidth.x (width) = " << lp.lopnWidth.x;
      dumpcontext << "\nlgpn.lopnColor = " << (void *)(dword_ptr)lp.lopnColor;

      dumpcontext << "\n";
*/
   }

#endif




      // IMPLEMENT_DYNAMIC(resource_exception, ::exception::exception)
      //resource_exception _simpleResourceException(false, __IDS_RESOURCE_EXCEPTION);

      // IMPLEMENT_DYNAMIC(user_exception, ::exception::exception)
      //user_exception _simpleUserException(false, __IDS_USER_EXCEPTION);

      // IMPLEMENT_DYNCREATE(::draw2d::graphics_pointer, object)
      // IMPLEMENT_DYNAMIC(CClientDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNAMIC(CWindowDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNAMIC(CPaintDC, ::draw2d::graphics_pointer)
      // IMPLEMENT_DYNCREATE(object, object)

      // IMPLEMENT_DYNAMIC(pen, object)
      // IMPLEMENT_DYNAMIC(::draw2d::brush, object)
      // IMPLEMENT_DYNAMIC(::draw2d::font, object)
      // IMPLEMENT_DYNAMIC(::draw2d::bitmap, object)
      // IMPLEMENT_DYNAMIC(::draw2d::palette, object)
      // IMPLEMENT_DYNAMIC(::aura::rgn, object)

      /////////////////////////////////////////////////////////////////////////////
      // Standard exception processing


   void * pen::get_os_data() const
   {
   return nullptr;
   }

} // namespace draw2d_xlib





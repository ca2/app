#pragma once


namespace win32
{


   class CLASS_DECL_APEX font :
      virtual public object
   {
   public:


#ifdef WINDOWS
      HFONT m_hfont;
#endif


      font();
      virtual ~font();

      bool create_point_font(int iPoint, const char * pszFontFamily, int iWeight = FW_NORMAL);
      void destroy();

#ifdef WINDOWS
      HFONT get_os_data() { return m_hfont; }
#endif

   };



} // namespace win32



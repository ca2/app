#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D font :
      virtual public ::draw2d_direct2d::object,
      virtual public ::draw2d::font
   {
   public:


      Microsoft::WRL::ComPtr < IDWriteTextFormat >    m_pformat;


      font();
      virtual ~font();


      // virtual IDWriteTextFormat* get_os_data(::draw2d::graphics * pgraphics, index i) const;
      //virtual void * _get_os_data(::draw2d::graphics * pgraphics, index i) const override;

      virtual void destroy() override;
      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate) override;


      /*      virtual void construct(const ::draw2d::font & fontParam);

            virtual bool CreateFontIndirect(const LOGFONTW* lpLogFont);
            virtual bool CreateFont(int nHeight, int nWidth, int nEscapement,
                  int nOrientation, int nWeight, byte bItalic, byte bUnderline,
                  byte cStrikeOut, byte nCharSet, byte nOutPrecision,
                  byte nClipPrecision, byte nQuality, byte nPitchAndFamily,
                  const char * lpszFacename);
            virtual bool CreatePointFont(int nPointSize, const char * lpszFaceName, const ::draw2d::graphics * pgraphics = nullptr);
            virtual bool CreatePointFontIndirect(const LOGFONTW* lpLogFont, const ::draw2d::graphics * pgraphics = nullptr);

            virtual int GetLogFont(LOGFONTW* pLogFont);*/

      virtual void dump(dump_context & dumpcontext) const;

      //bool destroy();


   };


} // namespace draw2d_direct2d





//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSørensen!!
//


namespace windows
{


   class CLASS_DECL_ACME nano_device :
      virtual public ::nano_device
   {
   public:


      HDC         m_hdc;


      nano_device(HDC hdc);
      ~nano_device() override;


      void draw_text(const ::string & strMessage, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont) override;
      void rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen) override;


   };


} // namespace windows




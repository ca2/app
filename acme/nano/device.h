//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSørensen!!
//


class CLASS_DECL_ACME nano_device :
   virtual public ::matter
{
public:


   nano_device();
   ~nano_device() override;


   virtual void draw_text(const ::string & strMessage, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font  * pnanofont);
   virtual void rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen);


};





#pragma once


namespace user
{


   enum enum_zorder
   {

      e_zorder_none = 0,
      e_zorder_front = 1,
      e_zorder_back = 2,
      e_zorder_any = e_zorder_front | e_zorder_back,

   };


   DECLARE_ENUMERATION(e_zorder, enum_zorder);


   enum enum_style
   {


      StyleLightBlue,
      StyleBlackBorder,
      StyleLightGreen,
      StyleRedOrange,
      StyleDarkRed,
      StyleBlueRedPurple,
      StyleEveningSun,
      StyleTranslucidLightBlue,
      StyleTranslucidLightGreen,
      StyleTranslucidWarmGray,
      StyleTranslucidWarmLiteGray,
      StyleDarkWarmBlue,
      StyleBlackPiano,


   };


} // namespace user




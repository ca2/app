#pragma once


class variant :
   public VARIANT
{
public:
   variant()
   {
      ::VariantInit(this);
   }
   ~variant()
   {
      ::VariantClear(this);
   }

};

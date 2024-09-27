//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/graphics/brush.h"
#include "object.h"


namespace windows
{



   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_ACME brush :
            virtual public ::nano::graphics::brush,
            virtual public object
         {
         public:


            //CreatableFromBase(brush, brush);


            brush();
            ~brush() override;


            void update(::nano::graphics::device* pnanodevice) override;


         };



      } // namespace graphics


   } // namespace nano


} // namespace windows




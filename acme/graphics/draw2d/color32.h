//
// Created by camilo on 28/01/2021. 03:28 CamiloSasukeThomasBorregaardSørensen
//
#pragma once


using color32_t = unsigned int;


#pragma pack( push , color32, 1 )


class COLOR32
{
public:


   union
   {

      color32_t      color32;

      struct
      {

         unsigned char        red;
         unsigned char        green;
         unsigned char        blue;
         unsigned char        alpha;

      };

   };

};


#pragma pack( pop , color32 )




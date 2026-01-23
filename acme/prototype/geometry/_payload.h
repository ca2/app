// Created by camilo on 2025-12-07 21:57 <3ThomasBorregaardSørensen!!
#pragma once


template < prototype_number NUMBER >
inline void copy_color(sequence_type < NUMBER, 4 > & sequence4, const ::payload & payload)
{

   if (payload.array_get_count() == 3)
   {

      payload[0].as(sequence4.r);
      payload[1].as(sequence4.g);
      payload[2].as(sequence4.b);

   }
   else if (payload.array_get_count() >= 4)
   {

      payload[0].as(sequence4.r);
      payload[1].as(sequence4.g);
      payload[2].as(sequence4.b);
      payload[3].as(sequence4.a);

   }
   else
   {

      throw "too few elements for at least a r,g,b color";

   }


}


template<prototype_number NUMBER, int t_iSize>
inline auto defer_copy(sequence_type<NUMBER, t_iSize> &sequence, const ::payload &payload)
{

   auto iCopyCount = minimum(payload.array_get_count(), t_iSize);

   for (decltype(iCopyCount) i = 0; i < iCopyCount; i++)
   {

      NUMBER n;

      payload[i].as(n);

      sequence.set_coordinate(i, n);

   }

   return iCopyCount;

}


template<prototype_number NUMBER, int t_iSize>
inline void copy(sequence_type<NUMBER, t_iSize> & sequence, const ::payload & payload)
{

   auto iCopyCount = defer_copy(sequence, payload);

   if (iCopyCount < t_iSize)
   {

      throw "too few items to create sequence";

   }

}

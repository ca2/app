#pragma once


inline bool get_bounding_rect(RECT32* prectBounding, const lines* plines)
{

   plines->get_bounding_rect(prectBounding);

   return true;
}



inline bool get_bounding_rect(RECTD* prectBounding, const lines* plines)
{

   ::RECT32 r;

   plines->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const linesd* plines)
{

   ::RECTD r;

   plines->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const linesd* plines)
{

   plines->get_bounding_rect(prectBounding);

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const polygon* ppolygon)
{

   ppolygon->get_bounding_rect(prectBounding);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const polygon* ppolygon)
{

   ::RECT32 r;

   ppolygon->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECT32* prectBounding, const polygond* ppolygon)
{

   ::RECTD r;

   ppolygon->get_bounding_rect(&r);

   copy(prectBounding, &r);

   return true;

}


inline bool get_bounding_rect(RECTD* prectBounding, const polygond* ppolygon)
{

   ppolygon->get_bounding_rect(prectBounding);

   return true;

}




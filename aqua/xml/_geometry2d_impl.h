//
// Created by camilo on 30/12/2021 20:21 BRT <3ThomasBorregaardSorensend!!
//
#pragma once




template < typename POINT_TYPE >
inline ::xml::input_tree & operator >> (::xml::input_tree & xmlif, point_array_base < POINT_TYPE > & pointa)
{

   pointa.erase_all();

   string strPoints;

   xmlif.get_value(strPoints);

   string_array straPoints;

   straPoints.explode(";", strPoints);

   for (auto & strPoint : straPoints)
   {

      string_array straCoord;

      straCoord.explode(",", strPoint);

      add(POINT_TYPE(__conv < typename POINT_TYPE::UNIT_TYPE >(straCoord[0]),
                     __conv < typename POINT_TYPE::UNIT_TYPE >(straCoord[1])));


   }

   return xmlif;

}


template < typename POINT_TYPE >
inline ::xml::output_tree & operator << (::xml::output_tree & xmlof, point_array_base < POINT_TYPE > & pointa)
{

   string strPoints;

   string strFormat = __xmlpri < POINT_TYPE::UNIT_TYPE > +"," + __xmlpri < POINT_TYPE::UNIT_TYPE > + ";";

   for (auto & point : pointa)
   {

      string strPoint;

      strPoint.format(strFormat, point.x(), point.y());

      strPoints += strPoint;

   }

   xmlof.set_value(strPoints);

   return xmlof;

}




// Created by camilo on 2022-03-14 18:10 <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/prototype/prototype/object.h"


namespace user
{


   class CLASS_DECL_BERG impact_kit :
virtual public ::object
   {
   public:


      class CLASS_DECL_BERG item :
         virtual public ::matter
      {
      public:


         string                     m_strName;
         string                     m_strIcon;
         bool                       m_bVisible = true;
         bool                       m_bPermanent = false;
         ::pointer<impact_creator> m_pimpactcreator;


      };


      pointer_array < item >               m_itema;


      virtual void add_impact_item(const ::atom & atom, const ::scoped_string & scopedstrTitle, ::user::impact_creator * pimpactcreator);


   };


} // namespace user




//
// Created by camilo on 2024-10-28 01:00 <3ThomasBorregaardSorensen!!
//
#pragma once

namespace accessibility
{
   class accessibility;
} // namespace accessibility


namespace platform
{


   struct axis_system_layer_t
   {


      ::pointer<class ::account::user_set>            m_puserset;

      //::pointer<class ::xml::department>              m_pxml;


      ::pointer<class ::geo::geo>                     m_pgeo;


      ::pointer<::networking::email_department>      m_pemaildepartment;


      ::pointer<::html::html>                        m_phtml;

      ::pointer<::factory::factory>                          m_pfactoryRegularExpressionPcre;

      ::pointer<::accessibility::accessibility> m_paccessibility;


   };





   class CLASS_DECL_ACME axis_system_layer
   {
   public:


      virtual ::networking::email_department * email();

      //::xml::department &                          xml();

      virtual ::geo::geo * geo();

      virtual ::pointer<::account::user_set>              userset();

      virtual void create_html();

      virtual void defer_create_html();


      virtual ::accessibility::accessibility * accessibility();
      


   };



} // namespace platform





// Created on 2021-11-01 18:12 BRT <3ThomasBorregaardS�rensen!!
#pragma once


typedef void FN_IMPLEMENT(::acme::system * psystem);
typedef FN_IMPLEMENT* PFN_IMPLEMENT;


namespace acme
{


   class CLASS_DECL_ACME implementable
   {
   public:


      PFN_IMPLEMENT              m_pfnImplement = nullptr;


      virtual bool defer_implement(::acme::system * psystem);


   };


} // namespace acme




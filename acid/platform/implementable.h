// Created on 2021-11-01 18:12 BRT <3ThomasBorregaardSorensen!!
#pragma once


typedef void FN_IMPLEMENT(::acid::context * pcontext);
typedef FN_IMPLEMENT* PFN_IMPLEMENT;


namespace acid
{


   class CLASS_DECL_ACID implementable
   {
   public:


      PFN_IMPLEMENT              m_pfnImplement = nullptr;


      virtual bool defer_implement(::acid::context * pcontext);


   };


} // namespace acid




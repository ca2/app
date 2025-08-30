//
// Created by camilo on 2025-08-30 02:07 <3ThomasBorregaardSorensen!!
//
#pragma once
namespace data
{
   class CLASS_DECL_ACME block

   : virtual public ::particle
{
   public:

   bool m_bWrite = false;
   ::procedure m_procedureOnFinished;
   ::string m_strPath;
   ::string m_strMime;
   ::memory m_memory;

   block();

   ~

   block()

   override;
};
using block_array = ::pointer_array_base<block>;
} // namespace data
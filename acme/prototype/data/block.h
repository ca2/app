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
   ::string m_strPath;
   ::string m_strMime;
   ::memory m_memory;
   ::pointer < ::manual_reset_happening > m_pmanualresethappening;

   block();

   ~

   block()

   override;

   virtual void initialize_set_operation(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrMime, const ::block & block);
   virtual void initialize_get_operation(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrMime);


   virtual void byte2_exchange(byte2_stream & stream);

};
using block_array = ::pointer_array_base<block>;
} // namespace data
#pragma once


namespace crypto
{


   class CLASS_DECL_APEX hasher_algorithm :
      virtual public ::matter
   {
   public:


      virtual ::e_status initialize_hasher_algorithm(enum_hash ehash) = 0;

      virtual enum_hash ehash() const = 0;

      virtual ::e_status hash(memory & memoryHash, const block & block) = 0;

      virtual __transport(::crypto::hasher) create_hasher() = 0;


   };


} // namespace crypto



//CLASS_DECL_APEX ::crypto::hasher_algorithm * __hasher_algorithm(enum_hash ehash);


//CLASS_DECL_APEX ::crypto::hasher_algorithm * __create_hasher_algorithm(enum_hash ehash);





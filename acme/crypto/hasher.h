#pragma once





namespace crypto
{


   class CLASS_DECL_ACME hasher :
      virtual public ::particle
   {
   public:


      virtual enum_hash ehash() const = 0;

      virtual void update(const block & block) = 0;

      virtual memory get_hash_and_reset() = 0;


   };

   
} // namespace crypto








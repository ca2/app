#pragma once


#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/collection/array.h"
//#include "acme/primitive/collection/pointer_array.h"


namespace match
{


   class CLASS_DECL_ACME item :
      virtual public particle
   {
   public:


      item() {}
      ~item() override {}


      virtual bool matches(const ::payload & payload) const = 0;


   };


   class CLASS_DECL_ACME _and :
      virtual public item
   {
   public:


      item* m_pitem1;
      item* m_pitem2;


      virtual bool matches(const ::payload & payload) const;

   };


   class CLASS_DECL_ACME string :
      virtual public item
   {
   public:


      ::string      m_str;


      string(const ::scoped_string & scopedstr = nullptr);


      virtual bool matches(const ::payload & payload) const;


   };


   class CLASS_DECL_ACME ci_string :
      virtual public item
   {
   public:


      ::string      m_str;

      ci_string(const ::scoped_string & scopedstr = nullptr);


      virtual bool matches(const ::payload & payload) const;


   };


   class CLASS_DECL_ACME prefix :
      virtual public item
   {
   public:


      ::string      m_str;

      prefix(const ::scoped_string & scopedstr = nullptr);


      virtual bool matches(const ::payload & payload) const;


   };


   class CLASS_DECL_ACME ci_prefix :
      virtual public item
   {
   public:


      ::string      m_str;


      ci_prefix(const ::scoped_string & scopedstr = nullptr);


      virtual bool matches(const ::payload & payload) const;


   };


   class CLASS_DECL_ACME suffix :
      virtual public item
   {
   public:


      ::string      m_str;


      suffix(const ::scoped_string & scopedstr = nullptr);


      virtual bool matches(const ::payload & payload) const;


   };


   class CLASS_DECL_ACME ci_suffix :
      virtual public item
   {
   public:


      ::string      m_str;

      ci_suffix(const ::scoped_string & scopedstr = nullptr);


      virtual bool matches(const ::payload & payload) const;

   };


   class CLASS_DECL_ACME any :
      virtual public item
   {
   public:


      HAVE_ARRAY_OF(item, m_itema, item);


      virtual bool matches(const ::payload & payload) const;



   };


} // namespace match




#pragma once


struct CLASS_DECL_ACME elemental :
   virtual public elemental
{

   
   __pointer(property_set)    m_pset;


   elemental() { }
   virtual ~elemental();


   virtual stream & do_property_exchange(stream & stream) const;
   virtual stream & do_property_exchange(stream & stream);
   virtual void exchange(::stream & stream);


   virtual stream & write(::stream & stream) const override;
   virtual stream & read(::stream & stream) override;

   using elemental::cast;

   inline bool has_property(const id & id) const;
   inline property * lookup_property(const id & id) const;
   inline bool remove_key(const id & id);

   inline property_set & get_propset();
   inline const property_set & get_propset() const;
   inline property_set & propset();
   inline const property_set & propset() const;
   inline bool contains(const property_set & set) const;

   inline property & set(const ::id & id);

   
   inline ::papaya::topic topic(const ::id & id);


   inline property * find_property(const ::id & id) const;


   inline var attribute(const ::id & id);
   ::property * find_attribute(const ::id & id);

   template < typename TYPE >
   inline bool find_attribute(const ::id & id, TYPE & t);
 
   inline var find_value(const ::id & id) const;
   inline var find_value(const ::id & id, const var & varDefault) const;
   
   
   inline var & elemental(const ::id & id);


   inline var operator()(const ::id & id) const;
   inline var operator()(const ::id & id, const var & varDefault) const;


   inline property & operator[](const ::id & id);


   inline var operator[](const ::id & id) const;


   inline var value(const ::id & id) const;
   inline var value(const ::id & id, const var & varDefault) const;


   inline string find_string(const ::id & id, const ansichar * pszDefault = nullptr) const;


   inline ::i32 find_i32(const ::id & id, ::i32 iDefault = 0) const;


   inline ::u32 find_u32(const ::id & id, ::u32 iDefault = 0) const;


   template < typename TYPE > inline TYPE & get_cast(const ::id & id, TYPE * pDefault = nullptr);
   template < typename TYPE > inline __pointer(TYPE) cast(const ::id & id) const;


   inline void defer_propset();


   inline bool is_true(const ::id & id) const;
   inline bool is_true(const ::id & id, const var & varDefault, bool bDefault) const;


}; // struct elemental




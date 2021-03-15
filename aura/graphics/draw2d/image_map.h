#pragma once



class image_map :
   virtual public map < enum_image, ::image_pointer >
{
public:

};


class CLASS_DECL_AURA size_image :
   virtual public map < concrete < size_i32 >, ::image_pointer >
{
public:


   ::image_pointer & operator[](const concrete < size_i32 > & size);
   ::image_pointer & get(const concrete < size_i32 > & size, bool & bExists);


};


using image_descriptor_map_base = map < image_header, ::image_pointer >;


class CLASS_DECL_AURA image_descriptor_map :
   virtual public image_descriptor_map_base
{
public:


   i32 m_iLimitCount;


   image_descriptor_map(i32 iLimitCount = 500) 
   {

      m_iLimitCount = iLimitCount;

   }


   inline ::image * operator[](const image_header & key)
   {

      while (get_count() > m_iLimitCount)
      {

         remove_bigger();

      }

      auto & pimage = image_descriptor_map_base::operator [](key);

      if (pimage->is_null())
      {

         __construct(pimage);
         
         
         pimage->create(key.m_size);

      }

      return pimage;

   }


   void remove_bigger()
   {

      image_header keyFind;

      u64 uAreaMax = 0;

      auto passociation = get_start();

      while (passociation != nullptr)
      {

         if (!passociation->element2()->is_shared() && passociation->element2()->area() > uAreaMax)
         {

            uAreaMax = passociation->element2()->area();

            keyFind = passociation->element1();

         }

         passociation = passociation->m_pnext;

      }

      if (uAreaMax > 0)
      {

         remove_key(keyFind);

      }
      else
      {

         remove_key(get_start()->element1());

      }

   }

};



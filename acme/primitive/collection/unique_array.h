#pragma once

template < class TYPE, class ARG_TYPE = const TYPE &, class BASE_ARRAY = array < TYPE, ARG_TYPE >, class COMPARE = ::comparison::less < TYPE, ARG_TYPE > >
class unique_sort_array :
   protected BASE_ARRAY
{
public:
   unique_sort_array(::particle * pparticle = nullptr);
   unique_sort_array(const unique_sort_array & array);

   virtual index add(ARG_TYPE newElement)
   {
      index iFind = 0;
      if(find(newElement, iFind))
      {
         return -1;
      }
      else
      {
         this->insert_at(iFind, newElement);
         return iFind;
      }
   }

   bool find(ARG_TYPE t, index & find) const
   {
      index iL = find;
      index iU = this->get_upper_bound();
      while(iU - iL > 5)
      {
         find = (iL + iU) / 2;
         if(COMPARE::compare(t, this->element_at(find)))
         {
            iU = find - 1;
         }
         else if(COMPARE::compare(this->element_at(find), t))
         {
            iL = find + 1;
         }
         else
         {
            return true;
         }
      }
      for(; find >= 0; find--)
      {
         if(COMPARE::compare(this->element_at(find), t))
         {
            break;
         }
      }
      for(; find < this->get_size(); find++)
      {
         if(COMPARE::compare(t, this->element_at(find)))
         {
            return false;
         }
         else if(COMPARE::compare(this->element_at(find), t))
         {
         }
         else
         {
            return true;
         }
      }
      return false;
   }

   void clear()
   {
      BASE_ARRAY::clear();
   }

   void erase_all()
   {
      BASE_ARRAY::erase_all();
   }

};


template < typename TYPE >
class unique_array :
   protected array < TYPE >
{
public:
   unique_array(::particle * pparticle = nullptr);
   unique_array(const unique_array & array);

   virtual index add(TYPE newElement)
   {
      index iFind = 0;
      if(find(newElement, iFind))
      {
         return -1;
      }
      else
      {
         insert_at(iFind, newElement);
         return iFind;
      }
   }

   bool find(const TYPE &t, index & find) const
   {
      for(; find < this->get_size(); find++)
      {
         if(this->element_at(find) == t)
            break;
      }
      return find;
   }

};

//
// Created by camilo on 5/6/21 20:00 BRT <3ThomasBS_!!
//


inline void copy(::int_rectangle * prectTarget, const cairo_rectangle_int_t * prectSource)
{

   prectTarget->left() = prectSource->x;
   prectTarget->top() = prectSource->y;
   prectTarget->right() = prectSource->x + prectSource->width;
   prectTarget->bottom() = prectSource->y + prectSource->height;

}


inline void copy(cairo_rectangle_int_t * prectTarget, const ::int_rectangle * prectSource)
{

   prectTarget->x = prectSource->left();
   prectTarget->y = prectSource->top();
   prectTarget->width = width(prectSource);
   prectTarget->height = height(prectSource);


}




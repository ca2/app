//
// Created by camilo on 5/6/21 20:00 BRT <3ThomasBS_!!
//


inline void copy(RECTANGLE_I32 * prectTarget, const cairo_rectangle_int_t * prectSource)
{

   prectTarget->left = prectSource->x;
   prectTarget->top = prectSource->y;
   prectTarget->right = prectSource->x + prectSource->width;
   prectTarget->bottom = prectSource->y + prectSource->height;

}


inline void copy(cairo_rectangle_int_t * prectTarget, const RECTANGLE_I32 * prectSource)
{

   prectTarget->x = prectSource->left;
   prectTarget->y = prectSource->top;
   prectTarget->width = width(prectSource);
   prectTarget->height = height(prectSource);


}




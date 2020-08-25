#include "framework.h"
#include "aura_gdk.h"


void copy(RECT * prectTarget, const GdkRectangle * prectSource)
{

   prectTarget->left = prectSource->x;

   prectTarget->top = prectSource->y;

   prectTarget->right = prectSource->x + prectSource->width;

   prectTarget->bottom = prectSource->y + prectSource->height;


}



void copy(GdkRectangle * prectTarget, const RECT * prectSource)
{

   prectTarget->x = prectSource->left;

   prectTarget->y = prectSource->top;

   prectTarget->width = ::width(prectSource);

   prectTarget->height = ::height(prectSource);


}




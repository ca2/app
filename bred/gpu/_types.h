/// Created by camilo on 2025-08-23 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/geometry/quaternion.h"
#include "acme/prototype/geometry/sequence.h"
#include "acme/prototype/geometry/matrix.h"


using floating_sequence2 = ::float_sequence2;
using floating_sequence3 = ::float_sequence3;
using floating_sequence4 = ::float_sequence4;


using floating_matrix2 = ::float_matrix2;
using floating_matrix3 = ::float_matrix3;
using floating_matrix4 = ::float_matrix4;

using floating_angle = float_angle;
using floating_quaternion = ::float_quaternion;


namespace gpu
{



	struct point_light
	{

		floating_sequence4       position{};  // ignore w
		floating_sequence4       color{};     // w is intensity

	};


   struct point_light_push_constants
   {

      floating_sequence4 position{}; // ignore w
      floating_sequence4 color{}; // w is intensity
      float radius;
   };



} // namespace gpu




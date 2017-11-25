#ifndef SDLFRAMEWORK_LINAL_INTERFACES_DRAWABLE
#define SDLFRAMEWORK_LINAL_INTERFACES_DRAWABLE

#include "FWapplication.h"

namespace Linal
{
	namespace Interfaces
	{
		class Drawable
		{
		public:
			virtual void Draw(FWApplication*& application, int offsetX, int offsetY) = 0;

		private:

		};
	}
}


#endif
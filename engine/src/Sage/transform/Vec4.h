#pragma once

namespace Sage {
	template<typename T>
	struct Vec4
	{
		union 
		{
			struct
			{
				T x, y, w, h;
			};
			struct
			{
				T r, g, b, a;
			};
		};

		operator T* ()
		{
			return &x;
		}
	};
}
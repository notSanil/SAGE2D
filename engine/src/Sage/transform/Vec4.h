#pragma once

namespace Sage {
	struct Vec4
	{
		union 
		{
			struct
			{
				int x, y, w, h;
			};
			struct
			{
				int r, g, b, a;
			};
		};
	};
}
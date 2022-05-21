#include <Sage/Sage.h>

#include "EditorLayer.h"


namespace Sage {

	class SageEditor : public Engine
	{
	public:
		SageEditor():
			Engine(960, 540, "Sage")
		{
			PushLayer(std::make_unique<EditorLayer>());
		}

		~SageEditor()
		{
		}
	};


}
extern Sage::Engine* CreateApplication()
{
	return new Sage::SageEditor();
}
#include <Glacier.h>
#include <Glacier/Core/EntryPoint.h> // 여기서만 진입점을 include 해주어야 main 함수가 중복되지 않음.

#include "EditorLayer.h"

namespace Glacier {

	class GlacierEditor : public Application
	{
	public:
		GlacierEditor()
			: Application(L"Glacier Editor")
		{
			PushLayer(new EditorLayer());
		}

		~GlacierEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new GlacierEditor();
	}

}
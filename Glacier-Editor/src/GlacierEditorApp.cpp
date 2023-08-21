#include <Glacier.h>
#include <Glacier/Core/EntryPoint.h> // ���⼭�� �������� include ���־�� main �Լ��� �ߺ����� ����.

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
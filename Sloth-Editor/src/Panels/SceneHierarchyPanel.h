#pragma once

#include "Sloth/Core/Base.h"
#include "Sloth/Core/Log.h"
#include "Sloth/Scene/Scene.h"
#include "Sloth/Scene/Entity.h"

namespace Sloth {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}
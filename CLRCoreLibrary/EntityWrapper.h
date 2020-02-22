#pragma once
#include "ManagedObject.h"
#include "../CPPStaticLibrary/Entity.h"

using namespace System;

namespace CLRCoreLibrary
{
	public ref class EntityWrapper : public ManagedObject<Core::Entity>
	{
	public:
		EntityWrapper(String^ name, float xPos, float yPos);

		void Move(float deltaX, float deltaY);

		property float XPosition
		{
		public:
			float get()
			{
				return m_Instance->GetXPosition();
			}
		private:
			void set(float value)
			{
			}
		}

		property float YPosition
		{
		public:
			float get()
			{
				return m_Instance->GetYPosition();
			}
		private:
			void set(float value)
			{
			}
		}
	};
}
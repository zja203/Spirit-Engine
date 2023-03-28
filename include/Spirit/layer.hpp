#pragma once

#include "Spirit/core/base.hpp"
#include "Spirit/events/event.hpp"

namespace Spirit {
       class Layer {
       public:
               Layer(const std::string& name = "Layer");
               virtual ~Layer();

               virtual void OnAttach() {}
               virtual void OnDetach() {}
               virtual void OnUpdate() {}
               virtual void OnEvent(Event& event) {}

               inline const std::string& getName() const { return m_DebugName; }
       protected:
               std::string m_DebugName;
       };
}

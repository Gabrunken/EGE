#pragma once
#include <vector>
#include <string>
#include <EGE_transform.hpp>
#include <EGE_component.hpp>

namespace EGE
{
    class GameObject
    {
    protected:
        std::string m_Name;
        Transform m_Transform;
        std::vector<Component> m_Components;
    };
}
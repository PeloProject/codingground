#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Comopnent;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID GetComponentID() noexcept
{
    static ComponentID typeID = GetComponentID();
    return typeID();
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;





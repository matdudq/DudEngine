#pragma once

#include <memory>

namespace dud {
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T>
const auto MakeScope = std::make_unique<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T>
const auto MakeRef = std::make_shared<T>;
}
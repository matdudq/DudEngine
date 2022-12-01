#pragma once

#include <memory>

namespace dud {
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T>
    using Weak = std::weak_ptr<T>;
}
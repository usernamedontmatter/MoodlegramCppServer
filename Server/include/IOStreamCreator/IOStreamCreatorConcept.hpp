#pragma once

#include "../IOStream/IOStreamConcept.hpp"

namespace IOStream {
    template <typename T>
    concept IOStreamCreatorConcept = IOStreamConcept<typename T::Stream> && requires(T obj) {
        { obj.getStream() } -> std::same_as<typename T::Stream*>;
    };
}
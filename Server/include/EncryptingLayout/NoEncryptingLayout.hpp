#pragma once

#include "EncryptingLayoutInterface.hpp"

namespace EncryptingLayout {
    template<IOStream::IOStreamConcept IOStreamType>
    class NoEncryptingLayout : public EncryptingLayoutInterface<IOStreamType> {
    public:
        explicit NoEncryptingLayout(IOStreamType* iostream) : EncryptingLayoutInterface<IOStreamType>(iostream) {}
    };
}
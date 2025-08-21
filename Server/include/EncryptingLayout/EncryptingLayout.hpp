#pragma once

#include "../IOStream/IOStream.hpp"

#include "EncryptingLayoutInterface.hpp"
#include "NoEncryptingLayout.hpp"

static_assert(IOStream::IOStreamConcept<EncryptingLayout::EncryptingLayoutInterface<IOStream::TCPStreamCreator::Stream>>);
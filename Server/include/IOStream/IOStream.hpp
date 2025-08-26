#pragma once

#include "IOStreamConcept.hpp"
#include "TCPStream.hpp"

static_assert(IOStream::IOStreamConcept<IOStream::TCPStream>);

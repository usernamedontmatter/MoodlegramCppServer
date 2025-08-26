#pragma once

#include "IOStreamCreatorConcept.hpp"
#include "TCPStreamCreator.hpp"

static_assert(IOStream::IOStreamCreatorConcept<IOStream::TCPStreamCreator>);
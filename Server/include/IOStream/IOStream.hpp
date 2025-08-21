#pragma once

#include "IOStreamConcept.hpp"
#include "IOStreamCreatorConcept.hpp"
#include "TCPStreamCreator.hpp"

static_assert(IOStream::IOStreamCreatorConcept<IOStream::TCPStreamCreator>);

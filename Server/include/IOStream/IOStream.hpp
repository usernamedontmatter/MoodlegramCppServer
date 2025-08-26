#pragma once

#include "IOStreamConcept.hpp"
#include "../IOStreamCreator/IOStreamCreatorConcept.hpp"
#include "../IOStreamCreator/TCPStreamCreator.hpp"

static_assert(IOStream::IOStreamCreatorConcept<IOStream::TCPStreamCreator>);

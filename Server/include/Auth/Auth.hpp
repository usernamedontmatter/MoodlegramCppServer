#pragma once

#include "AuthData.hpp"
#include "AuthConcept.hpp"
#include "NoAuth.hpp"

#include "../Database/TempDatabase.hpp"
#include "../IOStream/TCPStreamCreator.hpp"

static_assert(Auth::AuthConcept<Auth::NoAuth<Database::TempDatabase, IOStream::TCPStreamCreator::Stream>, Database::TempDatabase, IOStream::TCPStreamCreator::Stream>);
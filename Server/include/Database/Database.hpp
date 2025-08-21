#pragma once

#include "DatabaseConcept.hpp"
#include "TempDatabase.hpp"

#include "../Auth/AuthData.hpp"

static_assert(Database::DatabaseConcept<Database::TempDatabase<Auth::NoAuthData>, Auth::NoAuthData>);
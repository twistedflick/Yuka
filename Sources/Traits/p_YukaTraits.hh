/* Copyright 2018 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef P_YUKA_TRAITS_HH_
# define P_YUKA_TRAITS_HH_             1

# include <iostream>
# include <iomanip>
# include <cstring>
# include <string>
# include <vector>
# include <unordered_map>

# if WITH_LUA
extern "C" {
#  include <lua.h>
#  include <lualib.h>
#  include <lauxlib.h>
}
# endif

# include "Yuka/Traits.hh"

# include "Yuka/Behaviours/Behaviour.hh"

using namespace Yuka;
using namespace Yuka::Traits;
using Yuka::Traits::Trait;

typedef std::vector<Listening *> ListenerVector;
typedef std::unordered_map<Yuka::Events::EventKind, ListenerVector> ListenerMap;

struct Yuka::Traits::ObservableData
{
	Flexible *flex;
	ListenerMap map;
	
	ObservableData(Observable *owner);
	ListenerVector *vectorFor(Events::EventKind what, bool shouldCreate = false);
};

#endif /*!P_YUKA_TRAITS_HH_*/

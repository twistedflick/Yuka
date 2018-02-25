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
# include <unordered_map>

/* Include each trait header directly to avoid dependency hell at build-time */
# include "Yuka/Trait.hh"
# include "Yuka/Traits/Debuggable.hh"
# include "Yuka/Traits/Flexible.hh"
# include "Yuka/Traits/Identifiable.hh"
# include "Yuka/Traits/Scriptable.hh"
# include "Yuka/Traits/Spatial.hh"

using namespace Yuka;
using namespace Yuka::Traits;

#endif /*!P_YUKA_TRAITS_HH_*/

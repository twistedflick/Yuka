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

#ifndef YUKA_TRAITS_SCRIPTABLE_HH_
# define YUKA_TRAITS_SCRIPTABLE_HH_    1

# include <string>

# include "../Trait.hh"
# include "../decl.h"

namespace Yuka
{
	namespace Traits
	{
		const IdentityFlag ScriptableTrait = 0x00000004;
		
		/* Classes with the Scriptable trait can be populated and manipulated
		 * through a simplified interface suitable for integration with scripting
		 * languages, or for use by parsers constructing scenes.
		 */
		class YUKA_EXPORT_ Scriptable:
			public virtual Trait
		{
		public:
			/* Set a named property to a supplied value, emitting a warning
			 * and returning false upon error.
			 */
			virtual bool set(const std::string key, const std::string value);
		public:
			/* Utility methods for converting values supplied via set() into
			 * native types; these methods return false upon error and log
			 * a message to std::cerr.
			 */
			static bool parseDouble(const std::string str, double *out);
			static bool parseBool(const std::string str, bool *out);
			static bool parseInt(const std::string str, int *out);
			static bool parseUInt(const std::string str, unsigned int *out);
		};
	};
};

#endif /*!YUKA_TRAITS_SCRIPTABLE_HH_*/

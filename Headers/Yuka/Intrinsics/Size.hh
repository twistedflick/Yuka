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

#ifndef YUKA_SIZE_HH_
# define YUKA_SIZE_HH_          1

# include <string>

# include "Vector.hh"
# include "../decl.h"

namespace Yuka
{
	/* Yuka::Size represents a distance or scale factor in three-dimensional
	 * space
	 */
	struct YUKA_EXPORT_ Size: public Vector
	{
		Size(),
		Size(const double amount);
		Size(const double nx, const double ny, const double nz);
		
		virtual std::string kind(void) const;
	};
	
};

#endif /*!YUKA_SIZE_HH_*/

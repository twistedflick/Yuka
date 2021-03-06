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

#ifndef YUKA_VECTOR_HH_
# define YUKA_VECTOR_HH_               1

# include <string>

# include "../Traits/Debuggable.hh"
# include "../decl.h"

namespace Yuka
{
	/* Yuka::Vector represents some sort of three-dimensional value */
	struct YUKA_EXPORT_ Vector:
		public virtual Traits::Debuggable
	{
		double x;
		double y;
		double z;
		
		Vector();
		Vector(const double nx, const double ny, const double nz);
		
		void setX(const double nx);
		bool setX(const std::string nx);
		void setY(const double ny);
		bool setY(const std::string ny);
		void setZ(const double nz);
		bool setZ(const std::string nz);
		
		virtual std::string kind(void) const;
	protected:
		/* Printable trait */
		virtual std::ostream &print(std::ostream &stream) const;
	public:
		/* Mathematical operators */
		YUKA_EXPORT_ Vector &operator+=(const Vector &rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		};

		YUKA_EXPORT_ Vector &operator-=(const Vector &rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}
		
		YUKA_EXPORT_ Vector &operator*=(const Vector &rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}

		YUKA_EXPORT_ Vector &operator/=(const Vector &rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			return *this;
		}
		
	};
	
};

#endif /*!YUKA_VECTOR_HH_*/

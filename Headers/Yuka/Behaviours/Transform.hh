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

#ifndef YUKA_BEHAVIOURS_TRANSFORM_HH_
# define YUKA_BEHAVIOURS_TRANSFORM_HH_ 1

#include "../Behaviour.hh"
#include "../Intrinsics/Point.hh"
#include "../Intrinsics/Orientation.hh"
#include "../Intrinsics/Size.hh"
#include "../decl.h"

namespace Yuka
{
	namespace Behaviours
	{
		class YUKA_EXPORT_ Transform:
			public Yuka::Behaviour
		{
		public:
			Transform();
			Transform(const Point pos);
			Transform(const double px, const double py, const double pz);
		
			virtual Point position(void) const;
			virtual void setPosition(const Point pos);
		
			virtual double x(void) const;
			virtual void setX(double nx);
			virtual bool setX(const std::string nx);

			virtual double y(void) const;
			virtual void setY(double nx);
			virtual bool setY(const std::string nx);

			virtual double z(void) const;
			virtual void setZ(double nx);
			virtual bool setZ(const std::string nx);
		
			virtual Orientation rotation(void) const;
			virtual void setRotation(const Orientation rot);

			virtual double rotX(void) const;
			virtual void setRotX(double nx);
			virtual bool setRotX(const std::string nx);

			virtual double rotY(void) const;
			virtual void setRotY(double nx);
			virtual bool setRotY(const std::string nx);

			virtual double rotZ(void) const;
			virtual void setRotZ(double nx);
			virtual bool setRotZ(const std::string nx);
		
			virtual Size scale(void) const;
			virtual void setScale(const Size factor);
			virtual void setScale(const double factor);
			virtual bool setScale(const std::string factor);
		
			virtual double scaleX(void) const;
			virtual void setScaleX(const double nx) ;
			virtual bool setScaleX(const std::string factor);

			virtual double scaleY(void) const;
			virtual void setScaleY(const double nx) ;
			virtual bool setScaleY(const std::string factor);
		
			virtual double scaleZ(void) const;
			virtual void setScaleZ(const double nx) ;
			virtual bool setScaleZ(const std::string factor);
		
			virtual bool set(const std::string key, const std::string value);
			virtual std::string kind(void) const;
		protected:
			virtual std::ostream &printProperties(std::ostream &stream) const;
		private:
			Point m_position;
			Orientation m_rotation;
			Size m_scale;
		};
	};
};

#endif /*!YUKA_BEHAVIOURS_TRANSFORM_HH_*/

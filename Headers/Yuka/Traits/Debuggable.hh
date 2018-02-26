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

#ifndef YUKA_TRAITS_DEBUGGABLE_HH_
# define YUKA_TRAITS_DEBUGGABLE_HH_    1

# include <ios>

# include "../Trait.hh"
# include "../decl.h"

namespace Yuka
{
	namespace Traits
	{
		
		const IdentityFlag DebuggableTrait = 0x00000001;

		/* The Debuggable trait provides methods for serialising an object
		 * for logging output.
		 *
		 * The operator<< implementation allows any Printable class to be
		 * sent to a std::ostream.
		 */
	
		class YUKA_EXPORT_ Debuggable:
			public virtual Trait
		{
		public:
			virtual void dump(void) const;
		public:
			/* Enable debugging output for objects on this thread */
			static void debug(void);
		protected:
			/* Override these methods to provide more detailed output */
			virtual std::ostream &print(std::ostream &stream) const;
			virtual std::ostream &printTraits(std::ostream &stream) const;
			virtual std::ostream &printProperties(std::ostream &stream) const;
			virtual std::ostream &printChildren(std::ostream &stream) const;
			virtual std::ostream &printBehaviours(std::ostream &stream) const;

			/* Utilities for use while printing objects */
			virtual unsigned int printDepth(void) const;
			virtual std::string printIndent(void) const;
			virtual void printPush(void) const;
			virtual void printPop(void) const;
		
			virtual bool debugging(void) const;
		
			friend YUKA_EXPORT_ std::ostream &operator<<(std::ostream &stream, const Debuggable &obj);
			friend YUKA_EXPORT_ std::ostream &operator<<(std::ostream &stream, const Debuggable *obj);
		};
	};
};

#endif /*!YUKA_TRAITS_DEBUGGABLE_HH_*/

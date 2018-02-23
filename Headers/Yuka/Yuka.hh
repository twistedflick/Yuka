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

#ifndef YUKA_HH_
# define YUKA_HH_                      1

# define NS_YUKA                       "https://twistedflick.github.io/Yuka/"

/* Threading note: unless otherwise noted, it is unsafe to invoke multiple
 * method calls on a single given instance of any of these classes across
 * multiple threads simultaneously, without using some kind of external
 * barrier (such as a POSIX mutex or a spinlock).
 *
 * However, it is perfectly safe to use them in multiple threads so long
 * as no single object is being accessed by two threads at the same time.
 * Particular care must be taken with scenes and the objects within them -
 * if one thread is touching part of a scene, you can't assume it's safe
 * to modify a different part of the scene at the same time in a different
 * thread. In contrast, if you have two threads which are each manipulating
 * independent scenes, then no concurrency issues will arise.
 *
 * This is unquestionably a limitation of the implementation, but it's a
 * limitation which can be removed in future by adding and using locking
 * primitives in certain parts of the code without requiring significant
 * reorganisation.
 */

# include "SceneObject.hh"
# include "Scene.hh"
# include "SceneParser.hh"
# include "Prop.hh"
# include "Primitive.hh"
# include "Sphere.hh"
# include "Cube.hh"

#endif /*!YUKA_HH_*/

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

/* This header will redefine various macros at the point that it is
 * included. These macros are used to decorate class and function
 * definitions depending upon what is being compiled, for which platform,
 * and for which compiler.
 */

#undef YUKA_EXPORT_
#undef YUKA_PRIVATE_
#undef YUKA_WEAKPTR_
#ifdef __GNUC__
# define YUKA_EXPORT_ __attribute__((visibility ("default")))
# define YUKA_PRIVATE_ __attribute__((visibility ("hidden")))
#else
# define YUKA_EXPORT_
# define YUKA_PRIVATE_
#endif
#define YUKA_WEAKPTR_

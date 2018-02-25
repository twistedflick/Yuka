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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_YukaTraits.hh"

bool
Scriptable::set(const std::string key, const std::string value)
{
	Identifiable *id = dynamic_cast<Identifiable *>(this);
	
	if(id)
	{
		if(key == "tag")
		{
			return id->setTag(value);
		}
	}
	
	std::cerr << "Warning: Unsupported property: ";
	if(id)
	{
		std::cerr << id->kind() << "['" << key << "']\n";
	}
	else
	{
		std::cerr << "'" << key << "'\n";
	}
	return false;
}

/* String to native type conversions */
bool
Scriptable::parseInt(const std::string str, int *out)
{
	char *endp;
	int d;
	
	endp = NULL;
	d = (int) strtol(str.c_str(), &endp, 0);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << str << "' to an integer value\n";
		return false;
	}
	*out = d;
	return true;
}

bool
Scriptable::parseBool(const std::string str, bool *out)
{
	const char *cstr;
	char *endp;
	int d;
	
	cstr = str.c_str();
	if(!strcasecmp(cstr, "t") ||
		!strcasecmp(cstr, "true") ||
		!strcasecmp(cstr, "yes") ||
		!strcasecmp(cstr, "on"))
	{
		*out = true;
		return true;
	}
	if(!strcasecmp(cstr, "f") ||
		!strcasecmp(cstr, "false") ||
		!strcasecmp(cstr, "no") ||
		!strcasecmp(cstr, "off"))
	{
		*out = false;
		return true;
	}
	endp = NULL;
	d = (int) strtol(cstr, &endp, 0);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << str << "' to boolean value\n";
		return false;
	}
	*out = d ? true : false;
	return true;
}

bool
Scriptable::parseDouble(const std::string str, double *out)
{
	char *endp;
	double d;
	
	endp = NULL;
	d = strtod(str.c_str(), &endp);
	if(endp && *endp)
	{
		std::cerr << "Error: Cannot convert '" << str << "' to a double-precision floating point value\n";
		return false;
	}
	*out = d;
	return true;
}

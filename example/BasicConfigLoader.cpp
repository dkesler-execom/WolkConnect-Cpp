/*
 * Copyright 2017 WolkAbout Technology s.r.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "BasicConfigLoader.h"
#include "utilities/FileSystemUtils.h"
#include "utilities/json.hpp"

namespace example
{
bool BasicConfigLoader::load(const std::string& confFile, std::string& key, std::string& password, std::string& host)
{
	std::string content;
	if(!wolkabout::FileSystemUtils::readFileContent(confFile, content))
	{
		return false;
	}

	try
	{
		nlohmann::json j = nlohmann::json::parse(content);

		if(j.find("key") != j.end())
		{
			key = j.at("key").get<std::string>();
		}

		if(j.find("password") != j.end())
		{
			password = j.at("password").get<std::string>();
		}

		if(j.find("host") != j.end())
		{
			host = j.at("host").get<std::string>();
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}
}
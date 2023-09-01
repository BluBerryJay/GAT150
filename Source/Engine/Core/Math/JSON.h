#pragma once
#include "Vector2.h"
#include "Color.h"
#include "Rect.h"
#include <rapidjson/include/rapidjson/document.h>
#include <string>
#include <vector>

#define READ_DATA(value, data) kiko::JSON::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) kiko::JSON::Read(value, #data, data, true)
#define READ_NAME_DATA(value, name, data) kiko::JSON::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) kiko::JSON::Read(value, name, data, true)
#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]
namespace kiko
{
	class JSON
	{
	public:
		static bool Load(const std::string& fileName, rapidjson::Document& document);
		static bool Read(const rapidjson::Value & value, const std::string& name, int& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required = false);
	};
	using json_t = rapidjson::Value;
}
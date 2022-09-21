#include "variables.hpp"
#include <direct.h>

static std::string path = "custom configs/";
static const std::filesystem::path path_fs = "custom configs";

nlohmann::json config;

template<typename T>
void read_value(T& value, std::string str)
{
	if (config[str].empty())
		return;

	value = config[str].get<T>();
}

void read_value_array(float_t value[4], std::string str)
{
	if (config[str]["0"].empty() || config[str]["1"].empty() || config[str]["2"].empty() || config[str]["3"].empty())
		return;

	value[0] = config[str]["0"].get<float_t>();
	value[1] = config[str]["1"].get<float_t>();
	value[2] = config[str]["2"].get<float_t>();
	value[3] = config[str]["3"].get<float_t>();
}

void read_value_array2(bool value[14], std::string str)
{
	if (config[str]["0"].empty() || config[str]["1"].empty() || config[str]["2"].empty() || config[str]["3"].empty()
		|| config[str]["4"].empty() || config[str]["5"].empty() || config[str]["6"].empty() || config[str]["7"].empty()
		|| config[str]["8"].empty() || config[str]["9"].empty() || config[str]["10"].empty() || config[str]["11"].empty()
		|| config[str]["12"].empty() || config[str]["13"].empty())
		return;

	value[0] = config[str]["0"].get<bool>();
	value[1] = config[str]["1"].get<bool>();
	value[2] = config[str]["2"].get<bool>();
	value[3] = config[str]["3"].get<bool>();
	value[4] = config[str]["4"].get<bool>();
	value[5] = config[str]["5"].get<bool>();
	value[6] = config[str]["6"].get<bool>();
	value[7] = config[str]["7"].get<bool>();
	value[8] = config[str]["8"].get<bool>();
	value[9] = config[str]["9"].get<bool>();
	value[10] = config[str]["10"].get<bool>();
	value[11] = config[str]["11"].get<bool>();
	value[12] = config[str]["12"].get<bool>();
	value[13] = config[str]["13"].get<bool>();
}

template<typename T>
void write_value(T& value, std::string str)
{
	config[str] = value;
}

void write_value_array(float_t value[4], std::string str)
{
	config[str]["0"] = value[0];
	config[str]["1"] = value[1];
	config[str]["2"] = value[2];
	config[str]["3"] = value[3];
}

void write_value_array2(bool value[14], std::string str)
{
	config[str]["0"] = value[0];
	config[str]["1"] = value[1];
	config[str]["2"] = value[2];
	config[str]["3"] = value[3];
	config[str]["4"] = value[4];
	config[str]["5"] = value[5];
	config[str]["6"] = value[6];
	config[str]["7"] = value[7];
	config[str]["8"] = value[8];
	config[str]["9"] = value[9];
	config[str]["10"] = value[10];
	config[str]["11"] = value[11];
	config[str]["12"] = value[12];
	config[str]["13"] = value[13];
}

namespace variables
{
	void create_directory() noexcept
	{
		if (!std::filesystem::exists(path_fs)) // std::string will alloc.
		{
			std::filesystem::create_directory(path_fs);
		}
		else
		{
			update_configs();
		}
	}

	void update_configs() noexcept
	{
		configs.clear();

		for (const auto& entry : std::filesystem::directory_iterator{ path_fs })
		{
			if (!entry.is_regular_file() || entry.path().extension() != ".json") continue;

			const auto& file_name = entry.path().stem().string();
			configs.emplace_back(file_name);
		}
	}

	void create_file(const std::string_view name) noexcept
	{
		if (name.empty() || name.find_first_not_of(' ') == std::string_view::npos) return;
		if (std::find(configs.cbegin(), configs.cend(), name) != configs.cend()) return;

		configs.emplace_back(name);
		save(configs.size() - 1);
	}

	void delete_file(const std::size_t index) noexcept
	{
		if (configs.size() <= index) return;

		path.append(configs.at(index));
		path.append(".json");
		std::filesystem::remove(path);
		path.erase(path.size() - configs.at(index).size() - 5);

		configs.erase(configs.cbegin() + index);
		configs.shrink_to_fit();
	}

	void save(const std::size_t index) noexcept
	{
		nlohmann::json json;
//

		path.append(configs.at(index));

		const bool has_json_in_filename = path.rfind(".json") != std::string::npos;
		if (!has_json_in_filename)
		{
			path.append(".json");
		}

		if (std::ofstream output_file{ path }; output_file.good())
		{
			output_file << std::setw(4) << json;
		}

		path.erase(path.size() - configs.at(index).size() - (!has_json_in_filename ? 5 : 0));
	}

	void load(const std::size_t index) noexcept
	{
		path.append(configs.at(index));
		path.append(".json");

		if (std::ifstream input_file{ path }; input_file.good())
		{
			nlohmann::json json;
			input_file >> json;
// 
		}

		path.erase(path.size() - configs.at(index).size() - 5);
	}
}

//
// write_value(json["Miscellaneous"]["Fake Prime"], fake_prime);
// 
// 
// read_value(json["Miscellaneous"]["Fake Prime"], fake_prime);
//
// 
// DOC:
// 
// inline color is something different and not a float like f_blabla_blbla 
// 
// 
// 
//
#pragma once
#include <vector>
template <typename T>
class ConfigItem
{
	std::string category, name;
	T* value;
public:
	ConfigItem(std::string category, std::string name, T* value)
	{
		this->category = category;
		this->name = name;
		this->value = value;
	}
};

template <typename T>
class ConfigValue
{
public:
	ConfigValue(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
protected:
	std::vector<ConfigValue<int>*> ints;
	std::vector<ConfigValue<bool>*> bools;
	std::vector<ConfigValue<float>*> floats;
private:
	void SetupValue(int&, int, std::string, std::string);
	void SetupValue(bool&, bool, std::string, std::string);
	void SetupValue(float&, float, std::string, std::string);
public:
	CConfig()
	{
		Setup();
	}
	void Setup();
	void SaveLegit();
	void LoadLegit();
	void SaveLegit2();
	void LoadLegit2();
	void SaveLegit3();
	void LoadLegit3();
	void SaveHVH();
	void LoadHVH();
	void SaveHVH2();
	void LoadHVH2();
	void SaveHVH3();
	void LoadHVH3();
	void SaveCustom();
	void LoadCustom();
	void SaveCustom2();
	void LoadCustom2();
	void SaveCustom3();
	void LoadCustom3();
};

extern CConfig* Config;
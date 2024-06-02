#pragma once

#include <unordered_map>
#include <string>

#include "config.hpp"

namespace Materials
{
	enum class Id { Air = 0, Sand, Water, Stone, Gas, Poison, Acid };
	enum class Type { Void = 0, Gas, Liquid, Powdery, Solid };
	enum class Feature { None = 0, Acidic, Flamable, Diffusing };

	struct Material
	{
		char symbol;
		std::string color;
		std::string displayName;
		Type type;
		Feature feature;
	};

	static const std::unordered_map<Id, Material> materials
	{
	  {Id::Air,		{Config::Signs::air,	Config::Escape::Colors::black,			"Air",		Type::Void,		Feature::None}},
	  {Id::Sand,	{Config::Signs::sand,	Config::Escape::Colors::yellowBright,	"Sand",		Type::Powdery,	Feature::None}},
	  {Id::Water,	{Config::Signs::water,	Config::Escape::Colors::blueBright,		"Water",	Type::Liquid,	Feature::None}},
	  {Id::Stone,	{Config::Signs::stone,	Config::Escape::Colors::blackBright,	"Stone",	Type::Solid,	Feature::None}},
	  {Id::Gas,		{Config::Signs::gas,	Config::Escape::Colors::green,			"Gas",		Type::Gas,		Feature::Flamable}},
	  {Id::Poison,	{Config::Signs::poison,	Config::Escape::Colors::magenta,		"Poison",	Type::Liquid,	Feature::Diffusing}},
	  {Id::Acid,	{Config::Signs::acid,	Config::Escape::Colors::greenDark,		"Acid",		Type::Liquid,	Feature::Acidic}}
	};

	static const Id matIdBySign(char sign)
	{
		for (auto& material : materials)
		{
			if (sign == material.second.symbol)
				return material.first;
		}

		return Id::Air;
	}
}

#pragma once

#include <unordered_map>
#include <string>

#include "common_utils.hpp"

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
	  {Id::Air,		{AIR_SIGN,		BLACK,		"Air",		Type::Void,		Feature::None}},
	  {Id::Sand,	{SAND_SIGN,		YELLOW_BR,	"Sand",		Type::Powdery,	Feature::None}},
	  {Id::Water,	{WATER_SIGN,	BLUE_BR,	"Water",	Type::Liquid,	Feature::None}},
	  {Id::Stone,	{STONE_SIGN,	BLACK_BR,	"Stone",	Type::Solid,	Feature::None}},
	  {Id::Gas,		{GAS_SIGN,		GREEN,		"Gas",		Type::Gas,		Feature::Flamable}},
	  {Id::Poison,	{POISON_SIGN,	MAGENTA,	"Poison",	Type::Liquid,	Feature::Diffusing}},
	  {Id::Acid,	{ACID_SIGN,		GREEN_DK,	"Acid",		Type::Liquid,	Feature::Acidic}}
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

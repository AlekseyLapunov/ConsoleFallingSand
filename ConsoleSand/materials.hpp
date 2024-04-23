#include <unordered_map>
#include <string>

#include "common_utils.hpp"

enum class MaterialId		{ Air = 0, Sand, Water, Stone, Gas, Poison, Acid };
enum class MaterialType		{ Void = 0, Gas, Liquid, Powdery, Solid };
enum class MaterialFeature	{ None = 0, Acidic, Flamable, Diffusing };

struct Material
{
	char symbol;
	std::string color;
	std::string displayName;
	MaterialType type;
	MaterialFeature feature;
};

static const std::unordered_map<MaterialId, Material> materials
{
  {MaterialId::Air,		{AIR_SIGN,		BLACK,		"Air",		MaterialType::Void,		MaterialFeature::None}},
  {MaterialId::Sand,	{SAND_SIGN,		YELLOW_BR,	"Sand",		MaterialType::Powdery,	MaterialFeature::None}},
  {MaterialId::Water,	{WATER_SIGN,	BLUE_BR,	"Water",	MaterialType::Liquid,	MaterialFeature::None}},
  {MaterialId::Stone,	{STONE_SIGN,	BLACK_BR,	"Stone",	MaterialType::Solid,	MaterialFeature::None}},
  {MaterialId::Gas,		{GAS_SIGN,		GREEN,		"Gas",		MaterialType::Gas,		MaterialFeature::Flamable}},
  {MaterialId::Poison,	{POISON_SIGN,	MAGENTA,	"Poison",	MaterialType::Liquid,	MaterialFeature::Diffusing}},
  {MaterialId::Acid,	{ACID_SIGN,		GREEN_DK,	"Acid",		MaterialType::Liquid,	MaterialFeature::Acidic}}
};
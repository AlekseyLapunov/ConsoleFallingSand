#include "common_utils.hpp"

enum class MaterialId		{ Air = 0, Sand, Water, Stone, Gas, Poison };
enum class MaterialType		{ Void = 0, Gas, Liquid, Powdery, Solid };
enum class MaterialFeature	{ None = 0, Acidic, Flamable, Diffusing };

struct Material
{
	char symbol;
	std::string color;
	std::string displayName;
	MaterialType type;
};

static const std::unordered_map<MaterialId, Material> materials
{
  {MaterialId::Air,		{AIR_SIGN,		BLACK,		"Air",		MaterialType::Void}},
  {MaterialId::Sand,	{SAND_SIGN,		YELLOW_BR,	"Sand",		MaterialType::Powdery}},
  {MaterialId::Water,	{WATER_SIGN,	BLUE_BR,	"Water",	MaterialType::Liquid}},
  {MaterialId::Stone,	{STONE_SIGN,	BLACK_BR,	"Stone",	MaterialType::Solid}},
  {MaterialId::Gas,		{GAS_SIGN,		GREEN,		"Gas",		MaterialType::Gas}},
  {MaterialId::Poison,	{POISON_SIGN,	MAGENTA,	"Poison",	MaterialType::Liquid}}
};
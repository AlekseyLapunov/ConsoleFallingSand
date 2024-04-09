#include "common_utils.hpp"

typedef enum class MaterialId   { Air = 0, Sand, Water, Stone, Gas };
typedef enum class MaterialType { Void = 0, Solid, Powdery, Liquid, Gas };

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
  {MaterialId::Gas,		{GAS_SIGN,		GREEN,		"Gas",		MaterialType::Gas}}
};
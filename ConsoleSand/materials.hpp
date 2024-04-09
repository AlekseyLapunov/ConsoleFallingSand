#include "common_utils.hpp"

typedef enum class MaterialId { Air = 0, Sand, Water, Stone, Gas };

struct Material
{
	char symbol;
	std::string color;
	std::string displayName;
};

static const std::unordered_map<MaterialId, Material> materials
{
  {MaterialId::Air,		{AIR_SIGN,		BLACK,		"Air"}},
  {MaterialId::Sand,	{SAND_SIGN,		YELLOW_BR,	"Sand"}},
  {MaterialId::Water,	{WATER_SIGN,	BLUE_BR,	"Water"}},
  {MaterialId::Stone,	{STONE_SIGN,	BLACK_BR,	"Stone"}},
  {MaterialId::Gas,		{GAS_SIGN,		GREEN,		"Gas"}}
};
#include "common_utils.hpp"

typedef enum { Air = 0, Sand, Water, Stone } materialId;

struct Material
{
	char symbol;
	std::string color;
	std::string displayName;
};

static const std::unordered_map<materialId, Material> materials
{
  {Air,		{AIR_SIGN,		BLACK,		"Air"}},
  {Sand,	{SAND_SIGN,		YELLOW_BR,	"Sand"}},
  {Water,	{WATER_SIGN,	BLUE_BR,	"Water"}},
  {Stone,	{STONE_SIGN,	BLACK_BR,	"Stone"}}
};
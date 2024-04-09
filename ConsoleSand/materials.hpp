#include "common_utils.hpp"

// Unified Material Representation
enum MaterialsId { Air, Sand, Water, Stone };

struct Material
{
	char symbol;
	std::string color;
	std::string displayName;
};

static const std::unordered_map<int, Material> materials
{
  {Air,		{AIR,	BLACK,		"Air"}},
  {Sand,	{SAND,	YELLOW_BR,	"Sand"}},
  {Water,	{WATER,	BLUE_BR,	"Water"}},
  {Stone,	{STONE,	BLACK_BR,	"Stone"}}
};
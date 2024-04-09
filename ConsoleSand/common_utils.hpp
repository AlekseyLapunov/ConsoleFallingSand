#pragma once

#include <stdint.h>
#include <string>
#include <unordered_map>

#define CURSOR	'4'

// Types to Char
#define AIR		' '
#define SAND	'S'
#define WATER	'W'
#define STONE	'T'

// Colors escape sequences
#define YELLOW_BR		"\033[93m"
#define BLUE_BR			"\033[94m"
#define BLACK_BR		"\033[90m"
#define WHITE			"\033[97m"
#define BLACK			"\033[30m"

// Text formatting escape sequences
#define STANDARD_STYLE	"\033[0m"
#define UNDERLINE		"\033[4m"

// Console manipulations escape sequences
#define HIDE_CARRIAGE		"\033[?25l"
#define SHOW_CARRIAGE		"\033[?25h"
#define MOVE_CARRIAGE_START	"\033[0;0H"

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
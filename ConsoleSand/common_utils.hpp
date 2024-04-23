#pragma once

#define CURSOR	'+'

// Types to Char
#define AIR_SIGN	' '
#define SAND_SIGN	'S'
#define WATER_SIGN	'W'
#define STONE_SIGN	'T'
#define GAS_SIGN	'G'
#define POISON_SIGN	'P'
#define ACID_SIGN	'A'

// Colors escape sequences
#define YELLOW_BR		"\033[93m"
#define BLUE_BR			"\033[94m"
#define BLACK_BR		"\033[90m"
#define WHITE			"\033[97m"
#define BLACK			"\033[30m"
#define GREEN			"\033[92m"
#define GREEN_DK		"\033[32m"
#define MAGENTA			"\033[35m"

// Text formatting escape sequences
#define STANDARD_STYLE	"\033[0m"
#define UNDERLINE		"\033[4m"

// Console manipulations escape sequences
#define HIDE_CARRIAGE		"\033[?25l"
#define SHOW_CARRIAGE		"\033[?25h"
#define MOVE_CARRIAGE_START	"\033[0;0H"
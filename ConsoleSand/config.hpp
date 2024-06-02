#pragma once

namespace Config 
{
	namespace Signs
	{
		static const char cursor	= '+';
		static const char air		= ' ';
		static const char sand		= 'S';
		static const char water		= 'W';
		static const char stone		= 'T';
		static const char gas		= 'G';
		static const char poison	= 'P';
		static const char acid		= 'A';
	}

	namespace Escape
	{
		namespace Colors
		{
			static const char yellowBright[]	= "\033[93m";
			static const char blueBright[]		= "\033[94m";
			static const char blackBright[]		= "\033[90m";
			static const char white[]			= "\033[97m";
			static const char black[]			= "\033[30m";
			static const char green[]			= "\033[92m";
			static const char greenDark[]		= "\033[32m";
			static const char magenta[]			= "\033[35m";
		}

		namespace Formatting
		{
			static const char standart[]	= "\033[0m";
			static const char underline[]	= "\033[4m";
		}

		namespace Carriage
		{
			static const char hide[]		= "\033[?25l";
			static const char show[]		= "\033[?25h";
			static const char moveStart[]	= "\033[0;0H";
		}
	}

	namespace Grid 
	{
		static const uint8_t height	= 22;
		static const uint8_t width	= 50;
	}

	static const uint16_t frequency = 60;
}

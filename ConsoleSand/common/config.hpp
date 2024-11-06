#pragma once

namespace Config 
{
    using symbol    = const char;
    using sequence  = const char[];

    namespace Signs
    {
        static symbol cursor    = '+';
        static symbol air       = ' ';
        static symbol sand      = 'S';
        static symbol water     = 'W';
        static symbol stone     = 'T';
        static symbol gas       = 'G';
        static symbol poison    = 'P';
        static symbol acid      = 'A';
    }

    namespace Escape
    {
        namespace Colors
        {
            static sequence yellowBright    = "\033[93m";
            static sequence blueBright      = "\033[94m";
            static sequence blackBright     = "\033[90m";
            static sequence white           = "\033[97m";
            static sequence black           = "\033[30m";
            static sequence green           = "\033[92m";
            static sequence greenDark       = "\033[32m";
            static sequence magenta         = "\033[35m";
        }

        namespace Formatting
        {
            static sequence standart    = "\033[0m";
            static sequence underline   = "\033[4m";
        }

        namespace Carriage
        {
            static sequence hide        = "\033[?25l";
            static sequence show        = "\033[?25h";
            static sequence moveStart   = "\033[0;0H";
        }
    }

    namespace Grid
    {
        static const uint16_t width     = 128;
        static const uint16_t height    = 128;
    }

    namespace ViewPort
    {
        static const uint8_t width  = 50;
        static const uint8_t height = 22;
    }

    static const uint16_t frequency = 25;

    static constexpr uint16_t refreshMilliseconds(const uint16_t& frequency) 
    {
        return static_cast<uint16_t>(1000.f / frequency);
    }
}

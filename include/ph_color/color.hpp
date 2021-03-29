#pragma once
#include <iostream>
#include <sstream>
using namespace std;

namespace _color {
/**
 43

 ANSI escape color codes :

 Name            FG  BG
 Black           30  40
 Red             31  41
 Green           32  42
 Yellow          33  43
 Blue            34  44
 Magenta         35  45
 Cyan            36  46
 White           37  47
 Bright Black    90  100
 Bright Red      91  101
 Bright Green    92  102
 Bright Yellow   93  103
 Bright Blue     94  104
 Bright Magenta  95  105
 Bright Cyan     96  106
 Bright White    97  107
 */
    enum Code {
        RED      = 91,
        GREEN    = 92,
        BLUE     = 34,
        WHITE  = 97,
        BLACK = 90,
        PINK = 95,
        YELLOW = 93,
        CYAN = 96,
//        TEST = 36
    };

    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
_color::Modifier red {_color::RED};
_color::Modifier green {_color::GREEN};
_color::Modifier blue {_color::BLUE};
_color::Modifier yellow {_color::YELLOW};
_color::Modifier black {_color::BLACK};
_color::Modifier pink {_color::PINK};
_color::Modifier cyan {_color::CYAN};
_color::Modifier white {_color::WHITE};

}

template <int code>
class color : public std::ostream
{
    static std::mutex& getCoutMutex()
        // use a Meyers' singleton for the cout mutex to keep this header-only
    {
        static std::mutex m;
        return m;
    }

    std::lock_guard<std::mutex> lg_;

  public:
    // Generic constructor
    // You need to pass the right mutex to match the stream you want
    color(std::mutex& m, std::ostream& os)
      : std::ostream(os.rdbuf())
      , lg_{m}
    { }

    // Cout specific constructor
    // Uses a mutex singleton specific for cout
    color()
      : color(getCoutMutex(), std::cout)
    { }
};




color<_color::Code::RED> red;
color<_color::Code::WHITE> white;
color<_color::Code::GREEN> green;
color<_color::Code::BLUE> clue;
color<_color::Code::YELLOW> yellow;
color<_color::Code::BLACK> black;
color<_color::Code::PINK> pink;
color<_color::Code::CYAN> cyan;



template <int code, int i>
color<i>& operator<< (color<code>& c, color<i>& j)
{
    static_cast<std::ostream&>(c) << "\033[" << i << "m";
    return j;
//    return c;
}

template <int code, typename T>
color<code>& operator<< (color<code>& c, T const& a)
{

    static_cast<std::ostream&>(c) << "\033[" << code << "m" << a;
//    c << white;
    return c;
}

template <int code>
color<code>& operator<<(color<code>& c, std::ostream& (*fun)(std::ostream&)) {
    c << "\n";
    return c;
}

#pragma once
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


#define yellow "\033[93m"
#define green "\033[92m"
#define black "\033[90m"
#define red "\033[91m"
#define blue "\033[94m"
#define magenta "\033[95m"
#define cyan "\033[96m"
#define white "\033[97m"

//string color;

struct text {
    string text;
    string color {white};
    string color_before {white};
    
    friend ostream& operator<< (ostream& os, struct text const& t) {
        os << t.color << t.text << t.color_before;
        return os;
    }
};

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

//#define set_color(x) color = x;



#define SET_COLOR_OR_WHITE(_color) if (string (_color).empty ()) cout << white; else cout << _color; color = _color;

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
//_color::Modifier red {_color::RED};
//_color::Modifier green {_color::GREEN};
//_color::Modifier blue {_color::BLUE};
//_color::Modifier yellow {_color::YELLOW};
//_color::Modifier black {_color::BLACK};
//_color::Modifier pink {_color::PINK};
//_color::Modifier cyan {_color::CYAN};
//_color::Modifier white {_color::WHITE};

}








//color<_color::Code::RED> red;
//color<_color::Code::WHITE> white;
//color<_color::Code::GREEN> green;
//color<_color::Code::BLUE> clue;
//color<_color::Code::YELLOW> yellow;
//color<_color::Code::BLACK> black;
//color<_color::Code::PINK> pink;
//color<_color::Code::CYAN> cyan;

//template <int i>
//inline ostream& green(ostream& o){
//    return o;
//}

//struct _end{};
//_end nd;
//
//template <int code>
//color<code>& operator<< (color<code>& c, _end& j)
//{
//    static_cast<std::ostream&>(c) << "\n";
//    return c;
////    return c;
//}

//template <int code, int i>
//color<i>& operator<< (color<code>& c, color<i>& j)
//{
//    static_cast<std::ostream&>(c) << "\033[" << i << "m";
//    return j;
////    return c;
//}

//template <int code, typename T>
//color<code>& operator<< (color<code>& c, T&& a)
//{
// 
//    stringstream ss;
//    ss << c.str;
//    ss << forward<T>(a);
//    static_cast<std::ostream&>(c) << forward<T>(a) << "\033[93m";
////    c << white;
//    return c;
//}

//template <int code>
//color<code>& operator<< (color<code>& c, ostream&(*f)(ostream&))
//{
//    cout << "yoyoyo" << endl;
//    return c;
//}







/**
 cout << left << setw(40) << s
 <<  setw(30) << s2  << "kuk" << "\t" << endl;
 */




#include <ostream>
#include <istream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <strstream>
#include <ios>
class LoggingOutputStreambuf : public std::streambuf, public ostream
{
    std::streambuf* myDest;
//    ofstreambuf myLogFile;
    std::ostream* myOwner;
protected:
    int overflow( int ch ) override
    {
//        cout << "kndksnf" << endl;
//        printf(char(ch);
//        myLogFile.sputc( ch );  //  ignores errors...
        return myDest->sputc( ch );
    }
public:
    LoggingOutputStreambuf(
            std::streambuf* dest
//                           ,
//            std::string const& logfileName
                           )
        : myDest( dest )
//        , myLogFile( logfileName.c_str(), std::ios_base::out )
        , myOwner( nullptr )
    {
//        if ( !myLogFile.is_open() ) {
//            //  Some error handling...
//        }
    }
    LoggingOutputStreambuf(
            std::ostream& dest
//                           ,
//            std::string const& logfileName
                           )
        : myDest( dest.rdbuf()), myOwner (nullptr), ostream(this)
    {
        dest.rdbuf( this );
        myOwner = &dest;
//        myDest->sputc('\0');
//        myDest->sputc('3');
//        myDest->sputc('[');
//        myDest->sputc('9');
//        myDest->sputc('3');
//        myDest->sputc('m');
    }
    ~LoggingOutputStreambuf()
    {
//        cout << "yo" << endl;
//        stringstream buf;
//        streambuf *backup;
//        
//        backup = cout.rdbuf();
//        cout.rdbuf(buf.rdbuf());
//        buf << "normal buf" << endl;
//        cout << "cout to buf" << endl;
//        cout.rdbuf(backup);
//        cout << "normal cout" << endl;
//        cout << buf.str() << endl;
//        cout << "w" << endl;
//        std::ostringstream ss;
//        ss << std::cin.rdbuf();
//        std::string s = ss.str();
//        cout << s << endl;
        if ( myOwner != nullptr ) {
            myOwner->rdbuf( myDest );
        }
    }
};



class MyStream : public std::iostream, private std::streambuf
{
private:
    std::string     str;
    
    virtual std::streamsize xsputn(const char* s, std::streamsize n)
    {
        cout << "xsputn" << endl;
        str.append(s, n);
        setp(&(*str.begin()), &(*str.end()));
        return n;
    }

    virtual int overflow(char c)
    {
        str.push_back(c);
        setp(&(*str.begin()), &(*str.end()));
        return c;
    }


public:
    MyStream() : std::iostream(this), str() { }
    ~MyStream() {
        
    }
    void print()
    {
        std::cout << str;
    }
};








namespace ansi {
  template < class CharT, class Traits >
  constexpr
  std::basic_ostream< CharT, Traits > & reset( std::basic_ostream< CharT, Traits > &os )
  {
     return os << "\033[0m";
  }

  template < class CharT, class Traits >
  constexpr
  std::basic_ostream< CharT, Traits > & foreground_black( std::basic_ostream< CharT, Traits > &os )
  {
     return os << "\033[30m";
  }

  template < class CharT, class Traits >
  constexpr
  std::basic_ostream< CharT, Traits > & foreground_red( std::basic_ostream< CharT, Traits > &os )
  {
     return os << "\033[31m";
  }

 } // ansi


/**
 std::cout << ansi::foreground_red << "in red" << ansi::reset << std::endl;

 */

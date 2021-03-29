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
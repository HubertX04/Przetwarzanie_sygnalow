#include <pybind11/pybind11.h>
#include <matplot/matplot.h>
#include <cmath>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
#define pi 3.14159

int sinus()
{
     using namespace matplot;
    std::vector<double> x = linspace(0, 2 * pi);
    std::vector<double> y=transform(x, [](auto x) { return sin(x); });
    plot(x, y)->line_width(2).color("red");
    show();
    return 0;
}

int cosinus()
{
    using namespace matplot;
    std::vector<double> x = linspace(0, 2 * pi);
    std::vector<double> y=transform(x, [](auto x) { return cos(x); });
    plot(x, y)->line_width(2).color("red");
    show();
    return 0;
}



PYBIND11_MODULE(projekt3, m) {

    m.def("sinus", &sinus);
    m.def("cosinus",&cosinus );
   

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
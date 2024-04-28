#include <pybind11/pybind11.h>
#include <matplot/matplot.h>
#include <cmath>
#include "AudioFile.h"

AudioFile<double> audioFile;

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)
#define pi 3.14159265358979323

int sin(int a)
{
    using namespace matplot;
    std::vector<double> x = linspace(0, a * pi);
    std::vector<double> y=transform(x, [](auto x) { return sin(x); });
    plot(x, y)->line_width(2).color("red");
    xlabel("X");
    ylabel("Y");
    show();
    return 0;
}

int cos(int a)
{
    using namespace matplot;
    std::vector<double> x = linspace(0, a * pi);
    std::vector<double> y=transform(x, [](auto x) { return cos(x); });
    plot(x, y)->line_width(2).color("red");
    xlabel("X");
    ylabel("Y");
    show();
    return 0;
}

int pilo(int a)
{
    using namespace matplot;
    std::vector<double> x;
    std::vector<double> y;
    for(int i=0; i<5; i++)
    {
        x.push_back(a*i);
        y.push_back(-1);
        x.push_back(a*i+a);
        y.push_back(1);
    }
    plot(x, y)->line_width(2).color("red");
    xlabel("X");
    ylabel("Y");
    show();

    return 0;
}

int prostokat(int a)
{
   using namespace matplot;
    std::vector<double> x;
    std::vector<double> y;
    for(int i=0; i<10; i+=2)
    {
        x.push_back(a*i);
        y.push_back(1);
        x.push_back(a*i);
        y.push_back(-1);
        x.push_back(a*i+a);
        y.push_back(-1);
        x.push_back(a*i+a);
        y.push_back(1);
        x.push_back(a*i+2*a);
        y.push_back(1);
    }
    plot(x, y)->line_width(2).color("red");
    xlabel("X");
    ylabel("Y");
    show();

    return 0; 
}

int show_audio()
{
    std::vector<double> x;
    std::vector<double> y;

    audioFile.load ("test-audio.wav");
    int channel = 0;
    int numSamples = audioFile.getNumSamplesPerChannel();

    if(numSamples>500)
    {
        numSamples=500;
    }
    for (int i = 0; i < numSamples; i++)
    {
        double currentSample = audioFile.samples[channel][i]*10;
        x.push_back(i);
        y.push_back(currentSample);
    }

    

    matplot::plot(x, y)->line_width(2).color("red");
    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::show();

    return numSamples;
}

PYBIND11_MODULE(projekt3, m) {

    m.def("sin", &sin);
    m.def("cos", &cos );
    m.def("pilo", &pilo );
    m.def("prostokat", &prostokat);
    m.def("show_audio", &show_audio);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
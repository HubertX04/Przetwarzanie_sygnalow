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

int pilo(double a)
{
    a = 1/a;
    using namespace matplot;
    std::vector<double> x;
    std::vector<double> y;
    for(int i=0; i<20; i++)
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

int prostokat(double a)
{
    a = 1/a;
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
        double currentSample = (audioFile.samples[channel][i]);
        x.push_back(i);
        y.push_back(currentSample);
    }

    

    matplot::plot(x, y)->line_width(2).color("red");
    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::show();

    return 0;
}

int DFT()
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

    double Xr[505]={}, Xi[505]={}; //rzeczywiste + urojone

    for (int i = 0; i < numSamples; i++)
    {   
        Xr[i]=0; Xi[i]=0;
        for(int n=0; n < numSamples; n++)
        {
            Xr[i]=(Xr[i]+(audioFile.samples[channel][n]*cos(2 * pi * i * n / numSamples)));
            Xi[i]=(Xi[i]-(audioFile.samples[channel][n]*sin(2 * pi * i * n / numSamples)));
        }

        x.push_back(Xr[i]);
        y.push_back(Xi[i]);
    }

    std::vector <double> spectrum;
    std::vector <double> pom;
    for(int i=0; i<x.size(); i++)
    {
        spectrum.push_back((x[i]*x[i]+y[i]*y[i]));
        pom.push_back(i);
    }

    matplot::plot(pom, spectrum)->line_width(2).color("red");
    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::show();
    return 0;
}

int DFT_IDFT()
{
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> x_pom;
    std::vector<double> y_pom;

    audioFile.load ("test-audio.wav");
    int channel = 0;
    int numSamples = audioFile.getNumSamplesPerChannel();

    if(numSamples>500)
    {
        numSamples=500;
    }

    //************************************* DFT *******************************************
    double Xr[505]={}, Xi[505]={}; //rzeczywiste + urojone

    for (int i = 0; i < numSamples; i++)
    {   
        Xr[i]=0; Xi[i]=0;
        for(int n=0; n < numSamples; n++)
        {
            Xr[i]=(Xr[i]+(audioFile.samples[channel][n]*cos(2 * pi * i * n / numSamples)));
            Xi[i]=(Xi[i]-(audioFile.samples[channel][n]*sin(2 * pi * i * n / numSamples)));
        }

        x_pom.push_back(Xr[i]);
        y_pom.push_back(Xi[i]);
        x.push_back(i);
        y.push_back(0);
    }
    //**************************************************************************************
    // PRZEKSZTAŁCENIE SYGNAŁU NA DFT, A POTEM W IDFT MA NA CELU POKAZANIA, ŻE POWYŻSZE ALGORYTMY DZIAŁAJĄ
    // TZN. NA WYJŚCIU DOSTANIEMY TEN SAM SYGNAŁ

    double theta;
    for (int n = 0; n < numSamples; n++) 
    {
        for (int k = 0; k < numSamples; k++) 
        {
            theta = (2 * pi * k * n) / numSamples;
            y[n] = y[n] + Xr[k] * cos(theta) + Xi[k] * sin(theta);
        }
        y[n] = y[n] / numSamples;
    }

    matplot::plot(x, y)->line_width(2).color("red");
    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::show();

    return 0;
}

int IDFT()
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

    double Xr[505]={}, Xi[505]={}; //rzeczywiste + urojone

    for (int i = 0; i < numSamples; i++)
    {   
        Xr[i]=i; Xi[i]=audioFile.samples[channel][i];
        x.push_back(i);
        y.push_back(0);
    }
    double theta;
    for (int n = 0; n < numSamples; n++) 
    {
        for (int k = 0; k < numSamples; k++) 
        {
            theta = (2 * pi * k * n) / numSamples;
            y[n] = y[n] + Xr[k] * cos(theta) + Xi[k] * sin(theta);
        }
        y[n] = y[n] / numSamples;
    }

    matplot::plot(x, y)->line_width(2).color("red");
    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::show();

    return 0;
}

int remove_high_freq()
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

    //************************************* DFT *******************************************
    double Xr[505]={}, Xi[505]={}; //rzeczywiste + urojone

    for (int i = 0; i < numSamples; i++)
    {   
        Xr[i]=0; Xi[i]=0;
        for(int n=0; n < numSamples; n++)
        {
            Xr[i]=(Xr[i]+(audioFile.samples[channel][n]*cos(2 * pi * i * n / numSamples)));
            Xi[i]=(Xi[i]-(audioFile.samples[channel][n]*sin(2 * pi * i * n / numSamples)));
        }

        x.push_back(i);
        y.push_back(0);
    }
    double spectrum=0;
    for(int i=0; i<numSamples; i++)
    {
        if(Xr[i]>=Xi[i])
        {
            spectrum = Xr[i]*Xr[i]+Xi[i]*Xi[i];
            if(spectrum>1.5)
            {
                Xr[i]=0;
                Xi[i]=0;
            }
        }
    }

    //************************************* IDFT ******************************************
    double theta;
    for (int n = 0; n < numSamples; n++) 
    {
        for (int k = 0; k < numSamples; k++) 
        {
            theta = (2 * pi * k * n) / numSamples;
            y[n] = y[n] + Xr[k] * cos(theta) + Xi[k] * sin(theta);
        }
        y[n] = y[n] / numSamples;
    }

    matplot::plot(x, y)->line_width(2).color("red");
    matplot::xlabel("X");
    matplot::ylabel("Y");
    matplot::show();

    return 0;
}


PYBIND11_MODULE(projekt3, m) {

    m.def("sin", &sin);
    m.def("cos", &cos );
    m.def("pilo", &pilo );
    m.def("prostokat", &prostokat);
    m.def("show_audio", &show_audio);
    m.def("DFT", &DFT );
    m.def("IDFT", &IDFT );
    m.def("DFT_IDFT", &DFT_IDFT );
    m.def("remove_high_freq", &remove_high_freq );

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
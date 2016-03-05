/* 
 * File:   Plotter.h
 * Author: qfeuille
 *
 * Created on December 6, 2011, 8:01 PM
 */

#ifndef PLOTTER_H
#define	PLOTTER_H

#include "gnuplot_i.hpp"
#include<string>
#include <functional>
#include<vector>
#include<boost/shared_ptr.hpp>






typedef boost::shared_ptr<Gnuplot> GnuPtr;
//typedef boost::shared_ptr<CasUnaryFunction> CasPtr;

//
// Class for handling generic Gnuplot interface: saving plots and
// closing gnuplot windows when finished. Derived classes must handle
// the original plotting of the graphs.
//






class Plotter {
protected:
    std::vector<GnuPtr> plots;
    std::vector<PlotterParams> params;
public:
    void setParams (GnuPtr plot, const PlotterParams & param);
    void save(int GraphIdentifier, std::string iName);
    void saveImage(int GraphIdentifier, std::string iName, bool ToPng = true);
     template<typename X>
    void writeToFile (std::string iName,const  X& x, bool rewrite = true);
    template<typename X,typename Y>
    void writeToFile (std::string iName,const  X& x,const  Y& y, bool rewrite = true);
    template<typename X,typename Y,typename Z>
    void writeToFile (std::string iName,const  X& x,const  Y& y,const  Z& z, bool rewrite = true);
    template<typename X>
    void readfromFile (std::string iName, X& x);
    void wait (){
        int x;
        std::system("read");
    }
    ~Plotter();
};
template<typename X>
void Plotter::writeToFile (std::string iName,const  X& x, bool rewrite){
        std::ofstream outfile;
        if (rewrite)
          outfile.open(iName.c_str(), std::ios::trunc);
        else
          outfile.open(iName.c_str(), std::ios::app);
        if (outfile){
        outfile << std::string("# ") + iName<<'\n';
        for (int i =0; i<x.size();i++)
            outfile<< x[i]<<'\n';
        outfile.flush();
        outfile.close();
        }
}

template<typename X>
void Plotter::readfromFile (std::string iName, X& x){
        std::ifstream file;
        file.open(iName.c_str());
        if (file)
        	for  (int i =0; i<x.size()&& file >> x[i]; i++);
        else std::cout<<"Could not open file!"<<std::endl;
}

template<typename X,typename Y>
void Plotter::writeToFile (std::string iName,const  X& x, const  Y& y, bool rewrite){
        std::ofstream outfile;
        if (x.size()==y.size()){
        if (rewrite)
          outfile.open(iName.c_str(), std::ios::trunc);
        else
          outfile.open(iName.c_str(), std::ios::app);
        if (outfile){
        outfile << std::string("# ") + iName<<'\n';
        for (int i =0; i<x.size();i++)
            outfile<< x[i]<<" "<<y[i]<<'\n';
        outfile.flush();
        outfile.close();
        }
        }
        else std::cout<<"Sizes are not equal!";
}


   template<typename X,typename Y,typename Z>
    void Plotter::writeToFile (std::string iName,const  X& x,const  Y& y,const  Z& z, bool rewrite){
             std::ofstream outfile;
        if (x.size()==y.size()&&x.size()==z.size()){
        if (rewrite)
          outfile.open(iName.c_str(), std::ios::trunc);
        else
          outfile.open(iName.c_str(), std::ios::app);
        if (outfile){
        outfile << std::string("# ") + iName<<'\n';
        for (int i =0; i<x.size();i++)
            outfile<< x[i]<<" "<<y[i]<<" "<<z[i]<<'\n';
        outfile.flush();
        outfile.close();
        }
        }
        else std::cout<<"Sizes are not equal!";
}

//
// Plots functions given by class CasUnaryFunction. The range must
// first be set using SetRange. Functions can then be plotted using
// plot (), which returns the indentifier of the plot, which can be
// used to save the plot in a .tex file if desired.

/*class FunctionPlotter : public Plotter {
    double Begin;
    double End;
    int NumSteps;
    std::string Style;
public:
    void SetRange(double iBegin = -1, double iEnd = 1, int iNumSteps = 100, std::string iStyle = "lines");
    int plot(CasUnaryFunction * ToPlot);
};*/




class ScatterPlotter : public Plotter {
public:
    template<typename X, typename T = double>
            int plot1(const X& x, PlotterData data = PlotterData(),
            PlotterParams params = PlotterParams());
    template<typename X, typename Y, typename T = double>
            int plot2(const X& x, const Y& y,PlotterData data = PlotterData(),
            PlotterParams params = PlotterParams());
    template<typename X, typename Y, typename FunctPtr, typename T = double>
            int plot2withAnalytic(const X& x, const Y& y,FunctPtr&& analytic, int nSample = 0, PlotterData data = PlotterData(),
            PlotterParams params = PlotterParams());
    template<typename FunctPtr, typename T = double>
    int plot2Analytic(FunctPtr&& f, const T& xlower,const T& xupper, const int& nSample,PlotterData data = PlotterData(),
            PlotterParams params = PlotterParams());
    template<typename X, typename Y, typename Z, typename T = double>
            int plot3(const X& x, const Y& y, const Z& z,PlotterData data = PlotterData(),
            PlotterParams params = PlotterParams());
     template<typename X, typename T = double>
            int plot1(const X& x, const std::string& input, PlotterParams params = PlotterParams()){
         return plot1 (x, PlotterData (input,input),params);
     };
    template<typename X, typename Y, typename T = double>
            int plot2(const X& x, const Y& y,const std::string& input, PlotterParams params = PlotterParams()){
        return plot2 (x,y, PlotterData (input,input),params);
    };
    template<typename X, typename Y, typename FunctPtr, typename T = double>
            int plot2withAnalytic(const X& x, const Y& y, FunctPtr&& analytic,const std::string& input, int nSample = 0){
        return plot2withAnalytic (x,y, analytic,nSample, PlotterData (input,input));
    }
    template<typename FunctPtr, typename T = double>
    int plot2Analytic(FunctPtr&& f, const T& xlower,const T& xupper,const int& nSample, const std::string& input){
        return plot2Analytic (f,xlower,xupper,nSample, PlotterData (input,input));
    }
    
     
    
    template<typename X, typename Y, typename Z, typename T = double>
            int plot3(const X& x, const Y& y, const Z& z,const std::string& input, PlotterParams params = PlotterParams()){
        return plot3 (x,y,z, PlotterData (input,input),params);
    };
    int plot (std::vector<PlotterData> data, PlotterParams params = PlotterParams(), int nDim = -1);
};



template<typename X, typename Y, typename T>
int ScatterPlotter::plot2(const X& x, const Y& y, PlotterData data,
            PlotterParams params) {
    plots.push_back(GnuPtr(new Gnuplot()));
    if (data.input.empty()){
        data.input = plots.back()->get_tmpfile_name();
    }
    writeToFile (data.input,x,y,true);
    setParams (plots.back(), params);
    std::vector<PlotterData> datavec;
    datavec.push_back(data);
    plots.back()->plotfile_xy_general(datavec);
    return (plots.size() - 1);
}

template<typename X, typename Y,typename FunctPtr, typename T>
int ScatterPlotter::plot2withAnalytic(const X& x, const Y& y,FunctPtr&& analytic,  int nSample, PlotterData data,
            PlotterParams params) {
    plots.push_back(GnuPtr(new Gnuplot()));
    if (data.input.empty()){
        data.input = plots.back()->get_tmpfile_name();
    }
    writeToFile (data.input,x,y,true);
    
    
    std::vector<T> yAnalytic;
    if (nSample == 0) {
           yAnalytic.resize(x.size());
            for (int i=0;i<x.size();i++)
                yAnalytic [i] = analytic (x[i]);
            writeToFile (data.input + std::string("analytic"),x,yAnalytic,true);
    }
    else {
        std::vector<T> xAnalytic;
        xAnalytic.resize(nSample);
        yAnalytic.resize(nSample);
        T xmax;
        T xmin;
        NumMethod::cMinMax (x,xmin,xmax);
        T stepSize = (xmax - xmin)/ (T) nSample;
        T xs =xmin;
            for (int i=0;i<nSample;i++){
                yAnalytic [i] = analytic (xs);
                xAnalytic [i] = xs;
                xs += stepSize;
            }
        writeToFile (data.input + std::string("analytic"),xAnalytic,yAnalytic,true);
      }
    PlotterData dataA = data;
    dataA.input += std::string("analytic");
    dataA.title += std::string("analytic");
    setParams (plots.back(), params);
    std::vector<PlotterData> datavec;
    datavec.push_back(data);
    datavec.push_back(dataA);
    plots.back()->plotfile_xy_general(datavec);
    return (plots.size() - 1);
}



template<typename FunctPtr, typename T>
    int ScatterPlotter::plot2Analytic(FunctPtr&& f, const T& xlower,const T& xupper, const int& nSample,PlotterData data,
            PlotterParams params){
    //nSample invalid
    if (nSample<=0)
        return -1;
    plots.push_back(GnuPtr(new Gnuplot()));
        std::vector<T> xAnalytic(nSample),yAnalytic(nSample);
        T stepSize = (xupper - xlower)/ (T) nSample;
        T xs =xlower;
            for (int i=0;i<nSample;i++){
                yAnalytic [i] = f(xs);
                xAnalytic [i] = xs;
                xs += stepSize;
            }
        writeToFile (data.input,xAnalytic,yAnalytic,true);
    setParams (plots.back(), params);
    std::vector<PlotterData> datavec = {data};
    plots.back()->plotfile_xy_general(datavec);
    return (plots.size() - 1);
}




template<typename X, typename T>
int ScatterPlotter::plot1(const X& x, PlotterData data,
            PlotterParams params) {
    plots.push_back(GnuPtr(new Gnuplot()));
    if (data.input.empty()){
        data.input = plots.back()->get_tmpfile_name();
    }
    writeToFile (data.input, x,true);
    setParams (plots.back(), params);
    std::vector<PlotterData> datavec;
    datavec.push_back(data);
    plots.back()->plotfile_x_general(datavec);
    return (plots.size() - 1);
}

template<typename X, typename Y, typename Z, typename T>
int ScatterPlotter::plot3(const X& x, const Y& y, const Z& z, PlotterData data,
            PlotterParams params) {
    plots.push_back(GnuPtr(new Gnuplot()));
    if (data.input.empty()){
        data.input = plots.back()->get_tmpfile_name();
    }
    writeToFile (data.input,x,y,z,true);
    setParams (plots.back(), params);
    std::vector<PlotterData> datavec;
    datavec.push_back(data);
    plots.back()->plotfile_xyz_general(datavec);
    return (plots.size() - 1);
}


#endif	/* PLOTTER_H */


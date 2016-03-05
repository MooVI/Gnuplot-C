/* 
 * File:   Plotter_noc11.h
 * Author: qfeuille
 *
 * Created on 07 October 2012, 15:14
 */

#ifndef PLOTTER_NOC11_H
#define	PLOTTER_NOC11_H

#include "gnuplot_i.hpp"
#include<string>
#include<vector>
#include<boost/shared_ptr.hpp>
#include <NumericalMethods/NumericalMethods/StdVectorMath_noc11.h>
#include <fstream>
#include<iostream>
//#include <CAS IO.h> 



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
public:
    void save(int GraphIdentifier, std::string iName);
    void saveImage(int GraphIdentifier, std::string iName, bool ToPng = true);
    template<typename X>
    void writeToFile (std::string iName,const  X& x, bool rewrite = true);
    template<typename X,typename Y>
    void writeToFile (std::string iName,const  X& x,const  Y& y, bool rewrite = true);
    template<typename X,typename Y,typename Z>
    void writeToFile (std::string iName,const  X& x,const  Y& y,const  Z& z, bool rewrite = true);
    template<typename X>
    void writeMatrixToFile (std::string iName,const X* x,int nrows,int ncols, bool rewrite=true);
    template<typename X>
    void readfromFile (std::string iName, X& x);
    
    void wait (){
        int x;
        std::cin>>x;
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
   
   template<typename X>
    void Plotter::writeMatrixToFile (std::string iName,const X* x,int nrows,int ncols, bool rewrite){
             std::ofstream outfile;
        if (rewrite)
          outfile.open(iName.c_str(), std::ios::trunc);
        else
          outfile.open(iName.c_str(), std::ios::app);
        if (outfile){
        outfile << std::string("# ") + iName<<'\n';
        for (int i =0; i<nrows;i++){
        	for (int j=0;j<ncols;j++)
              outfile<< x[i] [j]<<" ";
        	outfile<<'\n';
        }
        outfile.flush();
        outfile.close();
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
    template<typename X, typename T>
            int plot1(const X& x, T typedummy,
            std::string title = "",
            std::string xlabel = "", std::string ylabel = "",
            std::string style = "lines", bool setgrid = true, T xmin = 0,
            T xmax = 0, T ymin = 0, T ymax = 0);
    template<typename X, typename Y, typename T>
            int plot2(const X& x, const Y& y,T typedummy,
            std::string title = "",
            std::string xlabel = "", std::string ylabel = "",
            std::string style = "lines", bool setgrid = true, T xmin = 0,
            T xmax = 0, T ymin = 0, T ymax = 0);
    template<typename X, typename Y, typename Z, typename T>
            int plot3(const X& x, const Y& y, const Z& z,T typedummy,
            std::string title = "",
            std::string xlabel = "", std::string ylabel = "",
            std::string style = "points", bool setgrid = true, T xmin = 0,
            T xmax = 0, T ymin = 0, T ymax = 0);
};

template<typename X, typename Y, typename T>
int ScatterPlotter::plot2(const X& x, const Y& y,T typedummy,
        std::string title,
        std::string xlabel, std::string ylabel,
        std::string style, bool setgrid, T xmin, T xmax, T ymin, T ymax) {
    plots.push_back(GnuPtr(new Gnuplot()));
    if (!xlabel.empty())plots.back()->set_xlabel(xlabel);
    if (!ylabel.empty()) plots.back()->set_ylabel(ylabel);
    if (!title.empty()) {
     //   plots.back()->set_title(title);
    //    std::ofstream outfile;
     //   outfile.open(title);
       // NumMethod::cColumnWrite(outfile, x, y);
      //  outfile.close();
    }
    if (setgrid) plots.back()->set_grid();
    if (xmax != xmin) plots.back()->set_xrange(xmin, xmax);
    if (ymax != ymin) plots.back()->set_yrange(ymin, ymax);
    plots.back()->set_style(style);
    plots.back()->plot_xy(x, y, "");
    plots.back()->showonscreen();
    return (plots.size() - 1);


}

template<typename X, typename T>
int ScatterPlotter::plot1(const X& x,T typedummy,
        std::string title,
        std::string xlabel, std::string ylabel,
        std::string style, bool setgrid, T xmin, T xmax, T ymin, T ymax) {
    plots.push_back(GnuPtr(new Gnuplot()));
    if (!xlabel.empty())plots.back()->set_xlabel(xlabel);
    if (!ylabel.empty()) plots.back()->set_ylabel(ylabel);
    if (!title.empty()) {
      //  plots.back()->set_title(title);
      //  std::ofstream outfile;
       // outfile.open(title);
      //  NumMethod::cColumnWrite(outfile, x);
     //   outfile.close();
    }
    if (setgrid) plots.back()->set_grid();
    if (xmax != xmin) plots.back()->set_xrange(xmin, xmax);
    if (ymax != ymin) plots.back()->set_yrange(ymin, ymax);
    plots.back()->set_style(style);
    plots.back()->plot_x(x, "");
    plots.back()->showonscreen();
    return (plots.size() - 1);


}

template<typename X, typename Y, typename Z, typename T>
int ScatterPlotter::plot3(const X& x, const Y& y, const Z& z,T typedummy,
        std::string title,
        std::string xlabel, std::string ylabel,
        std::string style, bool setgrid, T xmin, T xmax, T ymin, T ymax) {
    plots.push_back(GnuPtr(new Gnuplot()));
    if (!xlabel.empty())plots.back()->set_xlabel(xlabel);
    if (!ylabel.empty()) plots.back()->set_ylabel(ylabel);
    if (!title.empty()) {
      //  plots.back()->set_title(title);
      //  std::ofstream outfile;
       // outfile.open(title);
       // NumMethod::cColumnWrite(outfile, x, y, z);
      //  outfile.close();
    }
    if (setgrid) plots.back()->set_grid();
    if (xmax != xmin) plots.back()->set_xrange(xmin, xmax);
    if (ymax != ymin) plots.back()->set_yrange(ymin, ymax);
    plots.back()->set_style(style);
    plots.back()->plot_xyz(x, y, z, "");
    plots.back()->showonscreen();
    return (plots.size() - 1);


}




#endif	/* PLOTTER_NOC11_H */


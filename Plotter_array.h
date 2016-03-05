/* 
 * File:   Plotter_array.h
 * Author: qfeuille
 *
 * Created on 09 October 2012, 01:33
 */

#ifndef PLOTTER_ARRAY_H
#define	PLOTTER_ARRAY_H

#include "gnuplot_i.hpp"
#include<string>
#include<vector>

#include <fstream>
#include<iostream>

//typedef boost::shared_ptr<Gnuplot> GnuPtr;


//
// Class for handling generic Gnuplot interface: saving plots and
// closing gnuplot windows when finished. Derived classes must handle
// the original plotting of the graphs.
//

class Plotter {
protected:
    std::vector<Gnuplot*> plots;
public:
    void wait (){
        int x;
        std::cin>>x;
    }
    ~Plotter();
};


class ScatterPlotter : public Plotter {
public:
    template<typename T>
            int plot1(const T *  x,
            const int size,
            std::string title = "",
            std::string xlabel = "", std::string ylabel = "",
            std::string style = "lines", bool setgrid = true, T xmin = 0,
            T xmax = 0, T ymin = 0, T ymax = 0);
    template<typename T>
            int plot2(const T* x, const T* y,const int size,
            std::string title = "",
            std::string xlabel = "", std::string ylabel = "",
            std::string style = "lines", bool setgrid = true, T xmin = 0,
            T xmax = 0, T ymin = 0, T ymax = 0);
    template<typename T>
            int plot3(const T* x,const T*y,const T*z, const int size,
            std::string title = "",
            std::string xlabel = "", std::string ylabel = "",
            std::string style = "points", bool setgrid = true, T xmin = 0,
            T xmax = 0, T ymin = 0, T ymax = 0);
};

template<typename T>
int ScatterPlotter::plot2(const T* x, const T* y, const int size, std::string title,
        std::string xlabel, std::string ylabel, std::string style, bool setgrid,
        T xmin, T xmax, T ymin, T ymax){
    plots.push_back((new Gnuplot()));
    if (!xlabel.empty())plots.back()->set_xlabel(xlabel);
    if (!ylabel.empty()) plots.back()->set_ylabel(ylabel);
    if (!title.empty()) {
        plots.back()->set_title(title);
        std::ofstream outfile;
        outfile.open(title);
        for (int i =0; i<size;i++)
            outfile<< x[i]<<" "<<y[i]<<std::endl;
        outfile.close();
    }
    if (setgrid) plots.back()->set_grid();
    if (xmax != xmin) plots.back()->set_xrange(xmin, xmax);
    if (ymax != ymin) plots.back()->set_yrange(ymin, ymax);
    plots.back()->set_style(style);
    
    //Copy array into vector(!) to pass to C++ gnuplot interface
    //Clearly would be more efficient just to rewrite interface
    std::vector<T> xv,yv;
    xv.assign(x,x+size); yv.assign(y,y+size);
    plots.back()->plot_xy(xv, yv, "");
    plots.back()->showonscreen();
    return (plots.size() - 1);


}

template<typename T>
int ScatterPlotter::plot1(const T * x,const int size,
        std::string title,
        std::string xlabel, std::string ylabel,
        std::string style, bool setgrid, T xmin, T xmax, T ymin, T ymax) {
    plots.push_back(new Gnuplot());
    if (!xlabel.empty())plots.back()->set_xlabel(xlabel);
    if (!ylabel.empty()) plots.back()->set_ylabel(ylabel);
    if (!title.empty()) {
        plots.back()->set_title(title);
        std::ofstream outfile;
        outfile.open(title);
        for (int i =0; i<size;i++)
            outfile<< x[i] <<std::endl;
        outfile.close();
    }
    if (setgrid) plots.back()->set_grid();
    if (xmax != xmin) plots.back()->set_xrange(xmin, xmax);
    if (ymax != ymin) plots.back()->set_yrange(ymin, ymax);
    plots.back()->set_style(style);
    std::vector<T> xv;
    xv.assign(x,x+size);
    plots.back()->plot_x(xv, "");
    plots.back()->showonscreen();
    return (plots.size() - 1);


}

template<typename T>
int ScatterPlotter::plot3(const T* x,const T*y,const T*z, const int size, 
        std::string title, std::string xlabel, std::string ylabel, 
        std::string style, bool setgrid, T xmin, T xmax, T ymin, T ymax){
    plots.push_back(new Gnuplot());
    if (!xlabel.empty())plots.back()->set_xlabel(xlabel);
    if (!ylabel.empty()) plots.back()->set_ylabel(ylabel);
    if (!title.empty()) {
        plots.back()->set_title(title);
        std::ofstream outfile;
        outfile.open(title);
        for (int i =0; i<size;i++)
            outfile<< x[i]<<" "<<y[i]<<" "<<z[i]<<std::endl;
        outfile.close();
    }
    if (setgrid) plots.back()->set_grid();
    if (xmax != xmin) plots.back()->set_xrange(xmin, xmax);
    if (ymax != ymin) plots.back()->set_yrange(ymin, ymax);
    plots.back()->set_style(style);
    std::vector<T> xv,yv,zv;
    xv.assign(x,x+size); yv.assign(y,y+size); zv.assign(y,y+size);
    plots.back()->plot_xyz(xv, yv, zv, "");
    plots.back()->showonscreen();
    return (plots.size() - 1);


}

Plotter::~Plotter() {
    for (std::vector<Gnuplot*>::iterator i = plots.begin(); i < plots.end(); i++) {
        (*i)->cmd("quit");
        delete (*i);
    }
}

#endif	/* PLOTTER_ARRAY_H */


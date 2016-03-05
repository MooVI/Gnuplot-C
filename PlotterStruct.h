/* 
 * File:   PlotterStruct.h
 * Author: qfeuille
 *
 * Created on 25 March 2013, 19:33
 */
#include <string>
#include <NumericalMethods/NumericalMethods/StdVectorMath.h>
#include <fstream>
#include<iostream>

#ifndef PLOTTERSTRUCT_H
#define	PLOTTERSTRUCT_H



struct PlotterParams {
    
     std::string xlabel;
     std::string ylabel;
     std::string output;
     std::string terminal;
     std::vector<std::string> cmds;
     bool setgrid; 
     double xmin;
     double xmax;
     double ymin; 
     double ymax;
     
      PlotterParams (
            std::string xlabel = "", std::string ylabel = "",
             bool setgrid = true, double xmin = 0,
            double xmax = 0, double ymin = 0, double ymax = 0, std::string terminal = "", std::string output ="") ; 
};

struct PlotterData {
 std::string input;   
  std::string title;
 std::string style;

 std::vector<int> columns;
 PlotterData (std::string iinput="",
 std::string ititle="",
 std::string istyle="lines",
 std::vector<int> icolumns = std::vector<int> (0));
  template <typename A, typename... Args>
 PlotterData (std::string ititle,const A& first, const Args&... rest);
 
};

 template <typename A, typename... Args>
 PlotterData::PlotterData (std::string ititle,const A& first, const Args&... rest): title(ititle){
     input = ititle;
     style = "lines";
     std::ofstream outfile;
     outfile.open(input.c_str(),std::ios::trunc);
     if (outfile){
         NumMethod::cColumnWrite(outfile,first,rest...);
         outfile.flush();
         outfile.close();
     }
     else std::cerr<< "Could not open file!";
     int size = 0; NumMethod::cCount (size, first, rest...);
     columns.resize(size);
     for (int i=0;i<size;i++){
         columns[i]= i+1;
     }
 };

#endif	/* PLOTTERSTRUCT_H */


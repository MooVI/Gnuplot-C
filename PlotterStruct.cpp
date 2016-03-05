/* 
 * File:   PlotterStruct.cpp
 * Author: qfeuille
 *
 * Created on 25 March 2013, 19:33
 */

#include <vector>

#include "PlotterStruct.h"

PlotterParams::PlotterParams(std::string ixlabel, std::string iylabel, bool isetgrid, double ixmin, double ixmax, double iymin, double iymax,std::string iterminal, std::string ioutput):
xlabel (ixlabel), ylabel(iylabel), setgrid (isetgrid), xmin(ixmin),xmax(ixmax),ymin (iymin),ymax(iymax),terminal(iterminal),output(ioutput){};

PlotterData::PlotterData (std::string iinput,
 std::string ititle,
 std::string istyle,
std::vector<int> icolumns): style(istyle),title(ititle),input(iinput), columns (icolumns){
    columns.push_back(1);
    columns.push_back(2);
}

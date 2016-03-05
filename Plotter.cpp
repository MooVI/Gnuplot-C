/* 
 * File:   Plotter.cpp
 * Author: qfeuille
 *
 * Created on December 6, 2011, 8:03 PM
 */


#include"Plotter.h"


using std::string;
using std::vector;







//Function Plotter

//
// Calculate the values of the function given by the input across the
// chosen range, then plot to screen using Gnuplot.  Returns the
// integer identifier of the plot, which can be used to save it or
// further manipulate it.
//

/*int FunctionPlotter::plot(CasUnaryFunction * ToPlot) {


    // Calculate the values of the function in the chosen range,
    // finding the step size by dividing the size of the range by the
    // desired number of steps.
    //
    vector<double> Xvalues, Yvalues;
    double Step = (End - Begin) / NumSteps;
    for (double x = Begin; x < End; x += Step) {
        Xvalues.push_back(x);
        Yvalues.push_back(ToPlot->evaluateAt(x));
    }


    // Create a new member of plots for handling plotting
    plots.push_back(GnuPtr(new Gnuplot()));

    // Add title and axes titles to the graph.
    std::stringstream ylabel, title;
    ylabel << "set ylabel \'" << ToPlot->latex() << "\'";
    plots.back()->set_xlabel(ToPlot->getInputVar());
    plots.back()->cmd(ylabel.str());
    title << "Plot of " << ToPlot->getName();
    plots.back()->set_title(title.str());

    // Draw the graph grid and have borders and tics on only the
    // bottom and left borders.
    plots.back()->set_grid();
    plots.back()->cmd("set border 3");
    plots.back()->cmd("set xtics nomirror");
    plots.back()->cmd("set ytics nomirror");

    // Plot the values calculated above using the style Style.
    plots.back()->set_style(Style).plot_xy(Xvalues, Yvalues, "");
    plots.back()->showonscreen();
    return (plots.size() - 1);
}

*/

//Plotter

//
// Save the plot identified by GraphIdentifier to a .tex to be
// included in a LaTex doucument. The filename will be iName 
// followed by GraphIdentifier.
//

void Plotter::setParams(GnuPtr plot, const PlotterParams& param) {
    if (param.terminal.empty()) plot->showonscreen();
    else {
        plot->cmd(std::string("set terminal ") + param.terminal);
        plot->cmd(std::string("set output ") + param.output);
    } 
    if (!param.xlabel.empty())plot->set_xlabel(param.xlabel);
    if (!param.ylabel.empty()) plot->set_ylabel(param.ylabel);
    if (param.setgrid) plot->set_grid();
    if (param.xmax != param.xmin) plot->set_xrange(param.xmin, param.xmax);
    if (param.ymax != param.ymin) plot->set_yrange(param.ymin, param.ymax);
    for (std::string cmd : param.cmds)
        plot->cmd(cmd.c_str());
}

void Plotter::save(int GraphIdentifier, string iName) {

    //Create filename, with a .tex extension.
    std::stringstream ssfilename;
    ssfilename << iName << GraphIdentifier << ".tex";
    string filenametex = ssfilename.str();

    //Save to .tex file
    plots [GraphIdentifier]->cmd("set output \"" + filenametex + "\"");
    plots [GraphIdentifier]->cmd("set terminal epslatex color colortext");
    plots [GraphIdentifier]->cmd("set lmargin 10");
    plots [GraphIdentifier]->cmd("replot");
}

//
// Save the plot identified by GraphIdentifier to a .ps and to a .png
// file if ToPng is set to true, which it is by default.  The filename
// will be iName followed by GraphIdentifier.  This requires Linux
// with latex, dvips and for .png ImageMagick installed.
//

void Plotter::saveImage(int GraphIdentifier, string iName, bool ToPng) {

    //Create filename, with and without .tex extension.
    std::stringstream ssfilename;
    ssfilename << iName << GraphIdentifier << ".tex";
    string filenametex = ssfilename.str();
    string filename = filenametex.substr(0, filenametex.length() - 4);

    //Save to .tex file
    plots [GraphIdentifier]->cmd("set output \"" + filenametex + "\"");
    plots [GraphIdentifier]->cmd("set terminal epslatex standalone color colortext");
    plots [GraphIdentifier]->cmd("set lmargin 10");
    plots [GraphIdentifier]->cmd("replot");
    plots [GraphIdentifier]->cmd("set output \"flush.tex\"");

    //Convert to .ps and .png if necessary.
    system(("latex " + filenametex).c_str());
    system(("dvips -o " + filename + ".ps " + filename + ".dvi").c_str());
    if (ToPng)
        system(("convert -density 500 " + filename + ".ps " + filename + ".png").c_str());

    //Clean up temporary files.
    system(("rm " + filenametex).c_str());
    system(("rm " + filename + ".dvi").c_str());
    system(("rm " + filename + ".log").c_str());
    system(("rm " + filename + ".aux").c_str());
    system(("rm " + filename + "-inc.eps").c_str());

}

//
// Remove the plots from the screen on finishing the plotting session.
//

Plotter::~Plotter() {
    for (vector<GnuPtr>::iterator i = plots.begin(); i < plots.end(); i++) {
        (*i)->cmd("quit");
    }
}



int ScatterPlotter::plot (std::vector<PlotterData> data, PlotterParams params, int nDim){
    if (nDim = -1) nDim = data [0].columns.size();
    for (int i=0;i<data.size();i++){
       if (data[i].columns.size()<nDim) {
           std::cerr<<"Data #"<<(i+1)<<" dimension too low!;";
           return -1;
       } 
       }
    plots.push_back(GnuPtr(new Gnuplot()));
    setParams (plots.back(), params);
    switch (nDim){
        case 1:  plots.back()->plotfile_x_general(data);
        break;
        case 2:  plots.back()->plotfile_xy_general(data);
        break;
        case 3:  plots.back()->plotfile_xyz_general(data);
        break;
        default: std::cerr<<"Invalid number of dimensions for plotting!";
        return -1;
    }
    return (plots.size()-1);
    
};
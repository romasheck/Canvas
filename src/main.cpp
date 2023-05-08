
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <SFML/System/Sleep.hpp>

#include "GEO/geo_lib.hpp"
#include "GEO/FigureManager.hpp"

using namespace geo;

int main()
{
/*
    gui::CanvasMaster canvas_master({1000, 1000});
    
    canvas_master.createAll();
    canvas_master.drawAll();

    canvas_master.loop();
*/
    FigureManager FM;
/*
    Line    lne1(2, 2, 4, 3);
    Line    lne2(0, 3, 3, 3);
    Circle  cir1(sqrtf(2), 2.f, 2.f);
    Circle  cir2(2, 6, 4);
    Circle  cir3(3, 3, 3);
*/
    Line* lne1 = new Line(2, 10, 4, 7);
    Line* lne2 = new Line(2, 2, 4, 3);
    Line* lne3 = new Line(0, 2, 10, 2);
    Circle* cir1 = new Circle(2, 6, 4);

    FM.pushFigure(lne1);
    FM.pushFigure(lne2);
    FM.IntersectWithAll(lne2);
    FM.pushFigure(lne3);
    FM.IntersectWithAll(lne3);
    
    FM.IntersectWithAll(cir1);
    FM.pushFigure(cir1);
    //FM.debugPrintFigures();

    DebugPrintFigure(FM.whichFig(Point(8,5)));

    //DebugTwoPoints(findIsctDots[lne1.type_][cir2.type_](&lne1, &cir2));

    printf("ENDED!\n");

    return 0;

}
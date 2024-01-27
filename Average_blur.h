#pragma once

#include "Gaussian_blur.h"

void judge(quadTree &qt);
void Average_blur();

void judge(quadTree &qt)
{
    double var_R = qt.variance_R();
    double var_G = qt.variance_G();
    double var_B = qt.variance_B();
    if (qt.subSideLength < 5 || (var_R <= tolerance && var_G <= tolerance && var_B <= tolerance))
        qt.sub_average_blur();
    else
    {
        position center_p1;
        center_p1.x = qt.center_pos.x + qt.subSideLength / 4;
        center_p1.y = qt.center_pos.y - qt.subSideLength / 4;

        position center_p2;
        center_p2.x = qt.center_pos.x - qt.subSideLength / 4;
        center_p2.y = qt.center_pos.y - qt.subSideLength / 4;

        position center_p3;
        center_p3.x = qt.center_pos.x - qt.subSideLength / 4;
        center_p3.y = qt.center_pos.y + qt.subSideLength / 4;

        position center_p4;
        center_p4.x = qt.center_pos.x + qt.subSideLength / 4;
        center_p4.y = qt.center_pos.y + qt.subSideLength / 4;

        qt.q1 = new quadTree(center_p1, qt.subSideLength / 2);
        qt.q2 = new quadTree(center_p2, qt.subSideLength / 2);
        qt.q3 = new quadTree(center_p3, qt.subSideLength / 2);
        qt.q4 = new quadTree(center_p4, qt.subSideLength / 2);

        judge(*(qt.q1));
        judge(*(qt.q2));
        judge(*(qt.q3));
        judge(*(qt.q4));
    }
}

void Average_blur()
{
    position root_center_pos;
    root_center_pos.x = sideLength / 2;
    root_center_pos.y = sideLength / 2;
    quadTree root(root_center_pos, sideLength);
    judge(root);
}
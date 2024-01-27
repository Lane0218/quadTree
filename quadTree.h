#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct color
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};
struct position
{
    int x;
    int y;
};

int sideLength = INT16_MAX, tolerance;
vector<vector<color>> ori_colors(sideLength, vector<color>(sideLength, color{0, 0, 0}));
vector<vector<color>> res_colors(sideLength, vector<color>(sideLength, color{255, 255, 255}));

class quadTree
{
public:
    position center_pos;
    int subSideLength;
    quadTree *q1;
    quadTree *q2;
    quadTree *q3;
    quadTree *q4;

public:
    quadTree(position center_pos, int subSideLength);
    ~quadTree();
    double average_R();
    double average_G();
    double average_B();
    double variance_R();
    double variance_G();
    double variance_B();
    void sub_average_blur();
};

quadTree::quadTree(position center_p, int subSideL)
{
    center_pos = center_p;
    subSideLength = subSideL;
    q1 = NULL;
    q2 = NULL;
    q3 = NULL;
    q4 = NULL;
}
quadTree::~quadTree()
{
    if (q1 != NULL)
    {
        delete q1;
        delete q2;
        delete q3;
        delete q4;
    }
}
double quadTree::average_R()
{
    double sum = 0;
    for (int i = center_pos.x - subSideLength / 2; i < center_pos.x + subSideLength / 2; i++)
    {
        for (int j = center_pos.y - subSideLength / 2; j < center_pos.y + subSideLength / 2; j++)
        {
            sum += ori_colors[i][j].R;
        }
    }
    return sum / (subSideLength * subSideLength);
}
double quadTree::average_G()
{
    double sum = 0;
    for (int i = center_pos.x - subSideLength / 2; i < center_pos.x + subSideLength / 2; i++)
    {
        for (int j = center_pos.y - subSideLength / 2; j < center_pos.y + subSideLength / 2; j++)
        {
            sum += ori_colors[i][j].G;
        }
    }
    return sum / (subSideLength * subSideLength);
}
double quadTree::average_B()
{
    double sum = 0;
    for (int i = center_pos.x - subSideLength / 2; i < center_pos.x + subSideLength / 2; i++)
    {
        for (int j = center_pos.y - subSideLength / 2; j < center_pos.y + subSideLength / 2; j++)
        {
            sum += ori_colors[i][j].B;
        }
    }
    return sum / (subSideLength * subSideLength);
}
double quadTree::variance_R()
{
    double ave_R = average_R();
    double sum = 0;
    for (int i = center_pos.x - subSideLength / 2; i < center_pos.x + subSideLength / 2; i++)
    {
        for (int j = center_pos.y - subSideLength / 2; j < center_pos.y + subSideLength / 2; j++)
        {
            sum += pow(ori_colors[i][j].R - ave_R, 2);
        }
    }
    return sum / (subSideLength * subSideLength);
}
double quadTree::variance_G()
{
    double ave_G = average_G();
    double sum = 0;
    for (int i = center_pos.x - subSideLength / 2; i < center_pos.x + subSideLength / 2; i++)
    {
        for (int j = center_pos.y - subSideLength / 2; j < center_pos.y + subSideLength / 2; j++)
        {
            sum += pow(ori_colors[i][j].G - ave_G, 2);
        }
    }
    return sum / (subSideLength * subSideLength);
}
double quadTree::variance_B()
{
    double ave_B = average_B();
    double sum = 0;
    for (int i = center_pos.x - subSideLength / 2; i < center_pos.x + subSideLength / 2; i++)
    {
        for (int j = center_pos.y - subSideLength / 2; j < center_pos.y + subSideLength / 2; j++)
        {
            sum += pow(ori_colors[i][j].B - ave_B, 2);
        }
    }
    return sum / (subSideLength * subSideLength);
}
void quadTree::sub_average_blur()
{
    double sum_R = average_R();
    double sum_G = average_G();
    double sum_B = average_B();
    for (int i = center_pos.x - subSideLength / 2; i < center_pos.x + subSideLength / 2; i++)
        for (int j = center_pos.y - subSideLength / 2; j < center_pos.y + subSideLength / 2; j++)
        {
            res_colors[i][j].R = (unsigned char)(sum_R);
            res_colors[i][j].G = (unsigned char)(sum_G);
            res_colors[i][j].B = (unsigned char)(sum_B);
        }
}

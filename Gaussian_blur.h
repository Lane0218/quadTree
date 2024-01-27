#pragma once

#include "quadTree.h"

void sub_Gaussian_blur(int i, int j);
void Gaussian_blur();

double weight[5][5] = {{0.0368834, 0.0391642, 0.0399554, 0.0391642, 0.0368834}, {0.0391642, 0.0415860, 0.0424261, 0.0415860, 0.0391642}, {0.0399554, 0.0424261, 0.0432831, 0.0424261, 0.0399554}, {0.0391642, 0.0415860, 0.0424261, 0.0415860, 0.0391642}, {0.0368834, 0.0391642, 0.0399554, 0.0391642, 0.0368834}};

void sub_Gaussian_blur(int i, int j)
{
    double sum_R = 0, sum_G = 0, sum_B = 0;
    if (i * j == 0 || i == sideLength - 1 || j == sideLength - 1 || i == 1 || j == 1 || i == sideLength - 2 || j == sideLength - 2)
        res_colors[i][j] = ori_colors[i][j];
    else
    {
        for (int p = 0; p < 5; p++)
            for (int q = 0; q < 5; q++)
            {
                sum_R += weight[p][q] * ori_colors[p + i - 2][q + j - 2].R;
                sum_G += weight[p][q] * ori_colors[p + i - 2][q + j - 2].G;
                sum_B += weight[p][q] * ori_colors[p + i - 2][q + j - 2].B;
            }
        res_colors[i][j].R = (unsigned char)(sum_R);
        res_colors[i][j].G = (unsigned char)(sum_G);
        res_colors[i][j].B = (unsigned char)(sum_B);
    }
}
void Gaussian_blur()
{
    for (int i = 0; i < sideLength; i++)
        for (int j = 0; j < sideLength; j++)
            sub_Gaussian_blur(i, j);
}
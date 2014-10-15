#include <iostream>
using namespace std;
#include <cstdio>
#include <cstdlib>
void Floyd(int *edge, int *path, const int order, const int maxNum)
{
    int length;
    if (path != NULL)
        for (int i = 0; i < order; i++)
            for (int j = 0; j < order; j++)
                if (i != j && (*(edge+ order * i + j) < maxNum))
                    *(path + order * i + j) = i;
                else
                    *(path + order * i + j) = 0;

    for (int k = 0; k < order; k++)
        for (int i = 0; i < order; i++)
            for (int j = 0; j < order; j++)
            {
                length = (*(edge + i * order + k) + *(edge + k * order + j));
                if (length < *(edge + i * order + j))
                {
                    *(edge + i * order + j) = length;
                    if (path != NULL)
                        *(path + i * order + j) = *(path + k * order + j);                
                }
            }
}
int main()
{
    const int MaxNum = 1000;
    int a[4][4] = {{0, 1, MaxNum, 4}, {MaxNum, 0, 9, 2}, {3, 5, 0, 8}, {MaxNum, MaxNum, 6, 0}};
    int b[4][4];
    Floyd((int *)a, (int *)b, 4, MaxNum);
    for (int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}

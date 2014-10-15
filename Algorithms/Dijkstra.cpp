#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#define INF 10000000

int map[][7] = {                     
    {0,20, INF, INF, 10, INF,15},
    {INF, 0, 7,INF,INF,INF,INF},
    {INF, INF, 0,INF, INF,INF,INF},
    {INF, 3,9, 0, 4,INF,INF},
    {INF, 9, INF, 4, 0,10,INF},
    {INF,INF,3,INF,INF,0,INF},
    {INF,INF,7,INF,INF,INF,0}
};

void Dijkstra(
              const int numOfVertex,    
              const int startVertex,    
              int (map)[][7],          
              int *distance,            
              int *prevVertex           
              )
{
    vector<bool> isInS;                 
    isInS.reserve(0);
    isInS.assign(numOfVertex, false);   
    
    
    for(int i =0; i < numOfVertex; ++i)
    {
        distance[ i ] = map[ startVertex ][ i ];
        if(map[ startVertex ][ i ] < INF)
            prevVertex[ i ] = startVertex;
        else
            prevVertex[ i ] = -1;       
    }
    prevVertex[ startVertex ] = -1;
    
    
    isInS[startVertex] = true;          
    
    
    int u = startVertex;
    
    for (int i = 1; i < numOfVertex; i ++)      
    {
        
        
        int nextVertex = u;
        int tempDistance = INF;
        for(int j = 0; j < numOfVertex; ++j)
        {
            if((isInS[j] == false) && (distance[j] < tempDistance))
            {
                nextVertex = j;
                tempDistance = distance[j];
            }
        }
        isInS[nextVertex] = true;
        u = nextVertex;
        
        
        
        for (int j =0; j < numOfVertex; j ++)
        {
            if (isInS[j] == false && map[u][j] < INF)
            {
                int temp = distance[ u ] + map[ u ][ j ];
                if (temp < distance[ j ])
                {
                    distance[ j ] = temp;
                    prevVertex[ j ] = u;
                }
            }
        }
    }
    
    
    
}


int main (int argc, const char * argv[])
{
    int distance[7];
    int preVertex[7];
    
    for (int i =0 ; i < 7; ++i )
    {
        Dijkstra(7, i, map, distance, preVertex);
         for(int j =0; j < 7; ++j)
         {
             int index = j;
             stack<int > trace;
             while (preVertex[index] != -1) {
                 trace.push(preVertex[index]);
                 index = preVertex[index];
             }
             
             cout << "route：";
             while (!trace.empty()) {
                 cout<<trace.top()<<" -- ";
                 trace.pop();
             }
             cout <<j;
             cout <<" distance："<<distance[j]<<endl;

             
         }
    }

    return 0;
}

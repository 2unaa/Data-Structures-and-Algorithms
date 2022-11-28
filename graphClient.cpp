/******************************
Implemented by Kazumi Slott
CS311

This clinet tests graph::BFT and DFT
*******************************/
#include <iostream>
#include <fstream>
using namespace std;
#include "graph.h"

int main()                                                                                         
{          
  cout << "testing unweighted graph--------------------" << endl;
                                                                                        
  graph g(9); //a to i

  ifstream fin;
  fin.open("graph.in");
  int v, u, w; //v --> u
               //  w 

  if(!fin)
    cout << "graph.in doesn't exist" << endl;
  else
    {
      fin >> v >> u;
      while(fin)
	{
	  g.addEdge(v,u);
	  fin >> v >> u;
	}

      cout << "BFS: ";                                                                                 
      g.BFT(0);                                                                                     
      cout << "\nDFS: ";                                                                 
      g.DFT(0); 
    }                                                                                    
  fin.close();

  cout << "\ntesting weighted graph--------------------" << endl;
  graph g2(10); //a to j
  fin.open("graph2.in");
  if(!fin)
    cout << "graph2.in doesn't exist" << endl;
  else
    {
      fin >> v >> u >> w;
      while(fin)
        {
          g2.addEdge(v,u, w);
          fin >> v >> u >> w;
        }

      cout << "BFS: ";
      g2.BFT(0);
      cout << "\nDFS: ";
      g2.DFT(0);

       //You don't need to make Dijkstra's algo for homework on graph - part 1
      cout << "\nDijkstra's algo: " << endl;
      g2.DijkstraShortestPath(3);
      
    }
  fin.close();
  cout << endl;                                                                                                   
  return 0;                                                                                        
}                                 

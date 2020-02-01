#include<iostream>
#include<stdio.h>
#include<fstream>
#include<map>
#include<iterator>
#include<vector>
#include<functional>
#include<queue>
#include<algorithm>

#define INF 0x3f3f3f3f

typedef std::pair<int, int> edge_t;
typedef std::multimap<int, edge_t>::iterator mmap_iter; //Version of map where multiple elements can have same keys

struct compare
{
   bool operator()(std::pair<int,int> const &a, std::pair<int, int> const &b) const noexcept
  {
    return a.second > b.second;
  }
  
};

int main()
{
  std::ifstream infile;
  infile.open("edges.txt");
  int edges, vertices;
  infile>>vertices>>edges;

  int src, dest, wt; 
  int cost = 0;
  std::multimap<int, edge_t> preprocess; //<source, dest-weight> 
  std::priority_queue<edge_t, std::vector<edge_t>, compare> pq; //Discovered vertex and weight associated with it
  
  while(infile>>src>>dest>>wt)
    {
      preprocess.insert(std::make_pair(src, std::make_pair(dest,wt)));
      preprocess.insert(std::make_pair(dest, std::make_pair(src,wt)));
    }

  infile.close();

  std::vector<bool> visited (vertices, 0); //Index+1 represents the vertex number
  std::pair<mmap_iter, mmap_iter> range;
  std::vector<int> weight (vertices, INF); //Represents the weight of the edge that optimally discovers that vertex
  
  src = 1;
  weight[src-1] = 0;
  pq.push(std::make_pair(src, weight[src-1]));
  
  while(!pq.empty())
    {
      int u = pq.top().first;
      visited[u-1] = 1;
      pq.pop();

      range = preprocess.equal_range(u);
      for(auto it = range.first; it != range.second; it++)
	{
	  if( (!visited[(it->second.first)-1]) && (weight[(it->second.first)-1] > it->second.second) ) //Second condition ensures that the given vertex hasn't been discovered with a lower weight and already been pushed into pq, waiting in queue to be marked as visited
	    {
	      std::cout<<it->second.first<<" : "<<it->second.second<<"\n";
	      weight [(it->second.first)-1] = it->second.second;
	      pq.push(std::make_pair(it->second.first, weight[(it->second.first)-1]));
	    }
	}
      
    }

  for(int i=0; i<vertices; i++)
    {
      std::cout<<weight[i]<<"\n";
    cost += weight[i];
    }
  std::cout<<cost<<"\n";
 
}

#include<iostream>
#include<stdio.h>
#include<fstream>
#include<map>
#include<iterator>
#include<vector>
#include<functional>
#include<queue>
#include<algorithm>

typedef std::pair<std::pair<int,int>, int> edge_t; //<<vert1,vert2>,weight>

struct compare
{
   bool operator()(edge_t const &a, edge_t const &b) const noexcept
  {
    return a.second > b.second;
  }
  
};

int return_min (int vert1, int vert2)
{
  if(vert1 < vert2)
    return vert1;

  else return vert2;
}

int return_max (int vert1, int vert2)
{
  if(vert1 > vert2)
    return vert1;

  else return vert2;
}

int find_parent (int vert, std::vector<int> parent) //Find operation in Union-Find
{
  int p = parent[vert-1];
  if(p == vert)
    return vert;

  else
    return find_parent(p, parent);
}

int main()
{
  std::ifstream infile;
  infile.open("clustering1.txt"); 
  int vertices;
  infile>>vertices;

  int vert1, vert2, distance;

  std::priority_queue<edge_t, std::vector<edge_t>, compare> pq; //Minimum edge and weight associated with it
  
  while(infile>>vert1>>vert2>>distance)
    {
      pq.push(std::make_pair(std::make_pair(vert1,vert2),distance));
    }

  infile.close();
  
  int cost = 0;
  std::vector<bool> visited (vertices, 0); //Index+1 represents the vertex number, eg. [vert1-1] represents vert1 
  
  //Temporary variables
  edge_t current;
  int weight;
  std::vector<int> parent (vertices);
  std::vector<int> cluster_size (vertices, 1);

  for(int i=0; i<parent.size(); i++)
    parent[i] = i+1;
  
    while(!pq.empty())
    {
      current = pq.top();
      vert1 = current.first.first;
      vert2 = current.first.second;
      weight = current.second;

      //Both vertices unvisited, add an edge between them to form new cluster
      if(!visited[vert1-1] && !visited[vert2-1])
	{	  
	 parent[vert1-1] = return_min(vert1, vert2); //Breaks ties for parents by choosing lower numbered node, eg. nodes 1 and 2 will have 1 as parent.
         parent[vert2-1] = parent[vert1-1];
	 visited[vert1-1] = 1;
	 visited[vert2-1] = 1;
	 cost += weight;
	 cluster_size[parent[vert1-1]-1] += 1;
	 cluster_size[return_max(vert1, vert2)-1] = -1;
	}

      //One vertex visited, one unvisited, add edge to an existing cluster
      else if(visited[vert1-1] && !visited[vert2-1])
	{	  
	  parent[vert2-1] = find_parent(vert1, parent);
	  visited[vert2-1] = 1;
	  cost += weight;
	  cluster_size[parent[vert2-1]-1] += 1;
	  cluster_size[vert2-1] = -1;
	}

      //Same as above, vertices reversed
      else if(!visited[vert1-1] && visited[vert2-1])
	{	  
	  parent[vert1-1] = find_parent(vert2, parent);
	  visited[vert1-1] = 1;
	  cost += weight;
	  cluster_size[parent[vert1-1]-1] += 1;
	  cluster_size[vert1-1] = -1;
	}

      //Different cluster vertices, check for smaller cluster and merge, update parent pointer of smaller cluster
      else if(visited[vert1-1] && visited[vert2-1])
	{ 
	  int parent1 = find_parent(vert1, parent);
	  int parent2 = find_parent(vert2, parent);
	  if (parent1 != parent2)
	 {
	  cost += weight;
	  
	  //Find smaller cluster
	  if(cluster_size[parent1-1] < cluster_size[parent2-1])	    
	    {
	      parent[parent1-1] = parent2;
	      cluster_size[parent2-1] += cluster_size[parent1-1];
	      cluster_size[parent1-1] = -1;
	    }

	  else
	    {
	      parent[parent2-1] = parent1;
	      cluster_size[parent1-1] += cluster_size[parent2-1];
	      cluster_size[parent2-1] = -1;
	    }
	  
	 }

	}
      
      pq.pop();

      int count = 0, sum = 0;
      for(int i=0; i<cluster_size.size(); i++)
	{
	  if(cluster_size[i] >= 1)
	    {
	      count++;
	      sum += cluster_size[i];
 	    }
	}

      if((count < 4) && (sum == vertices))
	{
	  std::cout<<"Maximum Spacing: "<<weight<<"\n";
	  break;
	}
      
     }

}

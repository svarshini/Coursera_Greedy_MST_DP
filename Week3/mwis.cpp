#include<iostream>
#include<stdio.h>
#include<fstream>
#include<map>
#include<iterator>
#include<vector>
#include<functional>
#include<queue>
#include<algorithm>


int main()
{
  std::ifstream infile;
  infile.open("mwis.txt");
  
  int num_verts;
  long weight;
  
  infile>>num_verts;

  std::vector<long> vert_wts;
  std::vector<bool> recon(num_verts+1, 0);
  std::vector<long> mwis(num_verts+1, 0);

  vert_wts.push_back(0); //Initializing zero weight for zero vertex
  
  while(infile>>weight)
    {
      vert_wts.push_back(weight);
    }

  infile.close();

  for(int i=0; i<vert_wts.size(); i++) 
    {
      if(i == 0)
	{
	  mwis[i] = 0;
	  continue;
	}

      if(i == 1)
	{
	  mwis[i] = vert_wts[i];
	  continue;
	}

      else
	{
	  if(mwis[i-1] < (vert_wts[i] + mwis[i-2]))
	    {
	      mwis[i] = vert_wts[i] + mwis[i-2];
	    }

	  else
	    mwis[i] = mwis[i-1];
        }
     
    }

  //Reconstruction
  for(int i=recon.size()-1; i>0; i--) 
    {
     if(i != 1)
     {
       if(i == recon.size()-1) //Boundary case: edge of graph
	 {
	   if(mwis[i] == (mwis[i-2] + vert_wts[i]))
	     recon[i] = 1;
	   else 
	     recon[i] = 0;
	 }

       else
	 {
	   if((mwis[i] == (mwis[i-2] + vert_wts[i])) && (recon[i+1]==0))
	     recon[i] = 1;
	   else
	     recon[i] = 0;
	 }
     }

     else if(i == 1) //Boundary case
       {
	 if(recon[i+1] == 0)
	   recon[i] = 1;
	 else
	   recon[i] = 0;
       }
     
    }

    std::cout<<recon[1]<<" ";
    std::cout<<recon[2]<<" ";
    std::cout<<recon[3]<<" ";
    std::cout<<recon[4]<<" ";
    std::cout<<recon[17]<<" ";
    std::cout<<recon[117]<<" ";
    std::cout<<recon[517]<<" ";
    std::cout<<recon[997]<<"\n";
  
}
 
  

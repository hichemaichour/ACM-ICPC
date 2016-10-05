// Johnny hates math
// by G.Barlas, September 2009

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

int value[251][6];
int plusposition[250];
int numpluses;

int N;
int target;
int totalplus;
int maxdigits;

#define IMPOSSIBLE 255
unsigned char allV[251][100000];

bool findSolution_aux(int idx, int targetV, int N, int remainplus);

//***********************************************************
void preProcess(int N, int target)
{
  memset(allV, IMPOSSIBLE, sizeof(char)*100000*251);
  
  int pos = N-1;
  while(value[pos][0] ==0) pos--;
  allV[pos][value[pos][N-pos]] = 0; // 0 additions
  pos--;
  
  while(pos>=0)
  {
    if(value[pos][0] !=0) // if this part of the input does not start with 0
    {
        if(N-pos<=maxdigits)
           allV[pos][value[pos][N-pos]] = 0; // 0 additions

	for(int i=pos+1;i<N && i-pos<=maxdigits ;i++)
	   if(value[i][0] !=0)  // if breaking up at pos is possible
	     {	       
	        int part1 = value[pos][i-pos];
		for(int j=1;j<=target;j++)
		   if(allV[i][j] != IMPOSSIBLE)
                      {
		         int sum = part1 + j;
			 if(sum <= target)
			    {
			      if(allV[pos][sum] != IMPOSSIBLE)
			      {
				if(allV[pos][sum] > allV[i][j]+1)
				   allV[pos][sum] = allV[i][j]+1;
			      }
			      else
				allV[pos][sum] = allV[i][j]+1;
			    }
		      }
	     }
    }
    pos--;
  }
}

//***********************************************************
bool findSolution(int targetV, int N)
{
  bool found=false;
  totalplus = (int)ceil(N/(maxdigits*1.0)) - 1;
  while(!found && totalplus <N)
  {
//     printf("Trying %i\n", totalplus);
    numpluses=0;
    found = findSolution_aux(0, targetV, N, totalplus);
    totalplus++;
  }
  totalplus--; 
  return found;
}
//***********************************************************
//recursive function that prunes impossible tree branches
// idx provides the position to start from
bool findSolution_aux(int idx, int targetV, int N, int remainplus)
{
  if(allV[idx][targetV]==IMPOSSIBLE || (allV[idx][targetV]!=IMPOSSIBLE && allV[idx][targetV] > remainplus))
      return false;

  for (int len = maxdigits; len >= 1 ; len--)
    if(idx + len <= N)
    {
      int tmp = value[idx][len];
      if (idx + len == N && targetV == tmp) return true;
      else if(tmp < targetV && idx+len!=N && value[idx+len][0]!=0)
      {
	plusposition[numpluses++] = idx+len;
	bool res=findSolution_aux(idx+len, targetV - tmp, N, remainplus-1);
	if(res) return true;
	numpluses--;
      }
    }
    return false;
}
//***********************************************************
int main (int argc, char *argv[])
{
  long long N, old;
  char buffer[257];
  int cases=1;
  
#ifndef ONLINE_JUDGE
  freopen ("Johnny.h", "r", stdin);
#endif

  scanf("%s", buffer);
  while(strcmp(buffer,"0=0"))
   {
      char *pos = strtok (buffer, "=");
      N = strlen (buffer);


      pos = strtok (NULL, "=");
      target = atoi (pos);
      maxdigits = strlen(pos);
      
      //calculate the possible values that can come off the input and store them in value array
      for (int i = 0; i < N; i++)
	{
	  value[i][0] = buffer[i] - '0';	// plain value
	  for (int j = 1; j <= maxdigits; j++)
	    {
	      if (buffer[i] != '0' && i + j <= N)
		{
		  int tmp = 0;
		  for (int k = 0; k < j; k++)
		    tmp = tmp * 10 + buffer[i + k] - '0';
		  value[i][j] = tmp;
		}
	      else
		value[i][j] = -1;	// illegal start of number
	    }
	}

      preProcess(N, target);


      cout << cases++ << ". ";
      if (allV[0][target] == IMPOSSIBLE) 
	cout << "IMPOSSIBLE\n";
      else
      {
	  if (findSolution (target,N))
	    {

	      for (int i = 0; i < totalplus; i++)
		{
		  if (i == 0)
		    cout << value[0][plusposition[0]];
		  else
		    {
		      cout << "+" <<
			value[plusposition[i - 1]][plusposition[i] - plusposition[i - 1]];
		    }
		}
	      if (totalplus > 0)
		cout << "+" << value[plusposition[totalplus - 1]][N - plusposition[totalplus-1]];
	      cout << "=" << target << endl;
	    }
	  else
	    cout << "IMPOSSIBLE\n";
	}
      scanf("%s", buffer);
    }    
  return 0;

}

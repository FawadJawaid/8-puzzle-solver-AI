
// Name: Muhammad Fawad Jawaid Malik
// Roll No. 11k - 2116
// Submitted To: Sir Rafi

#include <iostream>
#include <vector>
#include <set>
#include <fstream>

//Uinformed - Breadth First Search
using namespace std;

struct Statespace
{
      int Puzzle[3][3];
      int Spare[2];
      int Eval;
      
      bool operator< (Statespace) const;
      int operator- (Statespace) const;
      bool operator== (Statespace) const;
      void operator= (Statespace);
};

class Equal
{
      bool Greater;
      
      public:
      Equal(const bool& Lesser=1)
      {
           Greater=Lesser?0:1;       
      }
      
      bool operator() (const Statespace& src, const Statespace& dest) const
      {
           if(Greater) 
              return (src<dest?0:1);
           else 
              return (src<dest);
      } 
};

istream& operator>> (istream& input, Statespace& s)
{
      for(int i=0; i<3; i++)
      {
          for(int j=0; j<3; j++)
          {
              input>>s.Puzzle[i][j];
                 
              if(s.Puzzle[i][j]==0)
              {
                  s.Spare[0]=i;
                  s.Spare[1]=j;                 
              }
          }
      }
         
      return input;        
} 

ostream& operator<< (ostream& output, Statespace& s)
{
     for(int i=0; i<3; i++)
     {
         for(int j=0; j<3; j++)
         {
             output<<s.Puzzle[i][j]<<" ";    
         }
         output<<endl;    
     }   
     
     return output;
}

bool Statespace::operator< (Statespace s) const
{
     return (Eval<s.Eval);
}

int Statespace::operator- (Statespace s) const
{
    int count=0;
    for (int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
             if(Puzzle[i][j]!=s.Puzzle[i][j] && Puzzle[i][j]!=0)
                count++;    
        }
    }
    return count;
}

bool Statespace::operator== (Statespace s) const
{
     if((*this)-s==0)
        return 1;
     else
        return 0;                     
}

void Statespace::operator= (Statespace s)
{
     for(int i=0; i<3; i++)
     {
          for(int j=0; j<3; j++)
          {
              Puzzle[i][j]=s.Puzzle[i][j];    
          }
     }
     
     Spare[0]=s.Spare[0];
     Spare[1]=s.Spare[1];
     Eval=s.Eval;
}

Statespace Initial, Goal, get();
int t=0;
Statespace st;
ofstream ofs("out.txt");
set<Statespace, Equal> Openlist;
vector<Statespace> Explored;

//Move Fuction, To move blocks
inline int Move(char pos)
{
     int p, q;
     int r, c;
     
     int s1=st.Spare[0];
     int s2=st.Spare[1];
     
     if(pos == 'R')
     {   
         p=0;
         q=1;
     }
     else if(pos == 'L')
     {
          p=0;
          q=-1;
     }
     else if(pos == 'U')
     {
          p=1;
          q=0;
     }
     else if(pos == 'D')
     {
          p=-1;
          q=0;
     } 
  
     r = s1+p;
     c = s2+q;
     
     swap(st.Puzzle[s1][s2], st.Puzzle[r][c]);
     
     if(find(Explored.begin(),Explored.end(),st) != Explored.end())
     {
          st=Initial;
          return 0;                         
     }
     
     st.Spare[0]=r;
     st.Spare[1]=c;
     get(); 
     
     Openlist.insert(st);
     st=Initial;
       
     return 0;  
}

Statespace get()
{ st.Eval=Goal-st; }


int BFS()
{
    set<Statespace, Equal>::iterator l=Openlist.begin();
    st=*l;
    
    if(st==Goal)
    {  
      return t;
    }
    
    ofs<<st<<endl;
    cout<<st<<endl;
    
    Explored.push_back(st);
    Openlist.erase(l);

    Initial=st;
    
    if(st.Spare[1]<2)
       Move('R');
    if(st.Spare[1]>0)
       Move('L');
    if(st.Spare[0]<2)
       Move('U');
    if(st.Spare[0]>0)
       Move('D');
       
       
    t++;   
    BFS();
}


int main()
{
    ifstream inf("A2in1.txt");
    inf>>Initial>>Goal;
    
    Openlist.insert(Initial);
    
    BFS();
    
    ofs<<st<<endl;
    cout<<st<<endl;
    
    ifstream infile("out.txt");
    ofstream ofile("A2P1out1.txt");
    
    int arr[10], arr1[10], arr2[10], arr3[10], arr4[10];
    int l=0, m=0, n=0, p=0, q=0;
    
    for(int i=0; i<9; i++)
    {
      infile>>arr[i];
      
      if(arr[i]==0)
      {
         l=i;
      }
    }
    
    for(int i=0; i<9; i++)
    {
      infile>>arr1[i];
      
      if(arr1[i]==0)
      {
         m=i;
      }
    }
    
    for(int i=0; i<9; i++)
    {
      infile>>arr2[i];
      
      if(arr2[i]==0)
      {
         n=i;
      }
    }
    
    for(int i=0; i<9; i++)
    {
      infile>>arr3[i];
      
      if(arr3[i]==0)
      {
         p=i;
      }
    }
    
    for(int i=0; i<9; i++)
    {
      infile>>arr4[i];
      
      if(arr4[i]==0)
      {
         q=i;
      }
    }
    
    if(m==l+1)
    {
       ofile<<arr[m]<<" left"<<endl;
    }
    else if(m==l+3)
    {
       ofile<<arr[m]<<" up"<<endl;
    }
    
    if(n==m+1)
    {
        ofile<<arr1[n]<<" left"<<endl;
    }
    else if(n==m+3)
    {
        ofile<<arr1[n]<<" up"<<endl;
    }
    else if(n==m-3)
    {
        ofile<<arr1[n]<<" down"<<endl;
    }
    else if(n==m-1)
    {
        ofile<<arr1[n]<<" right"<<endl; 
    }
    
    if(p==n+1)
    {
        ofile<<arr2[p]<<" left"<<endl;
    }
    else if(p==n+3)
    {
        ofile<<arr2[p]<<" up"<<endl;
    }
    else if(p==n-3)
    {
        ofile<<arr2[p]<<" down"<<endl;
    }
    else if(p==n-1)
    {
        ofile<<arr2[p]<<" right"<<endl; 
    }
    
    if(q==p+1)
    {
        ofile<<arr3[q]<<" left"<<endl;
    }
    else if(q==p+3)
    {
        ofile<<arr3[q]<<" up"<<endl;
    }
    else if(q==p-3)
    {
        ofile<<arr3[q]<<" down"<<endl;
    }
    else if(q==p-1)
    {
        ofile<<arr3[q]<<" right"<<endl; 
    }
	
	ofile << "Goal state found." << endl;
	cout<<"Goal state found."<<endl;
    
    system("pause");
    return 0;
}         

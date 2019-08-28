
// Name: Muhammad Fawad Jawaid Malik
// Roll No. 11k - 2116
// Submitted To: Sir Rafi

#include<iostream>
#include<fstream>
#include<math.h>

//Beyond Classical search-Steepest hill climbing
using namespace std;

ofstream ofile("A2P5out1.txt");

//Move function, To move blocks                                                   
void Moved(int** st, int move)
{
     int g=0;
     for(int i=0; i<3; i++)
     {
         for(int j=0; j<3; j++)
         {
             if(*(*(st+i)+j)==0)
             {
                 if(move==1)
                 {
                    *(*(st+i)+j)=*(*(st+(i-1))+j);
                    *(*(st+(i-1))+j)=0;
                    g=1;
                    break;        
                 }
                 else if(move==2)
                 {
                    *(*(st+i)+j)=*(*(st+(i+1))+j);
                    *(*(st+(i+1))+j)=0;
                    g=1;
                    break;        
                 }
                 else if(move==3)

                {    
                    *(*(st+i)+j)=*(*(st+i)+(j-1));
                    *(*(st+i)+(j-1))=0;
                    g=1;
                    break;
                }
                else
                {
                    *(*(st+i)+j)=*(*(st+i)+(j+1));
                    *(*(st+i)+(j+1))=0;
                    g=1;
                    break;
                }
            }
         }
         
         if(g==1)
         {
            break;     
         }
     }
}

// To print best move result
void Moved_Result(int** st, int move)
{
     int g=0;
     for(int i=0; i<3; i++)
     {
         for(int j=0; j<3; j++)
         {
             if(*(*(st+i)+j)==0)
             {
                 if(move==1)
                 {
                    ofile<<*(*(st+(i-1))+j)<<" down"<<endl;           
                    *(*(st+i)+j)=*(*(st+(i-1))+j);
                    *(*(st+(i-1))+j)=0;
                    g=1;
                    break;        
                 }
                 else if(move==2)
                 {
                    ofile<<*(*(st+(i+1))+j)<<" up"<<endl;  
                    *(*(st+i)+j)=*(*(st+(i+1))+j);
                    *(*(st+(i+1))+j)=0;
                    g=1;
                    break;        
                 }
                 else if(move==3)

                {   
                    ofile<<*(*(st+i)+(j-1))<<" right"<<endl; 
                    *(*(st+i)+j)=*(*(st+i)+(j-1));
                    *(*(st+i)+(j-1))=0;
                    g=1;
                    break;
                }
                else
                {
                    ofile<<*(*(st+i)+(j+1))<<" left"<<endl;
                    *(*(st+i)+j)=*(*(st+i)+(j+1));
                    *(*(st+i)+(j+1))=0;
                    g=1;
                    break;
                }
            }
         }
         
         if(g==1)
         {
            break;     
         }
     }
}

// To calculate Manhattan Distance
int manhattan_dist(int** i, int** j)
{
    int m=0;
    for(int p=0; p<3; p++)
    {
        for(int q=0; q<3; q++)
        {
             if(*(*(i+p)+q)>0)
             {
                 for(int u=0; u<3; u++)
                 {
                    for(int v=0; v<3; v++)
                    {
                        if(*(*(j+u)+v)==*(*(i+p)+q))
                        {
                           m = m + (abs(p-u)+abs(q-v));                         
                        }    
                    }     
                 }
             }
        }
    }
    
    return m;
}

// To traverse the parent
int TraverseSuccessor(int** a, int** b, int move)
{
    int** st = new int*[3];
    
    for(int p=0; p<3; p++)
    {
        st[p]=new int[3];
        
        for(int q=0; q<3; q++)
        {
            *(*(st+p)+q)=*(*(a+p)+q);    
        }    
    }
    
    Moved(st,move);
    
    int m=manhattan_dist(st, b);
    
    for(int p=0; p<3; p++)
    {
        delete st[p];    
    }
    
    delete st;
    return m;
}

// To print each state
void PrintStates(int** arr)
{
     for(int i=0; i<3; i++)
     {
        for(int j=0; j<3; j++)
        {
            cout<<*(*(arr+i)+j)<<" ";    
        }
        cout<<endl;
     }
     cout<<endl;     
}

// Steepest Hill Climbing Function
void Hill_Climbing(int** src, int** des, int p)
{ 
      int array[4]={555,555,555,555};
      
      for(int i=0; i<3; i++)
      {
          for(int j=0; j<3; j++)
          {
              if(*(*(src+i)+j)==0)
              {
                  if(i>0 && p!=2)
                  {
                      array[0]=TraverseSuccessor(src,des,1);
                  }
                  if(i<2 && p!=1)
                  {
                      array[1]=TraverseSuccessor(src,des,2);
                  }
                  if(j>0 && p!=4)
                  {
                      array[2]=TraverseSuccessor(src,des,3);
                  }
                  if(j<2 && p!=3)
                  {
                      array[3]=TraverseSuccessor(src,des,4);   
                  } 
              }
          }
      }
      
      int k=555;
      int x=0;
      
      for(int i=0; i<4; i++)
      {
           if(array[i]<k)
           {
               k=array[i];
               x=i+1;
           }
      }
      
      Moved_Result(src, x);
      
      PrintStates(src);
      
      if(k==0)      // Checking whether we reach the goal or not
      {
          ofile<<"Goal state found."<<endl;
          cout<<"Goal state found."<<endl;
          
          return;
      }
      else
      Hill_Climbing(src,des,x);                                                               
}

int main()
{
    int** initial = new int*[3];
    int** goal = new int*[3];
    
    for(int a=0; a<3; a++)
    {
        initial[a] = new int[3];
    }    
    
    for(int a=0; a<3; a++)
    {
        goal[a] = new int[3];    
    }
    
    ifstream in("A2in1.txt");
    
    int input;

    for(int a=0; a<3; a++)
    {
        for(int b=0; b<3; b++)
        {
            in>>input;
            
            initial[a][b]=input;
        }
    }                 
    
    for(int a=0; a<3; a++)
    {
        for(int b=0; b<3; b++)
        {
            in>>input;
            
            goal[a][b]=input;
        }
    }         
    
    for(int a=0; a<3; a++)
    {
        for(int b=0; b<3; b++)
        {
            cout<<*(*(initial+a)+b)<<" ";     
        }
        
        cout<<endl;
    }    
    
    cout<<endl;
    
    Hill_Climbing(initial,goal,0);
    
    for(int a=0; a<3; a++)
    {
        delete initial[a];
        delete goal[a];
    }
    
    delete initial;
    delete goal;    
    
    system("pause");
    return 0;
}

                                        

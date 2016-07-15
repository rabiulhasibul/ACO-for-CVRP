#include<bits/stdc++.h>
#define ALPHA 1.0
#define BETA 1.0
#define RHO 0.5 //eva
#define QVAL 100


using namespace std;
int c = 0,cost = 999;
float sum1=0;
int visit_cost[100];
vector<int>solution[100];

vector<double>prob[100];

float graph[50][50];

int row,col;

int main()
{
    srand((unsigned)time(0));
    freopen("cluster.txt","r",stdin);

    cin>>row;
    col=row;


    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            scanf("%f",&graph[i][j]);
        }
    }

    double tourLength;
    float pheromone[100][100];
    double heuristic[100][100];
    double probability[100][100];
    double p;
    float sum=0;

    double Tao_for_best_sol=(1.0/RHO);
    double Tao_for_other_sol=(1.0/RHO);


    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            cout<<" " <<graph[i][j];
            pheromone[i][j]=1/RHO;
            if(i==j)
            {
                p=0;
            }
            else
            {
                p=float(1/(1.0*graph[i][j]));
            }

            heuristic[i][j]=p;
        }
        cout<<"\n";
    }

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {

            // cout<<" "<<heuristic[i][j];
            //cout<<tou[i][j];
            //cout<<" "<<pheromone[i][j];

            sum=sum+(heuristic[i][j]*pheromone[i][j]);
            //cout<<" "<<sum;


        }

        //cout<<"\n";
    }
    cout<<"\n";
    //cout<<" "<<sum;
//-------------------------------------------------------------------------------

    cout<<"\n"<<"-------------------------------------------Initial probability------------------------------------------------------"<<"\n";
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {

            probability[i][j]=(heuristic[i][j]*pheromone[i][j])/sum;
            cout<<" "<<probability[i][j];

        }
        cout<<"\n";
    }
    cout<<endl;



    for(int iteration=1; iteration<=100; iteration++)
    {

        for(int i=0; i<=100; i++)
        {
            prob[i].clear();
            solution[i].clear();
        }


        for(int i=0; i<row; i++)
        {
            double val=0;
            for(int j=0; j<col; j++)
            {
                val+=probability[i][j];
                prob[i].push_back(val);
            }
        }

        int dist=10000000,indx;

        int ant=50;
        for(int i=0; i<ant; i++)
        {

            bool taken[100]= {false};
            float cost=0;
            solution[i].push_back(0);
            taken[0]=true;
            int k=0;

            for(int j=1; j<row; j++)
            {

                double div=1.0/prob[k][prob[k].size()-1];

                bool found=false;
                double  pb;
                while(1)
                {

                    int Random = rand()%100;
                    //cout<<Random<<" ";
                    pb=Random/100.0;
                    pb/=div;


                    int nibo=-1;
                    for(int x=0; x<prob[k].size(); x++)
                    {

                        if(x==0)
                        {
                            if((pb>=0&&pb<=prob[k][x])&&!taken[x])
                                nibo=x;
                        }
                        else
                        {
                            if((pb>=prob[k][x-1]&&pb<=prob[k][x])&&!taken[x])
                                nibo=x;
                        }
                    }
                    if(nibo!=-1)
                    {
                        cost+=graph[k][nibo];
                        solution[i].push_back(nibo);
                        k=nibo;
                        found=true;
                        taken[k]=true;
                    }
                    if(found)
                        break;
                }

            }
            cost+=graph[k][0];
            solution[i].push_back(0);
            visit_cost[i]=cost;
            if(cost<dist)
            {
                dist=cost;
                indx=i;
            }

//            cout<<"Path cost "<<cost<<endl;
//            for(int x=0; x<solution[i].size(); x++)
//                cout<<solution[i][x]<<" ";
//            cout<<endl<<endl;

        }



        cout<<"Path for iteration "<<iteration<<endl;
        for(int j=0; j<solution[indx].size(); j++)
            cout<<solution[indx][j]<<" ";
        cout<<endl<<endl;
        cout<<"Path cost "<<dist<<endl<<endl;
        bool check[50][50]= {false};


        for(int i=1; i<solution[indx].size(); i++)
        {
            pheromone[solution[indx][i-1]][solution[indx][i]]=(1.0-RHO)*Tao_for_best_sol+sum1/100;
            check[solution[indx][i-1]][solution[indx][i]]=true;
        }

        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                if(!check[i][j])
                    pheromone[i][j] = (1.0-RHO)*Tao_for_other_sol;

            }
        }


        Tao_for_best_sol = (1.0-RHO)*Tao_for_best_sol+100/dist;
        sum1=sum1+Tao_for_best_sol;
        Tao_for_other_sol = (1.0-RHO)*Tao_for_other_sol;

        sum=0;

        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
                sum=sum+(heuristic[i][j]*pheromone[i][j]);
        }

        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                probability[i][j]=(heuristic[i][j]*pheromone[i][j])/sum;
            }
        }


        cout<<"Probabilty "<<endl<<endl;
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                cout<<probability[i][j]<<ends;
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    return 0;
}



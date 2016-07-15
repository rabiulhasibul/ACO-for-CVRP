#include<bits/stdc++.h>
#define pp3 pair<float,pair<float,pair<float,float> > >

using namespace std;

vector<pp3>vec;
vector<pp3>group[100];
int city=33;
vector<float>dis[50][50];
int deg=270;
int main()
{

    freopen("n33-k5.txt","r",stdin);
    freopen("n33-k5_270.txt","w",stdout);

    float y_cordinate[100];
    float x_cordinate[100];
    float demand[100];
    float angle[100];

    for(int i=0; i<city; i++)
    {
        scanf("%f %f %f",&x_cordinate[i],&y_cordinate[i],&demand[i]);
    }

    for(int i=0; i<city; i++)
    {
        if(x_cordinate[i]<0 && y_cordinate[i]<0)
        {
            angle[i]=atan2(y_cordinate[i],x_cordinate[i]);
            angle[i]=floor(360+(angle[i]*180)/3.1416);
        }
        else if(x_cordinate[i]>=0 && y_cordinate[i]<0)
        {
            angle[i]=atan2(y_cordinate[i],x_cordinate[i]);
            angle[i]=floor(360+(angle[i]*180)/3.1416);
        }
        else
        {
            angle[i]=atan2(y_cordinate[i],x_cordinate[i]);
            angle[i]=floor((angle[i]*180)/3.1416);
        }
        vec.push_back(make_pair(angle[i],make_pair(demand[i],make_pair(x_cordinate[i],y_cordinate[i]))));
    }

    sort(vec.begin(),vec.end());

    cout<<"After sorting"<<endl;
    cout<<"A "<<"D "<<"X "<<"Y "<<endl;

    for(int i=0; i<vec.size(); i++)
        cout<<vec[i].first<<" "<<vec[i].second.first<<" "<<vec[i].second.second.first<<" "<<vec[i].second.second.second<<endl;


    int idx=1;

    float sum_of_deman=0;

    //Insert 0 degree angle to First Cluster

    group[idx].push_back(make_pair(vec[0].first,make_pair(vec[0].second.first,make_pair(vec[0].second.second.first,vec[0].second.second.second))));
    //Take angle from 45

    for(int i=0; i<vec.size(); i++)
    {
        if(vec[i].first<deg)
            continue;
        if(sum_of_deman+vec[i].second.first<=100.0)
        {
            sum_of_deman+=vec[i].second.first;
            group[idx].push_back(make_pair(vec[i].first,make_pair(vec[i].second.first,make_pair(vec[i].second.second.first,vec[i].second.second.second))));
        }
        else
        {
            idx++;
            sum_of_deman=vec[i].second.first;
            if(i!=1)
                group[idx].push_back(make_pair(vec[0].first,make_pair(vec[0].second.first,make_pair(vec[0].second.second.first,vec[0].second.second.second))));
            group[idx].push_back(make_pair(vec[i].first,make_pair(vec[i].second.first,make_pair(vec[i].second.second.first,vec[i].second.second.second))));
        }
    }

    //Take angle upto 45

    for(int i=1; i<vec.size(); i++)
    {
        if(vec[i].first>deg)
            break;
        if(sum_of_deman+vec[i].second.first<=100.0)
        {
            sum_of_deman+=vec[i].second.first;
            group[idx].push_back(make_pair(vec[i].first,make_pair(vec[i].second.first,make_pair(vec[i].second.second.first,vec[i].second.second.second))));
        }
        else
        {
            idx++;
            sum_of_deman=vec[i].second.first;
            if(i!=1)
                group[idx].push_back(make_pair(vec[0].first,make_pair(vec[0].second.first,make_pair(vec[0].second.second.first,vec[0].second.second.second))));
            group[idx].push_back(make_pair(vec[i].first,make_pair(vec[i].second.first,make_pair(vec[i].second.second.first,vec[i].second.second.second))));
        }
    }

    cout<<endl<<endl;

    for(int i=1; i<=idx; i++)
    {
        cout<<"CLUSTER "<<i<<endl;
         cout<<"A "<<"D "<<"X "<<"Y "<<endl;
        for(int j=0; j<group[i].size(); j++)
            cout<<group[i][j].first<<" "<<group[i][j].second.first<<" "<<group[i][j].second.second.first<<" "<<group[i][j].second.second.second<<endl;


        cout<<endl<<endl;
    }

    for(int i=1; i<=idx; i++)
    {
        for(int j=0; j<group[i].size(); j++)
        {
            for(int k=0; k<group[i].size(); k++)
            {
                float x1 = group[i][j].second.second.first;
                float x2 = group[i][k].second.second.first;
                float y1 = group[i][j].second.second.second;
                float y2 = group[i][k].second.second.second;
                float D = ((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2));
                dis[i][j].push_back(sqrt(D));
            }
        }
    }

    for(int i=1; i<=idx; i++)
    {
        cout<<"Distance for  Cluster "<<i<<endl<<endl;
        cout<<group[i].size()<<endl;
        for(int j=0; j<group[i].size(); j++)
        {
            for(int k=0; k<dis[i][j].size(); k++)
                cout<<dis[i][j][k]<<" ";
            cout<<endl;
        }
        cout<<endl<<endl;
    }

    return 0;
}

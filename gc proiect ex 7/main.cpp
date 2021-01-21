#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
using namespace std;
struct punkt{
float x, y;
bool evarf, econvex, eprincipal;
};

int position(punkt P, punkt Q, punkt R)
{
    float delta=Q.x*R.y+P.x*Q.y+R.x*P.y-P.y*Q.x-P.x*R.y-Q.y*R.x;
    if(delta==0)
        return delta;
    else if(delta>0)
        return 1;
    else return -1;
}
bool eintriunghi(punkt P, punkt Q, punkt R, punkt S)
{
    int p1, p2, p3;
    p1=position(P, Q, S);
    p2=position(R, P, S);
    p3=position(Q, R, S);
    if(p1==p2 && p2==p3)
        return true;
    return false;
}
int main()
{

    ifstream f;
    f.open("date2.in");

    int n, ymax=INT_MIN,pozy;
    vector<punkt> myVector;
    f>>n;
    if(n<3)
    {
        cout<<"Eroare de input - figura nu este POLIGON\n";
        return 0;
    }
    punkt elem_auxiliar;
    for(int i=0; i<n; i++)
    {
        f>>elem_auxiliar.x>>elem_auxiliar.y;
        if(elem_auxiliar.y>ymax)
        {ymax=elem_auxiliar.y;
        pozy=i;}
        elem_auxiliar.evarf=true;
        elem_auxiliar.econvex=false;
        elem_auxiliar.eprincipal=true;
        myVector.push_back(elem_auxiliar);
    }

    myVector[pozy].econvex=true;
   // myVector.resize(n);
    int poz;
    bool convex;
    if(pozy==n-1)
    {
        poz=position(myVector[n-2], myVector[n-1], myVector[0]);
        convex=poz;
        myVector[pozy].econvex=true;
    }
    else if(pozy==0)
    {
    poz=position(myVector[n-1], myVector[0], myVector[1]);
    convex=poz;
    myVector[pozy].econvex=true;
    }
    else
    {
    poz=position(myVector[pozy-1], myVector[pozy], myVector[pozy+1]);
    convex=poz;
    myVector[pozy].econvex=true;
    }


     poz=position(myVector[n-2], myVector[n-1], myVector[0]);
        if(poz==0)
        {
            myVector[n-1].evarf=false;
        }
        else if(poz==convex)
        {
            myVector[n-1].econvex=true;
        }
        else{
            myVector[n-1].econvex=false;
        }
    poz=position(myVector[n-1], myVector[0], myVector[1]);
        if(poz==0)
        {
            myVector[0].evarf=false;
        }
        else if(poz==convex)
        {
            myVector[0].econvex=true;
        }
        else{
            myVector[0].econvex=false;
        }
    for(int i=0; i<n-2; i++)
    {
        poz=position(myVector[i], myVector[i+1], myVector[i+2]);
        if(poz==0)
        {
            myVector[i+1].evarf=false;
        }
        else if(poz==convex)
        {
            myVector[i+1].econvex=true;
        }
        else{
            myVector[i+1].econvex=false;
        }
    }
    int vf1, vf2, vf3;
    int c=0;
    for(int i=0; i<n; i++)
    {

        if(myVector[i].evarf==false) c++;
    }
    if(c==n)
    {
    cout<<"Eroare de input - figura nu este POLIGON\n";
        return 0;
    }
    c=0;
        for(int i=0; i<n; i++)
    {
        if(myVector[i].evarf==false)
        {
            myVector.erase(myVector.begin()+i);
            c++;
            myVector.resize(n-c);
            if(i!=0) i--;
        }
    }
    n=n-c;

    if(n<3)
    {
        cout<<"Eroare de input - figura nu este POLIGON\n";
        return 0;
    }
    if(n==3)
    {
        myVector[0].eprincipal=true;
        myVector[1].eprincipal=true;
        myVector[2].eprincipal=true;
    }
    for(int i=0; i<n-2; i++)
    {
        vf1=i;
        vf2=i+1;
        vf3=i+2;
        for(int j=0; j<n; j++)
        {
            if(j!=vf1 && j!=vf2 && j!=vf3)
            {
                if(eintriunghi(myVector[vf1], myVector[vf2], myVector[vf3], myVector[j])==true)
                {
                    myVector[vf2].eprincipal=false;
                    break;
                }
            }
        }
        vf1=vf2;
        vf2=vf3;
        vf3++;
    }
    for(int j=0; j<n; j++)
        {
            if(j!=n-2 && j!=n-1 && j!=0)
            {
                if(eintriunghi(myVector[n-2], myVector[n-1], myVector[0], myVector[j])==true)
                {
                    myVector[n-1].eprincipal=false;
                    break;
                }
            }
        }
      for(int j=0; j<n; j++)
        {
            if(j!=n-1 && j!=0 && j!=1)
            {
                if(eintriunghi(myVector[n-1], myVector[0], myVector[1], myVector[j])==true)
                {
                    myVector[0].eprincipal=false;
                    break;
                }
            }
        }
    for(int i=0; i<n; i++)
    {
        cout<<"Varful de coordonate ("<<myVector[i].x<<", "<<myVector[i].y<<") este ";
        if(myVector[i].econvex==true)
            cout<<"convex si ";
        else cout<<"concav si ";
        if(myVector[i].eprincipal==true)
        {
            cout<<"principal.\n";
        }
        else cout<<"neprincipal.\n";
    }
    f.close();
    return 0;
}


#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
struct punct
{
    int x, y;
};
bool comp(punct a, punct b)
{
    if (a.x != b.x)
        return a.x < b.x;
    else return (a.y < b.y);
}
vector<punct> nonhull;

int orientation(punct p, punct q, punct r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // coliniare
    if (val > 0)
        return 1; //Clockwise
    else
        return 2; //Counterclockwise
}

void convexHull(vector<punct>puncte, int n)
{
    if (n < 3) return;
    vector<punct> hull;

    sort(puncte.begin(), puncte.end(), comp);
    //daca toate sunt coliniare
    if (orientation(puncte[0], puncte[1], puncte[2]) == 0 && orientation(puncte[0], puncte[1], puncte[3]) == 0)
    {
        hull.push_back(puncte[0]);
        hull.push_back(puncte[3]);
        nonhull.push_back(puncte[1]);
        nonhull.push_back(puncte[2]);
        cout << "\n I este format din (" << hull[0].x << ", " << hull[0].y << ") si (" << hull[1].x << ", " << hull[1].y << ")";
        cout << "\n j este format din (" << nonhull[0].x << ", " << nonhull[0].y << ") si (" << nonhull[1].x << ", " << nonhull[1].y << ")";
        return;
    }
    //cazuri cand ai triunghi cu 3 puncte coliniare
    if (orientation(puncte[0], puncte[1], puncte[2]) == 0)
    {
        hull.push_back(puncte[0]);
        hull.push_back(puncte[2]);
        hull.push_back(puncte[3]);
        nonhull.push_back(puncte[1]);
        cout << "\n I este format din (" << hull[0].x << ", " << hull[0].y << ") si (" << hull[1].x << ", " << hull[1].y << ") si (" << hull[2].x << ", " << hull[2].y << ")";
        cout << "\n J este formata din (" << nonhull[0].x << ", " << nonhull[0].y << ")";
        return;
    }

    if (orientation(puncte[0], puncte[1], puncte[3]) == 0)
    {
        hull.push_back(puncte[0]);
        hull.push_back(puncte[2]);
        hull.push_back(puncte[3]);
        nonhull.push_back(puncte[1]);
        cout << "\n I este format din (" << hull[0].x << ", " << hull[0].y << ") si (" << hull[1].x << ", " << hull[1].y << ") si (" << hull[2].x << ", " << hull[2].y << ")";
        cout << "\n J este formata din (" << nonhull[0].x << ", " << nonhull[0].y << ")";
        return;
    }
    if (orientation(puncte[1], puncte[2], puncte[3]) == 0)
    {
        hull.push_back(puncte[0]);
        hull.push_back(puncte[1]);
        hull.push_back(puncte[3]);
        nonhull.push_back(puncte[2]);
        cout << "\n I este format din (" << hull[0].x << ", " << hull[0].y << ") si (" << hull[1].x << ", " << hull[1].y << ") si (" << hull[2].x << ", " << hull[2].y << ")";
        cout << "\n J este formata din (" << nonhull[0].x << ", " << nonhull[0].y << ")";
        return;
    }
    if (orientation(puncte[0], puncte[2], puncte[3]) == 0)
    {
        hull.push_back(puncte[0]);
        hull.push_back(puncte[1]);
        hull.push_back(puncte[3]);
        nonhull.push_back(puncte[2]);
        cout << "\n I este format din (" << hull[0].x << ", " << hull[0].y << ") si (" << hull[1].x << ", " << hull[1].y << ") si (" << hull[2].x << ", " << hull[2].y << ")";
        cout << "\n J este formata din (" << nonhull[0].x << ", " << nonhull[0].y << ")";
        return;
    }

    // Cauta cel mai din stanga punct
    int l = 0;

      // practic mereu cauti punctul cel mai din stanga "din perspectiva" punctului ala
    int p = l, q;
    do
    {
        hull.push_back(puncte[p]);
            //aici practic cauti cel mai din stanga punct, daca gasesti unu mai la stanga, actualizezi
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(puncte[p], puncte[i], puncte[q]) == 2)
                q = i;
        }
        p = q;

    } while (p != l);    // pana ajungem inapoi la primul punct

    // Print Result
    cout << "Acoperirea convexa este : \n ";
    for (int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", "
        << hull[i].y << ")\n";



    for (int i = 0; i < n; i++)
    {
        int k = 0;
        for (int j = 0; j < hull.size(); j++)
            if (puncte[i].x == hull[j].x && puncte[i].y == hull[j].y)
                k = 1;
        if (k == 0)
            nonhull.push_back(puncte[i]);
    }

    for (int i = 0; i < nonhull.size(); i++)
        cout << nonhull[i].x << nonhull[i].y;


    if (hull.size() == 4)
    {
        cout << "\n I este format din (" << hull[0].x << ", " << hull[0].y << ") si (" << hull[2].x << ", " << hull[2].y << ")";
        cout << "\n J este format din (" << hull[1].x << ", " << hull[1].y << ") si (" << hull[3].x << ", " << hull[3].y << ")";
    }
    else if (hull.size() == 3)
    {
        cout << "\n I este format din (" << hull[0].x << ", " << hull[0].y << ") si (" << hull[1].x << ", " << hull[1].y << ") si (" << hull[2].x << ", " << hull[2].y << ")";
        cout << "\n J este formata din (" << nonhull[0].x << ", " << nonhull[0].y << ")";

    }


}

int main()
{
    vector<punct> puncte = { {0, 0},{3, 0}, {0, 3}, {1, 1} };
    int n = 4;
    convexHull(puncte, n);


    return 0;
}

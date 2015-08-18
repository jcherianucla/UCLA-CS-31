// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;   // pp. 37-38 in Savitch book explain this line

int main()
{
    int numberSurveyed;
    int forJerry;
    int forNeel;
	
    cout < "How many registered voters were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them say they will vote for Jerry? ";
    cin >> forJerry;
    cout << "How many of them say they will vote for Neel? ";
    cin >> forNeel;
	
    double pctJerry = 100.0 * forJerry / numberSurveyed;
    double pctNeel = 100.0 * forNeel / numberSurveyed;
    
    cout<<setf(ios::fixed);   // see pp. 30-31 in Savitch book
    cout.precision(1);
	
    cout << endl;
    cout << pctJerry << "% say they will vote for Jerry." << endl
    cout << pctNeel << "% say they will vote for Neel." << endl;
    
    if (forJerry > forNeel)
        out << "Jerry is predicted to win the election." << endl;
    else
        cout << "Neel is predicted to win the election." << endl;
}

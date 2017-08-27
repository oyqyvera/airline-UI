//
//  main.cpp
//  airline Ui
//
//  Created by Qianyu Ouyang on 5/5/17.
//  Copyright © 2017 Qianyu Ouyang. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

struct flightdata {
    string city1;
    string city2;
    int distance;
    int price;
    string time1hours;
    string time1minutes;
    string time2hours;
    string time2minutes;
};
int fill_itine(ifstream& instream,flightdata str[],int size);
void Destination_fun(flightdata str[],int size);

void Mile_fun(flightdata str[],int size);
void Price_fun(flightdata str[],int size);
void Flighttime_fun(flightdata str[],int size);
void get_data();
void fly_time(int hour1,int hour2,int min1,int min2);
void search(flightdata str[],int size,string target,string target2);
int main(int argc, const char * argv[]) {
    /*struct flightdata {
        string city1;
        string city2;
        int distance;
        int price;
        int time1hours;
        int time1minutes;
        int time2hours;
        int time2minutes;
    };*/
    
    ifstream flight;
    flight.open("/Users/oyqy/Desktop/codeX/vehicle/airline Ui/airline Ui/flight copy 3.txt");
    if(flight.fail())
    {
        cout<<"File open error.\n";
        exit(1);
    }
    if(flight.is_open())
    {
    flightdata myitinerary[7];
    int SIZE;
    SIZE=fill_itine(flight, myitinerary,7)-1;
    cout<<SIZE<<endl;
    //cout<<myitinerary[3].city1<<myitinerary[3].city2<<myitinerary[3].price<<endl;
    get_data();
    int op;
    cin>>op;
    cin.ignore(100,'\n');
    cout<<endl;
    switch(op)
    {
        case 1:
                
                cout<<"Welcome to the ticket searching system."<<endl;
                Destination_fun(myitinerary,SIZE);
                break;
        case 2:
                cout<<"Welcome to the mileage query system."<<endl;
                Mile_fun(myitinerary,SIZE);
                break;
        case 3:
                cout<<"Welcome to the ticket inquiry system"<<endl;
                Price_fun(myitinerary,SIZE);
                break;
        case 4:
                cout<<"Welcome to our flight time info system"<<endl;
                Flighttime_fun(myitinerary,SIZE);
                break;
        default:
                cout<<"Invalid input."<<"Enter again."<<endl;
            
                
        }
    //cin.ignore(1000,'\n');
    char ans;
    cout<<"Do you need other service we cam offer you with?"<<endl;
    cout<<"Enter y or n.\n";
    cin >> ans;
        
    if(ans == 'Y' || ans == 'y')
    {
            
        get_data();
        int op;
        cin>>op;
        cin.ignore(100,'\n');
        switch(op)
        {
            case 1:
                
                cout<<"Welcome to the ticket searching system."<<endl;
                Destination_fun(myitinerary,SIZE);
                break;
            case 2:
                cout<<"Welcome to the mileage query system."<<endl;
                Mile_fun(myitinerary,SIZE);
                break;
            case 3:
                cout<<"Welcome to the ticket inquiry system"<<endl;
                Price_fun(myitinerary,SIZE);
                break;
            case 4:
                cout<<"Welcome to our flight time info system"<<endl;
                Flighttime_fun(myitinerary,SIZE);
                break;
            default:
                cout<<"Invalid input."<<"Enter again."<<endl;
            /*cin.ignore(1000,'\n');
            cout<<"Do you need other service we cam offer you with?"<<endl;
            cout<<"Enter y or n.\n";
            cin >> ans;*/

                
        }
         //cin.ignore(1000,'\n');
    }
    
    }
    
    flight.close();
    return 0;
}
int fill_itine(ifstream& instream,flightdata str[],int size)
{
    
    string string1,string2,string3,string4,newline;
    int next5=0,next6=0;
    int i=0;
    //char next;
    
    
    
        while(!instream.eof())
        {
            for(i=0;i<size;i++)
            {
            
             //instream>>string1 >>string2>>next3 >>next4 >>next5 >>next6>>next7>>next8;
                getline(instream,string1,'\t');
                getline(instream,string2,'\t');
                instream>>string3>>string4>>next5>>next6;
                getline(instream,newline,'\n');
                cout<<string1<<" "<<string2<<" "<<string3<<" "<<string4<<endl;
                string achar=":";
                //int sep=string3.find(achar,0);
                //int rep=string4.find(achar,0);
                str[i].city1=string1;
                str[i].city2=string2;
                str[i].time1hours=string3.substr(0,2);
                str[i].time1minutes=string3.substr(3,2);
                str[i].time2hours=string4.substr(0,2);
                str[i].time2minutes=string4.substr(3,2);
                str[i].distance=next5;
                str[i].price=next6;
            
            }
        }
    for(int j=0;j<i-1;j++)
    {
    cout<<str[j].city1<<" "<<str[j].time2hours<<" "<<str[j].time2minutes<<" "<<endl;
    }
    cout<<"Is your flight info table sample.\n";
    cout<<"Checked."<<endl;
    int SIZE = i;
    return SIZE;
}
void search(flightdata str[],int size,string target1,string target2)
{
    int i;
    int count=0;
    for( i=0;i<size;i++)
    {
        if(str[i].city1==target1)
        {
            for(int j=0;j<size;j++)
            {
                if(str[j].city2==target2 && str[j].city1==str[i].city2 && j!=i)
                {
                    int miles_mid;
                    string midstop(str[j].city1);
                    miles_mid = str[i].distance + str[j].distance;
                    cout<<"Your mileage from "<<target1 <<"to "<<target2<<" is "<<miles_mid<<" miles.\n";
                    cout<<"Including connecting stop: "<<midstop<<endl;
                    count++;
                }
                
                
            }
        }
        
    }
    if(count==0)
    {
        cout<<"No matching connecting flights found.\n";
        
    }
    
}

void fly_time(int hour1,int hour2,int min1,int min2)
{
    int flyhour,flymin;
    
    if(hour2>=hour1&&min2>=min1)
    {
    flyhour=hour2-hour1;
    flymin=min2-min1;
        cout<<"Your flight duration is"<<flyhour<<"hours and"<< flymin <<"minutes.\n";
        }
    else if(hour2>=hour1&&min2<min1)
    {
        flyhour=hour2-hour1-1;
        flymin=min2-min1+60;
        cout<<"Flight total duration: "<<flyhour<<" hours "<<flymin<<" minutes.\n";
    }
    else if(hour2<hour1&&min2>=min1)
    {
        flyhour=hour2-hour1+24;
        flymin=min2-min1;
        cout<<"Flight total duration: "<<flyhour<<" hours "<<flymin<<" minutes.\n";
    }
    else
    {
        flyhour=hour2-hour1+23;
        flymin=min2-min1+60;
        cout<<"Flight total duration: "<<flyhour<<" hours "<<flymin<<" minutes.\n";
    }
}
void Destination_fun(flightdata str[],int size)
{
  string data1,data2;
  cout<<"Enter places of interest on your mind.\n";
  cout<<"Please Enter departure city and destination city in order.\n";
    getline(cin,data1);
    getline(cin,data2);
    int count=0;
    cout<<"Two stop connecting flight is on deck.\n";
    cout<<"Choose your favour as whether want to check its info.(y/n).\n";
    char ans1;
    cin>>ans1;
    for(int i=0;i<size;i++)
    {
        if(str[i].city1==data1)
        {
           if(str[i].city2==data2)
            {
                cout<<"We have found tickets go through your choices of airports."<<endl;
                cout<<str[i].city1<<str[i].city2<<endl;
                cout<<"Time for departure:"<< str[i].time1hours<<":"<<str[i].time1minutes<<endl;
                cout<<"Time for arrival:"<< str[i].time2hours<<":"<<str[i].time2minutes<<endl;
                cout<<"Total distance covered:"<< str[i].distance<< "miles."<<endl;
                cout<<"Ticket Price of journey:"<< str[i].price<< "dollars."<<endl;
                count++;
            }
            else
            {
                
            for(int j=0;j<size;j++)
            {
                if(str[j].city2==data2&&str[i].city2==str[j].city1)
                {
                    string midstop(str[i].city2);
                    cout<<"Your flight from"<< data1 <<"to "<<data2 <<"has results as below."<<endl;
                    
                        char ans;
                        cout<<"Do you want to consider connecting flights?(y/n)"<<endl;
                        cin>>ans;
                        if(ans=='y'||'Y')
                        {
                            cout<<"Connecting flights outcome info as your wish:"<<endl;
                            cout<<"middle stop at "<<midstop<<" at "<<str[i].time2hours<<":"<<str[i].time2minutes<<endl;
                        cout<<"Departure time is "<<str[i].time1hours<<":"<<str[i].time1minutes<<endl;
                        cout<<"Arrival time is "<<str[j].time2hours<<":"<< str[j].time2minutes<<endl;
                        int h1=stoi(str[i].time1hours);
                        int h2=stoi(str[j].time2hours);
                        int m1=stoi(str[i].time1minutes);
                        int m2=stoi(str[j].time2minutes);
                        fly_time(h1,h2,m1,m2);
                        cout<<"Total flight distanced accounts to "<<str[i].distance+str[j].distance<<" miles."<<endl;
                        cout<<"Price adds to "<<str[i].price+str[j].price<< "dollars."<<endl;
                            count++;
                            
                        }
                    
                    
                }
               
                
                else if(str[j].city2==data2&&ans1=='y')
                {
                    for(int k=0;k<size;k++)
                    {
                        if(str[k].city1==str[i].city2 && str[k].city2==str[j].city1)
                        {
                            cout<<"Found one flight with two stops: "<<str[k].city1<<" "<<str[k].city2<<endl;
                            cout<<"Departure time is "<<str[i].time1hours<<":"<<str[i].time1minutes<<endl;
                            cout<<"Arriving time is "<<str[j].time2hours<<":"<<str[j].time2minutes<<endl;
                            cout<<"Total mileage rounds up to "<<str[i].distance+str[j].distance+str[k].distance<<" miles.\n";
                            cout<<"Total price:"<<str[i].price+str[k].price+str[j].price<<" dollars.\n";
                            count++;
                            
                        }
                    }
                }
                
            }
        }
    }
    }
    if(count==0)
        {
            cout<<"No tickets available.\n";
        }
    /*if(count<0)
    {
        cout<<"Connect flight available.\n";
    }*/

}
void Mile_fun(flightdata str[],int size){
    string apt1,apt2;
    cout<<"Please enter your departure and arrival airports."<<endl;
    getline(cin,apt1);
    getline(cin,apt2);
    int mileage;
    int count=0;
    cout<<"Would you like connecting flights?"<<endl;
    cout<<"Enter y or n.\n";
    char rep;
    cin>>rep;

    for(int i=0;i<size;i++)
    {
        if(str[i].city1==apt1&&str[i].city2==apt2)
        {
            
            mileage=str[i].distance;
            cout<<"Distance Between two airports are "<<mileage<<" miles"<<endl;
            count++;
        }
    }
    if(count==0)
    {
        cout<<"No direct flights on deck.\n";
    }
    if(rep=='y'||'Y')
    {search(str,size,apt1,apt2);}
            


}
void Price_fun(flightdata str[],int size)
{
    cout<<"Please enter your ticket info regarding the departure and destination airports one by one.\n";
    cout<<"Departure airport followed by destination,and separated by a tab,thanks.\n";
    string part,dest;
    getline(cin,part);
    cout<<part<<endl;
    cout<<"Enter your destination.\n";
    getline(cin,dest);
    cout<<dest<<endl;
    cout<<"Do you wany to check for connect flights?\n";
    cout<<"Enter Y or N.\n";
    char ans;
    cin>>ans;
    int count=0;
    int count1=0;
    for(int i=0;i<size;i++)
    {
        //cout<<(str[i].city1==part)<<" "<<(str[i].city2==dest)<<endl;
        if(str[i].city1==part&&str[i].city2==dest)
        {
            
            int price=str[i].price;
            cout<<"Price for your booking equals to "<<price<<"dollars."<<endl;
            count++;
        }
        
        if(ans=='Y'||ans=='y')
        {
            if(str[i].city2!=dest && str[i].city1==part)
            {
                for(int j=0;j<size;j++)
                {
                    if(str[j].city2==dest && str[j].city1==str[i].city2)
                    {
                    cout<<"Found one stop connecting airflight for you."<<endl;
                    cout<<"From "<<part<<" to "<<dest<<", price is "<<str[i].price+str[j].price<<" altogether."<<endl;
                    cout<<"Mid stop at "<<str[i].city2<<" ."<<endl;
                    count1++;
                    }
                else if(str[i].city2==str[j].city1 && str[j].city2!=dest){
                    for(int k=0;k<size;k++)
                    {
                        if(str[k].city1 == str[j].city2 && str[k].city2==dest)
                        {
                            cout<<"Found two stops connecting flight through "<<part <<" to "<<dest<<endl;
                            cout<<"two stops are: "<<str[j].city1<<" and "<<str[k].city1<<endl;
                            cout<<"Total price add to "<<str[i].price+str[j].price+str[k].price<<endl;
                            count1++;
                        }
                    }
                
                }
                }
            }
       
        }
    }
    if(count==0){
        cout<<"No matching direct ticket available in the system.\n";
    }
    if(count1==0)
    {
        cout<<"No connecting ticket.\n";
    }
}
       
void Flighttime_fun(flightdata str[],int size)
{
   cout<<"Enter your departure and arrival airports in a row.\n";
    string depart,destin;
    cin>>depart>>destin;
    cout<<"Do you want to search for connecting flights?\n";
    char ans;
    cin>>ans;
    int count=0;
    while(ans=='N'||ans=='n')
    {
        for(int i=0;i<size;i++)
        {
            if(str[i].city2==destin && str[i].city1==depart)
            {
                cout<<"Direct flight goes from "<<depart<<" to "<<destin<<" has the following flight time options:"<<endl;
                cout<<"Time for departure:"<< str[i].time1hours<<":"<<str[i].time1minutes<<endl;
                cout<<"Time for arrival:"<< str[i].time2hours<<":"<<str[i].time2minutes<<endl;
                
                count++;
            }
        }
        if(count==0)
        {
           cout<<"No direct flight is in the system currently.\n";
        }
    }
    if(ans=='Y'||ans=='y')
    {
        cout<<"Direct flight first displayed as following:\n";
        for(int i=0;i<size;i++)
        {
            if(str[i].city2==destin&& str[i].city1==depart)
            {
                cout<<"Direct flight goes from "<<depart<<" to "<<destin<<" has the following flight time options:"<<endl;
                cout<<"Time for departure:"<< str[i].time1hours<<":"<<str[i].time1minutes<<endl;
                cout<<"Time for arrival:"<< str[i].time2hours<<":"<<str[i].time2minutes<<endl;
                count++;
            }
        }
        if(count==0)
        {
            cout<<"No direct flight is in the system currently.\n";
        }
        count=0;
        //connecting flight module
        for(int i=0;i<size; i++)
        {
            if(str[i].city1==depart)
            {for(int j=0;j<size;j++)
            {
                if(str[j].city2==destin && str[j].city1==str[i].city2 )
                {
                    cout<<"There appears choices of one stop connecting flight.\n";
                    cout<<"From "<<depart<<" to "<<str[i].city1<<" then to "<<destin<<endl;
                    cout<<"Time specific info generals to "<<endl;
                    cout<<"Departure time is "<<str[i].time1hours<<":"<<str[i].time1minutes<<endl;
                    cout<<"Arrival time is "<<str[j].time2hours<<":"<< str[j].time2minutes<<endl;

                    count++;
                }
                else if(str[j].city2==destin)
                {
                    for(int k=0;k<size; k++)
                    {
                        if(str[k].city1==str[i].city2 && str[k].city2==str[j].city1 )
                        {
                            cout<<"Found two stopping flight combo for your refrence.\n";
                            cout<<"From "<<depart<<" to "<<str[i].city2<<" to "<<str[j].city1<<" to "<<destin<<endl;
                            cout<<"Time accumulates to: "<<endl;
                            cout<<"Departure time is "<<str[i].time1hours<<":"<<str[i].time1minutes<<endl;
                            cout<<"Arrival time is "<<str[j].time2hours<<":"<< str[j].time2minutes<<endl;
                            cout<<"Stopping time at "<<str[i].city2<<" at "<<str[i].time2hours<<":"<<str[i].time2minutes<<endl;
                            cout<<"Taking off at "<<str[k].city1<<" at "<<str[k].time1hours<<":"<<str[k].time1minutes<<endl;
                            cout<<"Second stop time at "<<str[k].city2<<" at "<<str[k].time2hours<<":"<<str[k].time2minutes<<endl;
                            cout<<"Taking off time at "<<str[j].city1<<" at "<<str[j].time1hours<<":"<<str[j].time1minutes<<endl;
                            count++;
                        }
                    }
                }
            }
            }
        }
        if(count==0)
        {
            cout<<"No connecting flight as well.\n";
        }

    }
}
void get_data()
{
    
        cout<<setw(10)<<"Your have entered airline utility system."<<endl;
        cout<<setw(10)<<"Enter your choice."<<endl;
        cout<<setw(10)<<"Press 1 for departure and destination city searching"<<endl;
        cout<<setw(10)<<"Press 2 for mileage query"<<endl;
        cout<<setw(10)<<"Press 3 for ticket price inquiry"<<endl;
        cout<<setw(10)<<"Press 4 for flight time info"<<endl;
        cout<<"Enter your choice:"<<endl;
    
}
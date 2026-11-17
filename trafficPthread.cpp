#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <omp.h>
#include "queue.h"
#include <vector>
#include <string>

using namespace std::chrono;
using namespace std;


string trafficData;
// queue that holds input data 
Queue* inputBuffer = new Queue;
vector<trafficPthread> info ={};
int amount_of_traffic_signals;


void read_traffic_data(){
    ifstream trafficDataFile("traffic_signal_simulation_data.txt");

    // helper variables to temp store info before conversion to int
    string tr_ID;
    string cars_pasd;

    string time_days;
    string time_hours;
    string time_minutes;
    // varaible to hold the current data in a trafficPthread object then
    // push that info into the queue 
    trafficPthread holder;
    
    while(getline (trafficDataFile, trafficData)){    
        tr_ID = trafficData.substr(10,1);
        holder.trafficLightID= stoi(tr_ID);
        //cout << "OG ID " << tr_ID << "STOID " << stoi(tr_ID) << endl;  TEST STATEMENT
            
        cars_pasd = trafficData.substr(13, trafficData.find('\n')-1);
        holder.amountOfCars = stoi(cars_pasd);
        cout << "OG passed " << tr_ID << " STOID " << stoi(cars_pasd) << endl; //TEST STATEMENT;


        time_days =trafficData.substr(0,2);
        time_hours =trafficData.substr(3,2);
        time_minutes =trafficData.substr(6,2);
        holder.timeStamp = (stoi(time_days)-1)* 1440 + stoi(time_hours) * 60 + stoi(time_minutes);
        //TEST STATEMENT
        // cout << "OG hours " << time_hours << " minutes " << time_minutes << " STOID " << 
        // stoi(time_hours) * 60 + stoi(time_minutes) << endl; 

        inputBuffer->enqueue(holder);
    }
}

void Serial(){
        trafficPthread result;
        // for X amount of traffic signals makes an vector to store each signals data so 
        // can eventually be added up it has an extra space to store the hour interval
        // at the start of the vector and it easily is retrivable
        vector<int> already_existing_traffic_IDs;
        for(int i=0;i <= amount_of_traffic_signals;i++){
            already_existing_traffic_IDs.push_back(0);
        }
        
        vector<vector<int>> hourly_results_vectors;
        // here can parralelize by telling each node to work on some subset of traffic lights
        // then we dont have to worry about them interfering with each other when accessing
        // the array since they would not ever look at the same data spot in it so we shouldnt
        // need mutex lock
    for(int j=0; j< info[info.size()-1].timeStamp;j++){
        for(int i=0; i<info.size(); i++){
            already_existing_traffic_IDs[info[i].trafficLightID] += info[i].amountOfCars;
        }
        if(j%60 == 0){
            // every hour stores the count from each traffic light and then resets the count
            // task can be split by time (have each node handle some percentage of time incoming
            // data would naturaly be sorted by time so can give each node an hour interval and
            // add it to the result 
            hourly_results_vectors.push_back(already_existing_traffic_IDs);
            for(int i=0;i <already_existing_traffic_IDs.size(); i++){
                already_existing_traffic_IDs[i]=0;
            }
        }
    } 

}

int main(){

    // testing only not needed normaly
    // cout << " QueueMade " << endl;
    
    /* cout << "Checking if queue empty" << endl;
    inputBuffer->is_empty();
    cout << "adding node to queue head Node" << endl;
    trafficPthread addNode;
    addNode.amountOfCars=0;
    addNode.timeStamp= 0;
    addNode.trafficLightID=0;
    inputBuffer->enqueue(addNode);
    inputBuffer->peek();
    inputBuffer->print();
    */

    read_traffic_data();

    /* //TRAFFIC LIGHT TEST PRINT
    for(int i=0;i<10;i++){
        cout << trafficlight_ID[i] << endl;
    }
    */
     //CARSPASSED TEST PRINT
    for(int i=0;i<10;i++){
        cout << "hi";
        (*inputBuffer).peek().amountOfCars;
    }

    
    cout << " hi";
    
    return 0;
}
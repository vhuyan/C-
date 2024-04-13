/***********************************************************************
Matr.-Nr:                     3071014
Nachname/Surname:             Bhuyan
Vorname/Given name:           Mohammad Rakib
Uni-Email:                    mohammad.bhuyan@stud.uni-due.de
Studiengang/Course of studis: ISE Computer Engineering
***********************************************************************/

#include <iostream>
#include <string>

using namespace std;

struct Bus
{
    int numberOfPassengers;
    int maxNumberOfPassengers;
};

void init(Bus &bus)
{
    bus.numberOfPassengers = 0;
    bus.maxNumberOfPassengers = 0;
}

void output(Bus &bus)
{
    cout << "bus data: passengers: actual: " << bus.numberOfPassengers << " maximum in simulation: " << bus.maxNumberOfPassengers << endl;
}

struct Stop
{
    string stopName;
    int numberOfStops;
    int numberPassengersGotOn;
    int numberPassengersGotOff;
    Stop *nextStop;
};

struct Stop *head = nullptr;

Stop* generate_stop(string newStopName)
{
    Stop *newStop = new Stop; // creating a new stop variable on the heap
    newStop->stopName = newStopName; // setting the name of the stop to the passed parameter
    newStop->numberOfStops = 0;
    newStop->numberPassengersGotOn = 0;
    newStop->numberPassengersGotOff = 0;
    newStop->nextStop = nullptr;
    return newStop;
}

Stop *generate_circular_line(int n)
{
    for(int i = 0; i < n; i++)
    {
        const string constant = "Bus Stop ";
        string busStopNumber = to_string(n-i); //in this way, we make sure that buses are outputted in ascending order (from 1 to 5) instead of descending order if we did simply to_string(i)
        string fullStopName = constant + busStopNumber;
        Stop *newStop = new Stop;
        newStop = generate_stop(fullStopName);
        newStop->nextStop = head;
        head = newStop;
    }
    return head;
}

void output(Stop *head)
{
    cout << head->stopName <<  ":      sums: off: " << head->numberPassengersGotOff << "    on: " << head->numberPassengersGotOn << "   stops: " << head->numberOfStops << endl;
}

void output_whole_line(Stop *head)
{
    Stop *iterator = head; //iterator is not treated as a special keyword here, it is just a normal pointer variable and we are using it to iterate through the list
    if (head != NULL)
    {
        while (iterator != nullptr)
        {
            output(iterator);
            iterator = iterator->nextStop;
        }
    }
    if (head == NULL)
    {
        cout << "The list is empty" << endl;
    }
}

void simulate_get_on_off(Bus &bus, Stop *stop, int numberPassengersGettingOff, int numberPassengersGettingOn)
{
    if(numberPassengersGettingOff > bus.numberOfPassengers) // setting the number of passengers getting off the bus exactly to the number of passengers on the bus in order not to get a negative number of passengers on the bus in case the if-condition holds
    {
        numberPassengersGettingOff = bus.numberOfPassengers;
    }
    cout << "simulate " << stop->stopName << ":     getting off: " << numberPassengersGettingOff << " getting on: " << numberPassengersGettingOn << endl;
    bus.numberOfPassengers = bus.numberOfPassengers - numberPassengersGettingOff + numberPassengersGettingOn; // updating the number of passengers on the bus
    stop->numberOfStops = stop->numberOfStops + 1; // increase the total number of times a bus stopped at the station
    stop->numberPassengersGotOn = stop->numberPassengersGotOn + numberPassengersGettingOn; // adding the passengers who got in as a result of this function's call to the passengers who have gotten in so far
    stop->numberPassengersGotOff = stop->numberPassengersGotOff + numberPassengersGettingOff;
    if ((numberPassengersGettingOff || numberPassengersGettingOn) != 0) // if necessary, update the maximum number of passengers in the simulation
    {
        if (bus.maxNumberOfPassengers < bus.numberOfPassengers)
        {
            bus.maxNumberOfPassengers = bus.numberOfPassengers;
        }
    }
}

int main()
{
    Bus bus;
    Stop *firstStop = head;
    Stop *currentStop;
    init(bus);
    cout << "input number of bus stops: ";
    int numberOfStops;
    cin >> numberOfStops;
    head = generate_circular_line(numberOfStops);
    firstStop = head;
    char selection;
    do
    {
        cout << "Simulation Bus Circular Line" << endl
        << "0 End" << endl
        << "1 Show data of bus" << endl
        << "2 Show all bus stops" << endl
        << "3 Simulate bus stops" << endl;
        cin >> selection;
        switch (selection)
        {
            case '0':
                break;
            case '1':
            {
                output(bus);
                break;
            }
            case '2':
            {
                output_whole_line(firstStop);
                break;
            }
            case '3':
            {
                cout << "Input number of stops: ";
                int numberOfStopsToSimulate;
                cin >> numberOfStopsToSimulate;
                for (int i = 0; i < numberOfStopsToSimulate; i++)
                {
                    int numberPassengersGettingOn = rand() % 10; // generate a random number in the range from 0 to 9
                    int numberPassengersGettingOff = rand() % 10; // generate a random number in the range from 0 to 9
                    simulate_get_on_off(bus, firstStop, numberPassengersGettingOff, numberPassengersGettingOn);
                    output(firstStop);
                    if(firstStop->nextStop == nullptr)
                    {
                        firstStop = head;
                    }
                    else
                    {
                        firstStop = firstStop->nextStop;
                    }
                }
                break;
            }
            default: cerr << "Sorry, wrong choice. Please choose 0, 1, 2, or 3. " << endl;
        }
    } while(selection != '0');
    return 0;
}

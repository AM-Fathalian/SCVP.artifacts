#include <iostream>
#include <string>
#include <systemc.h>
#include <queue>

using namespace std;

// Interface Making!
// %%%%%%%%%%%%%
// Interface
template <class T>  // making a type by template, so that we can use this interface for any type of data (int, float, string, etc.)
class SimpleFIFOInterface : public sc_interface
{
    public:
    virtual T read() = 0; // Pure virtual methods, making this a dynamic abstract of a method -
                          // - For variable definition of inherited classes. 
    virtual void write(T) = 0;
};   
// Channel
template <class T>
class SimpleFIFO : public SimpleFIFOInterface<T>{ //putting <T>
    private: // only the class SimpleFIFO itself can have access to the actual data.
    queue<T> fifo; // Using STL queue to implement the FIFO buffer.

    // We need them events to lock/unlock producer and consumer when FIFO is full/empty.s
    sc_event writtenEvent;
    sc_event readEvent;

    uint64_t maxSize; // maxsize of queue.

    public:
    SimpleFIFO(uint64_t size=16) : maxSize(size) {

    }
    T read() {
        if(fifo.empty())
            {
                cout << "Wait for writing" << endl;
                wait(writtenEvent); // Wait until the producer writes something to the FIFO. Once happned, it continues the code.
            }
        T val = fifo.front(); // Get the front element of the queue (the oldest element).
        fifo.pop(); // Remove the front element from the queue.
        readEvent.notify(SC_ZERO_TIME);
        return val; // Return the value read from the FIFO.
        }
    void write(T data){
        if(fifo.size() == maxSize){
            cout << "waiting to be empty" << endl;
            wait(readEvent); // Wait until the consumer reads something from the FIFO. Once happned)"
        }
        fifo.push(data); // Add the new data to the back of the queue.
        writtenEvent.notify(SC_ZERO_TIME); // Notify the consumer that new data has been written;
    }
};

SC_MODULE(PRODUCER){
    sc_port<SimpleFIFOInterface<int>> master; // Port to connect to the FIFO channel.

    SC_CTOR(PRODUCER){
        SC_THREAD(process);
    }

    void process() {
        int cnt = 0;

        while(true){
            wait(1,SC_NS);
            cout << "P writes " << cnt << "@ : " << sc_time_stamp()<< endl;
            master->write(cnt++);

        }
    }
};

SC_MODULE(CONSUMER){
    sc_port<SimpleFIFOInterface<int>> slave;

    SC_CTOR(CONSUMER){
        SC_THREAD(process);
    }

    void process(){
        while(true){
            wait(4,SC_NS); // we wait 4 just to observe the way queue goes up.
            cout << "C reads = " << slave->read() << "@ : " << sc_time_stamp() << endl;
        }
    }
};


int sc_main(int __attribute__((unused)) argc,
            char __attribute__((unused)) *argv[])
{
    SimpleFIFO<int> channel(4); // Running by only this line is erroneous. WE must define virtuals somewhere!
    CONSUMER c1("consumer1");
    PRODUCER p1("producer1");

    p1.master.bind(channel); // Connect the producer's port to the FIFO channel.
    c1.slave.bind(channel); // Connect the consumer's port to the FIFO channel.
 
    sc_start(17,SC_NS);
    return 0;
}


// %%%%%%%%%%%%%%%%%%%%%%55%%%%%%%5
// class vehicle
// {
//     public:

//     //member Variables
//     std::string color;
//     std:: string vendor;
//     float fuel;
    
//     //member functions (Methods)
//     void drive();  //Implemented outside of the Class definition.
    
    
//     void refuel(float f);
//     float getfuel();

//     // constructor : when an object of the class is created, the constructor is called automatically to initialize the object.
//     // same name as class
//     vehicle(std::string c, std::string v, float f) : color(c), vendor(v), fuel(f) {
 
//         // fuel = 93.59f;
//     }
//     // Another type:
//     vehicle() : color("white"), vendor("Ferrari"), fuel(0.0f) {}

//     // Destructor: when an object of the class is destroyed, the destructor is called automatically 
//     // to clean up any resources that the object may have acquired during its lifetime.
//     ~vehicle() {
//         // Clean up resources if needed     
//     }

// };


// class bus : public vehicle {
//     public:
//     int guests;
//     static int number_busses; // Static member variable shared and readable simultaneously for all the objects of the class.
//                               // It is shared among all the objects of the class. It is not tied to any specific object. 
//                               // It is initialized outside the class definition.

//     void board(int g) {guests += g;};
//     void unboard(int g) {guests -= g;};

//     bus (std::string c, std::string v, float f, int g) : vehicle(c, v, f), guests(g) {
//         number_busses++; // Increment the static member variable whenever a new bus object is created.
//     }; 


// };


// void vehicle::drive (){
//     if (fuel > 10 && fuel <100){ // For identifying variable <fuel> when we are outside the Class, we specify the function belongs to The Class by using the scope resolution operator <vehicle::drive()>.
//         std::cout << "vehicle has enough fuel to drive." << std::endl;

//     } else if (fuel > 100) {
//         std::cout << "You Fuel-meter is Broken Bruh..." << std::endl;
//     } else {
//         std::cout << "vehicle has LOW Fuel. Please refuel before driving." << std::endl;
//     }
// }

// void vehicle::refuel(float f) {
//     fuel += f;
// }

// float vehicle::getfuel() {
//     return fuel;
// }

// int bus::number_busses = 0; // Initialize the static member variable outside the class definition.

// int main()
// {
//     std::cout << "Hello World!" << std::endl;
//     int var = 20;
//     int * p;
//     p = &var;
//     std::cout << " var: " << var << std::endl;
//     std::cout<< "  p:   " << p << std::endl; 
//     std::cout << " *p:  " << *p << std::endl;




//     vehicle kl_tu_1("green", "BMW", 99.67f);
//     vehicle default_car;
//     kl_tu_1.drive();
//     vehicle * ptr_obj_car = new vehicle("red", "Toyota", 50.0f);
    
//     unsigned int n;
//     std::cout << "Enter the number of vehicles you want to create: ";
//     std::cin >> n;
//     vehicle * ptr_cars = new vehicle[n]; // Dynamically allocate an array of 'n' vehicle objects. (The array of objects made with Pointer!)
    
//     for (int i=0; i<n; i++){
//         ptr_cars[i].refuel(10.0f + i*10.0f); // The way we can use each element of the array of the objects. 
//         std::cout << "vehicle " << i << " has fuel: " << ptr_cars[i].getfuel() << std::endl;
//     }





//     /////////////////
//     ptr_obj_car->drive();
//     std::cout << kl_tu_1.getfuel() << std::endl;    
//     std::cout << default_car.getfuel() << std::endl;
//     std::cout << ptr_obj_car->getfuel() << std::endl;

//     delete ptr_obj_car; // Clean up the dynamically allocated object (The object made with Pointer!)
//     delete [] ptr_cars; // Clean up the dynamically allocated array of objects (The array of objects made with Pointer!)



//     ////////////
//     bus kl_bus_1("Red", "Volvo", 77.0, 0);
//     std::cout << "Bus color: " << kl_bus_1.color << std::endl;
//     std::cout << "Bus vendor: " << kl_bus_1.vendor << std::endl;
//     std::cout << "Bus fuel: " << kl_bus_1.fuel << std::endl;
//     std::cout << "Bus guests: " << kl_bus_1.guests << std::endl;

//     kl_bus_1.board(10);
//     std::cout << "Bus guests after boarding: " << kl_bus_1.guests << std::endl;

//     kl_bus_1.unboard(4);
//     std::cout << "Bus guests after unboarding: " << kl_bus_1.guests << std::endl;

//     bus kl_bus_2("Blue", "Mercedes", 88.0, 0);
//     std::cout << "Number of busses: " << bus::number_busses << std::endl; // Accessing the static member variable using the class name and scope resolution operator.
//     std::cout << "Number of busses (using object): " << kl_bus_1.number_busses << std::endl; // Accessing the static member variable using an object of the class.
//                                                                                              // It is also possible but not recommended as it can be confusing.
//     return 0;
// }
#include <iostream>
#include <string>


class car
{
    public:
    //member variables
    std::string color;
    std:: string vendor;
    float fuel;
    
    //member functions
    void drive() {};
    
    void refuel(float f) {
        fuel += f;
    };

    float getfuel() {
        return fuel;
    };

    // constructor : when an object of the class is created, the constructor is called automatically to initialize the object.
    // same name as class
    car(std::string c, std::string v, float f) : color(c), vendor("BMW") {
 
        fuel = 93.59f;
    }
    // Another type:
    car() : color("white"), vendor("Ferrari"), fuel(0.0f) {}

    // Destructor: when an object of the class is destroyed, the destructor is called automatically 
    // to clean up any resources that the object may have acquired during its lifetime.
    ~car() {
        // Clean up resources if needed     
    }

};



int main()
{
    std::cout << "Hello World!" << std::endl;

    car kl_tu_1("green", "BMW", 99.67f);
    car default_car;

    std::cout << kl_tu_1.getfuel() << std::endl;
    std::cout << default_car.getfuel() << std::endl;

    return 0;
}
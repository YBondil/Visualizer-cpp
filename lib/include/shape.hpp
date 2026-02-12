#include <vector>

struct R3 {
    int x;
    int y;
    int z;
};


class Shape {
    
    private :
        std::vector<R3> apex ;
        std::vector<R3> vertices;

    public:  
        Shape(){};
        ~Shape(){};
        virtual bool draw() = 0; 
        bool rotate() ;
        
};

class Triangle : public Shape {

    Triangle(std::vector<R3> apex){}
};
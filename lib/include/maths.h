#include <vector>

namespace MATHS {

    struct N3 {
        int x;
        int y;
        int z;
    };

    template <typename T>
    class Matrix {
        public :
            std::vector<std::vector<T>> data ;
            int rows ;
            int cols ;
            Matrix(int rows, int cols) ;
            Matrix(const Matrix<T>& other) ;
            Matrix(const N3& other) ;
    
            Matrix<T>& operator=(const Matrix<T>& other) ;
            Matrix<T> operator+  (const Matrix<T>&  other) const ;
            Matrix<T> operator+  (T value) const ;
            Matrix<T>& operator+=(const Matrix<T>&  other) ;
            Matrix<T> operator-  (const Matrix<T>&  other) const ;
            Matrix<T> operator-  (T value) const ;
            Matrix<T>& operator-=(const Matrix<T>&  other) ;
            Matrix<T> operator*  (const Matrix<T>&  other) const ;
            Matrix<T> operator* (T lambda) ;
            Matrix<int> operator* (const N3& vec) const ;

            
            
            

    };
}


class Shape {
    friend class Cube ;

    private :
        int nb_apex;
        int nb_vertice;

        std::vector<MATHS::N3> apex ;
        std::vector<MATHS::N3> vertices;

    public:  
        Shape(){};
        ~Shape(){}; 
        bool rotate() ;

        std::vector<MATHS::N3>get_vertices(){return vertices ;};
        std::vector<MATHS::N3>get_apex(){return apex ;}
        
};

class Cube : public Shape {

    private :
        int size ; 
    public : 
        Cube(int size) : size(size) { 
            // Initialize the cube's vertices and apexes based on the size // This is a placeholder implementation 
            apex.push_back({0, 0, 0}); 
            apex.push_back({size, 0, 0}); 
            apex.push_back({size, size, 0}); 
            apex.push_back({0, size, 0}); 
            apex.push_back({0, 0, size}); 
            apex.push_back({size, 0, size}); 
            apex.push_back({size, size, size});
            apex.push_back({0, size, size}); 
            vertices = apex; // In a cube, vertices are the same as apexes } 
        }
        ~Cube(){}; 
        void rotate(Matrix<int>& rotation_matrix) ;

};
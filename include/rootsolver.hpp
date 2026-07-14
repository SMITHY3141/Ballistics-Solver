


#ifndef ROOTSOLVER_HPP
#define ROOTSOLVER_HPP

/*
class Solver {
    template <int N>
private:
    Vector<N> state;
    //Matrix<N, N> jacobian;
    Vector<N> error(Vector<N> state);

public:
    Solver();
    Solver(Vector<N>) : ;

    //step(); // step using numerical jacobian
    step(Matrix<N, N> jacobian);


}
*/

#include <VECTORS/vectors.hpp>
#include <VECTORS/matrices.hpp>

namespace solver {
    template <int N>
    using ErrorType = std::function<Vector<N>(const Vector<N>&)>;
    
    template <int N>
    using JType = std::function<Matrix<N, N>(const Vector<N>&)>;
    
    // Vector<N> step(int n, Vector<N> state, ErrorType error_func);
   
    template <int N>
    Vector<N> solve(int n, const Vector<N> &state, const ErrorType<N> error_f, const JType<N> jacobian_f);

    template <int N>
    Vector<N> step(const Vector<N> &state, const Matrix<N, N> &jacobian);

    // Matrix<N, N> jacobian(ErrorType error_func, float gap);





    // .cpp

    template <int N>
    Vector<N> solve(int n, const Vector<N> &state, const ErrorType<N> error_f, const JType<N> jacobian_f) {

        Vector<N> vec{0};
        return vec;
        
    }

    template <int N>
    Vector<N> step(const Vector<N> &state, const Matrix<N, N> &jacobian) {
        Vector<N> vec;
        return vec;
    }
}


#endif // ROOTSOLVER_HPP

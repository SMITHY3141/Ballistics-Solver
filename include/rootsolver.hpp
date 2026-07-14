


#ifndef ROOTSOLVER_HPP
#define ROOTSOLVER_HPP

#include <VECTORS/vectors.hpp>
#include <VECTORS/matrices.hpp>

#include <iostream>

namespace solver {
    // .hpp
    template <int N>
    using ErrorType = std::function<Vector<N>(const Vector<N>&)>;
    
    template <int N>
    using JType = std::function<Matrix<N, N>(const Vector<N>&)>;
    
    template <int N>
    Vector<N> solve(int n, const Vector<N> &guess, float desired, const ErrorType<N> error_f, const JType<N> jacobian_f);



    // .cpp
    template <int N>
    Vector<N> solve(int n, const Vector<N> &guess, float desired, const ErrorType<N> error_f, const JType<N> jacobian_f) {
        std::cout << "SOLVING" << '\n';
        
        Vector<N> state = guess;
        for (int i = 0; i < n + 1; i++) {

            Vector<N> error = error_f(state);
            float miss = error.length();

            std::cout << i << ": " << state << ", error: " << miss << '\n';
            if (miss < desired || i == n) {
                break;
            }

            Matrix<N, N> jacobian = jacobian_f(state);
            Matrix<N, N> inverse = jacobian.inverse();
            state -= inverse * error;


        }

        return state;
        
    }

    

}


#endif // ROOTSOLVER_HPP

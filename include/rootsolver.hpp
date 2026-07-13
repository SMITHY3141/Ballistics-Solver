


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

namespace solver {
    template <int N>
    using ErrorType = std::Function<Vector<N>(const Vector<N>&)>;
    using JType = std::Function<Matrix<N, N>(const Vector<N>&)>;
    // Vector<N> step(int n, Vector<N> state, ErrorType error_func);
    Vector<N> solve(int n, const Vector<N> state, const ErrorType error_f, const JType jacobian_f);

    Vector<N> step(Vector<N> state, Matrix<N, N> jacobian);

    // Matrix<N, N> jacobian(ErrorType error_func, float gap);
}


#endif // ROOTSOLVER_HPP

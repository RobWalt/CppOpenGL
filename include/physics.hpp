#pragma once     
#include <array>

using precision_type = float;
using integer_type = std::size_t;

template <integer_type domain_size>
using domain_type = std::array<precision_type, domain_size>;

template <integer_type domain_size>
class DifferentialEquation
{
    public:
        domain_type<domain_size> get_current_solution();

    private:
        domain_type<domain_size> runge_kutta_4_step();

        integer_type iteration_step_ = 0; 
        precision_type time_step_size_ = precision_type(1e-3);
        precision_type space_step_size_ = precision_type(1e-3);
        domain_type<domain_size> initial_data_;
        domain_type<domain_size> solution_;

        precision_type u_xx(precision_type point_middle,
                            precision_type point_above,
                            precision_type point_below,
                            precision_type point_right,
                            precision_type point_left);

        /*
        y : T x R^2 -> R
        z : T x R^2 -> R^2

            z = dy/dx
        dy/dt = trace(dz/dx)

        new ode.
        a = [y z]
        da/dt = [trace(da[2]/dx) a[1]/dx]

        */
        
};
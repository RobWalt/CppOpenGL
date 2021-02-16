#include "physics.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

DifferentialEquation::DifferentialEquation(precision_type c, precision_type dx, precision_type dt)
{
    c_ = c;
    dx_ = dx;
    dt_ = dt;
    lambda_ = (c_ * c_ * dt_) / (dx_ * dx_);
    std::fill(solution_.begin() + (domain_size / 2) - (domain_width/2) , solution_.begin() + (domain_size / 2) + (domain_width/2), 1.0f);
    solution_[domain_size/2] = 1.0f;
    if (!is_stable()) {
        std::cout << "NOT STABLE!!!! EVERYTHING WILL BREAK!!" << std::endl;
    } else {
        std::cout << "This differential equation is stable!" << std::endl;
    }
}

domain_type DifferentialEquation::get_current_solution()
{
    return solution_;
}

bool DifferentialEquation::is_stable()
{
    return dt_ < (dx_ * dx_) / (2 * c_ * c_);
}

bool DifferentialEquation::is_upper_boundary_node(integer_type index)
{
    return index < domain_width;
}

bool DifferentialEquation::is_lower_boundary_node(integer_type index)
{
    return index > (domain_size-domain_width-1);
}

bool DifferentialEquation::is_right_boundary_node(integer_type index)
{
    return ((index + 1) % domain_width) == 0;
}

bool DifferentialEquation::is_left_boundary_node(integer_type index)
{
    return (index % domain_width) == 0;
}

void DifferentialEquation::solver_step()
{
    domain_type next_solution;

    for (integer_type i=0; i<solution_.size(); i++)
    {
        precision_type u_n_down = 0.0;
        precision_type u_n_up = 0.0;
        precision_type u_n_right = 0.0;
        precision_type u_n_left = 0.0;

        if ( !is_lower_boundary_node(i) ) {
            u_n_down = solution_[i+domain_width];
        }

        if ( !is_upper_boundary_node(i) ) {
            u_n_up = solution_[i-domain_width];
        }

        if ( !is_right_boundary_node(i) ) {
            u_n_right = solution_[i+1];
        }

        if ( !is_left_boundary_node(i) ) {
            u_n_left = solution_[i-1];
        }

        auto u_n_middle = solution_[i];

        next_solution[i] = lambda_ * (u_n_right + u_n_left + u_n_down + u_n_up) + (1-4*lambda_) * u_n_middle;
    }

    solution_ = next_solution;

}

void DifferentialEquation::print_solution()
{
    std::cout << std::fixed << std::setprecision(2);
    for (integer_type i=0; i<solution_.size(); i++)
    {
        std::cout << "[" << solution_[i] << "]";
        if (is_right_boundary_node(i)){
            std::cout << "\n";
        } 
    }
}
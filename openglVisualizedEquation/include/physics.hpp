#pragma once     
#include <array>

constexpr unsigned int domain_width = 101;
constexpr unsigned int domain_height = 101;
constexpr unsigned int domain_size = domain_width * domain_height;

using precision_type = float;
using integer_type = std::size_t;
using domain_type = std::array<precision_type, domain_size>;

class DifferentialEquation
{
    public:
        DifferentialEquation(precision_type c, precision_type dx, precision_type dt);
        void solver_step();
        domain_type get_current_solution();
        void print_solution();
        void add_heat(const std::array<bool, domain_size>& add_heat_here);

    private:

        bool is_stable();

        bool is_upper_boundary_node(integer_type index);
        bool is_lower_boundary_node(integer_type index);
        bool is_right_boundary_node(integer_type index);
        bool is_left_boundary_node(integer_type index);

        integer_type iteration_step_ = 0; 
        precision_type dt_ = precision_type(1e-3);
        precision_type dx_ = precision_type(1e-3);
        precision_type c_{};
        precision_type lambda_{};
        domain_type solution_{};

        /*
        012
        345
        678
        */
};
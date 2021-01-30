#include "physics.hpp"

template <integer_type domain_size>
precision_type DifferentialEquation<domain_size>::u_xx(precision_type point_middle,
                                        precision_type point_above,
                                        precision_type point_below,
                                        precision_type point_right,
                                        precision_type point_left)
                                        {
                                            return (point_above + point_below + point_left + point_right - 4 * point_middle)/ this->space_step_width;
                                        }
        
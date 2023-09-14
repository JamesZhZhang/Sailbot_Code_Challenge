#include "stdbool.h"
#include "standard_calc.h"

/**
 * @brief Bounds the provided angle between [-180, 180) degrees.
 *
 * e.g.)
 *      bound_to_180(135) = 135.0
 *      bound_to_180(200) = -160.0
 *
 * @param angle: The input angle in degrees.
 *
 * @return float: The bounded angle in degrees.
 */
float bound_to_180(float angle) {
    //Since these are local to bound_to_180, the const doesn't do much
    //Ideally, we'd like to declare these separately, in a namespace, and possibly in a header file
    const float angle_bound {180.0f};
    const float angle_increment {360.0f};

    //The angle parameter can only satisfy one of the while loop ocnditions 
    //So structuring the while loops like this gives us an implicit if, else
    while (angle >= angle_bound)
        angle -= angle_increment;   //Subtract increments of 360 degrees
                                    //Allows us to deal with angles > 360, and angles between [180, 360]
                                    //in the same line
    
    while (angle < -angle_bound)
        angle += angle_increment;

    return angle;
}

/**
 * @brief Determines whether an angle is between two other angles
 *
 *  e.g.)
 *      is_angle_between(0, 45, 90) = true
 *      is_angle_between(45, 90, 270) = false
 * 
 * @param first_angle:  The first bounding angle in degrees.
 * @param middle_angle: The angle in question in degrees.
 * @param second_angle: The second bounding angle in degrees.
 * @return bool: TRUE when `middle_angle` is not in the reflex angle of `first_angle` and `second_angle`, FALSE otherwise
 */

/**
*ASSUMPTIONS
* I apologize, as I don't quite understand the phrase: TRUE when `middle_angle` is not in the reflex angle of `first_angle` and `second_angle`
* As such, I've made the following assumption for what the function should do:
* Find out if the middle angle is between the 1st and 2nd angle, provided all angles are bound between [-180, 180) degrees
*/
bool is_angle_between(float first_angle, float middle_angle, float second_angle) {
    //Ideally we'd like to pass the angle to bound_to_180 by reference to avoid creating extra variables 
    //But we'll utilize bound_to_180 having a return value

    //Bind angles between [-180, 180) degrees, as per the assumption
    float bound_first_angle {bound_to_180(first_angle)};
    float bound_middle_angle {bound_to_180(middle_angle)};
    float bound_second_angle {bound_to_180(second_angle)};

    //Determine if first_angle or second_angle is the lower bound
    //Depending on the result, check that middle_angle is greater than the lower bound (could be first or second_angle)
    //And that middle_angle is less than upper bound
    if (bound_first_angle < second_angle){
        return (bound_first_angle < bound_middle_angle && bound_middle_angle < bound_second_angle);
    }
    else {
        return (bound_first_angle > bound_middle_angle && bound_middle_angle > bound_second_angle);
    }
}

/* See if a string contains a python integer, and return the contained long. */
#include <limits.h>
#include "parsing.h"
#include "fast_conversions.h"

inline static bool check_for_overflow(const long value, const long cur_val);

long parse_integer_from_string (const char *str, bool *error, bool *overflow)
{
    register long value = 0L;
    register bool valid = false;
    *overflow = false;
    *error = true;
 
    consume_white_space(&str);
    const long sign = consume_sign_and_is_negative(&str) ? -1L : 1L;

    /* Convert digits, if any. Check for overflow. */
 
    for (value = 0L; is_valid_digit(str); valid = true, str += 1) {
        const long tmpval = ascii2long(str);
        *overflow = *overflow || check_for_overflow(value, tmpval);
        value *= 10L;
        value += tmpval;
    }
 
    consume_python2_long_literal_lL(&str);
    *error = !valid || !trailing_characters_are_vaild_and_nul_terminated(&str);
    return sign * value;

}

bool check_for_overflow(const long value, const long cur_val)
{
    static const long overflow_cutoff = LONG_MAX / 10L;
    static const long overflow_last_digit_limit = LONG_MAX % 10L;
    return value > overflow_cutoff ||
          (value == overflow_cutoff && cur_val > overflow_last_digit_limit);
}
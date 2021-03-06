from __future__ import print_function, division

import sys
from timeit import repeat
from time_base import mean


def time_input_against_all_functions(value, label):
    """Run the given input on all function types."""
    funcs = ('fast_real', 'fast_float', 'fast_int', 'fast_forceint',
             'isreal', 'isfloat', 'isint', 'isintlike',)
    fmt = '{func}({value!r})'
    for func in funcs:
        print(label + ',', func + ':', end=' ')
        sys.stdout.flush()
        time_results = repeat(fmt.format(func=func, value=value),
                              'from fastnumbers import {}'.format(func),
                              repeat=10)
        time_results = mean(time_results)
        print(time_results, 'seconds')
    print()


print('All timing results are the average of 10 runs.')
print()
time_input_against_all_functions('not_a_number', 'Non-number String')
time_input_against_all_functions('-41053', 'Int String')
time_input_against_all_functions('35892482945872302493947939485729', 'Large Int String')
time_input_against_all_functions('-41053.543034e34', 'Float String')
time_input_against_all_functions('-41053.543028758302e256', 'Large Float String')
time_input_against_all_functions(-41053.543028758302e100, 'Float')
time_input_against_all_functions(-41053, 'Int')

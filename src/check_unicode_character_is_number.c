/*
 * Functions that will assess if a unicode character is numeric.
 *
 * Author: Seth M. Morton
 *
 * January 2017
 */

#include "unicode_handling.h"
#include "number_handling.h"


static bool
numeric_unicode_is_intlike(Py_UCS4 uni)
{
    const double val = uni_tonumeric(uni);
    /* Lowerbound of values is > -1.0.
     * tonumeric will always return values within "long" range
     * (or "long long" on MSVC), so no overflow risk below.
     */
#ifdef _MSC_VER
    return (val > -1.0) && val == (long long) val;
#else
    return (val > -1.0) && val == (long) val;
#endif
    /* return (val > -1.0) && double_is_intlike(val); */
}


PyObject*
PyUnicode_is_number(PyObject *obj, const PyNumberType type)
{
    const Py_UCS4 uni = convert_PyUnicode_to_unicode_char(obj);
    if (unicode_conversion_success(uni)) {
        switch (type) {
        case REAL:
        case FLOAT:
            return PyBool_from_bool(uni_isnumeric(uni));
        case INT:
            return PyBool_from_bool(uni_isdigit(uni));
        case FORCEINT:
        case INTLIKE:
        default:
            return PyBool_from_bool(uni_isdigit(uni) ||
                                    numeric_unicode_is_intlike(uni));
        }
    }
    else
        return Py_None;  /* Not unicode. */
}

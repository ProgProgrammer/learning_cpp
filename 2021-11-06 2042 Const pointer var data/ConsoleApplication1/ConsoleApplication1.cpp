#include <iostream>

void error_calls()
{
    int data = 3;
    const int* var_pointer_const_data = &data;
    int* const const_pointer_var_data = &data;

    // *var_pointer_const_data = 100;  // error C3892: 'var_pointer_const_data': you cannot assign to a variable that is const
    // const_pointer_var_data = &data; // error C3892: 'const_pointer_var_data': you cannot assign to a variable that is const
}

void sucsess_calls()
{
    int data = 3;
    const int* var_pointer_const_data = &data;
    int* const const_pointer_var_data = &data;

    var_pointer_const_data = var_pointer_const_data + 1;
    *const_pointer_var_data = 5;
}


int main()
{
    return 0;
}
#include<vector>
#include<stdio.h>
#include<iostream>

#include<dio.h>

using namespace dio;

void line()
{
    for(int i=0; i<50; ++i)
        printf("-");
    printf("\n");
}

int main()
{
    Node x = Variable(5.00);
    // Node z = -((0.5-x)^2); // precendence(^) < precedence(-)
    Node z = (0.5-x)^2; 

    for(int epoch=0; epoch<12; ++epoch)
    {
        printf("Epoch %d: z:", epoch);
        z.compute_val(); // re-calculates value of z
        z.print_val();
        printf(" x: ");
        x.print_val();
        printf(" new x: ");
        x.update_val(x - 0.3*z.grad(x).index(0)); // DO NOT do: x = x - 0.3*z.grad(x).index(0), as it creates a new node
        x.print_val();
        printf("\n");
    }

    line();

    

}
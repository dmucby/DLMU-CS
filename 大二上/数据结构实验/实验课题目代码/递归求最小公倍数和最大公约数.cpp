#include<iostream>

int gcd1(int x, int y)
{	if (y)
            return gcd(y, x%y);
        else
            return x;
}

#���������������㷨
int gcd2(int x, int y)
{
    while(y^=x^=y^=x%=y);
    return x;
}

int gbs(int x,int y){
    return x * y /gcd1();
}

package 第1章_summary;

import static java.lang.Math.abs;
import static java.lang.Math.min;

/**
 * 1.4 求两个正整数的最大公约数
 */
public class HCF {
    public static void main(String[] args) {
        System.out.println(Euclid(10,20));
        System.out.println(Stein(10,20));
    }

    static int Euclid(int a,int b){
        return b!=0 ? Euclid(b,a%b) : a;
    }

    static int Stein(int a,int b){
        if(a == 0){
            return b;
        }else if (b == 0) {
            return a;
        }
        if (a % 2 ==0 && b % 2 ==0) {
            return 2 * Stein(a >> 1, b >> 1);
        }else if(a % 2 == 0){
            return Stein( a >> 1,b);
        }else if (b % 2 == 0) {
            return Stein(a, b >> 1);
        }else{
            return Stein(abs(a-b),min(a,b));
        }
    }
}

package 第3章_循环和递归;

import java.util.Scanner;

/**
 * 3.2 实现数学表达式
 */

public class FactorialLoop {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        System.out.println(factorialLoop(n));
    }
    static double factorialLoop(int n){
        double S = 1.0000;
        double sign = 1;
        double t = 1;
        for (double i = 2; i <= n; i++) {
            sign = -sign;
            t = t  * ( (2 * i - 2) * (2 * i - 1));
            S += sign / t;
        }
        return S;
    }
}

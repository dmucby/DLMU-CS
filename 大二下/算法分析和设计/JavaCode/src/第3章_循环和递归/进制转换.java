package 第3章_循环和递归;

import java.util.Scanner;
import java.util.Stack;

/**
 * 3.6 进制转换问题
 */

public class 进制转换 {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        print(n);

    }

    static void print(int n){

        Stack<Integer> a = new Stack<Integer>();

        int s;

        while (n != 0) {
            s = n % 2;
            n = n / 2;
            a.push(s);
        }

        StringBuilder ans = new StringBuilder();

        while (!a.isEmpty()){
            ans.append(a.pop());
        }

        System.out.println(ans);
    }

}

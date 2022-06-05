package 第8章_贪心法;

import java.util.Scanner;

/**
 * 币种统计问题
 */
public class money {

    static int[] arrays = {100,50,20,10,5,2,1};

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        print(n);
    }

    static void print(int n){

        int[] s = new int[arrays.length];
        int a;

        for (int i = 0; i < arrays.length; i++) {
            a = n / arrays[i];
            s[i] = s[i] + a;
            n -= a * arrays[i];
        }

        for (int i = 0; i < arrays.length ; i++) {
            if (s[i]!=0) {
                System.out.println(arrays[i] + " " + s[i]);
            }
        }
    }
}

package 第5章_算法优化基本技巧;

import java.util.Scanner;

/**
 * 5.2.4 找次品算法
 */

public class boxQuestion {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int w2 = sc.nextInt();
        print(n,w2);
    }

    static void print(int n,int w2){
        int w1 = 0;
        int t = 1;
        int k;
        for (int i = 1; i <= n; i++){
            System.out.println(i+" box take " + t +" letter");
            w1 = w1 + t;
            t *= 2;
        }
        System.out.println("all weight: " + w1);
        System.out.println("actual weight: " + w2);
        w2 = w1 - w2;
        while(w2 != 0){
            k = (int) (Math.log(w2)/Math.log(2));
            System.out.println(k+1 + " is bad!");
            w2 = (int) (w2 - Math.pow(2,k));
        }
    }
}

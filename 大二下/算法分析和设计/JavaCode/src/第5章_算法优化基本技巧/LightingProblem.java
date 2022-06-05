package 第5章_算法优化基本技巧;

import java.util.Scanner;

/**
 * 5.1.2 开灯问题
 */

public class LightingProblem {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        print(n);
    }

    static void print(int n){
        int[] array = new int[n+1];
        int k;
        for (int i = 1; i <= n; i++) {
            array[i] = 0;
        }
        for(int i = 2; i <= n; i++){
            k = 1;
            while (i * k <= n){
                array[i*k] = 1 - array[i*k];
                k++;
            }
        }
        for (int i = 1; i <= n; i++) {
            System.out.print(array[i]+" ");
        }
    }
}

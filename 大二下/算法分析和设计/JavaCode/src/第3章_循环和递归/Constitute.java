package 第3章_循环和递归;

import java.util.Scanner;

public class Constitute {
    static int total = 0;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int r = sc.nextInt();
        constitute(n,r);
    }

    static void constitute(int n,int r){
        if (n < r){
            return;
        }
        int[] a = new int[n];
        a[0] = r;
        comb(n,r,a);
        System.out.println(total);
    }

    static void comb(int n,int r,int[] a){
        for (int i = n; i >= r; i--) {
            a[r] = i;
            if(r > 1){
                comb(i-1,r-1,a);
            }else {
                for (int j = a[0]; j > 0 ; j--) {
                    System.out.print(a[j] + " ");
                }
                total = total + 1;
                System.out.println();
            }
        }
    }
}

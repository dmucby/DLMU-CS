package 第4章_算法与数据结构;

import java.util.Scanner;

/**
 * 4.5.2 圆圈定值报退
 */
public class circle {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        int k = scanner.nextInt();
        print(n,m,k);
    }

    static void print(int n,int m,int k){
        int[] ans = new int[100];
        for (int i = 1; i <= n ; i++) {
            ans[i] = 1;
        }
        int p =0;
        k--;
        int x = 0;
        System.out.print("在圈中的编号： ");
        for (int i = 1; i <= n; i++) {
            if (ans[i] == 1) {
                System.out.print("i= " + i + " ");
            }
        }
        System.out.println();
        System.out.println("出圈次序");
        while (p < n-1){
            x = 0;
            while (x < m){
                k++;
                if(k > n){
                    k = 1;
                }
                x = x + ans[k];
            }
            System.out.print("\t" + k);
            ans[k] = 0;
            p++;
        }

        System.out.println();
        for (int i = 1; i <= n; i++) {
            if (ans[i] == 1){
                System.out.println("最后的人： " + i );
            }
        }
    }
}

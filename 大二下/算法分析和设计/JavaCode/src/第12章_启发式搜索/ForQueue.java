package 第12章_启发式搜索;

import java.util.Scanner;

public class ForQueue {

    static int count = 0;
    static int[] q = new int[20];

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        dfs(1,n);
        System.out.println("共有" + count + "种摆放方式");
    }

    static void print(int n){
        int i, j;
        count++;
        System.out.println("第 " + count + " 个解：");
        for (i = 1; i <= n; i++) // 行
        {
            for (j = 1; j <= n; j++) // 列
            {
                if (q[i] != j)
                    System.out.print("x");
                else
                    System.out.print("Q");
            }
            System.out.println();
        }
        System.out.println();
    }

    static boolean isSafe(int k,int j){
        int i;
        for (i = 1;i < k;i++){
            // 如果位于同一
            if(q[i] == j ||Math.abs(i-k) == Math.abs(q[i]-j)){
                return false;
            }
        }
        return true;
    }

    static void dfs(int k,int n){
        int j;
        if (k > n){
            print(n);
        }else {
            for (j = 1; j <= n; j++) {  // 从第k行开始试错
                if(isSafe(k,j)){
                    q[k] = j;
                    dfs(k+1,n); // 确认第k行安全开始下一个
                }
            }
        }
    }
}

package 第10章_动态规划;

import java.util.Scanner;

/**
 * 10.4 资源分配问题
 */

public class divideResource {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int m,n; //  m个项目 n资源
        m = sc.nextInt();
        n = sc.nextInt();
        float[][] g = new float[100][100];
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                g[i][j] = sc.nextFloat();
            }
        }
        print(g,m,n);
    }


    static void print(float[][] g,int m,int n){
        float[] f = new float[100];
        float[][] ans = new float[100][100];
        float[] temp = new float[100];
        int num = 0;
        for (int j = 0; j <= n; j++) {
            f[j] = g[1][j];
            ans[1][j] = j;
        }

        //投资第后面项目的最大收益
        for (int k = 2;k < m;k++) {
            for (int j = 0;j <= n;j++) {
                temp[j] = g[k][j];
                ans[k][j] = 0;
            }
            for (int j = 0;j <= n;j++) {
                for (int i = 0;i <= j;i++) {
                    if (f[j - i] + g[k][i] > temp[j]) {
                        temp[j] = f[j - i] + g[k][i];
                        ans[k][j] = i;
                    }
                }
            }
            for (int j = 0;j <= n;j++) {
                f[j] = temp[j];
            }
        }

        for (int i = 0;i <= n;i++) {
            temp[i] = g[m][i] + f[n - i];
        }
        for (int j = 0;j <n;j++) {
            if (temp[j] < temp[j + 1]) {
                num = j+1;
            }
        }

        for (int i = 0; i <= n; i++) {
            System.out.println(temp[i]);
        }

        System.out.println("最大收益为：");
        System.out.println("第一个项目投资为:"+(n-num-ans[2][n-num]));
        System.out.println("第二个项目投资为:"+ans[2][n-num]);
        System.out.println("第三个项目投资为:"+num);
        System.out.println("最大收益为"+temp[num]);
    }
}

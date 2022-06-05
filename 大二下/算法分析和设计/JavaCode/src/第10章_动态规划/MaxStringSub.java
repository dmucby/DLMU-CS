package 第10章_动态规划;

import java.util.Locale;
import java.util.Scanner;

/**
 * 10.5 最长公共字符子序列
 */
public class MaxStringSub {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String str1 = scanner.nextLine().toLowerCase(Locale.ROOT);
        String str2 = scanner.nextLine().toLowerCase(Locale.ROOT);

//        int m = str1.length();
//        int n = str2.length();
//
//        print(str1,str1,m,n);

        System.out.println(findLCS(str1,str1.length(),str2,str2.length()));
    }

    public static int findLCS(String A, int n, String B, int m) {
        int[][] dp = new int[n + 1][m + 1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                dp[i][j] = 0;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (A.charAt(i - 1) == B.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
                }
            }
        }
        return dp[n][m];
    }

//    static void print(String str1,String str2,int m,int n){
//        //创建二维数组，也就是填表的过程
//        int[][] c = new int[m+1][n+1];
//
//        //初始化二维数组
//        for (int i = 0; i < m+1; i++) {
//            c[i][0] = 0;
//        }
//        for (int i = 0; i < n+1; i++) {
//            c[0][i] = 0;
//        }
//
//        //实现公式逻辑
//        int[][] path = new int[m+1][n+1];
//        //记录通过哪个子问题解决的，也就是递推的路径
//        for (int i = 1; i < m+1; i++) {
//            for (int j = 1; j < n+1; j++) {
//                if(str1.charAt(i-1) == str2.charAt(j-1)){
//                    c[i][j] = c[i-1][j-1] + 1;
//                }else if(c[i-1][j] >= c[i][j-1]){
//                    c[i][j] = c[i-1][j];
//                    path[i][j] = 1;
//                }else{
//                    c[i][j] = c[i][j-1];
//                    path[i][j] = -1;
//                }
//            }
//        }
//        PrintLCS(path,str2,m,n);
//    }
//
//    public static void PrintLCS(int[][]b,String x,int i,int j){
//        if(i == 0 || j == 0){
//            return;
//        }
//
//        if(b[i][j] == 0){
//            PrintLCS(b,x,i-1,j-1);
//            System.out.printf("%c",x.charAt(i-1));
//        }else if(b[i][j] == 1){
//            PrintLCS(b,x,i-1,j);
//        }else{
//            PrintLCS(b,x,i,j-1);
//        }
//    }



}

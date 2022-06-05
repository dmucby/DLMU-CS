package 第3章_循环和递归;

import java.util.Scanner;

/**
 * 3.5.2 整数划分问题
 */
public class DivInteger {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(Divider(n,n));
    }

    /**
     * 整数划分
     * @param n 输入数
     * @param m 不超过m的被加数
     * @return 组合方式
     */

    static int Divider(int n,int m){
        if(m==1 || n==1){
            return 1;
        }
        else if (n < m) {
            return Divider(n,n);
        }else if (n == m) {
            return Divider(n,n-1) + 1;
            // 注意 n和m相等时只有一种划分方式
        }else {
            // 划分方式为 包含m的划分方式 + 不包含m的划分方式
            return Divider(n-m,m)+Divider(n,m-1);
        }
    }
}

package 第12章_启发式搜索;

import java.util.Scanner;

import static java.lang.Math.abs;

/**
 * 回溯法
 * 12.3 n皇后问题
 * 给出解法 和 个数
 */
public class n_Queues2 {

    static int[] queen = new int[20];
    static int sum = 0;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        nQueens(0,n);
        System.out.println("总共有" + sum + "种解法");
    }

    static boolean PLACE(int n){
        // 确保保证元素不能在同一列
        // abs(queen[i] - queen[n]) == abs(n - i)
        // 用于约束元素不能再同一行且不能再同一条斜线上
        int i;
        for (i = 0; i < n; i++) { // 检查横排和对角线上是否可以防止皇后
            if (queen[i] == queen[n] ||abs(queen[i] - queen[n]) == abs(n - i)){
                return false;
            }
        }
        return true;
    }

    /**
     *
     */
    public static void nQueens(int row,int n){
        int i;
        for (i = 0; i < n; i++) {
            queen[row] = i; // 将皇后摆到当前位置
            if (PLACE(row)){
                if (row == n-1) {
                    show(n);
                }else {
                    nQueens(row+1,n);
                }
            }
        }
    }

    static void show(int n) /* 输出所有皇后的坐标 */
    {
        int i;
        System.out.print("(");
        //i代表行数，queen[i]代表当前行元素所处的列数，
        //注意此处下标是从0开始的

        for(i = 0; i < n; i++)
        {
            System.out.print( queen[i]+1);
        }
        System.out.println(")");
        //每次输出一种解的时候，那么他的解的数量就会增加1
        sum++;
    }

}

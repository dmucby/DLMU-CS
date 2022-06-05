package 第3章_循环和递归;

/**
 * 3.4 打印规律图形数组
 */
public class DiagonalMatrix {
    public static void main(String[] args) {
        int n = 4;
        print(n);
    }

    static void print(int n){
        int k = 1;
        int[][] nums = new int[n+1][n+1];
        for (int i = 1; i <= n ;i++) {
            for (int j = 1; j <= n + 1- i; j++) {
                nums[i - 1 + j][j] = k;
                k++;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                if(nums[i][j] != 0){
                    System.out.print(nums[i][j] + " ");
                }
            }
            System.out.println();
        }
    }
}

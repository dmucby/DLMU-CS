package 第10章_动态规划;

/**
 * 10.2 动态规划解决树塔问题
 */
public class mathTa {
    public static void main(String[] args) {
        int [][] nums = {
                {9},
                {12,15},
                {10,6,8},
                {2,18,9,5},
                {19,7,10,4,16}
        };
        int ans = math(nums);
        System.out.println(ans);
    }

    static int math(int[][] tower){

        int height = tower.length;//数塔高度
        int len = tower[height - 1].length;//数塔底部宽度
        int [][] resultTower = new int[height][len];//结果数塔，存放路径数值和
        int [][] path = new int[height][len];//计算结果数塔生成路径

        //初始化结果数塔
        for(int i = 0; i < len; i++)
        {
            resultTower[height - 1][i] = tower[height - 1][i];
        }
        for(int i = height - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                if (resultTower[i + 1][j] > resultTower[i + 1][j + 1]) {
                    resultTower[i][j] = tower[i][j] + resultTower[i + 1][j];
                    path[i][j] = j;
                } else {
                    resultTower[i][j] = tower[i][j] + resultTower[i + 1][j + 1];
                    path[i][j] = j + 1;
                }
            }
        }
        //打印路径
        System.out.println("最大数值和为" + resultTower[0][0] + "\n");
        System.out.print("路径为：" + tower[0][0]);
        int j = path[0][0];
        for(int i = 1; i <= height - 1; i++){
            System.out.print("->" + tower[i][j]);
            j = path[i][j];
        }
        System.out.println();

        return resultTower[0][0];
    }

}

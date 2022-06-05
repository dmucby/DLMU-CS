package 第12章_启发式搜索;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

/**
 * 不能用 n皇后问题
 */
public class N_Queues {

    static List<List<String>> res = new ArrayList<>();

    public static List<List<String>> solveNQueues(int n){
        //"." 表示空，"Q"表示皇后，初始化棋盘
        char[][] board = new char[n][n];
        for(char[] c:board){
            Arrays.fill(c,'.');
        }
        backtrack(board,0);
        return res;
    }

    /**
     * 从上到下填
     * @param board 初始化的棋盘
     * @param row 当前行数
     */
    public static void backtrack(char[][] board, int row){
        // 每一行都成功放置皇后 返回
        if(row == board.length){
            res.add((charToList(board)));
            return;
        }
        // 记录列 每一列都可能放皇后
        int n = board[row].length;
        // 遍历列
        for (int col = 0; col < n; col++) {
            // 排除危险的格子
            if(!isValid(board,row,col)){
                continue;
            }
            // 放下皇后试错
            board[row][col] = 'Q';
            // 进入下一行
            backtrack(board,row+1);
            // 回溯
            board[row][col] = '.';
        }
    }

    /**
     * 只需判断左上，右上，上方无皇后即可
     * @param board 期盼
     * @param row 行
     * @param col 列
     * @return ture or false
     */
    public static boolean isValid(char[][] board, int row, int col){
        // 判断当前列是否有皇后
        int n = board[row].length;
        for (int i = 0; i < n; i++) {
            if (board[row][col] == 'Q') {
                return false;
            }
        }

        // 检查右上方
        for (int i = row-1,j = col+1; i >= 0 && j < n; i--,j++) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        // 检查左上方
        for (int i = row-1, j = col - 1; i >= 0 && j >=0; i--,j--) {
            if (board[i][j] == 'Q') {
                return false;
            }
        }

        return true;
    }

    public static List<String> charToList(char[][] board){
        List<String> list = new ArrayList<String>();

        for (char[] c : board) {
            list.add(String.valueOf(c));
        }

        return list;
    }

    public static void print(){
        for (int i = 0; i < res.toArray().length; i++) {
            System.out.println(res.toArray()[i]);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        List<List<String>> res1 = new ArrayList<>();
        res1 = solveNQueues(n);
        print();
    }

}

package 第4章_算法与数据结构;

/**
 * 4.3.3 及格名单统计
 */

public class allowHeap {
    public static void main(String[] args) {
        int[] array = {
                1,9,6,8,4,3,7,
                5,2,9,1,3,7,
                8,1,6,7,3,5,4,9
        };
        print(array);
    }

    static void print(int[] array){
        int[] a = new int[10];
        for (int j : array) {
            a[j]++;
        }
        for (int i = 1; i <=9 ; i++) {
            if (a[i] == 3){
                System.out.print(i + " ");
            }
        }
    }
}

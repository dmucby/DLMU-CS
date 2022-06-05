package 第5章_算法优化基本技巧;

/**
 * 5.1.1 算法运算的妙用
 */

public class BestStudent {
    public static void main(String[] args) {
        System.out.println(statics());
    }

    static int statics(){
        int[] a = new int[55];
        int s = 0;
        int num = 0;

        for (int i = 1; i <= 50 ; i++) {
            s = 0;
            for (int j = 0;j <= 4;j++ ){
                if(a[j] >= 90){
                    s++;
                }
                if (s>=3){
                    num++;
                }
            }
        }

        return num;
    }
}

package 第4章_算法与数据结构;

/**
 * 4.5.1 异值平方问题
 */
public class square {
    public static void main(String[] args) {
        print();
    }

    static void print(){
        int[] s = new int[10];
        int k = 0; // 0~9 的个数
        int y1,y2 = 0; // 记录平方数
        int t; // 记录下标
        int num = 0; // 符合要求的个数
        for (int i = 10000; i < 32000; i++ ) {
            y1 = i * i;
            y2 = y1;
            k = 0;
            for (int j = 0; j <=9 ;j++) {
                s[j] = 1;
            }
            for (int j = 0; j <= 9;j++ ) {
                t = y2 % 10;
                y2 = y2 / 10;
                if(s[t] == 1){
                    k++;
                    s[t] = 0;
                }
            }
            if (k == 9) {
                num++;
                System.out.println(num+" " + i + " " + y1 );
            }
        }
    }
}

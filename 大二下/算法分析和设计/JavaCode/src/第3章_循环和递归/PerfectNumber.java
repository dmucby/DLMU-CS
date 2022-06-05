package 第3章_循环和递归;

/**
 * 3.3 找出1000以内的完数
 */
public class PerfectNumber {
    public static void main(String[] args) {
        perfectNumber();
    }

    static void perfectNumber(){
        int s ; // 统计和
        int k ; // 因子数
        for (int i = 1; i <= 1000; i++ ) {
            s = i;
            k = 0;
            for (int j = 1; j < i; j++ ) {
                if(i % j == 0) {
                   s-=j;
                }
            }
            if(s == 0){
                System.out.print(i + " ");
            }
        }
    }
}

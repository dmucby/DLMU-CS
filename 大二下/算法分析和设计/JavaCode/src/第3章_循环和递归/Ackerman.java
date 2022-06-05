package 第3章_循环和递归;

/**
 * 3.5.3 Ackerman函数
 */
public class Ackerman {
    public static void main(String[] args) {
        System.out.println(ackerman(1,9));
    }

    static int ackerman(int m,int n){
        if(m == 0){
            return n+1 ;
        }else if (m > 0 && n == 0) {
            return ackerman(m-1,n);
        }else {
            return ackerman(m-1,ackerman(m,n-1));
        }
    }

}

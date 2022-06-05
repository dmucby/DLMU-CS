package 第5章_算法优化基本技巧;

/**
 * 5.2.1 确定小偷
 */
public class thief {
    public static void main(String[] args) {
        printHelp();
    }

    static void printHelp(){
        int n =0;
        for (int x = 1; x <= 4 ;x++){
            n = 0;
            if(x != 1 ){
                n++;
            }
            if(x == 3) {
                n++;
            }
            if (x == 4) {
                n++;
            }
            if (x != 4) {
                n++;
            }
            if (n == 3){
                System.out.println( x +"  is a thief");
            }
        }
    }
}

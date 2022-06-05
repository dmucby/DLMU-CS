package 第7章_蛮力法;

/**
 * 7.2 数字迷
 */
public class NumProblem {
    public static void main(String[] args) {
        for(int i=1;i<=9;i++) {
            for(int j=1;j<=9;j++) {
                int a=j*(111111);//111111
                int b=a/i;
                if(b/100000==0&&a%i==0){//ABCAB是五位数且DDDDDD能整除A
                    if((b/10)%10==(b/10000)%10&&(b/10000)%10==i) {//1=4=A
                        if(b%10==(b/1000)%10) {//2=5
                            System.out.println("  "+b);
                            System.out.println("x     "+i);
                            System.out.println("="+a);
                        }
                    }
                }
            }
        }
    }
}

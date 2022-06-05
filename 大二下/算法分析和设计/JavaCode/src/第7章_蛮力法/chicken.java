package 第7章_蛮力法;

/**
 * 7.3 百鸡百钱
 */
public class chicken {
    public static void main(String[] args) {
        for(int i=0;i<=34;i++) {
            for(int j=0;j<=300;j++) {
                if(j%3==0&&2*i+5*j-j/3==400&&(100-i-j)>=0) {
                    System.out.println("公鸡a="+(100-i-j));
                    System.out.println("母鸡b="+i);
                    System.out.println("小鸡c="+j);
                    System.out.println();
                }
            }
        }
    }
}

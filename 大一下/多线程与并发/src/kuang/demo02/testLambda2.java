package kuang.demo02;

public class testLambda2 {
    public static void main(String[] args) {
        String s1 = "I love";

        iLove love = (String s) -> System.out.println(s +" you!");

        // 1.去掉参数类型
        iLove love2 = (s) -> System.out.println(s +" you!");
        //2.去掉括号
        iLove love3 = s -> System.out.println(s +" you!");

        love3.love(s1);
    }



}

interface iLove{
    void love(String s);
}


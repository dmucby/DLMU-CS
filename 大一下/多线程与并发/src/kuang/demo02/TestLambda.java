package kuang.demo02;

public class TestLambda {

    //2.静态内部类
    static class like2 implements iLike {

        @Override
        public void lambda() {
            System.out.println("I Like Lambda2!");
        }
    }

    public static void main(String[] args) {
        iLike l =  new like();
        l.lambda();

        l = new like2();
        l.lambda();

        //3.局部内部类
        class like3 implements iLike {

            @Override
            public void lambda() {
                System.out.println("I Like Lambda3!");
            }
        }

        l = new like3();
        l.lambda();

        //4.匿名内部类
        l = new iLike() {
            @Override
            public void lambda() {
                System.out.println("I Like Lambda4!");
            }
        };
        l.lambda();

        //5.lambda简化
        l = () -> {
            System.out.println("I Like Lambda5!");
        };
        l.lambda();

    }



}


interface iLike{
    void lambda();
}

class like implements iLike {

    @Override
    public void lambda() {
        System.out.println("I Like Lambda!");
    }
}
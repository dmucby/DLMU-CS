package kuang.demo01;

public class TestThread3 implements Runnable{
    @Override
    public void run() {
        System.out.println("线程跑起来了！");
    }

    public static void main(String[] args) {

        TestThread3 test = new TestThread3();

        new Thread(test).start();

        for (int i = 0; i <2000 ; i++) {
            System.out.println("sb");
        }
    }
}

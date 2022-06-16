package kuang.demo01;

public class TestThread1 extends Thread{

    @Override
    public void run() {
        for (int i = 0; i < 200;i++) {
            System.out.println("liuChang");
        }
    }

    public static void main(String[] args) {

        TestThread1 test = new TestThread1();

        test.start();

        for (int i = 0; i < 2000 ; i++) {
            System.out.println("sb");
        }
    }

}

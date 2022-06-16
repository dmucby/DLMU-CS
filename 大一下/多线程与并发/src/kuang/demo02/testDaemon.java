package kuang.demo02;

public class testDaemon {
    public static void main(String[] args) {
        God god = new God();
        People people = new People();

        Thread thread = new Thread(god);
        thread.setDaemon(true);

        thread.start();

        new Thread(people).start();

    }
}

class God implements Runnable{

    @Override
    public void run() {
        while (true) {
            System.out.println("上帝保佑！");
        }
    }
}


class People implements Runnable{

    @Override
    public void run() {
        for (int i = 0; i < 36500 ; i++) {
            System.out.println("认真的活着!");
        }
        System.out.println("======和世界拜拜=======");
    }

}

package kuang.demo02;

public class testState {
    public static void main(String[] args) {
       Thread thread = new Thread(()->{
            for (int i = 0; i < 5;i++) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("----------------------");
        });

        Thread.State state = thread.getState();
        System.out.println(state); // NEW

        // 启动
        thread.start();
        state = thread.getState();
        System.out.println(state);
        // RUN

        while (state != Thread.State.TERMINATED) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            state = thread.getState();
            System.out.println(state);
        }

    }

}


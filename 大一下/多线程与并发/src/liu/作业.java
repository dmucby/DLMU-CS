package liu;

import java.util.Scanner;

public class 作业 {
    static class ThreadA implements Runnable {
        Thread thread = new Thread();
        public void run() {
            System.out.println("创建启动");
        }
        public void a(){
            boolean b;int n;
            Scanner scanner = new Scanner(System.in);
            thread.start();
            System.out.println("线程已就绪");
            thread.run();

            b = scanner.nextBoolean();
            if(b==true){
                try {
                    thread.sleep(1000);
                    System.out.println("线程睡眠");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            else{
                thread.suspend();
                System.out.println("线程阻塞");
                thread.resume();
                System.out.println("线程已就绪");
            }
            System.out.println("请输入1或者2");
            n = scanner.nextInt();
            if(n==1){
                thread.stop();
                System.out.println("线程已被杀死");
            }
            else{
                System.out.println("线程正常死亡");
            }
        }
    }
    public static void main(String[] args) {
        ThreadA threada = new ThreadA();
        threada.a();
    }

}


package kuang.better;

public class testPC {
    public static void main(String[] args) {
        synContainer container = new synContainer();

        new producer(container).start();
        new consumer(container).start();
    }
}

class producer extends Thread{
    synContainer container;
    public producer(synContainer  container){
        this.container = container;
    }

    // 生产
    @Override
    public void run() {
        for (int i = 1; i <= 100 ;i++) {
            System.out.println("生产了第"+i+"个产品");
            container.push(new production(i));
        }
    }

}
class consumer extends Thread {
    synContainer container;
    public consumer(synContainer  container){
        this.container = container;
    }
    // 消费
    @Override
    public void run() {
        for (int i = 1; i <= 100; i++) {
            System.out.println("消费了第"+container.pop().id+"个产品");
        }
    }
}

class production{
    int id;

    public production(int id) {
        this.id = id;
    }
}

class synContainer{
    production[] productions = new production[10];

    int count = 0;

    public synchronized void push(production product){
        if(count == productions.length){
            // 生产等待
            try{
                this.wait();
            }catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        productions[count] = product;
        count++;

        this.notifyAll();

    }

    public synchronized production pop(){
        if(count == 0){
            try{
                // 消费等待
                this.wait();
            }catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        count--;
        this.notifyAll();
        return productions[count];
    }
}
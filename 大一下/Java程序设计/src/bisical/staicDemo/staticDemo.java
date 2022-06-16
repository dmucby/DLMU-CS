package bisical.staicDemo;

class Earth{
    int people_name = 70;
}

class People{

    //String name;
    void birth(){
        Earth e = new Earth();
        e.people_name += 1;
        System.out.println("当前人口数"+e.people_name);
    }

}

public class staticDemo {
    public static void main(String[] args) {
        People p1 = new People();
        p1.birth();
        People p2 = new People();
        p2.birth();
    }
}

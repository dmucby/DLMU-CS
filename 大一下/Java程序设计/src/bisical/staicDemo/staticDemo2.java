package bisical.staicDemo;

class Earth1{
    int people_name = 70;
}

class People1{
    String name;
    void birth(Earth1 e){
        e.people_name+=1;
    }
}

public class staticDemo2 {
    public static void main(String[] args) {
        Earth1 e = new Earth1();
        People1 p1 =new People1();
        p1.birth(e);
        System.out.println("当前人口数 "+ e.people_name);
        People1 p2 =new People1();
        p2.birth(e);
        System.out.println("当前人口数 "+ e.people_name);
    }
}

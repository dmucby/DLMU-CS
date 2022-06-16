package bisical.staicDemo;

class Earth2{
    static int people_name = 70;
}

class People2{
    String name;
    void birth(){
        Earth2.people_name+=1;
    }
}

public class staticDemo3 {
    public static void main(String[] args) {
        People2 p1 =new People2();
        p1.birth();
        System.out.println("当前人口数 "+ Earth2.people_name);
        People2 p2 =new People2();
        p2.birth();
        System.out.println("当前人口数 "+ Earth2.people_name);
    }
}

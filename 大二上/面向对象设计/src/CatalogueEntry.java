// 链接 某对象对另一个对象的引用
public class CatalogueEntry {
    private String name;
    private long number;
    private double cost;

    public CatalogueEntry(String nm,long num,double cst){
        name = nm;
        number = num;
        cost = cst;
    }
    public String getName(){return name;}
    public long getNumber(){return number;}
    public double getCost(){return cost;}

}

abstract class Component{
    public abstract double cost();
}

class Part extends Component{
    CatalogueEntry entry;
    public Part(CatalogueEntry e){
        entry = e;
    }
    // 消息传递
    public double cost(){return entry.getCost();}
}


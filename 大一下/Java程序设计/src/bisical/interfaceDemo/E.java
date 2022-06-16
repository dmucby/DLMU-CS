package bisical.interfaceDemo;

interface ShowMessage
{
    void 显示商标(String s);
}

class PC implements ShowMessage
{
    public void 显示商标(String s)
    {
        System.out.println("PC"+s);
    }
}
class TV implements ShowMessage
{
    public void 显示商标(String s)
    {
        System.out.println("TV"+ s);
    }
}
public class E {
    public static void main(String args[])
    {
        ShowMessage sm;
        sm=new TV();
        sm.显示商标("长城牌电视机");
        sm=new PC();
        sm.显示商标("联想奔月5008PC机");
    }

}

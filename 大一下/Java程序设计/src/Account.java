class Account
{  private int money;
    private int getMoney()
    {
        return money;
    }
    public static void main (String[] args)
    {
        Account exa=new Account();
        exa.money=3000;
        int m=exa.getMoney();
        System.out.println("money="+m);
    }
}
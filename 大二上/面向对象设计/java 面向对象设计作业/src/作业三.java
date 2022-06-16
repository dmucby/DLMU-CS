public class 作业三 {
    class 售货机{
        private int ticket=0;
        private int state;
        private int Idle = 0;
        private int No_Ticket_Selected = 1;
        private int Ticket_Selected = 2;

        public 售货机(){
            state = Idle;
        }

        public void coin(int amount,int issue){
            //一直投币 但没选择票
            //投币 选了票 但是不够
            //投币 币投多了 退钱
            if(ticket==0){
                state = No_Ticket_Selected;
                issue = 0;
                return ;
            }
            if (amount >= ticket) {
                issue = amount - ticket;
                // 回归空闲
                state = Idle;
                ticket = 0;
                return ;
            }
            else{
                ticket -=amount;
                issue = 0;
                return ;
            }
        }

        public void ticket(int cost){
            // 选择票
            ticket = cost;
            state = Ticket_Selected;
        }
     }

}

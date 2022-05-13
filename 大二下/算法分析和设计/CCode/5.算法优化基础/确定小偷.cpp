void print(){
	for(int x =1 ;x <= 4; ++x){
		if((x!=1) + (x==3) + (x==4) + (x!=4) == 3){
			printf("%c\n", (x+64));
		}
	}
}
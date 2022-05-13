int A,B,C,D;
int a,b,c,d;
void print(){
	for (int A = 1; A <= 4; ++A)
	{
		for(int B =1;B <= 4; ++B){
			if(A == B){
				continue;
			}
			if(((A==1)+(B==3)) == 1){
				for (int C = 1; C <= 4; ++C)
				{
					if(C == A || C == B){
						continue;
					}
					D = 10 - A - B - C;
					if(D == A||D == B||D == C){
						continue;
					}
					if(((C == 1)+(D == 4))==1 && ((D==2)+(A==3))==1){
						a = A;
						b = B;
						c = C;
						d = D;
					}
				}
			}
		}
	}
	printf("%d %d %d %d\n",a,b,c,d);
}

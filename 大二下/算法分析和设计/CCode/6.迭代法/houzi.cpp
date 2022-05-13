int eat(){
	int ans = 1;
	for (int i = 9; i >= 1; --i)
	{
		ans = 2 *(ans + 1);
	}
	return ans;
}
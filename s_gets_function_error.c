char * s_gets(char * st,int n)
{
	char * ret_val;

	ret_val = fgets(st,n,stdin);
	if(ret_val)
	{
		if(strchr(st,'\n'))
			*st = '\0';
		else
			while(getchar() != '\n')
				continue;
	}
	return ret_val;
}

char * s_gets(char * st,int n)
{
	char * ret_val;
	char * find;
	
	ret_val = fgets(st,n,stdin);
	if(ret_val)
	{
		find = strchr(st,'\n');
		if(find)
			*st = '\0';
		else
			while(getchar() != '\n')
				continue;
	}
	return ret_val;
}

//Note that the two programs is completely different,they are not the same.
//Why is there an error in the toper function?
//Becacuse it can't track the position of the line break,it can't record it's position.


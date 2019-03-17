#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct production
{
	char NT[1];
	char alpha[20];
};

int ret_T(struct production arr[],int i,int j,char cont_T[])	//prod[i].alpha[j]
	{
		int x;
		for(x=0;x<20;x++)
			{
				if( arr[i].alpha[j] != cont_T[x])
					{
						continue;
					}
				else
					return x;
			}
	};
	
int ret_NT(struct production arr[],int i,int j,char cont_NT[])	//prod[i].alpha[j]
	{
		int x;
		for(x=0;x<20;x++)
			{
				if( arr[i].alpha[j] != cont_NT[x])
					{
						continue;
					}
				else
					return x;
			}
	};
	
int ret_par(struct production arr[],int i,char cont_NT[])
	{
		int x;
		for(x=0;x<20;x++)
			{
				if(arr[i].NT[0] != cont_NT[x])
					continue;
				else
					return x;
			}		
	};

int main()
{
	struct production prods[20];
	int count_prod=0,count_NT=0,count_T=1,flag1=0,flag2=0,flag3=0,flag4=0,exit=0,len=0;
	int i=0,j=0,k=0,q=0;
	char temp_prods[20][24],all_NT[20],all_T[20]={"$"};
	int first[20][20],follow[20][20],parse[20][20];
do{
	//initialize values START
	count_prod=0;
	count_NT=0;
	flag1=0;
	flag2=0;
	exit=0;
	i=0;
	j=0;
	k=0;
	len=0;
	for(i=0;i<20;i++)
		{
			for(j=0;j<20;j++)
				{
					prods[i].alpha[j]=' ';
					first[i][j]=0;
					follow[i][j]=0;
				}
			prods[i].NT[0]=' ';
		}
	//initialize values END
	printf("\t\tLL(1) Identifier\n\nInput number of productions : ");
	while(count_prod<1)
		scanf("%d",&count_prod);
	printf("\nTotal Productions OK!!!\n\n");	
	
	printf("Input Productions :\n\twithout any spaces\n\tuse \'+\' for epsilon\n\n");
	for(i=0;i<count_prod;i++)
		{
			printf("%d. ",i+1);
			scanf("%s",temp_prods[i]);
		}
	/*
	printf("\nDisplaying All Temporary");
	for(i=0;i<count_prod;i++)		//display productions
		printf("\n%d. %s",i+1,temp_prods[i]);
	*/
	for(i=0;i<count_prod;i++)
		{
			for(j=0;j<24;j++)
				{
					if(temp_prods[i][j]>=65 && temp_prods[i][j]<=90)
						{
							for(k=0;k<count_NT;k++)
								{
									if(temp_prods[i][j]==all_NT[k])
										{
											flag1=1;
											break;
										}
								}
							if(flag1==0)
								{
									all_NT[count_NT]=temp_prods[i][j];
									count_NT++;
								}
						}
					flag1=0;
				}
		}
		
	printf("\n\nNon Terminals : ");
	for(i=0;i<count_NT;i++)
		printf("%c , ",all_NT[i]);
		
	//+++++++++++++++++++++++++++++++++++++++++++
	for(i=0;i<count_prod;i++)
		{
			for(j=0;j<24;j++)
				{
					if( (temp_prods[i][j]>=97 && temp_prods[i][j]<=122) || temp_prods[i][j]=='+')
						{
							for(k=1;k<count_T;k++)
								{
									if(temp_prods[i][j]==all_T[k])
										{
											flag1=1;
											break;
										}
								}
							if(flag1==0)
								{
									all_T[count_T]=temp_prods[i][j];
									count_T++;
								}
						}
					flag1=0;
				}
		}
		
	printf("\n\nTerminals : ");
	for(i=0;i<count_T;i++)
		printf("%c , ",all_T[i]);
	
	//+++++++++++++++++++++++++++++++++++++++++++
	
	printf("\n\nChecking Syntactical Errors : ");
	for(i=0;i<count_prod;i++)
		{
			for(j=0;j<strlen(temp_prods[i]);j++)
				{
					switch(j)
					{
						case 0:	{
									if(!(temp_prods[i][j]>=65 && temp_prods[i][j]<=90))
										{
											printf("\n\nERRORS IN PRODUCTIONS\nProduction : %d\nCharacter : %d",i+1,j+1);
											return 0;
										}
									break;
									
								}
						case 1:	{
									if(!(temp_prods[i][j]=='-'))
										{
											printf("\n\nERRORS IN PRODUCTIONS\nProduction : %d\nCharacter : %d",i+1,j+1);
											return 0;
										}
									break;
								}
						case 2:	{
									if(!(temp_prods[i][j]=='>'))
										{
											printf("\n\nERRORS IN PRODUCTIONS\nProduction : %d\nCharacter : %d",i+1,j+1);
											return 0;
										}
									break;
								}
						default:{
									if(temp_prods[i][j]=='+' && flag2==0 && j==3)
										{
											flag2=1;
										}
									else
										if(!(temp_prods[i][j]>=65 && temp_prods[i][j]<=90) && !(temp_prods[i][j]>=97 && temp_prods[i][j]<=122) )
											{
												printf("\n\nERRORS IN PRODUCTIONS\nProduction : %d\nCharacter : %d",i+1,j+1);
												return 0;
											}
									break;
								}
					};
					
				}
				flag2=0;
		}
	printf("No errors found\n");
	
	//make objects for productions START
	
	for(i=0;i<count_prod;i++)
		{
			for(j=0;j<strlen(temp_prods[i])+1;j++)
				{
					switch(j)
						{
							case 0:	{
									prods[i].NT[0]=(int)temp_prods[i][0];
									break;
									}
							case 1: {
									break;
									}
							case 2:	{
									break;
									}
							default:{
									prods[i].alpha[j-3]=(int)temp_prods[i][j];
									if(j==strlen(temp_prods[i]) && j!=19)
										prods[i].alpha[j-3]='\0';	
									break;
									}
							
						};
				}
				//printf("\nCopied alpha : %s",prods[i].alpha);
		}
		/*
		printf("\nDisplaying All Temporary");
	for(i=0;i<count_prod;i++)		//display productions
		printf("\n%d. %s",i+1,temp_prods[i]);
		*/
	
	//make objects for productions END
	
	//display objects START
	
	for(i=0;i<count_prod;i++)
		{
			printf("\n%c -> %s",prods[i].NT[0],prods[i].alpha);
		}
	
	//display objects END
	
	//check all defined non terminals, repeated productions START
	
	for(i=0;i<count_prod;i++)
		{
			for(j=0;j<count_prod;j++)
				{
					if(i==j)
						continue;
					if(prods[i].NT[0]==prods[j].NT[0])
						{
							flag3=0;
							for(k=0;k<20;k++)
								{
									if(!(prods[i].alpha[k]==prods[j].alpha[k]))
										{
											flag3=1;
											break;
										}
								}
							if(flag3!=1)
								{
									printf("\nREPEATED PRODUCTIONS");
									return 0;
								}
						}
					flag3=1;	
				}
		}
	for(i=0;i<count_NT;i++)
		{
			flag4=0;
			for(j=0;j<count_prod;j++)
				{
					if(all_NT[i]==prods[j].NT[0])
						flag4=1;
				}
			if(flag4==0)
				{
					printf("\nUndefined Non terminal found");
					return 0;
				}
		}
	
	//check all defined non terminals, repeated productions END
	// calculate first START
	for(i=0;i<count_NT;i++)		//for i non terminals
		{
			for(j=0;j<count_prod;j++)		//for j occurences of ith non terminal
				{
					if(all_NT[i]==prods[j].NT[0])	//if match NT and production
						{
							q=0;
							//if first match is terminal or epsilon
							if(prods[j].alpha[0]>96 && prods[j].alpha[0]<123 || prods[j].alpha[0]=='+')
								{
									first[i][ret_T(prods,j,q,all_T)]+=1;
								}
							//if first match is non terminal
							if(prods[j].alpha[0]>64 && prods[j].alpha[0]<91)
								{
									//if no epsilon, direct transfer first contents
									for(k=0;k<count_T;k++)
										{
											if(all_T[k]=='+')
												break;
										}
									if(k==count_T)
										{
											for(k=0;k<count_T;k++)
												{
													first[i][k] += first[ ret_NT(prods,j,q,all_NT) ][k];
												}
										}
									else
										{
											//if epsilon and next symbol T or NT doesnt have epsilon
											q++;
											if(prods[j].alpha[q]>96 && prods[j].alpha[q]<123)
												{
													first[i][ret_T(prods,j,q,all_T)]+=1;
												}
											if(prods[j].alpha[q]>64 && prods[j].alpha[q]<91)
												{
													for(k=0;k<count_T;k++)
													{
														first[i][k] += first[ret_NT(prods,j,q,all_NT)][k];
													}
													
												}
											//if epsilon and next symbol NT has epsilon	
												//not adding, brains will explode.
										}
									
									
								}
						}
				}
		}
	// calculate first END
	
	//display first table START
	printf("\n\n PRINTING FIRST NOW");
	printf("\n       ");
	for(i=0;i<count_T;i++)
		{
			printf("%7c",all_T[i]);
		}
	for(i=0;i<count_NT;i++)
		{
			printf("\n%7c",all_NT[i]);
			for(j=0;j<count_T;j++)
				{
					printf("%7d",first[i][j]);
				}
		}
	printf("\n\n PRINTING FIRST DONE"); 
	//display first table END
	
	// calculate follow START
	follow[0][0]=1;
	for(i=0;i<count_prod;i++)
		{
			for(j=0;j<strlen(prods[i].alpha);j++)
				{
					if(prods[i].alpha[j] > 64 && prods[i].alpha[j] < 91)
						{
							//if follow is T
							if( j < ( strlen(prods[i].alpha)-1 ) && prods[i].alpha[j+1] > 96 && prods[i].alpha[j+1] < 123)
								{
									follow[ret_NT(prods,i,j,all_NT)][ret_T(prods,i,j+1,all_T)]+=1;
								}
							//if follow is NT
							if( j < ( strlen(prods[i].alpha)-1 ) && prods[i].alpha[j+1] > 64 && prods[i].alpha[j+1] < 91)
								{
									for(k=0;k<count_T;k++)
										{
											follow[ret_NT(prods,i,j,all_NT)][k]+=first[ret_NT(prods,i,j+1,all_NT)][k];
										}									
								}
							//if NT is last symbol
							if( j == ( strlen(prods[i].alpha)-1 ) )
								{
									for(k=0;k<count_T;k++)
										{
											follow[ret_NT(prods,i,j,all_NT)][k] += follow[ret_par(prods,i,all_NT)][k];
										}									
								}
						}
						
				}
		}
	
	// calculate follow END
	
	//display follow table START
	printf("\n\n PRINTING FOLLOW NOW");
	printf("\n       ");
	for(i=0;i<count_T;i++)
		{
			printf("%7c",all_T[i]);
		}
	for(i=0;i<count_NT;i++)
		{
			printf("\n%7c",all_NT[i]);
			for(j=0;j<count_T;j++)
				{
					printf("%7d",follow[i][j]);
				}
		}
	printf("\n\n PRINTING FOLLOW DONE"); 
	//display follow table END
	
	//compute parse table START
	
	for(i=0;i<count_NT;i++)
		{
			for(j=0;j<count_T;j++)
				{
					parse[i][j]=first[i][j];
				}
		}
	//   printf("reached 1");
	for(k=0;k<count_T;k++)
		{
			if(all_T[k]=='+')
				break;
		}
	//printf("reached 2");
	if(k!=count_T)
		{
			for(i=0;i<count_NT;i++)
				{
					//printf("reached 4");
					if(first[i][k]==1)
						{
							//printf("reached 5");
							flag1=0;
							for(j=0;j<count_T;j++)
								{
									//printf("reached 6");
									if(j==k && flag1==0)
										{
											j++;
											flag1=1;
										}
									parse[i][j]+=follow[i][j];
								}
						}
				}
		}
	//printf("reached 3");
	//compute parse table END
	
	//display parse table START
	printf("\n\n PRINTING PARSE NOW");
	printf("\n       ");
	for(i=0;i<count_T;i++)
		{
			printf("%7c",all_T[i]);
		}
	for(i=0;i<count_NT;i++)
		{
			printf("\n%7c",all_NT[i]);
			for(j=0;j<count_T;j++)
				{
					printf("%7d",parse[i][j]);
				}
		}
	printf("\n\n PRINTING FOLLOW DONE"); 
	//display parse table END
	
	//check parse tree for ambiguity START
	
	for(i=0;i<count_NT;i++)
		{
			for(j=0;j<count_T;j++)
				{
					if(parse[i][j]>1)
						{
							printf("\n\nAMBIGUOUS GRAMMAR!!!");
							return 0;
						}
				}
		}
	printf("\n\nGrammar is non ambiguous\n");
	
	//check parse tree for ambiguity END
	
	//check left recursion START
	flag1=-1;
	flag2=-1;
	for(i=0;i<count_prod;i++)
		{
			if(prods[i].alpha[0] > 64 && prods[i].alpha[0] < 91 )
				{
					flag1=ret_NT(prods,i,0,all_NT);
					for(j=0;j<count_prod;j++)
						{
							if(prods[j].NT[0]==all_NT[flag1] && prods[j].alpha[0]>64 && prods[j].alpha[0]<91 && i!=j)							
								{
									flag2=ret_NT(prods,j,0,all_NT);
									if(ret_par(prods,i,all_NT)==flag1 || flag1==flag2 || ret_par(prods,i,all_NT)==flag2)
										{
											printf("\n\nNON AMBIGUOUS GRAMMAR, LEFT RECURSION DETECTED!!!");
											return 0;
										}
								}
						}
				}
		}
	
	//check left recursion END
	
	
	printf("\n\nExit 1/0 ? : ");
	scanf("%d",&exit);
}while(exit!=1);
	return 0;
}

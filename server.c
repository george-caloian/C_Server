#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10001


//returneaza valoarea unui bit
int bit_val (char octet, int bit)
{
	char poz = (1<<bit);
	if((octet&poz)==poz)
		return 1;
	else
		return 0;
}

//returneaza paritatea unui byte
int paritate (char octet)
{
	int prt=0,i;
	for(i=0;i<8;i++)
	{
		if(bit_val(octet,i)==1)
			prt=prt+1;
	}
	return prt%2;
}



//paritate mesaje primite
int paritate_mesaj (char * mes)
{
	int prt=0,i;
	for(i=1;i<=strlen(mes);i++)
		prt=prt+paritate(mes[i]);
	return prt%2;
}

//paritatea pentru mesajele trimise
int paritate_mesaj_aux (char * mes)
{
	int prt=0,i;
	for(i=0;i<strlen(mes);i++)
		prt=prt+paritate(mes[i]);
	return prt%2;
}		
int main(int argc,char *argv[])
{
	msg r,t;
	int i, res,number,nmb,low=0,high=999,j=1000;
	
	printf("[RECEIVER] Starting.\n");
	init(HOST, PORT);
	
	//modul simplu
	if(argc==1)
	{
		for (i = 0; i < COUNT; i++) 
		{
			/* wait for message */
			res = recv_message(&r);
			if (res < 0) {
				perror("[RECEIVER] Receive error. Exiting.\n");
				return -1;
			}
			
	
			if(i==0)
			{
				strcpy(t.payload,"Hello\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
			}	

			if(i==3)
			{
				strcpy(t.payload,"YEY\n");
				t.len=strlen(t.payload+1);
				res=send_message(&t);
				strcpy(t.payload,"OK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
			}	
	
			if(i==4)
			{
				number=(low+high)/2;
				sprintf(t.payload,"%d",number);
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
				
			}
	
			if(strncmp(r.payload,"bigger",6)==0)
			{
			
				low=number;
				number=(low+high)/2;
				sprintf(t.payload,"%d",number);
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
			}
			if(strncmp(r.payload,"smaller",7)==0)
			{
			
				high=number;
				number=(low+high)/2;
				sprintf(t.payload,"%d",number);
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
			}
		
			if(strncmp(r.payload,"succes",6)==0)
			{
				
				j=i;
			}
		
			if(i==j+1)
			{
				strcpy(t.payload,"exit\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
			}

			
			if (res < 0) {
				perror("[RECEIVER] Send error. Exiting.\n");
				printf("%d  -  ERROR\n",i);
				return -1;
			}
		}
	}
		
	//ack
	if(strcmp(argv[1],"ack")==0)
	{
		for (i = 0; i < COUNT; i++)
		{
			// wait for message 
			res = recv_message(&r);
			if (res < 0) {
				perror("[RECEIVER] Receive error. Exiting.\n");
				return -1;
			}
			
			if(i==0)
			{
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				
	
				strcpy(t.payload,"Hello\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
				
				
				
			}
			if(i==2 || i==3)
			{
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
				
				
			}	
		
			if(i==4)
			{
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				
	
				strcpy(t.payload,"YEY\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
				
				
			
			}
			if(i==5)
			{
				strcpy(t.payload,"OK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				
			
			}
			if(i==7)
			{
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				


				number=(low+high)/2;
				sprintf(t.payload,"%d",number);
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				
				
			}
			
			if(strncmp(r.payload,"bigger",6)==0)
			{
			
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				

				low=number;
				number=(low+high)/2;
				sprintf(t.payload,"%d",number);
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				
				
			}
			if(strncmp(r.payload,"smaller",7)==0)
			{
			
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				

				high=number;
				number=(low+high)/2;
				sprintf(t.payload,"%d",number);
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				
			}
		
			if(strncmp(r.payload,"succes",6)==0)
			{
				
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

				
				
				j=i;
			}
		
			if(i==j+1)
			{
				strcpy(t.payload,"ACK\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);

					

				strcpy(t.payload,"exit\n");
				t.len=strlen(t.payload)+1;
				res=send_message(&t);
				
				
			}

			
			if (res < 0) {
				perror("[RECEIVER] Send error. Exiting.\n");
				printf("%d  -  ERROR\n",i);
				return -1;
			}
		
	
			
		}
		
	}
	int in_numb = 0;

	//parity
	if(strcmp(argv[1],"parity")==0)
	{
		for (i = 0; i < COUNT; i++)
		{
			// wait for message 
			res = recv_message(&r);
			if (res < 0) {
				perror("[RECEIVER] Receive error. Exiting.\n");
				return -1;
			}
			
			
			if(r.len==5) //primesc NACK
			{
				
			
				if(in_numb == 1)
				{
					int var = paritate(t.payload[0]);
					int var2 = 1-var;
					t.payload[0]=var2;
				}
				res=send_message(&t); //retrimit
				
			}	
			else
				if(r.len==4) //primesc ACK
				{
					//pur si simplu astept urmatorul mesaj
				}
				else
					if(paritate(r.payload[0])==paritate_mesaj(r.payload)) //daca paritatea este corecta (mesaj necorupt)
					{
						int check=0;						
						
						if(strstr(r.payload+1,"homework"))
						{
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

							
	
							char mes[]="Hello";
							sprintf(t.payload,"%d",paritate_mesaj_aux(mes));
							t.len=1;
							strncat(t.payload,mes,5);
							t.len=strlen(t.payload)+1;
							res=send_message(&t);
				
							
							check=1;
						}

						if(strstr(r.payload+1,"able") || strstr(r.payload+1,"first"))
						{
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

							
	
							check=1;
						}
					
						if(strstr(r.payload+1,"second"))
						{
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

							
	
							char mes2[]="YEY";
							sprintf(t.payload,"%d",paritate_mesaj_aux(mes2));
							t.len=1;
							strncat(t.payload,mes2,3);
							t.len=strlen(t.payload)+1;
							res=send_message(&t);
				
							


							char mes3[]="OK";
							sprintf(t.payload,"%d",paritate_mesaj_aux(mes3));
							t.len=1;
							strncat(t.payload,mes3,2);
							t.len=strlen(t.payload)+1;
							res=send_message(&t);
				
							
							check=1;
						}
						

						if(strstr(r.payload+1,"random"))
						{
							in_numb=1;
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

							
						
							char mes4[10];
							int * numberp= (int *)(&mes4[0]);
							nmb= (low+high)/2;
							*numberp = nmb;						
							sprintf(t.payload,"%d",paritate_mesaj_aux(mes4));
							t.len=strlen(t.payload)+2;
							sprintf(t.payload+1,"%d",nmb);
							
							t.len=strlen(t.payload+1)+2;
							res=send_message(&t);
				
							

							check=1;
						}

						if(strncmp(r.payload+1,"smaller",7)==0)
						{
							in_numb=1;
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

							
															
							high=nmb;	
							char mes5[10];
							int * numberp= (int *)(&mes5[0]);
							nmb= (low+high)/2;
							*numberp = nmb;						
							sprintf(t.payload,"%d",paritate_mesaj_aux(mes5));
							t.len=strlen(t.payload)+2;
							sprintf(t.payload+1,"%d",nmb);
							
							t.len=strlen(t.payload+1)+2;
							res=send_message(&t);
				
							

							check=1;
						}
						if(strncmp(r.payload+1,"bigger",6)==0)
						{
							in_numb=1;
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

						
						
							low=nmb;							
							char mes6[10];
							int * numberp= (int *)(&mes6[0]);
							nmb= (low+high)/2;
							*numberp = nmb;						
							sprintf(t.payload,"%d",paritate_mesaj_aux(mes6));
							t.len=strlen(t.payload)+2;
							sprintf(t.payload+1,"%d",nmb);
							
							t.len=strlen(t.payload+1)+2;
							res=send_message(&t);
				
							


							check=1;
						}
						if(strncmp(r.payload+1,"success",7)==0)
						{
							
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

						
							check=1;
						
							
						}
						if(strstr(r.payload+1,"thanks"))
						{
							strcpy(t.payload,"ACK\n");
							t.len=4;
							res=send_message(&t);

							
	
							char mes[]="exit";
							sprintf(t.payload,"%d",paritate_mesaj_aux(mes));
							t.len=1;
							strncat(t.payload,mes,4);
							t.len=strlen(t.payload)+1;
							res=send_message(&t);
				
							
							check=1;
						}
						if(check==0)
						{	
							
							strcpy(t.payload,"NACK\n");
							t.len=strlen(t.payload)+1;
							res=send_message(&t);

							


						}
		


					}
					else //paritatea este corecta dar totusi mesajul este corupt ( corupt dar cu aceeasi paritate ca mesajul initial)
					{	
						
						strcpy(t.payload,"NACK\n");
						t.len=strlen(t.payload)+1;
						res=send_message(&t);

						


					}
		
			if (res < 0) {
				perror("[RECEIVER] Send error. Exiting.\n");
				printf("%d  -  ERROR\n",i);
				return -1;
			}
		
	
			
		}
		
	}

	
	printf("[RECEIVER] Finished receiving..\n");
	return 0;
	
	

}

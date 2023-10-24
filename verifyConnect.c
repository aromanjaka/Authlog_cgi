#include "auth.h"

int main(){
    char nom[100];
    char passwd[500];
    char* auth = getenv("QUERY_STRING");
    
    sscanf(auth,"%*[^=]=%[^&]&%*[^=]=%[^&]",nom,passwd);
    if(connected(nom)){
		printf("Location: http://www.cgi-scr.com/log/login.cgi?error=connexion\n\n");
	}
    else if(!verifyUser(nom,passwd)){
    	printf("Location: http://www.cgi-scr.com/log/login.cgi?error=incorrect\n\n");
	}
	else{
		connection(nom);
	}
}

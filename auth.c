#include "auth.h"

/*===================Pour La connexion ====================*/
void connection(char* nom){
	int n_user = countUser();
	User* users = malloc(n_user*sizeof(User));
	users = getUsers();
		
	for(int i=0; i<n_user;i++){
		if(strcmp(nom,users[i].name)==0){
			strcpy(users[i].connex,"connected");
		}
	}
		
	FILE* file = fopen("user.txt","w");
	for(int i=0; i<n_user;i++){
		fprintf(file,"%s:%s:%s\n",users[i].name,users[i].pswd,users[i].connex);
	}
		
	fclose(file);
		
	printf("Location: http://www.cgi-scr.com/log/log.cgi?nom=%s&user=allusers\n\n",nom);
}

bool connected(char* nom){
	FILE* file = fopen("user.txt","a+");
	char ligne[300];
	
	if(file==NULL){
		fprintf(stderr,"error open file");
		exit(1);
	}
	while(fgets(ligne,300,file)!=NULL){
		if(strstr(ligne,nom)!=NULL && strstr(ligne,":connected")!=NULL){
			return true;
		}
	}
	return false;
}
void deconnection(char* nom){
	int n_user = countUser();
	User* users = malloc(n_user*sizeof(User));
	users = getUsers();
			
	for(int i=0; i<n_user;i++){
		if(strcmp(nom,users[i].name)==0){
			strcpy(users[i].connex,"disconnected");
		}
	}
			
	FILE* file = fopen("user.txt","w+");
			
	for(int i=0; i<n_user;i++){
		fprintf(file,"%s:%s:%s\n",users[i].name,users[i].pswd,users[i].connex);
	}
			
	fclose(file);
}

/*===================Pour la création d'Utilisateur====================*/
void signInput(char* url){
	char ligne[300];
	
	FILE* file = fopen("signUp.html","r");	
	if(file == NULL){
		fprintf(stderr,"error open file");
		exit(1);
	}
	while(fgets(ligne,300,file)!=NULL){
		if(strstr(ligne,"<h1>")!=NULL && strstr(url,"error=name")!=NULL){
			printf("%s\n",ligne);
			printf("<h3>Cet identifiant est déja pris.</h3>");
		}
		else{
			printf("%s\n",ligne);
		}
	}
	
	fclose(file);
}
void addLog(char* nom, char* passwd){
	FILE* f = fopen("user.txt","a+");
				
	if(f == NULL){
		fprintf(stderr,"error open file");
		exit(1);
	}
				
	fprintf(f,"%s:%s:disconnected\n",nom,passwd);
					
	fclose(f);
}

/*===================Pour Log Utilisateur ====================*/
void loginInput(char* url){
	char ligne[300];
	
	FILE* file = fopen("login.html","r");
	
	if(file==NULL){
		fprintf(stderr,"error open file");
		exit(1);
	}
	while(fgets(ligne,300,file)!=NULL){
		if (strstr(ligne,"<h1>")!=NULL && strstr(url,"error=")==NULL && *url!=0 && strstr(url,"disconnect=")==NULL){
			printf("%s\n",ligne);
			printf("<h3 id=\"succes\">Registration à succès.</h3>");
		}
		else if (strstr(ligne,"<h1>")!=NULL && strstr(url,"error=connexion")!=NULL){
			printf("%s\n",ligne);
			printf("<h3>Utilisateur déjà connecté.</h3>");
		}
		else if (strstr(ligne,"<h1>")!=NULL && strstr(url,"error=incorrect")!=NULL){
			printf("%s\n",ligne);
			printf("<h3>Nom ou mot de passe incorrecte.</h3>");
		}
		else if (strstr(ligne,"<h1>")!=NULL && strstr(url,"error=none")!=NULL){
			printf("%s\n",ligne);
			printf("<h3>Connectez vous à votre identifiant.</h3>");
		}
		else{
			printf("%s",ligne);
		}
	}
	fclose(file);
}
int countUser(){
	int c = 0;
	char ligne[300];
	
	FILE* file = fopen("user.txt","a+");

	if(file==NULL){
		fprintf(stderr,"error open file");
		exit(1);
	}
	while(fgets(ligne,300,file)!=NULL){
		c++;
	}
	fclose(file);
	return c;
}
User* getUsers(){
	int c = countUser();
	int i=0;
	char ligne[300];
	User* users = malloc(c*sizeof(User));
	
	FILE* file = fopen("user.txt","a+");
	
	if(file==NULL){
		fprintf(stderr,"error open file");
		exit(1);
	}
	while(fgets(ligne,300,file)!=NULL){
		sscanf(ligne,"%[^:]:%[^:]:%s",users[i].name,users[i].pswd,users[i].connex);
		i++;
	}
	fclose(file);
	return users;
}
bool inUsers(char* nom){
	int c=countUser();
	User* users = malloc(c*sizeof(User));
	users = getUsers();
	
	for(int i=0; i<c; i++){
		if(strcmp(nom,users[i].name)==0){
			return true;
		}
	}
	return false;
}
bool verifyUser(char* nom, char* passwd){
	int c=countUser();
	User* users = malloc(c*sizeof(User));
	users = getUsers();
	
	for(int i=0; i<c; i++){
		if(strcmp(nom,users[i].name)==0 && strcmp(passwd,users[i].pswd)==0){
			return true;
		}
	}
	return false;
}

/*===================Pour la Date ====================*/
bool isB(int y){
	return (y%4==0 && y%100!=0);
}
int intMois(char* m){
	char mois[12][4] = {"Jan","Fev","Mar","Avr","Mai","Jun","Jui","Aou","Sep","Oct","Nov","Dec"};
	int i=0;
	while(strcmp(mois[i],m)!=0){
		i++;
	}
	return i;
}
int jourDuMois(int m,int y){
	if(m==1){
		if (isB(y)) return 29 ; 
		else return 28 ;
	}
	else if((m%2==0 && m <=6) || (m%2!=0 && m > 6)){
		return 31;
	}
	else{
		return 30;
	}
}
char* volana(char* m){
	int i=0;
	char mois[12][4] = {"Jan","Fev","Mar","Avr","Mai","Jun","Jui","Aou","Sep","Oct","Nov","Dec"};
	char* v[] = {"Janoary","Febroary","Martsa","Aprily","Mey","Jona","Jolay","Aogositra","Septambra","Oktobra","Novambra","Desambra"};
	for(; i<12; i++){
		if(strcmp(mois[i],m)==0){
			break;
		}
	} 
	return v[i];
}
char* andro(int y,char* m,int jour){
	char* weekday[] = {"Alatsinainy","Talata","Alarobia","Alakamisy","Zoma","Sabotsy","Alahady"};
	
	int mo = intMois(m);
	
	int l = 6;
	int k = 0;
	for(int a=2023; a<=y; a++){
		for(int i=0; i<=mo; i++){
			if(i==mo) k=jour ; 
			else k=jourDuMois(i,a);
			for(int j=1 ; j<=k; j++){
				l++;
			}
		}
	}
	l = (l-1)%7;
	return weekday[l];
}

/*===================Pour la Barre de navigation====================*/
char* caseChange(char* ch){
	for(int i=0; i<strlen(ch); i++){
		ch[i] = tolower(ch[i]);
	}
	return ch;
}
void displayBar(char* nom){
	printf("<nav>");
	printf("<form action=\"log.cgi\" method=\"get\">");
	printf("<input type=\"text\" name=\"nom\" value=\"%s\" hidden>",nom);
	printf("<input id=\"nom\" type=\"text\" name=\"user\" placeholder=\"Nom de l'utilisateur\">");
	printf("<input class=\"submit\" type=\"submit\" value=\"Rechercher\">");
	printf("<button class=\"submit\"><a href=\"log.cgi?nom=%s&user=allusers\">All</a></button>",nom);
	printf("</form>");
	printf("<div id=\"info\"><div id=\"identifier\"><abbr title=\"User : %s\">%c</abbr></div>",nom,toupper(nom[0]));
	printf("<button class=\"submit\"><a href=\"login.cgi?disconnect=%s\">Log out</a></button></div>",nom);
	printf("</nav>");		
}

/*===================Pour la Page auth.log ====================*/
void authLogPage(char* nom,char* u,Session*s,int c,int page){
	char ligne[500];
	FILE * file = fopen("logzzz.html","r");
    
	if(file==NULL){
		printf("error");
		exit(0);
	}
		
	while(fgets(ligne,500,file) != NULL){
		if(strstr(ligne,"<body>")){
			printf("%s\n",ligne); /// afficher <body>
				
			displayBar(nom);
			if(*u!=0){
				if(searchUser(s,c,u)) {
					printf("<table><tr id=\"en-tete\"><td>Time session</td><td>Type session</td><td>User</td></tr>");
				}
				else printf("<h1>Aucun utilisateur du nom \"%s\" n'a ouvert de session</h1>\n",u);
						
				sessionTable(nom,s,c,page);
					
				lienPagination(c,nom,u);
			}
		}
		else{
			printf("%s\n",ligne);
		}
	}
	free(s);
	fclose(file);
}

/*===================Pour la Session ====================*/
char* getUser(){
	char* t = malloc(100*sizeof(char));
	*t = 0;
	char* u = malloc(100*sizeof(char));
	t = getenv("QUERY_STRING");
	
	if(*t == 0){
		u = t;
	}
	else{
		sscanf(getenv("QUERY_STRING"),"nom=%*[^&]&user=%[^&]",u);
	}
	return u;
}
bool searchUser(Session* s,int c,char* u){
	for(int i=0; i<c; i++){
		if(strstr(caseChange(s[i].user),caseChange(u))!=NULL){
			return true;
		}
	}
	if(strcmp(u,"allusers") == 0){
		return true;
	}
	return false;
}
int countSession(char* u){
    FILE * file = fopen("/var/log/auth.log.1","r");
    int c = 0;
    char ligne[300];
	char* user = malloc(60*sizeof(char));
    while(fgets(ligne,300,file)!=NULL){
		sscanf(ligne,"%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s\n",user);
        if((strstr(ligne,"session opened")!= NULL || strstr(ligne,"session closed") != NULL) && ((strstr(caseChange(user),caseChange(u))!=NULL && *u!=0) || strcmp(u,"allusers") == 0)){
            c++;
        }
    }
    fclose(file);
    return c;
}
Session* getSession(char* u){
    int c = countSession(u);
    Session * s = malloc(c*sizeof(Session));
    int i = 0;
    char ligne[300];
    FILE * file = fopen("/var/log/auth.log.1","r");
	char* user = malloc(60*sizeof(char));
    
    if(file==NULL){
		exit(0);
	}	
    while(fgets(ligne,300,file)!=NULL){
    	sscanf(ligne,"%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s\n",user);
        if((strstr(ligne,"session opened") || strstr(ligne,"session closed")) && ((strstr(caseChange(user),caseChange(u))!=NULL && *u!=0)|| strcmp(u,"allusers") == 0)){
			sscanf(ligne,"%s %d %s %*s %*s %*s %*s %s %*s %*s %s\n", s[i].mois, &s[i].jour, s[i].heure, s[i].session, s[i].user);
			i++;
        }
    }
    fclose(file);
    return s;
}

/*===================Pour le tableau ====================*/
void sessionTable(char* nom,Session*s,int c,int page){
	char class[50];
	for(int i=page*LINE_SHOWN; i<page*LINE_SHOWN+LINE_SHOWN && i<c ;i++){
		if(strcmp(s[i].session,"opened")==0){
			strcpy(class,"class=\"open\"");
		}
		else{
			strcpy(class,"class=\"close\"");
		}
		printf("<tr %s>\n",class);						
		printf("\t<td>%s %d %s %s </td>\n",andro(2023,s[i].mois,s[i].jour),s[i].jour,volana(s[i].mois),s[i].heure);
		printf("\t<td> %s </td>\n",s[i].session);
		printf("\t<td><a href=\"log.cgi?nom=%s&user=%s\"> %s </a></td>\n",nom,s[i].user,s[i].user);
		printf("</tr>\n");
	}
}

/*===================Pour la Pagination ====================*/
int getNum(){
	int n = 0;
	char* url = malloc(50*sizeof(char));
	url = getenv("QUERY_STRING");
	sscanf(url,"nom=%*[^&]&user=%*[^=]=%d",&n);
	return n;
}
void lienPagination(int c,char* nom,char* u){
	int i=0;
	int j=0;
	char class[30];
			
	printf("</table>");
			
	int n_page = (c/LINE_SHOWN);
			
	if((c%LINE_SHOWN)!=0 && c/LINE_SHOWN > 0){
		n_page++;
	}
	
	if(getNum()%10==0 && getNum()!=0){
		i=getNum()-1;
		j = i+11;
	}
	else{
		i = (getNum()+1) - ((getNum()+1)%10);
		j = i+10;
	}
	
	if(getNum()-(getNum()%10) > 0){
		printf("<a href=\"log.cgi?nom=%s&user=%s&p=%d\" class=\"page boite\">«</a> ",nom,u,(getNum()-(getNum()%10))-10);
	}
	if(getNum() > 0){
		printf("<a href=\"log.cgi?nom=%s&user=%s&p=%d\" class=\"page boite\"> < </a> ",nom,u,getNum()-1);
	}
	
	for(; i<j && i<n_page; i++){
		if(getNum()==i){
			strcpy(class,"page inpage");
		}
		else{
			strcpy(class,"page");
		}
		if(i%10==0 && i!=0){
			printf("<a href=\"log.cgi?nom=%s&user=%s&p=%d\" class=\"%s\">%d</a> ",nom,u,i-10,class,i+1);
		}
		else {
			printf("<a href=\"log.cgi?nom=%s&user=%s&p=%d\" class=\"%s\">%d</a> ",nom,u,i,class,i+1);
		}
	}
	
	if(getNum()+1 < n_page){
		printf("<a href=\"log.cgi?nom=%s&user=%s&p=%d\" class=\"page boite\"> > </a> ",nom,u,getNum()+1);
	}
	if(getNum()+10 < n_page){
		printf("<a href=\"log.cgi?nom=%s&user=%s&p=%d\" class=\"page boite\">»</a> ",nom,u,(getNum()-(getNum()%10))+10);
	}
}

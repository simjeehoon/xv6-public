#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NULL 0

char userID[16][32];
char pwdID[16][32];
int idcnt=0;

char *getl(int fd, char *dst){
	static int n=0, i=0;
	static char buf[512];
	int di=0;
	while(1){
		if(i>=n){
			i = 0;
			n = read(fd, buf, sizeof(buf));
			if(n <= 0){
				if(di == 0)
					return NULL;
				dst[di] = '\0';
				return dst;
			}
		}
		while(i<n){
			if(buf[i] == '\n'){
				dst[di] = '\0';
				i++;
				return dst;
			}
			else{
				dst[di++] = buf[i++];
			}
		}
	}
}

int pickidpwd(const char* line, char *id, char *pwd){
	if(line == NULL)
		return -1;
	if(line[0] == '\0')
		return -1;
	char *space = strchr(line, ' ');
	if(space == NULL)
		return -1;
	*space = '\0';
	strcpy(id, line);
	strcpy(pwd, space+1);
	return 0;
}

int check_idpw(){
	char id[64];
	char pwd[64];
	int i;

	printf(1, "Username: ");
	getl(0, id);
	printf(1, "Password: ");
	getl(0, pwd);

	//check existence
	for(i=0;i<idcnt;i++){
		if(strcmp(userID[i], id) == 0){//match id
			if(strcmp(pwdID[i], pwd) == 0){//match pwd
				return 0;
			}
		}
	}
	return 1;
}

void get_user_list(){
	int fd;
	char buf[513];
	int i;

	fd = open("list.txt", O_RDONLY);
	if(fd < 0){
		printf(1,"file open error\n");
		exit();
	}

	char *res;
	//load id, pwd list
	for(i = 0 ; i < 16 ; i++){
		res = getl(fd, buf);
		if(pickidpwd(res, userID[i], pwdID[i]) == -1){
			break;
		}
		idcnt++;
	}
	close(fd);
}

char *argv[] = {"sh", 0};
int
main(void){
	int pid;
	int wpid;
	get_user_list();
	while(check_idpw())
		printf(1,"\nWrong Username or Password\n");
	pid = fork();
	if(pid < 0){//fork error
		printf(1, "ssu_login: fork failed\n");
		exit();
	}
	if(pid == 0){//child
		exec("sh", argv);
		printf(1,"ssu_login: exec sh failed\n");
		exit();
	}
    while((wpid=wait()) >= 0 && wpid != pid){
      printf(1, "zombie!\n");
	}
	return 0;
}

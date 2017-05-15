#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
regex_t regex;
int reti,m,n,p,q,r;

int main()
{  
	// char test[20]="12231";

	reti=regcomp(&regex,"[[:digit:]]",0);
	m=regcomp(&regex,"+[[:digit:]]",0);
	n=regcomp(&regex,"-[[:digit:]]",0);
	p=regcomp(&regex,"[[:digit:]].[[:digit:]]",0);
	q=regcomp(&regex,"-[[:digit:]].[[:digit:]]",0);
	r=regcomp(&regex,"+[[:digit:]].[[:digit:]]",0);
	
	if(reti && m && n && p && q && r){
		printf("Failed to compile the regex\n");
		exit(1);
	}

	reti=regexec(&regex,"122",0,NULL,0);	
	m=regexec(&regex,"12231",0,NULL,0);
	n=regexec(&regex,"12231",0,NULL,0);
	p=regexec(&regex,"12231",0,NULL,0);
	q=regexec(&regex,"12231",0,NULL,0);
	r=regexec(&regex,"12231",0,NULL,0);
	if(!reti|| !m || !n || !p || !q || !r){
		printf("Match\n");
	}else if (reti == REG_NOMATCH){
		printf("No match\n");
	}
}


// [[:digit:]]
// +-[[:d:]]
// [[d]].[[d]]
// -+[[d]].[[d]]



	// int size;
	// printf("Enter the order of the matrix\n");
	// scanf("%d",&size);

	// // initialize the size of the matrix
	// float matrix[size][size],temp;

	// printf("Enter the matrix\n");
	// for(i=0;i<size ;i++){
	// 	for(j=0;j<size;j++){
	// 		printf("matrix[%d][%d] : ",i,j);
	// 		fgets("%f",&temp);
	// 		if(isdigit(temp)){

	// 		}
	// 	}
	// }


// ((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?

 // [-+]?[0-9]*\.?[0-9]+

// (\\+|-)?[[:digit:]]*(\\.)?([[:digit:]]+)?

//  #include <regex.h>        
// regex_t regex;
// int reti;
// char msgbuf[100];

// /* Compile regular expression */
// reti = regcomp(&regex, "^a[[:alnum:]]", 0);
// if (reti) {
//     fprintf(stderr, "Could not compile regex\n");
//     exit(1);
// }

// /* Execute regular expression */
// reti = regexec(&regex, "abc", 0, NULL, 0);
// if (!reti) {
//     puts("Match");
// }
// else if (reti == REG_NOMATCH) {
//     puts("No match");
// }
// else {
//     regerror(reti, &regex, msgbuf, sizeof(msgbuf));
//     fprintf(stderr, "Regex match failed: %s\n", msgbuf);
//     exit(1);
// }
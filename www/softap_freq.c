#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <poll.h>
#include <sys/utsname.h>
#include <pthread.h>

#include "../wifi/list_network.h"
#include "../utility/string_ext.h"
#include "../utility/list.h"
#include "../wifi/operate.h"
#include "../utility/common_web.h"

void parse(char *str, char * freq) {
	int i=0;
	char * p = str;
	char *last;

	while(p != NULL) {
		if(i++ == 0) {
			p = strtok_r(p, "&", &last);
		} else {
			p = strtok_r(NULL, "&", &last);
		}

		if (p == NULL) break;
		if(str_startsWith(p, "freq=")) {
			strcpy(freq, p+strlen("freq="));
		}
	}

	ALOGD("parse: freq=%s", freq);
}

int main(void) {
	char * lenstr;
	char input[512];
	long len;
	char freq_pre[64] = {0};
	char freq[64] = {0};
	char cmdBuf[256];

	printf("Content-Type:text/html\n\n");

	printf("<TITLE>set password</TITLE>\n");
	lenstr = getenv("CONTENT_LENGTH");

	if(lenstr == NULL || sscanf(lenstr,"%ld",&len)!=1 ) {
		//printf("<P> wrong");
	} else {
		int i=0;
		fgets(input, len+1, stdin);
		ALOGD("recive post: %s\n", input);
		parse(input, freq);

		//lollipopConfInit();
		//getLollipopConf("softap_freq", freq_pre);
		//setLollipopConf("softap_freq", freq);
		//saveLollipopConf();
		//lollipopConfDeinit();
		if (strcmp(freq_pre, freq)) {
			system("/system/bin/reboot");
		}
	}
	
	printf("<meta HTTP-EQUIV=refresh Content=\'0;url=settings.cgi\'>");
	return 0;
}

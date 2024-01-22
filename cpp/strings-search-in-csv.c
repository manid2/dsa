/**
 * Search substring in comma separated values
 */

#include <stdio.h>
#include <string.h>

char *_strstr_csv(char *s, char *t)
{
	char d = ',';
	char nt = strlen(t);
	while (s && *s) {
		int nc;
		char p[12];
		char *pc = strchr(s, d);
		if (pc)
			nc = pc - s;
		else
			nc = strlen(s);
		strncpy(p, s, nc);
		p[nc] = '\0';
		if (!strncmp(p, t, nt)) {
			printf("found: p: %s t: %s nc: %d nt: %d\n", p, t, nc,
			       nt);
			return s;
		}
		s += nc + 1;
	}
	printf("not found: t: %s\n", t);
	return NULL;
}

int main(int argc, char *argv[])
{
	char port_list[] = "Ethernet1,Ethernet2,Ethernet3,Ethernet4,"
	                   "Ethernet6,Ethernet7,Ethernet8,Ethernet9,"
	                   "Ethernet10";
	char new_port3[] = "Ethernet3";
	char new_port6[] = "Ethernet6";
	char new_port10[] = "Ethernet10";
	char new_port19[] = "Ethernet19";
	char *new_ports[] = {new_port3, new_port6, new_port10, new_port19};
	for (int i = 0; i < 4; i++) _strstr_csv(port_list, new_ports[i]);
	return 0;
}

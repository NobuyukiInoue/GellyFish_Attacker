#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#define	LEN_IPv4	4

void print_usage_and_exit(char *[]);
void ipv4_addr_generate(int[]);
int portNum_generate();
void ipv4_addr_print(int[], int);
int attack_main(char[], int);
unsigned int sleepTime_genarate();
int datetime_print();
int datetime_print_usec();
int point_datetime_print_usec(int year, int month, int day, int hour);

int main(int argc, char *argv[])
{
	int attackCount;
	int ret_val;
	//int year, month, day, hour;

	if (argc < 2) {
		print_usage_and_exit(argv);
	}

	if (argc >= 3) {
		attackCount = atoi(argv[2]);

		if (attackCount < 0) {
			print_usage_and_exit(argv);
		}
	}
	else {
		attackCount = -1;
	}

	unsigned int now = (unsigned int)time( 0 );
	srand( now );

	ret_val = attack_main(argv[1], attackCount);

	printf("%s is finnished.", argv[0]);
	return ret_val;
}

void print_usage_and_exit(char *argv[])
{
	printf("Ussage %s target_HostName [AttackCount]\n", argv[0]);
	exit(1);
}

void ipv4_addr_generate(int addr[4])
{
	int i;

	for (i = 0; i < LEN_IPv4; i++) {
		addr[i] = rand()%255 + 1;
	}
}

int portNum_generate()
{
	int portNum;

	do {
		portNum = rand()%65535;
	} while (portNum <= 9000);

	return portNum;
}

void ipv4_addr_print(int addr[4], int portNum)
{
	printf("%d.%d.%d.%d:%d", addr[0], addr[1], addr[2], addr[3], portNum);
}

int attack_main(char targetHost[], int attackCount)
{
	char *requestArray[] = {
		"/?query=any%0D%0ASet-cookie%3A+Tamper%3Dbc537fbf-c202-433d-b9f4-189532af91ce",
		"/robots.txt?query=any%0D%0ASet-cookie%3A+Tamper%3Dcd134cf5-9995-456c-8f22-19899a62d17e",
		"/robots.txt?query=any%3F%0D%0ASet-cookie%3A+Tamper%3Dcd134cf5-9995-456c-8f22-19899a62d17e",
		"/?query=any%3F%0D%0ASet-cookie%3A+Tamper%3Dbc537fbf-c202-433d-b9f4-189532af91ce",
		"/robots.txt?query=any%0ASet-cookie%3A+Tamper%3Dcd134cf5-9995-456c-8f22-19899a62d17e",
		"/?query=any%0ASet-cookie%3A+Tamper%3Dbc537fbf-c202-433d-b9f4-189532af91ce",
		"/?query=any+%251%21s%252%21s%253%21s%255%21s%251%21s%252%21s%253%21s%255%21s%251%21s%252%21s%253%21s%255%21s%251%21s%252%21s%253%21s%255%21s",
		"/?query=any+%25n%25s%25n%25s%25n%25s%25n%21s%25n%25s%25n%25s%25n%25s%25n%21s%25n%25s%25n%25s%25n%25s%25n%21s%25n%25s%25n%25s%25n%25s%25n%21s",
		"/?query=any%3F%0D%0ASet-cookie%3A+Tamper%3Dcd134cf5-9995-456c-8f22-1099a62d17e%0D%0A",
		"/?query=Set-cookie%3A+ramper%3D98e2015e-71f8-44bb-ad04-c7d79151e298",
		"/sitemap.xml?query=any%3F%0D%0ASet-cookie%3A+Tamper%3D98e2015e-71f8-44bb-ad04-c7d79151e298%0D%0A",
		"/?query=%40",
		"/?query=%2B",
		"/?query=%00",
		"/?query=%7c",
		"/?query=%40",
		"/?query=any"
		"/?query=any%3F%0ASet-cookie%3A+Tamper%3Dbc537fbf-c202-433d-b9f4-189532af91ce",
		"/?p=31",
		"/?p=32",
		"/?p=35",
		"/?p=38",
		"/?p=39",
		"/?cat=1",
		"/index.php?format=xml&rest_route=%2Findex.php&url=http%3A%2F%2Fiteenslab.littlestar.jp%2Fhackersoucing%2F%3Fp%3D1",
		"/index.php?rest_route=%2Foembed%2F1.0%2Fembed&url=c%3A%5C",
		"/wp-comments-post.php?query=thishouldnotexistandhopefullyitwillnot"
		"/index.php?format=..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5C..%5CWindows%5Csystem.ini&rest_route=%2Foembed%2F1.0%2Fembed&url=http%3A%2F%2Fiteenslab.littlestar.jp%2Fhackersoucing%2F%3Fp%3D1",
		"/index.php?format=c%3A%2FWindows%2Fsystem.ini&rest_route=%2Foembed%2F1.0%2Fembed&url=http%3A%2F%2Fiteenslab.littlestar.jp%2Fhackersoucing%2F%3Fp%3D1",
		"/?query=c%3A%2FWindows%2Fsystem.ini",
		"/index.php?format=..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2FWindows%2Fsystem.ini&rest_route=%2Foembed%2F1.0%2Fembed&url=http%3A%2F%2Fiteenslab.littlestar.jp%2Fhackersoucing%2F%3Fp%3D1",
		"/?query=..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2FWindows%2Fsystem.ini",
		"/index.php?format=c%3A%5CWindows%5Csystem.ini&rest_route=%2Foembed%2F1.0%2Fembed&url=http%3A%2F%2Fiteenslab.littlestar.jp%2Fhackersoucing%2F%3Fp%3D1",
		"/?query=c%3A%5CWindows%5Csystem.ini",
		"/wp-content/themes/maxstore/css/bootstrap.css?ver=..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F",
		"/wp-content/themes/maxstore/css/bootstrap.css?ver=WEB-INF%2Fweb.xml",
		"/wp-comments-post.php",
		"/wp-content/themes/maxstore/css/bootstrap.css?ver=thishouldnotexistandhopefullyitwillnot",
		"/wp-content/themes/maxstore/css/font-awesome.min.css?ver=c%3A%2FWindows%2Fsystem.ini",
		"/wp-content/themes/maxstore/css/font-awesome.min.css?ver=..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2FWindows%2Fsystem.ini",
		"/wp-content/themes/maxstore/css/font-awesome.min.css?ver=%2Fetc%2Fpasswd",
		"/wp-comments-post.php",
		"/wp-content/themes/maxstore/css/font-awesome.min.css?ver=..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2F..%2Fetc%2Fpasswd",
		"/wp-content/themes/maxstore/css/font-awesome.min.css?ver=%2FWEB-INF%2Fweb.xml",
		"/wp-content/themes/maxstore/css/font-awesome.min.css?ver=%5CWEB-INF%5Cweb.xml"
	};
	int sendBytes[] = { 32, 48, 64, 72, 96, 128, 144, 192, 224, 240, 256, 512, 1024, 1200, 1216, 1220, 1320, 1440, 1472, 1500, 1512, 1518, 1582, 2048, 4096, 16384, 32268, 65535};
	int addr[LEN_IPv4];
	int i;
	int requestArray_size;
	int sendBytes_size;
	int LOOP_FLAG;

	requestArray_size = sizeof(requestArray) / sizeof(requestArray[0]);
	sendBytes_size = sizeof(sendBytes) / sizeof(sendBytes[0]);

	printf("TargetHost is %s\n", targetHost);

	if (attackCount == -1) {
		LOOP_FLAG = 1;
	}
	else
	{
		LOOP_FLAG = 0;
	}

	for (i = 0; i < attackCount || LOOP_FLAG; i++)
	{
		ipv4_addr_generate(addr);

		usleep( sleepTime_genarate()*1000 );
		//datetime_print_usec();

		point_datetime_print_usec(2018, 8, 2, 11);
		printf(" %s%s from ", targetHost, requestArray[rand()%requestArray_size]);
		ipv4_addr_print(addr, portNum_generate());
		printf(" send %d bytes.\n", sendBytes[rand()%sendBytes_size]);
	}

	return i;
}

unsigned int sleepTime_genarate()
{
	return(rand()%1000 + 1);
}

int datetime_print()
{
	char date[64];
	time_t t = time(NULL);
	//strftime(date, sizeof(date), "%Y/%m/%d %a %H:%M:%S", localtime(&t));
	strftime(date, sizeof(date), "%Y/%m/%d %H:%M:%S", localtime(&t));
	printf("%s", date);

	return 0;
}

int datetime_print_usec()
{
	struct timeval ct;
	struct tm *t;

	gettimeofday( &ct, NULL );
	t = localtime(&ct.tv_sec);

	printf("%04d-%02d-%02d %02d:%02d:%02d.%03d",
		t->tm_year+1900,
		t->tm_mon+1,
		t->tm_mday,
        t->tm_hour,
		t->tm_min,
		t->tm_sec,
        	(int)ct.tv_usec/1000
	);

	return 0;
}

int point_datetime_print_usec(int year, int month, int day, int hour)
{
	struct timeval ct;
	struct tm *t;

	gettimeofday( &ct, NULL );
	t = localtime(&ct.tv_sec);

	printf("%04d-%02d-%02d %02d:%02d:%02d.%03d",
		year, month, day, hour,
		t->tm_min,
		t->tm_sec,
        	(int)ct.tv_usec/1000
	);

	return 0;

}

int isDelimiter(char p, char delim){
  return p == delim;
}

int split(char *dst[], char *src, char delim){
	int count = 0;

	for(;;) {
		while (isDelimiter(*src, delim)){
			src++;
		}

		if (*src == '\0') {
			break;
		}

	    dst[count++] = src;

		while (*src && !isDelimiter(*src, delim)) {
			src++;
		}

		if (*src == '\0') {
			break;
		}

		*src++ = '\0';
		}

	return count;
}
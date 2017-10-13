#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <libkern/OSAtomic.h>

static double dtime(void);
static void bubble_sort(int64_t *a, long n);
static int verify_sort(int64_t *a, long n);
static double measure_sort(int64_t *a, long n);
extern int main(void);

static double dtime()
{
	double q;
	struct timeval tnow;

	gettimeofday(&tnow,NULL);
	q = (double)tnow.tv_sec + (double)tnow.tv_usec * 1.0e-6;

	return q;
}

static void bubble_sort(int64_t *a, long n) {
	long i,j;
	for(i=0; i<n; i++) {
		long x,y,z=a[0];
		for(j=0; j<n-1-i; j++) {
			int c;
			x=z;
			y=a[j+1];
			c=(x>y);
			a[j]=c?y:x;
			z=c?x:y;
		}
		a[n-1-i]=z;
	}
}

static int verify_sort(int64_t *a, long n) {
	long i;
	for(i=0; i<n-1; i++) {
		/* printf("%016llX\n",a[i]); */
		if(a[i]>a[i+1]) {
			return -1;
		}
	}
	return 0;
}

static double measure_sort(int64_t *a, long n) {
	double start_time,end_time,elapsed_time;
	
	int i;
	for (i = 0;  i < n;  i++) {
		long l0, l1;
		l0 = rand();
		l1 = l0*0x80000000l+rand();
		a[i] = l1;
	 }

	OSMemoryBarrier();
	start_time=dtime();
	OSMemoryBarrier();

	bubble_sort(a,n);

	OSMemoryBarrier();
	end_time=dtime();

	elapsed_time=end_time-start_time;
	return !verify_sort(a,n)?elapsed_time:NAN;
}

extern int main() {
	static const long n[] = {
		500l, 2000l, 4000l, 6000l, 8000l, 10000l
	};
	long i=0;
	int64_t *m;
	if(!(m=valloc(sizeof(int64_t)*n[sizeof(n)/sizeof(n[0])-1]))) {
		fputs("memory allocation failed\n",stderr);
		return EXIT_FAILURE;
	}

	for(i=0; i<sizeof(n)/sizeof(n[0]); i++) {
		long j=4;
		printf("%ld,",n[i]); fflush(stdout);
		do {
			double t=measure_sort(m,n[i]);
			printf("\t%f,",t); fflush(stdout);
		} while(--j);
		putchar('\n');
	}

	free(m);

	exit(EXIT_SUCCESS);
}

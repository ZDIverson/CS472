#include <stdio.h>
#include <string.h>


#define cpuid(a,b,c,d) __asm__( "cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(a), "b"(b), "c"(c), "d"(d))
#define b(val, base, end) ((val << (__WORDSIZE-end-1)) >> (__WORDSIZE-end+base-1))



int main(int argc, char **argv)
{
	unsigned long eax;
	unsigned long ebx;
	unsigned long ecx;
	unsigned long edx;
	unsigned long value;
	unsigned long vlaue2;
// GenuineIntel
	cpuid(0,0,0,0);
	printf("identification: \"%.4s%.4s%.4s\"\n", (char *)&ebx, (char *)&edx, (char *)&ecx);

// L1 Data Cache Size
//pg 760
 cpuid(0x04,0,1,0);
 value = (b(ebx, 22,31) +1 ) * (b(ebx,12,21)+1) * (b(ebx, 0,11)+1) * (b(ecx,0,31)+1);
 printf("L1 Data Cache Size: %ld\t\t", value);

 cpuid(0x80000006, 0, 0, 0);
 printf("L1 Data Line Info Size: %ld (in bytes)\n\n", b(ecx, 0,7));


//	L1 Instruction Cache size
cpuid(0x04, 0,2 ,0 );
value = (b(ebx, 22,31) +1 ) * (b(ebx,12,21)+1) * (b(ebx, 0,11)+1) * (b(ecx,0,31)+1);
printf("L1 Instruction Cahce Size: %ld\n\n", value);


// TLB Information
cpuid(0x02,0,0,0);
printf("TLB Information bytes: %4x\t", b(eax,8,15));
printf( "%04x\t", b(eax,16,23));
printf("%04x\n", b(eax,24,31));
printf("Look at the Intel Guide Page 780 to find what the the hex mean...\n\n");

// Memory Hierarchy information
//l1 cache size, l1 cahse Information
printf("Memory Hierarchy:\n");
//l1
cpuid(0x80000006, 0, 0, 0);
printf("L1 cache Line Info Size: %ld (in bytes)\n", b(ecx, 0,7));
//l2 Cache
cpuid(0x80000006, 0 , 0,0);
printf("L2 cache size line Info: %ld\n\n", b(ecx, 0,7));


// Physical Address Width
cpuid(0x80000008, 0,0,0);
printf("Physical Address Size: %ld\n\n", b(eax,0,7));

// Logical Address Width
printf("Linear/Logical Addres Size: %ld\n\n", b(eax,8,15));


// Number of logical CPU's
cpuid(0x0b,0,0,0);
printf("Number of Logical CPU's: %ld\n\n", b(eax,0,15));


// CPU Family
 cpuid(0x01, 0 , 0 , 0);
 value = b(eax,8,11);
 printf("Family ID: %ld\n\n", value);

// CPU Model
cpuid(0x01, 0 , 0 , 0);
value = b(eax,4,7);
printf("Model: %ld\t", value);
//value = (b(eax,16,19)) + Value;
printf("Extend Model ID: %ld\n", value);

printf("\tFinal Model ID: %ld\n\n", ((b(eax,16,19)<<4)+ b(eax,4,7)));

//CPU Frequency
cpuid(16,0,0,0);
printf("CPU Processor Frequency:\n - Base Frequency:\t %ld\n - Max Frequency: \t%ld\n - Bus Frequency:\t%ld\n\n", b(eax,0,15), b(ebx,0,15), b(ecx,0,15));

// CPU Features Available
printf("CPU Features Availabe:\n -- 1 = availabe\n");
cpuid(0x80000001,0,0,0);
printf("- LAHF/SAHF: %ld\n", b(ecx,0,0));
printf("- LZCNT: %ld\n",b(ecx,5,5));
printf("- PREFETCHW: %ld\n", b(ecx,8,8));
printf("- SYCALL/SYRET availabe in 64 bit mode: %ld\n", b(edx,11,11));
printf("- 1-GYBTE: %ld\n", b(edx, 26,26));
printf("- RDTSCP and IA_#@_TSC_AUX: %ld\n", b(edx,27,27));
printf("- INTEL 64 Architecture: %ld\n\n", b(edx,29,29));




	return 0;
}

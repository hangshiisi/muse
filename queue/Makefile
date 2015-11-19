all: CFLAGS := -O2 $(CFLAGS)
all: queue_example ex2

debug: CFLAGS := -g -O0 $(CFLAGS)
debug: queue_example ex2 

clean:
	rm queue_example ex2 

queue_example: queue_example.c  
	cc $? $(CFLAGS) -lpcap -lnfnetlink -lnetfilter_queue -lz -o $@



ex2: ex2.c  
	cc $? $(CFLAGS) -lpcap -lnfnetlink -lnetfilter_queue -lz -o $@

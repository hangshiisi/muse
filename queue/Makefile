all: CFLAGS := -O2 $(CFLAGS)
all: queue_example

debug: CFLAGS := -g -O0 $(CFLAGS)
debug: queue_example

clean:
	rm queue_example

queue_example: queue_example.c  
	cc $? $(CFLAGS) -lpcap -lnfnetlink -lnetfilter_queue -lz -o $@

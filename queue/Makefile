#all: CFLAGS := -std=c99 -O2 $(CFLAGS)
all: CFLAGS := -O2 $(CFLAGS)
all: queue_example ex2 tc_server tc_client 

#debug: CFLAGS := -std=c99 -g -O0 $(CFLAGS)
debug: CFLAGS :=  -g -O0 $(CFLAGS)
debug: queue_example ex2 tc_server tc_client 

clean:
	rm queue_example ex2 tc_server tc_client 

queue_example: queue_example.c  
	gcc $? $(CFLAGS) -lpcap -lnfnetlink -lnetfilter_queue -lz -o $@

ex2: ex2.c tc_mem.c 
	gcc $? $(CFLAGS) -lpcap -lnfnetlink -lnetfilter_queue -lz -o $@

tc_server: ex2.c tc_mem.c 
	gcc $? $(CFLAGS) -lpcap -lnfnetlink -lnetfilter_queue -lz -o $@

tc_client: tc_client.c tc_mem.c 
	gcc $? $(CFLAGS) -lpcap -lnfnetlink -lnetfilter_queue -lz -o $@

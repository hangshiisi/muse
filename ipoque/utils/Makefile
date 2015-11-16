all: CFLAGS := -O2 $(CFLAGS)
all: pace2_integration_example pace2_integration_example_smp pace2_integration_example_cdc pace2_integration_example_du pace2_integration_example_ext_tracking pace2_create_pa_tagging pace2_integration_example_separate_s4 pace2_integration_example_s4_stream_interface pace2_integration_example_cdd

debug: CFLAGS := -g -O0 $(CFLAGS)
debug: pace2_integration_example pace2_integration_example_smp pace2_integration_example_cdc pace2_integration_example_du pace2_integration_example_ext_tracking pace2_create_pa_tagging pace2_integration_example_separate_s4 pace2_integration_example_s4_stream_interface pace2_integration_example_cdd

clean:
	rm pace2_integration_example pace2_integration_example_smp pace2_integration_example_cdc pace2_integration_example_du pace2_integration_example_ext_tracking pace2_create_pa_tagging pace2_integration_example_separate_s4 pace2_integration_example_s4_stream_interface pace2_integration_example_cdd

pace2_integration_example: pace2_integration_example.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lpcap -lz -I../include/ipoque -o $@

pace2_integration_example_ext_tracking: pace2_integration_example_ext_tracking.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lpcap -lz -I../include/ipoque -o $@

pace2_integration_example_s4_stream_interface: pace2_integration_example_s4_stream_interface.c basic_reassembly.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lpcap -lz -I../include/ipoque -o $@

pace2_integration_example_separate_s4: pace2_integration_example_separate_s4.c basic_reassembly.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lpcap -lz -I../include/ipoque -o $@

pace2_integration_example_smp: pace2_integration_example_smp.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lpcap -lpthread -lz -I../include/ipoque -o $@

pace2_integration_example_cdc: pace2_integration_example_cdc.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lpcap -lz -I../include/ipoque -o $@
	
pace2_integration_example_cdd: pace2_integration_example_cdd.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -D_GNU_SOURCE -rdynamic ../lib/libipoque_pace2_static.a -lpcap -lz -I../include/ipoque -o $@

pace2_integration_example_du: pace2_integration_example_du.c event_handler.c read_pcap.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lpcap -ldl -lz -I../include/ipoque -o $@
	
pace2_integration_example_napatech: pace2_integration_example_napatech.c	
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -L/opt/napatech3/lib/ -lntos -lntapi -lz -I../include/ipoque -I/opt/napatech3/include/ -o $@

pace2_create_pa_tagging: pace2_create_pa_tagging.c
	cc $? $(CFLAGS) -rdynamic ../lib/libipoque_pace2_static.a -lz -I../include/ipoque -o $@

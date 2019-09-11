// FT8 recorder (RX) and decoder

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define diff 3


int func()
{
	struct timespec t;
	uint32_t dialfreq = 14074000;
	pid_t pid;

	// Wait until the start of a FT8 cycle
	/* clock_gettime(CLOCK_REALTIME, &t);
	// t.tv_sec = 58 - t.tv_sec % 60;
	t.tv_sec = (60 - diff) - t.tv_sec % 60;
	t.tv_nsec = 999999999L - t.tv_nsec;
	nanosleep(&t, NULL); */

	time_t now;
	struct tm *tm;

	while (1) {
		now = time(0);
		if ((tm = localtime (&now)) == NULL) {
			printf ("Error extracting time stuff\n");
			return 1;
		}

		if (tm->tm_sec == 14 || tm->tm_sec == 29 || tm->tm_sec == 44 || tm->tm_sec == 59) {
			break;
		}

		usleep(1000);
	}
	usleep(300000); // 300 msec

	pid = fork();
	if(pid == 0) { // child process
		setpgid(getpid(), getpid());
		// system("~/librtlsdr/src/rtl_sdr -s 1000000 -f 14074000 -g 20 -O dm=4:dm=20E6 - | csdr convert_u8_f | csdr fir_decimate_cc 250 0.00166665 HAMMING > /tmp/ft8_14074000.c2"); // works!
		// system("airspyhf_rx -w -a 384000 -f 14.074000 -g on -m on"); // works fine in sdr# but is unsuitable for us
		// system("airspyhf_rx -z -r stdout -f 14.074 > /tmp/airspy_768000_ft8_14074000.iq; cat /tmp/airspy_768000_ft8_14074000.iq | csdr fir_decimate_cc 192 0.00166665 HAMMING | csdr bandpass_fir_fft_cc 0 0.8 0.5 > /tmp/airspy_ft8_14074000.c2; dd if=/dev/zero bs=100000 count=1 >> /tmp/airspy_ft8_14074000.c2; ft8d /tmp/airspy_ft8_14074000.c2"); // best so far!
		system("airspyhf_rx -a 384000 -z -r stdout -f 14.074 > /tmp/airspy_384000_ft8_14074000.iq; cat /tmp/airspy_384000_ft8_14074000.iq | csdr fir_decimate_cc 96 0.00166665 HAMMING | csdr bandpass_fir_fft_cc 0 0.8 0.5 > /tmp/airspy_ft8_14074000.c2; dd if=/dev/zero bs=100000 count=1 >> /tmp/airspy_ft8_14074000.c2; ft8d /tmp/airspy_ft8_14074000.c2"); // best so far!
		// system("~/repos/airspy-fmradion/build/airspy-fmradion -t airspyhf -c freq=14074000,srate=768000 -b 1.0 -W /tmp/new.wav -m usb; sox /tmp/new.wav -r 12000 /tmp/new_new.wav; dd if=/dev/zero bs=1440000 count=1 >> /tmp/new_new.wav;  jt9 -8 /tmp/new_new.wav"); // works great!
		// system("~/airspy-fmradion/build/airspy-fmradion -t airspyhf -c freq=14074000,srate=768000 -b 1.0 -W /tmp/new.wav -m usb; sox /tmp/new.wav -r 12000 /tmp/new_new.wav; dd if=/dev/zero bs=1440000 count=1 >> /tmp/new_new.wav;  jt9 -8 /tmp/new_new.wav"); // works great!
		// https://github.com/airspy/airspyhf/blob/master/tools/src/README
		// system("airspyhf_rx -r /dev/stdout -a 768000 -f 14.074000 -g on -m on - | csdr fir_decimate_cc 160 0.00166665 HAMMING > /tmp/ft8_14074000.c2");
		// system("rx_sdr -s 768000 -f 14074000 -F CF32 - | csdr fir_decimate_cc 160 0.00166665 HAMMING > /tmp/ft8_14074000.c2");
		// system("rx_sdr -s 384000 -f 14074000 -I CF32 -F CU8 - | csdr convert_u8_f | csdr fir_decimate_cc 80 0.00166665 HAMMING > /tmp/ft8_14074000.c2");
		// system("rx_sdr -s 384000 -f 14074000 -I CF32 -F CF32 - | csdr fir_decimate_cc 80 0.00166665 HAMMING > /tmp/ft8_14074000.c2");
		// system("rx_sdr -s 1000000 -f 14074000 -g 20 -D 2 - | csdr convert_u8_f | csdr fir_decimate_cc 250 0.00166665 HAMMING > /tmp/ft8_14074000.c2");
		// Note: rx_sdr has never ever worked - even with RTL-SDR - weird!
		exit(0);  // ;)
	} else { // parent process
		sleep(13);
		// kill(-pid, SIGKILL);
		// system("killall -SIGINT rtl_sdr");
		// system("killall -SIGINT airspy-fmradion");
		system("killall -SIGINT airspyhf_rx");
		// system("killall -SIGINT rx_sdr");
		// printf("killed process group %d\n", pid);
	}

	return EXIT_SUCCESS;
}

int main()
{
	system("killall airspyhf_rx");

	while (1) {
		func();
	}


	exit(0);

	return EXIT_SUCCESS;
}

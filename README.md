### FastFT8

Fast FT8 decoder - based on the work of WSJT-X authors, Red Pitaya authors,
Pavel Demin, András Retzler, and others.


#### Currently supported platforms

- RPi 3B+ or better

- x86 boxes

- Production Platform: Raspberry Pi Zero 2 W

- Final Production Platform: Android phones


#### Currently supported SDR devices

- Genuine RTL SDR V3 USB Dongle

- Airspy HF+ Discovery

- Add others?


#### Build Steps

```
sudo apt-get install build-essential cmake git \
  libusb-dev libusb-1.0-0-dev pkg-config \
  gfortran
```


#### Libraries Used

- https://github.com/librtlsdr/librtlsdr

- https://github.com/airspy/airspyhf

- https://github.com/ha7ilm/csdr

- https://github.com/pavel-demin/red-pitaya-notes

- https://github.com/pavel-demin/ft8d


#### Usage Steps

```
export dialfreq="14074000"

~/librtlsdr/src/rtl_sdr -s 1000000 -f $dialfreq -g 20 -O dm=4:dm=20E6 - | csdr convert_u8_f | csdr fir_decimate_cc 250 0.00166665 HAMMING > /tmp/ft8_${dialfreq}.c2

ft8d /tmp/ft8_${dialfreq}.c2
```

```
pacmd load-module module-null-sink sink_name=Virtual0
pacmd update-sink-proplist Virtual0 device.description=Virtual0
pacmd update-source-proplist Virtual0.monitor device.description=Virtual0
```


#### Tips

In Gqrx, in `Input controls` tab to tick the `No limits` box. How useful that
will be depends on lots of things: YMMV!

Use https://github.com/kholia/Easy-Digital-Beacons-v1 to get sure shot FT8
traffic. Run beacon without PA ;)


#### References

- https://github.com/pavel-demin/red-pitaya-notes/issues/689

- http://sv3exp.blogspot.com/2019/09/decoding-ft8-in-with-any-sdr-like-usrp.html

- https://github.com/martinmarinov/rtl_tcp_andro-

- https://github.com/rxseger/rx_tools (not used yet)

- https://github.com/ha7ilm/openwebrx/blob/master/config_webrx.py

- https://github.com/simonyiszk/openwebrx/wiki/Using-rx_tools-with-OpenWebRX/

- https://0xfeed.tech/2017/04/remote-access-tools-for-sdr-receivers/

- https://github.com/pothosware/SoapyAirspyHF

- https://www.rtl-sdr.com/tutorial-setting-up-a-low-cost-qrp-ft8-jt9-wspr-etc-monitoring-station-with-an-rtl-sdr-v3-and-raspberry-pi-3/

- https://github.com/miek/inspectrum (super awesome for debugging work)

- https://www.pe0sat.vgnet.nl/sdr/iq-data-explained/

# Garcon
Garcon is a lightweight web-server that was developed as a coursework
for Newtwork Applications course as a demonstration of RFC-2616 implementation.

## Functions
* Serve keep-alive connections
* Accepting Range for continious downloadings
* Using multi-threading computions

Served 10K rps on text files transfer.
Supports multi-threading file transmission, 12Gbit/s metered.

## Auxilary
### Compile and assembly
It depends on:
* LibBoost 1.74
* Cmake 3.14+

### Assembling and run
```
cmake .
make && ./http_server
```

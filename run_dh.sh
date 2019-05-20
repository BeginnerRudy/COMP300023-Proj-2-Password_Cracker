#This is the bash file for running dh.c
gcc -Wall -o dh dh.c
scp -i /home/rudy/Downloads/openssh dh.c renjiem@172.26.37.44:dh.c
openssl sha256 dh.c
